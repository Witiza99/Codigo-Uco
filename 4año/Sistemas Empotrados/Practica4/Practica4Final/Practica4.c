/*********************************************************************************/
/* Practica4.C: Programa principal                                                  */
/* Sistemas Empotrados Universidad de Cordoba                                    */
/*********************************************************************************/
#include <stdio.h>
#include <LPC23xx.H>                      /* LPC23xx definitions                 */
#include "misTipos.h"
#include "Practica4.h"
extern void hardwareInit(void);

unsigned int signal0HIGH = FALSE;
unsigned int signal1HIGH = FALSE;

/* Timer0 and Timer1                                                             */

__irq void T0_IRQHandler(void){
	
	if(signal0HIGH==TRUE){
		signal0HIGH=FALSE;
		SIGNAL0_PIN_LOW;
		delayT0Unlocked(PULSO0_LOW);
	}else{
		signal0HIGH=TRUE;
		SIGNAL0_PIN_HIGH;
		delayT0Unlocked(PULSO0_HIGH);
	}
	
	T0IR = 1;
	VICVectAddr = 0; 
}

__irq void T1_IRQHandler(void){
	
	if(signal1HIGH==TRUE){
		signal1HIGH=FALSE;
		SIGNAL1_PIN_LOW;
		delayT1Unlocked(PULSO1_LOW);
	}else{
		signal1HIGH=TRUE;
		SIGNAL1_PIN_HIGH;
		delayT1Unlocked(PULSO1_HIGH);
	}
	
	T1IR = 1;
	VICVectAddr = 0; 
}

int main (void)
{
	hardwareInit();
	
	delayT0Unlocked(PULSO0_LOW);
	delayT1Unlocked(PULSO1_LOW);
	
	while(1){}

}
