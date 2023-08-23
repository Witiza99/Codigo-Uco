#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#define SONAR_PORT NXT_PORT_S4
#define PULSADOR_PORT NXT_PORT_S2

/*--------------------------------------------------------------------------*/
/* OSEK declarations                                                        */
/*--------------------------------------------------------------------------*/
DeclareCounter(Contador);
DeclareTask(Avance);
DeclareTask(Retroceso);
DeclareTask(Calibrar);
DeclareTask(SensorUltraSonidos);
DeclareTask(TomaDecision);
DeclareTask(Busqueda);
DeclareTask(GiroIzq);
DeclareTask(GiroDer);
DeclareTask(Pulsador);
DeclareTask(Final);

//Alarmas
DeclareAlarm(AlarmaCalibrar);
DeclareAlarm(AlarmaPulsador);
DeclareAlarm(AlarmaUltraSonidos);

void ecrobot_device_initialize()
{
	ecrobot_init_sonar_sensor(SONAR_PORT); // Inicializar los sensores activos
}
void ecrobot_device_terminate()
{
	ecrobot_term_sonar_sensor(SONAR_PORT); // Finalizar los sensores activos
}

/*--------------------------------------------------------------------------*/
/* Definitions                                                              */
/*--------------------------------------------------------------------------*/

int porcentajeB = 100;
int porcentajeC = 100;

int distancia = 1000;

int distanciaIzq = 0;
int distanciaDer = 0;

int N = 1;

int Tiempo_T1 = 0;
int Tiempo_T2 = 0;
int Tiempo_T3 = 0;

/*--------------------------------------------------------------------------*/
/* Function to be invoked from a category 2 interrupt                       */
/*--------------------------------------------------------------------------*/
void user_1ms_isr_type2()
{
    SignalCounter(Contador);
}

/*--------------------------------------------------------------------------*/
/*  Calcula el Modo, el tipo de avance que va a                             */
/*  realizar dependiendo de la distancia                                    */                         
/*--------------------------------------------------------------------------*/
int CalcularModo(int valor)
{
    if(valor > 100)
    {
        return 1;
    }
    else if(valor > 20)
    {
        return 2;
    }
    else
    {
        return 3;
    }
    
    return 0;
}

/*--------------------------------------------------------------------------*/
/*  Se aplica cada modo de funcionamiento                                   */                      
/*--------------------------------------------------------------------------*/
void AplicarModo(int valor)
{
    if(valor == 1)
    {
        N = 1;
    }
    else if(valor == 2)
    {
        N = 2;
    }
    else
    {   
        //cancelamos alarmas que no vamos a utilizar
        CancelAlarm(AlarmaCalibrar);
        CancelAlarm(AlarmaUltraSonidos);

        ActivateTask(Busqueda);

        //reactivamos las alarmas tras realizar la busqueda
        SetRelAlarm(AlarmaCalibrar,10,10);
        SetRelAlarm(AlarmaUltraSonidos,30,30);
    }
}

//Rotamos los tiempos, el tiempo más antiguo se pierde
void Rotacion()
{
    Tiempo_T2 = Tiempo_T1;
    Tiempo_T3 = Tiempo_T2;
}


