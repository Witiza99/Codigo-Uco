/*********************************************************************************/
/* timers.C: Programa principal                                                  */
/* Sistemas Empotrados Universidad de Cordoba                                    */
/*********************************************************************************/

#include <stdio.h>
#include <LPC23xx.H>                      /* LPC23xx definitions                 */
#include "timers.h"

extern void hardwareInit(void);

/* Timer0                                                                        */
int main (void)
{
	hardwareInit();
	while(1)
	{
		SIGNAL0_PIN_LOW;
		delayT0Unlocked(PULSO0_LOW);
		while(!(T0IR & 0x000000001));
		T0IR = 1;
		SIGNAL0_PIN_HIGH;
		delayT0Unlocked(PULSO0_HIGH);
		while(!(T0IR & 0x000000001));
		T0IR = 1;
	}
}
