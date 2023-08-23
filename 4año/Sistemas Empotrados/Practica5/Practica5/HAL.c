/*********************************************************************************/
/* HAL.C: funciones generales que acceden al hardware                            */
/* Capa de abstraccion del hardware (HAL)																				 */
/* Sistemas Empotrados Universidad de Cordoba                                    */
/*********************************************************************************/
#include <LPC23xx.H>                      /* LPC23xx definitions                 */
#include "Practica5.h"
/* Import external IRQ handlers from IRQ.c file																	 */
extern __irq void T0_IRQHandler	(void);

void pinesSignalInit(void)
{
	PINSEL9  = 0X00000000;
	PINMODE9 = 0X00000000;
	FIO4DIR3 = 0X03;//para usarlos dos pines
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
/* hardwareInit                                                                  */
/*********************************************************************************/
/* Esta funcion se llama al comienzo del programa para inicializar el Hardware   */
/*********************************************************************************/
void hardwareInit(void)
{
	pinesSignalInit();	// Configura los pines del circuito
	timer0Init();				// Inicializa el timer 0
}

