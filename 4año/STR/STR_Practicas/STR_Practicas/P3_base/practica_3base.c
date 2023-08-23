#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#define SONAR_PORT NXT_PORT_S4
#define PULSADOR_PORT NXT_PORT_S2
#define FREC 1800
#define MS 1000
#define VOL 100

/*--------------------------------------------------------------------------*/
/* OSEK declarations                                                        */
/*--------------------------------------------------------------------------*/
DeclareCounter(Contador);
DeclareTask(PulsosSonidos);

//Alarmas
DeclareAlarm(AlarmaPulsosSonidos);

/*--------------------------------------------------------------------------*/
/* Definitions                                                              */
/*--------------------------------------------------------------------------*/

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
/* Name    : PulsosSonidos                                                  */
/* Priority: ??                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Reproducir un pitido de un segundo.						    */
/*--------------------------------------------------------------------------*/

TASK(PulsosSonidos)
{
    ecrobot_sound_tone(FREC, MS, VOL);
    TerminateTask();
}
