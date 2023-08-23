
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/*--------------------------------------------------------------------------*/
/* OSEK declarations                                                        */
/*--------------------------------------------------------------------------*/
//CONTADORES
DeclareCounter(Contador);
//TAREAS
//DeclareTask(Retroceso);
DeclareTask(Avance);
DeclareTask(GiroIzq);
DeclareTask(GiroDer);
DeclareTask(Final);
DeclareTask(Principal);
DeclareTask(Calibrar);
//ALARMAS
DeclareAlarm(GiroIzqAlarma);
DeclareAlarm(GiroDerAlarma);
DeclareAlarm(AvanceAlarma);
DeclareAlarm(CalibrarAlarma);
//EVENTOS
DeclareEvent(evento);

/*--------------------------------------------------------------------------*/
/* Definitions                                                              */
/*--------------------------------------------------------------------------*/
int porcentajeB = 100;
int porcentajeC = 100;

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
/* Priority: 02                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Move forward                      						    */
/*--------------------------------------------------------------------------*/
TASK(Avance)
{
    nxt_motor_set_count(NXT_PORT_B, 0);
    nxt_motor_set_count(NXT_PORT_C, 0);

    //Activa servomotores para avanzar en linea recta
    nxt_motor_set_speed(NXT_PORT_B, porcentajeB, 1);
    nxt_motor_set_speed(NXT_PORT_C, porcentajeC, 1);

    CancelAlarm(AvanceAlarma);
    SetEvent(Principal, evento);

    //Termina la tarea actual
    TerminateTask();
}

/*TASK(Retroceso)
{
   // Activar servomotores para avanzar en linea recta
    nxt_motor_set_speed(NXT_PORT_B, -porcentajeB, 1);
    nxt_motor_set_speed(NXT_PORT_C, -porcentajeC, 1);

    // Termina la tarea actual
    TerminateTask();

}*/

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : Calibrar                                                       */
/* Priority: 03                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Calibrate servomotors.                                        */
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
        
        nxt_motor_set_speed(NXT_PORT_B, porcentajeB, 1);
        nxt_motor_set_speed(NXT_PORT_C, porcentajeC, 1);
    }
    else if(revC < revB)
    {
        if(porcentajeC < 100)
            porcentajeC++;
        else
            porcentajeB--;
        
        nxt_motor_set_speed(NXT_PORT_B, porcentajeB, 1);
        nxt_motor_set_speed(NXT_PORT_C, porcentajeC, 1);
    }
    
    nxt_motor_set_count(NXT_PORT_B, 0);
    nxt_motor_set_count(NXT_PORT_C, 0);

    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : GiroIzq                                                        */
/* Priority: 03                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Activate servomotors to make a left corner, taking into       */ 
/*            acount calibration.	    				                    */
/*--------------------------------------------------------------------------*/
TASK(GiroIzq)
{
    CancelAlarm(CalibrarAlarma);

    //Activa servomotores para realizar un giro a la izquierda
    nxt_motor_set_speed(NXT_PORT_B, porcentajeB/2, 1);
    nxt_motor_set_speed(NXT_PORT_C, -porcentajeC/2, 1);

    CancelAlarm(GiroIzqAlarma);
    SetEvent(Principal, evento);

    //Termina la tarea actual
    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : GiroDer                                                        */
/* Priority: 03                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Activate servomotors to make a right corner, taking into      */ 
/*            acount calibration.	    				                    */
/*--------------------------------------------------------------------------*/
TASK(GiroDer)
{
    CancelAlarm(CalibrarAlarma);
    
	//Activa servomotores para realizar un giro a la derecha
    nxt_motor_set_speed(NXT_PORT_B, -porcentajeB/2, 1);
    nxt_motor_set_speed(NXT_PORT_C, porcentajeC/2, 1);

    CancelAlarm(GiroDerAlarma);
    SetEvent(Principal, evento);

	//Termina la tarea actual
    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : Final                                                          */
/* Priority: 05                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Stop servomotors.                                             */
/*--------------------------------------------------------------------------*/
TASK(Final)
{
    nxt_motor_set_speed(NXT_PORT_B, 0, 1);
    nxt_motor_set_speed(NXT_PORT_C, 0, 1);

    //ShutdownOS(0);

    //Termina la tarea actual
    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : Principal                                                      */
/* Priority: 01                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL                                                           */
/* Objective: Initialize variables and organize tasks.                      */
/*--------------------------------------------------------------------------*/
TASK(Principal)
{
    // Inicializar variables


    // Organizar las tareas

    //Avanza
    ActivateTask(Avance);
    SetRelAlarm(GiroIzqAlarma, 950, 9999);//tiempo hasta que gire a la izquierda(Avanzando)
    WaitEvent(evento);
    ClearEvent(evento);
    WaitEvent(evento);
    ClearEvent(evento);//ha entrado a la izquierda
    //Giro izquierda
    SetRelAlarm(AvanceAlarma, 250, 9999);//tiempo hasta que avance(Girando a la izquierda)
    WaitEvent(evento);
    ClearEvent(evento);
    //Avanza
    SetRelAlarm(GiroDerAlarma, 500, 9999);//tiempo hasta que gira a la derecha(Avanzando)
    SetRelAlarm(CalibrarAlarma,10,10);
    WaitEvent(evento);
    ClearEvent(evento);
    //Gira derecha
    SetRelAlarm(AvanceAlarma, 410, 9999);//tiempo hasta finalizar(girando derecha)
    WaitEvent(evento);
    ClearEvent(evento);
    SetRelAlarm(CalibrarAlarma,10,10);
    //Final
    ActivateTask(Final);

    //Terminar la tarea actual
    TerminateTask();
}