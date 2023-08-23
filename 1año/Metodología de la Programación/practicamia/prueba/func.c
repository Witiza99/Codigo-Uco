#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int *reservav(int cantidad){

int *l=NULL;

	if((l=((int*)malloc(cantidad*sizeof(int))))==NULL){

		printf("Ha ocurrido un error al reservar memoria.\n");
		exit(-1);

	}

	return l;



}

struct libros *reservarmemoria(int cantidad){

	struct libros *v=NULL;

	if((v=((struct libros*)malloc(cantidad*sizeof(struct libros))))==NULL){

		printf("Ha ocurrido un error al reservar memoria.\n");
		exit(-1);

	}

	return v;


}