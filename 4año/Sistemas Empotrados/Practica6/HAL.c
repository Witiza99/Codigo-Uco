/*********************************************************************************/
/* HAL.C: funciones generales que acceden al hardware                            */
/* Capa de abstraccion del hardware (HAL)																				 */
/* Sistemas Empotrados Universidad de Cordoba                                    */
/*********************************************************************************/
#include <LPC23xx.H>                      /* LPC23xx definitions                 */
/* Import external IRQ handlers from IRQ.c file																	 */
extern int init_serial	(void);
/*********************************************************************************/
/* hardwareInit                                                                  */
/*********************************************************************************/
/* Esta funcion se llama al comienzo del programa para inicializar el Hardware   */
/*********************************************************************************/
void hardwareInit(void)
{
	init_serial();
}

