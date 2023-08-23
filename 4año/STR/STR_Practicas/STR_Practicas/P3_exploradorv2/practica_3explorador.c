#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#define MICROFONO_PORT NXT_PORT_S4
#define PULSADOR_PORT NXT_PORT_S2
#define N 8

/*--------------------------------------------------------------------------*/
/* OSEK declarations                                                        */
/*--------------------------------------------------------------------------*/
DeclareCounter(Contador);
DeclareTask(Busqueda);
DeclareTask(Pulsador);
DeclareTask(Avance);
DeclareTask(UsarSonar);
DeclareTask(PararRobot);
DeclareTask(Giro45gradosDerecha);
DeclareTask(Posicionamiento);


//Alarmas
DeclareAlarm(AlarmaCalibrar);
DeclareAlarm(AlarmaPulsador);
DeclareAlarm(AlarmaSonar);
DeclareAlarm(AlarmaBusqueda);
DeclareAlarm(AlarmaPosicionamiento);
DeclareAlarm(AlarmaAvance);
DeclareAlarm(AlarmaGiro45gradosDerecha);

//EVENTOS
DeclareEvent(evento);


/*--------------------------------------------------------------------------*/
/* Definitions                                                              */
/*--------------------------------------------------------------------------*/

int porcentajeB = 100;
int porcentajeC = 100;

int potencias[N];
int I;
int direccionMayor;
int potenciaMayor;

int posFlag = 0;


/*--------------------------------------------------------------------------*/
/* Function to be invoked from a category 2 interrupt                       */
/*--------------------------------------------------------------------------*/
void user_1ms_isr_type2()
{
    SignalCounter(Contador);
}


/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : Calibrar                                                       */
/* Priority: 2                                                              */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: calibrar el movimiento en línea recta.                        */
/*--------------------------------------------------------------------------*/

TASK(Calibrar)
{
    int revB = nxt_motor_get_count(NXT_PORT_B);
    int revC = nxt_motor_get_count(NXT_PORT_C);
    
    if(revB < revC)
    {
        if(porcentajeB < 100)
            porcentajeB++;
        else
            porcentajeC--;
    }
    else if(revC < revB)
    {
        if(porcentajeC < 100)
            porcentajeC++;
        else
            porcentajeB--;
    }
    
    nxt_motor_set_count(NXT_PORT_B, 0);
    nxt_motor_set_count(NXT_PORT_C, 0);

    ActivateTask(Avance);
    TerminateTask();
}


