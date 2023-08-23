#include <stdio.h>
#include <LPC23xx.h>
extern void init_serial(void);

 int main(void) { 
	int n=8;
	 n=8;
	 init_serial();
	 printf("hola mundo");
	 n=n+1;
	 n=n-4;
	 while(1);
 }
