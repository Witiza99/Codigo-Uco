#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "func.h"

int **reservamemoria(int fil,int col){

	int **m=NULL;

	if((m=(int **)malloc(fil*sizeof(int *)))==NULL){

		printf("Error al reservar memoria\n");
		exit(-1);

	}

	for(int i=0;i<fil;i++){

		if((m[i]=(int *)malloc(col*sizeof(int)))==NULL){

			printf("Error al reservar memoria\n");
			exit(-1);

		}

	}

	return m;

}

void rellenamatriz(int **m,int fil,int col){

	srand(time(NULL));

	for(int i=0;i<fil;i++){

		for(int j=0;j<col;j++){

			m[i][j]=rand()%11;

		}

	}

}

void imprimirmatriz(int **m, int fil, int col){

	for(int i=0;i<fil;i++){

		for(int j=0;j<col;j++){

			printf("%d\n",m[i][j]);

		}

	}

}

void liberamemoria(int ***m, int col){

	for(int i=0; i<col;i++){

		free((*m)[i]);

	}

	free(*m);

	(*m)=NULL;

}