
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/*--------------------------------------------------------------------------*/
/* OSEK declarations                                                        */
/*--------------------------------------------------------------------------*/
DeclareTask(Principal);
DeclareTask(Avance);
DeclareTask(Final);
DeclareTask(Calibrar);

/*--------------------------------------------------------------------------*/
/* Definitions                                                              */
/*--------------------------------------------------------------------------*/
int porcentajeB = 80;
int porcentajeC = 80;
/*--------------------------------------------------------------------------*/
/* Function to be invoked from a category 2 interrupt                       */
/*--------------------------------------------------------------------------*/
void user_1ms_isr_type2()
{}

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
    int time_out = systick_get_ms() + 10000 ; //Calculamos ?? segundos
    int time_out_calibrate = systick_get_ms() + 1;

    while(systick_get_ms() < time_out)
    {
        ActivateTask(Avance);
        while(systick_get_ms() < time_out_calibrate);
        time_out_calibrate += 1;
        ActivateTask(Calibrar);
    }
    ActivateTask(Final);
    TerminateTask();
}


TASK(Avance)
{
    nxt_motor_set_speed(NXT_PORT_B, porcentajeB, 0);    
    nxt_motor_set_speed(NXT_PORT_C, porcentajeC, 0);
    
    
    // Despierta la tarea de parada de motores
    //ChainTask(Principal);
    //ActivateTask(Final);

    // Termina la tarea actual
    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : Avance                                                         */
/* Priority: 02                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Calibrate servomotors function                                */
/*--------------------------------------------------------------------------*/
TASK(Calibrar)
{
    int revB = nxt_motor_get_count(NXT_PORT_B);
    int revC = nxt_motor_get_count(NXT_PORT_C);
    
    if(revB < revC)
    {
        if(porcentajeC < 100)
            porcentajeB++;
        else
            porcentajeC--;
        //nxt_motor_set_speed(NXT_PORT_C, porcentajeC, 1);
    }
    else if(revC < revB)
    {
        if(porcentajeB < 100)
            porcentajeC++;
        else
            porcentajeB--;
        //nxt_motor_set_speed(NXT_PORT_B, porcentajeB, 1);
    }
    
    nxt_motor_set_count(NXT_PORT_B, 0);
    nxt_motor_set_count(NXT_PORT_C, 0);

    TerminateTask();
}
/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : Final                                                          */
/* Priority: 04                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL 	                                                        */
/* Objective: Stop servomotors                                              */
/*--------------------------------------------------------------------------*/
TASK(Final)
{
    // Para los motores
    nxt_motor_set_speed(NXT_PORT_B, 0, 1);
    nxt_motor_set_speed(NXT_PORT_C, 0, 1);

    // Termina la tarea actual
    TerminateTask();
}
