#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#define SONAR_PORT NXT_PORT_S4
#define PULSADOR_PORT NXT_PORT_S2

/*--------------------------------------------------------------------------*/
/* OSEK declarations                                                        */
/*--------------------------------------------------------------------------*/

//CONTADORES
DeclareCounter(Contador);
//TAREAS
DeclareTask(Principal);
DeclareTask(Avance);
DeclareTask(Retroceso);
DeclareTask(CambioDir);
DeclareTask(Golpe);
DeclareTask(Calibrar);
DeclareTask(SensorUltraSonidos);
DeclareTask(TomaDecision);
//ALARMAS
DeclareAlarm(AlarmaCalibrar);
DeclareAlarm(AlarmaGolpe);
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

int Tiempo_T1 = 0;
int Tiempo_T2 = 0;
int Tiempo_T3 = 0;

int distancia = 1000;
int N = 1;

/*--------------------------------------------------------------------------*/
/* Function to be invoked from a category 2 interrupt                       */
/*--------------------------------------------------------------------------*/
void user_1ms_isr_type2()
{
    SignalCounter(Contador);
}


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

//Calcula divisor
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
        N = 4;
    }
}

void Rotacion()
{
    Tiempo_T2 = Tiempo_T1;
    Tiempo_T3 = Tiempo_T2;
}

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
/* Objective: Calibrate the wheels.                                         */
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
/* Name    : SensorUltraSonidos                                             */
/* Priority: 03                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Obtains the distance given by the ultra-sound sensor.         */
/*--------------------------------------------------------------------------*/
TASK(SensorUltraSonidos)
{
	distancia = ecrobot_get_sonar_sensor(SONAR_PORT);
    MostrarPorPantalla(distancia);
	ActivateTask(TomaDecision);
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
	if(Tiempo_T1 == 0)
    {
        Tiempo_T1 = CalcularModo(distancia);
        AplicarModo(Tiempo_T1);
        ActivateTask(Avance);
    }
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
/* Name    : Retroceso                                                      */
/* Priority: 06                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Move backward.                                                */
/*--------------------------------------------------------------------------*/
TASK(Retroceso)
{
    //Activar servomotores para retrocedera
    nxt_motor_set_speed(NXT_PORT_B, -porcentajeB, 1);
    nxt_motor_set_speed(NXT_PORT_C, -porcentajeC, 1);

	//Tiempo que vamos a estar retrocediendo
	systick_wait_ms(1000);

	//Parar servomotores
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);

    //Termina la tarea actual
    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : CambioDir		                                                */
/* Priority: 05                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: Change direction of the robot.				                */
/*--------------------------------------------------------------------------*/
TASK(CambioDir)
{
	//Giramos
	nxt_motor_set_speed(NXT_PORT_B, porcentajeB, 1);
    nxt_motor_set_speed(NXT_PORT_C, -porcentajeC, 1);

	//Tiempo girando
	systick_wait_ms(400);
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);

    //Termina la tarea actual
    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : Golpe                                                          */
/* Priority: 07                                                             */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: FULL		                                                    */
/* Objective: If the pushbutton is hit, the robot moves back and rotates.   */
/*--------------------------------------------------------------------------*/
TASK(Golpe)
{
	if(ecrobot_get_touch_sensor(PULSADOR_PORT)==1)
    {
		//Cancelamos la alarma de calibración
		CancelAlarm(AlarmaCalibrar);
		CancelAlarm(AlarmaUltraSonidos);

		//Retrocedemos
		ActivateTask(Retroceso);
		ActivateTask(CambioDir);

        //Actualizamos variables globales
        Tiempo_T1 = 0;
        Tiempo_T2 = 0;
        Tiempo_T3 = 0;

		//Volvemos a activar la calibración antes de terminar
		SetRelAlarm(AlarmaCalibrar,10,10);
		SetRelAlarm(AlarmaUltraSonidos,30,30);
	}

	TerminateTask();
}