#include <stdio.h>
#include <LPC23xx.h>
#include "misTipos.h"

extern void hardwareInit(void);
extern void init_serial(void);
extern void delayT0Unlocked(unsigned int);

int main (void){
	UINT32 AD_Value;
	AD_Value=0;
	hardwareInit();
	init_serial();
	while(1){
		AD0CR |= 0x01000000;
		AD_Value = AD0DR0;
		delayT0Unlocked(10000);
		while(!(T0IR & 0x00000001));
		T0IR = 1;
		while((AD_Value & 0x80000000) != 0x80000000) (AD_Value = AD0DR0);
			AD_Value = (AD0DR0 >> 6) & 0x3FF;
			printf("AD value = 0x%03x\n\r", AD_Value);
	}
}
