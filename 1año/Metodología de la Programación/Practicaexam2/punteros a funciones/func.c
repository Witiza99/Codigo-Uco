#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include <time.h>

int *reservamemoria(int cantidad){

	int *v=NULL;

	if((v=(int*)malloc(cantidad*sizeof(int)))==NULL){

		printf("Error al reservar memoria\n");
		exit(-1);

	}

	return v;

}

void rellenamemoria(int *v,int cantidad){

	srand(time(NULL));

	for(int i=0;i<cantidad;i++){

		v[i]=rand()%21;

	}

}

void imprimememoria(int *v,int cantidad){

	for(int i=0;i<cantidad;i++){

		printf("%d\n",v[i]);

	}

	printf("\n");

}

void ordena(int *v,int cantidad,int (*comparacion)(int, int)){

	int menor;
	int aux;

	for(int i=0;i<(cantidad-1);i++){

		menor=i;

		for(int j=i+1;j<cantidad;j++){

			if((*comparacion)(v[j],v[menor]))

				menor=j;

		}

		aux=v[menor];
		v[menor]=v[i];
		v[i]=aux;

	}

}

void liberamemoria(int **v){

	free(*v);

	(*v)=NULL;

}

int es_mayor(int a,int b){

	if(a>b){

		return 1;

	}else 

	return 0;

}

int es_menor(int a, int b){

	if(a<b){

		return 1;

	}else{

		return 0;

	}

}