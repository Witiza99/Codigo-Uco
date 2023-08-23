/*********************************************************************************/
/* Practica6.C: Programa principal                                                  */
/* Sistemas Empotrados Universidad de Cordoba                                    */
/*********************************************************************************/
#include <stdio.h>
#include <LPC23xx.H>                      /* LPC23xx definitions                 */
#include "misTipos.h"

extern void hardwareInit (void);
extern int getkey (void);
int main (void)
{
	UINT32 charTmp;
	UINT32 primerDigito, segundoDigito, resultado;
	//inicializacion del hardware
	hardwareInit();
	while(1){
		printf("Este programa multiplica dos digitos BCD \n");
		printf("Introduzca el primer digito: \n");
		do{
			charTmp=getkey();
			if((charTmp<0x3A)&(charTmp>=0x30)) printf("%c", (char) charTmp);
		}while(!(charTmp<0x3A)&(charTmp>=0x30));
		primerDigito=(charTmp-0x30);
		printf("\nIntroduzca el segundo digito: \n");
		do{
			charTmp=getkey();
			if((charTmp<0x3A)&(charTmp>=0x30)) printf("%c", (char) charTmp);
		}while(!(charTmp<0x3A)&(charTmp>=0x30));
		segundoDigito=(charTmp-0x30);
		//resultado
		resultado=primerDigito*segundoDigito;
		printf("\nResultado: %d\n", resultado);
		printf("Pulse una tecla para multiplicar de nuevo \n");
		(void)getkey();
		printf("\n \n");
	}
}
