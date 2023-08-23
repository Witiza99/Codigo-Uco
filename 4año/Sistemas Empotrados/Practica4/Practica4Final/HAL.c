/*********************************************************************************/
/* HAL.C: funciones generales que acceden al hardware                            */
/* Capa de abstraccion del hardware (HAL)																				 */
/* Sistemas Empotrados Universidad de Cordoba                                    */
/*********************************************************************************/
extern __irq void T0_IRQHandler	(void);
extern __irq void T1_IRQHandler	(void);
#include <LPC23xx.H>                      /* LPC23xx definitions                 */

void pinesSignalInit(void)
{
	PINSEL9  = 0X00000000;
	PINMODE9 = 0X00000000;
	FIO4DIR3 = 0X03;
}
/*********************************************************************************/
/* timer0Init                                                                    */
/*********************************************************************************/
/* Esta funcion configura el timer 0 con los parámetros que no cambian           */
/* durante la aplicacion                                                         */
/*********************************************************************************/
void timer0Init(void)
{
	T0PR = 0x00;										       				/* activa el preescalador a cero */
	VICVectAddr4 = (unsigned long) T0_IRQHandler;	/*Set Interrupt Vector					 */
	VICVectCntl4 = 15;
	VICIntEnable = (1 << 4);
}
/*********************************************************************************/
/* timer1Init                                                                    */
/*********************************************************************************/
/* Esta funcion configura el timer 1 con los parámetros que no cambian           */
/* durante la aplicacion                                                         */
/*********************************************************************************/
void timer1Init(void)
{
	PCONP |= (0 << 2);														/*Habilito Timer 1, power y reloj*/
	T1PR = 0x00;										       				/* activa el preescalador a cero */
	VICVectAddr5 = (unsigned long) T1_IRQHandler;	/*Set Interrupt Vector					 */
	VICVectCntl5 = 15;
	VICIntEnable = (1 << 5);
}
/*********************************************************************************/
/* hardwareInit                                                                  */
/*********************************************************************************/
/* Esta funcion se llama al comienzo del programa para inicializar el Hardware   */
/*********************************************************************************/
void hardwareInit(void)
{
	pinesSignalInit();	// Configura los pines del circuito
	timer0Init();				// Inicializa el timer 0
	timer1Init();				// Inicializa el timer 1
}

