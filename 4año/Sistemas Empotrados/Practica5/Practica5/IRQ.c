/*********************************************************************************/
/* IRQ.C: manejadores de interrupcion									                           */
/* Sistemas Empotrados Universidad de Cordoba                                    */
/*********************************************************************************/
#include <LPC23xx.H>                      /* LPC23xx definitions                 */
#include "misTipos.h"
#include "Practica5.h"
extern UINT32 timersw0;
extern UINT32 timersw1;
extern BOOL signal0HIGH;
extern BOOL signal1HIGH;
extern void delayT0Unlocked(unsigned int delayInDecimaMiliseg);
/* Timer0 IRQ																																			*/
__irq void T0_IRQHandler	(void){
	//codigo ISR
	timersw0--;
	timersw1--;
	if(timersw0==0)	//comprueba si el timer se 0 ha finalizado
	{
		if(signal0HIGH==TRUE)
		{
			SIGNAL0_PIN_LOW;
			signal0HIGH=FALSE;
			timersw0=SIGNAL0_LOWTIME;
		}
		else
		{
			SIGNAL0_PIN_HIGH;
			signal0HIGH=TRUE;
			timersw0=SIGNAL0_HIGHTIME;
		}
	}
	if(timersw1==0)	//comprueba si el timer se 1 ha finalizado
	{
		if(signal1HIGH==TRUE)
		{
			SIGNAL1_PIN_LOW;
			signal1HIGH=FALSE;
			timersw1=SIGNAL1_LOWTIME;
		}
		else
		{
			SIGNAL1_PIN_HIGH;
			signal1HIGH=TRUE;
			timersw1=SIGNAL1_HIGHTIME;
		}
	}
	T0IR				= 1;
	VICVectAddr	= 0;
	delayT0Unlocked(1);
}