/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : PararRobot                                                     */
/* Priority: 5                                                              */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: parar el robot.                                               */
/*--------------------------------------------------------------------------*/
TASK(PararRobot)
{
    //ponemos los motores a 0 potencia
    porcentajeB = 0;
    porcentajeC = 0;
    nxt_motor_set_speed(NXT_PORT_B, porcentajeB, 1);
  	nxt_motor_set_speed(NXT_PORT_C, porcentajeC, 1);

    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : Busqueda                                                       */
/* Priority: 6                                                              */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Buscar el origen del sonido.                                  */
/*--------------------------------------------------------------------------*/
TASK(Busqueda)
{
    //llamo evento para finalizar el avance
    SetEvent(Avance, evento);

    //apagamos y encendemos alarmas
    CancelAlarm(AlarmaCalibrar);
    CancelAlarm(AlarmaBusqueda);
    SetRelAlarm(AlarmaSonar, 100, 100);

    //reseteamos el vector de valores
    for(I = 0; I < N; I++){
        potencias[I] = 1024;
    }

    for(I = 0; I < N; I++){
        ActivateTask(PararRobot);
        SetRelAlarm(AlarmaGiro45gradosDerecha, 3000, 9999);
        WaitEvent(evento);
        ClearEvent(evento);
        CancelAlarm(AlarmaGiro45gradosDerecha);
    }
    ActivateTask(PararRobot);

    //apagamos y encendemos alarmas
    CancelAlarm(AlarmaSonar);
    SetRelAlarm(AlarmaPosicionamiento, 20, 9999);
    
    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : Posicionamiento                                                */
/* Priority: 7                                                              */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Posicionarse de acuerdo al origen del sonido.                 */
/*--------------------------------------------------------------------------*/
TASK(Posicionamiento)
{
    posFlag = 1;
    //apagamos y encendemos alarmas
    CancelAlarm(AlarmaPosicionamiento);

    //vemos que direccion ha encontrado el ruido mas fuerte
    direccionMayor = 0;
    potenciaMayor = 1024;
    for (I = 0; I < N; I++)
    {
        if(potenciaMayor > potencias[I]){
            direccionMayor = I;
            potenciaMayor = potencias[I];
        }
    }

    //giramos el robot a la posicion optima
    for(int w = 0; w < direccionMayor; w++){
        //mostramos por pantalla la direccion mayor para ver su funcionamiento
        display_clear(0);
        display_goto_xy(0,5);
        display_unsigned(w, 5);
        display_goto_xy(10,5);
        display_unsigned(direccionMayor, 5);
        display_update();
        //paramos robot y giramos
        ActivateTask(PararRobot);
        SetRelAlarm(AlarmaGiro45gradosDerecha, 300, 9999);
        WaitEvent(evento);
        ClearEvent(evento);
        //cancelamos alarma
        CancelAlarm(AlarmaGiro45gradosDerecha);
    }
    ActivateTask(PararRobot);

    //ahora como va a avanzar limpiamos revoluciones para que funcione calibrar
    nxt_motor_set_count(NXT_PORT_B, 0);
    nxt_motor_set_count(NXT_PORT_C, 0);

    //apagamos y encendemos alarmas
    SetRelAlarm(AlarmaAvance, 300, 9999);

    posFlag = 0;
    //Termina la tarea actual
    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : UsarSonar                                                      */
/* Priority: 7                                                              */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Utilizar el sonar para medir la potencia del sonido ambiente. */
/*--------------------------------------------------------------------------*/
TASK(UsarSonar)
{
    //comprueba si el valor por el sonar es menor y en el caso de que si se cambia
    if(potencias[I] > ecrobot_get_sound_sensor(MICROFONO_PORT)){
        potencias[I] = ecrobot_get_sound_sensor(MICROFONO_PORT);
    } 
        //mostramos por pantalla el valor obtenido por el sonar
        display_clear(0);
        display_goto_xy(0,5);
        display_unsigned(ecrobot_get_sound_sensor(MICROFONO_PORT), 5);
        display_goto_xy(10,5);
        display_unsigned(potencias[I], 5);
        display_update();

    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : Avance                                                         */
/* Priority: 1                                                              */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: El robot avanza hacia adelante.                               */
/*--------------------------------------------------------------------------*/
TASK(Avance)
{
    //apagamos y encendemos alarmas
    CancelAlarm(AlarmaAvance);
    SetRelAlarm(AlarmaCalibrar, 15, 15);

    //ponemos los motores a FULL potencia
    porcentajeB = 100;
    porcentajeC = 100;

    nxt_motor_set_speed(NXT_PORT_B, porcentajeB, 1);
  	nxt_motor_set_speed(NXT_PORT_C, porcentajeC, 1);

    //apagamos y encendemos alarmas
    SetRelAlarm(AlarmaBusqueda, 2000, 9999);
    WaitEvent(evento);
    ClearEvent(evento);

    //Termina la tarea actual
    TerminateTask();
}

/*------------------------------------------------------------------------------------*/
/* Task information:                                                                  */
/* -----------------                                                                  */
/* Name    : Pulsador                                                                 */
/* Priority: 8                                                                        */
/* Typ     : EXTENDED TASK                                                            */
/* Schedule: FULL		                                                              */
/* Objective: Detectar la pulsación de un botón y terminar la ejecución del sistema.  */
/*------------------------------------------------------------------------------------*/
TASK(Pulsador)
{
	if(ecrobot_get_touch_sensor(PULSADOR_PORT)==1)
    {
		//Finaliza el programa
        CancelAlarm(AlarmaCalibrar);
        CancelAlarm(AlarmaPulsador);
        CancelAlarm(AlarmaSonar);
        CancelAlarm(AlarmaBusqueda);
        CancelAlarm(AlarmaPosicionamiento);
        CancelAlarm(AlarmaAvance);
        CancelAlarm(AlarmaGiro45gradosDerecha);

        ActivateTask(PararRobot);//paramos el robot	
	}

	TerminateTask();
}


/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : Giro45gradosDerecha                                            */
/* Priority: 4                                                              */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: girar 45 grados hacia la derecha.                             */
/*--------------------------------------------------------------------------*/
TASK(Giro45gradosDerecha)
{
    //cancelamos alarmas
    CancelAlarm(AlarmaSonar);

    porcentajeB = -65;
    porcentajeC = 65;

    nxt_motor_set_speed(NXT_PORT_B, porcentajeB, 1);
  	nxt_motor_set_speed(NXT_PORT_C, porcentajeC, 1);

    nxt_motor_set_count(NXT_PORT_C, 0);

    //realizamos el giro dependiendo de las revoluciones
    while(nxt_motor_get_count(NXT_PORT_C)<75);

    //lanzamos eventos y activamos alarmas
    if(posFlag == 1){
        SetEvent(Posicionamiento, evento);
    }else{
        SetRelAlarm(AlarmaSonar, 100, 100);
        SetEvent(Busqueda, evento);
    }

    //Termina la tarea actual
    TerminateTask();
}