//funcion para mostrar por pantalla el dato enviado
void MostrarPorPantalla(int distancia)
{
    display_clear(0);
    display_goto_xy(0,5);
	display_unsigned(distancia, 5);
	display_update();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : Calibrar                                                       */
/* Priority: 04                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Calibrate the servomotors.                                    */
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
/* Name    : Avance                                                         */
/* Priority: 01                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Move forward.                     						    */
/*--------------------------------------------------------------------------*/
TASK(Avance)
{
    nxt_motor_set_speed(NXT_PORT_B, porcentajeB/N, 1);
  	nxt_motor_set_speed(NXT_PORT_C, porcentajeC/N, 1);

    //Termina la tarea actual
    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : Busqueda                                                       */
/* Priority: 02                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Search for the farthest wall.						            */
/*--------------------------------------------------------------------------*/
TASK(Busqueda)
{
    systick_wait_ms(200); 
    //giramos a la derecha
    ActivateTask(GiroDer);
    systick_wait_ms(360);

    //paramos y calculamos la distancia por la derecha
    nxt_motor_set_speed(NXT_PORT_B, 0, 1);
    nxt_motor_set_speed(NXT_PORT_C, 0, 1);
    distanciaDer = ecrobot_get_sonar_sensor(SONAR_PORT);
    systick_wait_ms(1000);

    //giramos a la izquierda
    ActivateTask(GiroIzq);
    systick_wait_ms(730);

    //paramos y calculamos la distancia por la izquierda
    nxt_motor_set_speed(NXT_PORT_B, 0, 1);
    nxt_motor_set_speed(NXT_PORT_C, 0, 1);
    distanciaIzq = ecrobot_get_sonar_sensor(SONAR_PORT);
    systick_wait_ms(1000);

    //comprobamos que distancia es la mayor
    if(distanciaDer > distanciaIzq)
    {
        //en el caso de ser la derecha ajustamos el robot hacia la derecha
        ActivateTask(GiroDer);
        systick_wait_ms(750);
    }

    //paramos el robot
    nxt_motor_set_speed(NXT_PORT_B, 0, 1);
    nxt_motor_set_speed(NXT_PORT_C, 0, 1);
    systick_wait_ms(600);

    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : SensorUltraSonidos                                             */
/* Priority: 03                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Obtain the distance given by the ultra-sound sensor.          */
/*--------------------------------------------------------------------------*/
TASK(SensorUltraSonidos)
{
	distancia = ecrobot_get_sonar_sensor(SONAR_PORT);
    MostrarPorPantalla(distancia);

    //llamamos a TomaDecision para ver dentro de la logica en que modo estamos
	ActivateTask(TomaDecision);

    //Termina la tarea actual
	TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : TomaDecision                                                   */
/* Priority: 02                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Decision-making.						                        */
/*--------------------------------------------------------------------------*/
TASK(TomaDecision)
{
    //si es la primera vez que se obtiene T1 aplicamos el modo
    if(Tiempo_T1 == 0 && distancia > 0)
    {
        Tiempo_T1 = CalcularModo(distancia);
        AplicarModo(Tiempo_T1);
        ActivateTask(Avance);
    }
    //si no lo es se aplica rotacion y se comprueba que los últimos 3 valores sean iguales
    else
    {
        Rotacion();
        Tiempo_T1 = CalcularModo(distancia);

        //Para evitar tirones
        if((Tiempo_T1 == Tiempo_T2) && (Tiempo_T1 == Tiempo_T3) && (Tiempo_T2 == Tiempo_T3))
        {
            AplicarModo(Tiempo_T1);
            ActivateTask(Avance);
            Tiempo_T1 = 0;
            Tiempo_T2 = 0;
            Tiempo_T3 = 0;
        }
    }

    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : GiroIzq                                                        */
/* Priority: 05                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Make a left turn.                                             */
/*--------------------------------------------------------------------------*/
TASK(GiroIzq)
{
    //Giramos
    nxt_motor_set_speed(NXT_PORT_B, 65, 1);
    nxt_motor_set_speed(NXT_PORT_C, -65, 1);
    //Termina la tarea actual
    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : GiroDer                                                        */
/* Priority: 05                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Make a right turn.                                            */
/*--------------------------------------------------------------------------*/
TASK(GiroDer)
{
    //Giramos
    nxt_motor_set_speed(NXT_PORT_B, -65, 1);
    nxt_motor_set_speed(NXT_PORT_C, 65, 1);
    //Termina la tarea actual
    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : Pulsador                                                       */
/* Priority: 08                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Activate the final task if the pushbutton is activated.       */
/*--------------------------------------------------------------------------*/
TASK(Pulsador)
{
	if(ecrobot_get_touch_sensor(PULSADOR_PORT)==1)
    {
		//Finaliza el programa
		ActivateTask(Final);
	}

	TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : Final                                                          */
/* Priority: 07                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Terminate program execution.                                  */
/*--------------------------------------------------------------------------*/
TASK(Final)
{
    //cancelamos alarmas
    CancelAlarm(AlarmaCalibrar);
    CancelAlarm(AlarmaPulsador);
    CancelAlarm(AlarmaUltraSonidos);

    //paramos motores
    nxt_motor_set_speed(NXT_PORT_B, 0, 1);
    nxt_motor_set_speed(NXT_PORT_C, 0, 1);
    porcentajeB = 0;
    porcentajeC = 0;

    ActivateTask(Avance);

    TerminateTask();
}