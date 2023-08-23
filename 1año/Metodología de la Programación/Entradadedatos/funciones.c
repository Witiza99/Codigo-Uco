#include <stdio.h>
#include "func.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

 int *reservamemoria(int valor){

	int *v=NULL;

	if(((v=(int*)malloc(valor*sizeof(int))))==NULL){

		printf("Hubo un error al hacer reserva de memoria\n");
		exit(-1);

	}

	return v;

}

void aleatorios(int *v,int *valor){

	srand(time(NULL));

	for(int i=0;i<(*valor);i++){

		v[i]=rand()%11;

	}

}


void imprimeporpantalla(int *v,int *valor){

	for(int i=0; i<(*valor);i++){

		printf("%d-->%d\n",i,v[i]);

	}

}
