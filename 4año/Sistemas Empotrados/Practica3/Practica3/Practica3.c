/*********************************************************************************/
/* timers.C: Programa principal                                                  */
/* Sistemas Empotrados Universidad de Cordoba                                    */
/*********************************************************************************/
#include <stdio.h>
#include <LPC23xx.H>                      /* LPC23xx definitions                 */
#include "misTipos.h"
#include "Practica3.h"
extern void hardwareInit(void);

/* Timer0 and Timer1                                                             */
int main (void)
{
	unsigned int signal0HIGH = FALSE;
	unsigned int signal1HIGH = FALSE;
	hardwareInit();
	delayT0Unlocked(PULSO0_LOW);
	delayT1Unlocked(PULSO1_LOW);	
	while(1)
	{
		if (( T0IR&0x01 ) == (unsigned int) 0x01 ) 	/* Se comprueba si el timers ha   */
		{																				 		/*					alcanzado la cuenta   */
			T0IR = 0x1;
			if(signal0HIGH== TRUE)
			{
				signal0HIGH = FALSE;
				SIGNAL0_PIN_LOW;
				delayT0Unlocked(PULSO0_LOW);
			}
			else
			{
				signal0HIGH = TRUE;
				SIGNAL0_PIN_HIGH;
				delayT0Unlocked(PULSO0_HIGH);
			}
		}
		if (( T1IR&0x01 ) == (unsigned int) 0x01 ) 	/* Se comprueba si el timers ha   */
		{																				 		/*					alcanzado la cuenta   */
			T1IR = 0x1;
			if ( signal1HIGH == TRUE)
			{
				signal1HIGH = FALSE;
				SIGNAL1_PIN_LOW;
				delayT1Unlocked(PULSO1_LOW);
			}
			else
			{
				signal1HIGH = TRUE;
				SIGNAL1_PIN_HIGH;
				delayT1Unlocked(PULSO1_HIGH);
			}
		}
	}
}
