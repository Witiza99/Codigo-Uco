#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/*--------------------------------------------------------------------------*/
/* OSEK declarations                                                        */
/*--------------------------------------------------------------------------*/
//CONTADORES
DeclareCounter(Contador);
//TAREAS
DeclareTask(Avance);
DeclareTask(Calibrar);
DeclareTask(Final);

/*--------------------------------------------------------------------------*/
/* Definitions                                                              */
/*--------------------------------------------------------------------------*/
int porcentajeB = 100;
int porcentajeC = 95;

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
/* Priority: 01                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Move forward.                                                 */
/*--------------------------------------------------------------------------*/
TASK(Avance)
{
    //Activa motores para comprobar si existe desvio en la navegacion
    nxt_motor_set_speed(NXT_PORT_B, porcentajeB, 1);
    nxt_motor_set_speed(NXT_PORT_C, porcentajeC, 1);

    //Espera hasta que se agote el time_out
    //systick_wait_ms(10000);

    //Despierta la tarea de parada de motores
    //ChainTask(Final);

    //Termina la tarea actual
    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : Calibrar                                                       */
/* Priority: 02                                                             */
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
/* Name    : Final                                                          */
/* Priority: 02                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL 	                                                        */
/* Objective: Stop servomotors.                                             */
/*--------------------------------------------------------------------------*/
TASK(Final)
{
    //Para los motores
    nxt_motor_set_speed(NXT_PORT_B, 0, 1);
    nxt_motor_set_speed(NXT_PORT_C, 0, 1);

    //Termina la tarea actual
    TerminateTask();
}