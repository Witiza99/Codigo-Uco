/*********************************************************************************/
/* Practica5.C: Programa principal                                                  */
/* Sistemas Empotrados Universidad de Cordoba                                    */
/*********************************************************************************/
#include <stdio.h>
#include <LPC23xx.H>                      /* LPC23xx definitions                 */
#include "misTipos.h"
#include "Practica5.h"
/* Variables globales */
UINT32 timersw0;
UINT32 timersw1;
BOOL signal0HIGH;
BOOL signal1HIGH;
extern void hardwareInit(void);
/*********************************************************************************/
/* delayT0Unlocked                                                               */
/*********************************************************************************/
/* Esta funcion arranca el timer 0 y progama el registro match0                  */
/*********************************************************************************/
void delayT0Unlocked(unsigned int delayInDecimaMiliseg)
{
	T0TCR = 0x02;		/* reset timer */
	T0MR0 = delayInDecimaMiliseg * (12000000 / 10000-1);
	T0MCR = 0x07;		/* timer on match */
	T0TCR = 0x01;		/* inicia timer y para cuando se llegue al final de cuenta     */
}                                                           

int main (void)
{
	/* Iniciaciones de variables globales */
	signal0HIGH = TRUE;
	signal1HIGH = TRUE;
	timersw0 = SIGNAL0_HIGHTIME;
	timersw1 = SIGNAL1_HIGHTIME;
	//inicializamos hardware
	hardwareInit();
	delayT0Unlocked(1);	//temporizo una decima de milisegundo
	while(1){}
}
