#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"

int main(int argc, char const *argv[]){
	
	if(argc!=2){

		printf("La entrada de datos es incorrecta solo debe de entrar un dato, el numero del tamaño del vector\n");
		exit(-1);

	}

	int valor=(atoi(argv[1]));

	int *v=NULL;

	v=reservamemoria(valor);

	aleatorios(v, &valor);

	imprimeporpantalla(v, &valor);

	free(v);

	return 0;
}