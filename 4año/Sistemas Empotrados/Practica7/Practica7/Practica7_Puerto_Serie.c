#include <stdio.h>
#include <LPC23xx.h>
#include "misTipos.h"
#include "timers.h"
#define SEMIPERIODO_INICIAL 5

UINT32 timersw0, timersw0InitialCount;
UINT32 timersw1, timersw1InitialCount;

BOOL signal0High;
BOOL signal1High;

extern void hardwareInit(void);
extern int getkey(void);

void continuosTimerT0(unsigned int delayInDecimaMiliseg)
{
	T0TCR = 0x02;		/* reset timer */
	T0MR0 = delayInDecimaMiliseg * (12000000 / 10000-1);
	T0MCR = 0x03;		/* timer on match */
	T0TCR = 0x01;		/* inicia timer y para cuando se llegue al final de cuenta     */
}      

UINT32 menuTimer(UINT32* timer, UINT32* semiperiodo)
{
	UINT32 charTmp;
	printf("Señal-Timer 0 o 1:\n");
	do
	{
		charTmp=getkey();
		if(charTmp==ESC) return charTmp;
		if((charTmp<0x32)&(charTmp>=0x30)) printf("%c\n",(char) charTmp);
	}while(!((charTmp<0x32)&(charTmp>=0x30)));
	* timer=(charTmp-0x30);
	printf("Indique el semiperiodo utilizando dos digitos 01 a 99:\n");
	do
	{
		charTmp=getkey();
		if(charTmp==ESC) return charTmp;
		if((charTmp<0x3A)&(charTmp>=0x30)) printf("%c",(char) charTmp);
	}while(!((charTmp<0x3A)&(charTmp>=0x30)));
	* semiperiodo=(charTmp-0x30)*10;
	do
	{
		charTmp=getkey();
		if(charTmp==ESC) return charTmp;
		if((charTmp<0x3A)&(charTmp>=0x30)) printf("%c\n",(char) charTmp);
	}while(!((charTmp<0x3A)&(charTmp>=0x30)));
	* semiperiodo=*semiperiodo+(charTmp-0x30);
	return OK;
}


int main (void){
	UINT32 timer, semiperiodo;
	signal0High=TRUE;
	signal1High=TRUE;
	hardwareInit();
	SIGNAL0_PIN_HIGH;
	SIGNAL1_PIN_HIGH;
	timersw0InitialCount=SEMIPERIODO_INICIAL;
	timersw0=SEMIPERIODO_INICIAL;
	printf("Señal 0 Timer 0 periodo =%d milisegundos\n", semiperiodo*2);
	
	timersw1InitialCount=SEMIPERIODO_INICIAL;
	timersw1=SEMIPERIODO_INICIAL;
	printf("Señal 1 Timer 1 periodo =%d milisegundos\n", semiperiodo*2);
	continuosTimerT0(10);
	while(1){
		printf("Pulse una tecla para cambiar el semiperiodo de las señales\n");
		(void)getkey();
		if(OK==menuTimer(&timer,&semiperiodo))
		{
			switch(timer)
			{
				case 0:
					timersw0InitialCount=semiperiodo;
					printf("Señal 0 Timer 0 nuevo periodo= %d milisegundos \n", semiperiodo*2);
					break;
				case 1:
					timersw1InitialCount=semiperiodo;
					printf("Señal 1 Timer 1 nuevo periodo= %d milisegundos \n", semiperiodo*2);
					break;
			}
		}
	}
}
