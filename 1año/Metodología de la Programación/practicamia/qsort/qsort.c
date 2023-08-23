#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"

int *reservavector(int *cantidad){

	int *v=NULL;

	if((v=(int *)malloc((*cantidad)*sizeof(int)))==NULL){

		printf("Error al reservar memoria para el vector\n");

	}

	return v;

}

void rellenavector(int *v, int *cantidad){

	srand(time(NULL));

	for(int i=0;i<(*cantidad);i++){

		v[i]=rand()%11;

	}

}

void imprimevector(int *v,int *cantidad){

	for(int i=0;i<(*cantidad);i++){

		printf("%d-->%d\n",i,v[i]);

	}

}
int ordenavector(const void *e1, const void *e2){

	int *a=NULL;
	int *b=NULL;

	a=(int *)e1;
	b=(int *)e2;

	if(*a>*b){

		return 1;

	}else if(*a==*b){

		return 0;

	}else

		return (-1);

}