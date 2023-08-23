#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#define MICROFONO_PORT NXT_PORT_S4
#define PULSADOR_PORT NXT_PORT_S2
#define N 8;

/*--------------------------------------------------------------------------*/
/* OSEK declarations                                                        */
/*--------------------------------------------------------------------------*/
DeclareCounter(Contador);
DeclareTask(Avance);
DeclareTask(Calibrar);
DeclareTask(Busqueda);
DeclareTask(Posicionamiento);
DeclareTask(Pulsador);
DeclareTask(Giro45gradosDerecha);
DeclareTask(Reseteo);
DeclareTask(Final);
DeclareTask(Principal);

//Alarmas
DeclareAlarm(AlarmaCalibrar);
DeclareAlarm(AlarmaPulsador);
DeclareAlarm(AlarmaReseteo);

//EVENTOS
DeclareEvent(evento);


/*--------------------------------------------------------------------------*/
/* Definitions                                                              */
/*--------------------------------------------------------------------------*/

int porcentajeB = 100;
int porcentajeC = 100;

int potencias[N];

int direccionMayor = 0;
int potenciaMayor = 0;


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
/* Name    : Avance                                                         */
/* Priority: ??                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: ??		                                                    */
/* Objective: Move forward.						    */
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
        
        //nxt_motor_set_speed(NXT_PORT_B, porcentajeB, 1);
        //nxt_motor_set_speed(NXT_PORT_C, porcentajeC, 1);
    }
    else if(revC < revB)
    {
        if(porcentajeC < 100)
            porcentajeC++;
        else
            porcentajeB--;
        
        //nxt_motor_set_speed(NXT_PORT_B, porcentajeB, 1);
        //nxt_motor_set_speed(NXT_PORT_C, porcentajeC, 1);
    }
    
    nxt_motor_set_count(NXT_PORT_B, 0);
    nxt_motor_set_count(NXT_PORT_C, 0);

    ActivateTask(Avance);
    TerminateTask();
}


TASK(Avance)
{
    nxt_motor_set_speed(NXT_PORT_B, porcentajeB, 1);
  	nxt_motor_set_speed(NXT_PORT_C, porcentajeC, 1);

    //Termina la tarea actual
    TerminateTask();
}

TASK(Busqueda)
{
    direccionMayor = 0;
    potenciaMayor = 0;
    for (int i = 0; i < N; i++)
    {
        potencias[i] = ecrobot_get_sound_sensor(MICROFONO_PORT);
        if (potencias[i] > potenciaMayor)
        {
            direccionMayor = i;
            potenciaMayor = potencias[i];
        }
        ActivateTask(Giro45gradosDerecha);
    }

    TerminateTask();
}

TASK(Posicionamiento)
{
    for (int i = 0; i < direccionMayor; i++)
    {
        ActivateTask(Giro45gradosDerecha);
    }
    //Termina la tarea actual
    TerminateTask();
}

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
/* Name    : CambioDir		                                            */
/* Priority: ??                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: ??		                                                    */
/* Objective: Change direction of the robot.				    */
/*--------------------------------------------------------------------------*/
TASK(Giro45gradosDerecha)
{
    //Giramos
    //nxt_motor_set_speed(NXT_PORT_B, -65, 1);
    //nxt_motor_set_speed(NXT_PORT_C, 65, 1);//si no funciona mirar con porcentajes

    porcentajeB = -65;
    porcentajeC = 65;

    ActivateTask(Avance);

    nxt_motor_set_count(NXT_PORT_B, 0);

    while(nxt_motor_get_count(NXT_PORT_B)<100);//modificarlo allí

    porcentajeB = 0;
    porcentajeC = 0;

    ActivateTask(Avance);
    //Termina la tarea actual
    TerminateTask();
}

TASK(Final)
{
    CancelAlarm(AlarmaCalibrar);
    CancelAlarm(AlarmaPulsador);
    CancelAlarm(AlarmaReseteo);

    nxt_motor_set_speed(NXT_PORT_B, 0, 1);
    nxt_motor_set_speed(NXT_PORT_C, 0, 1);
    porcentajeB = 0;
    porcentajeC = 0;

    ActivateTask(Avance);

    TerminateTask();
}

TASK(Reseteo)
{
    porcentajeB = 0;
    porcentajeC = 0;
    ActivateTask(Avance);
    nxt_motor_set_count(NXT_PORT_B, 0);
    nxt_motor_set_count(NXT_PORT_C, 0);

    SetEvent(Principal, evento);

    TerminateTask();
}

TASK(Principal)
{
    while(1)
    {
        CancelAlarm(AlarmaCalibrar);
        CancelAlarm(AlarmaReseteo);
        ActivateTask(Busqueda);
        ActivateTask(Posicionamiento);
        nxt_motor_set_count(NXT_PORT_B, 0);
        nxt_motor_set_count(NXT_PORT_C, 0);
        SetRelAlarm(AlarmaCalibrar,10,10);
        ClearEvent(evento);
        SetRelAlarm(AlarmaReseteo, 1000, 0); //Tiempo Avanzando
        porcentajeB = 100;
        porcentajeC = 100;
        ActivateTask(Avance);
        WaitEvent(evento);
    }

    TerminateTask();
}