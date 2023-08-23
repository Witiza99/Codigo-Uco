#include <LPC23xx.h>
#include "misTipos.h"
#include "GPIO_P1.h"
UINT32 image_pin24;

extern void hardwareInit(void);
extern void SO_Inicio_TCB_Var(void);
extern void startT1(void);
extern void ActVIC_T1(void);
extern void SOStart(void);
extern unsigned int SOAgrego_Tarea(int (*)(void),const unsigned int ,const unsigned int );
extern void SODespachador_Tareas(void);

int MyTask(void){
	if(image_pin24==0){
		PIN_P4_24_HIGH;
		image_pin24=1;
	}else{
		PIN_P4_24_LOW;
		image_pin24=0;
	}
	return 0;
}

int main (void){
	PIN_P4_24_LOW;
	image_pin24=0;
	hardwareInit();
	SO_Inicio_TCB_Var();
	startT1();
	ActVIC_T1();
	SOStart();
	SOAgrego_Tarea(MyTask, 100, 100);
	while(1){
		SODespachador_Tareas();
	}
}
