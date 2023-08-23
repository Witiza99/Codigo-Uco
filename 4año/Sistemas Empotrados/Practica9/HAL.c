/*********************************************************************************/
/* HAL.C: funciones generales que acceden al hardware                            */
/* Sistemas Empotrados Universidad de Cordoba                                    */
/*********************************************************************************/
#include <LPC23xx.H>                      /* LPC23xx definitions                 */

/*********************************************************************************/
/* pinesSignalInit                                                               */
/*********************************************************************************/
void pinesSignalInit(void)
{
	PINSEL9  = 0X00000000;
	PINMODE9 = 0X00000000;
	FIO4DIR3 = 0X03;//para usarlos dos pines
}
/*********************************************************************************/
/* hardwareInit                                                                  */
/*********************************************************************************/
/* Esta funcion se llama al comienzo del programa para inicializar el Hardware   */
/*********************************************************************************/
void hardwareInit(void)
{
	pinesSignalInit();
}

