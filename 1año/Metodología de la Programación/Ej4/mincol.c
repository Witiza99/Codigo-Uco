/**
@file mincol.c
*/
#include <stdio.h>
#include <stdlib.h>
/**
@fn int *minCol(int **matriz, int nFil, int nCol)
@brief funcion que devuelve un vector con los minimos de cada columna

Esta funcion primeramente reserva memoria para para el vector dinamico donde guardara todos los elementos
menores de cada columna de tal forma que se recorre la matriz por columnas almacenando el menor.
@param **matriz puntero a puntero de los elementos de la matriz
@param nFil numero de filas.
@param nCol numero de columnas.
@return vector de enteros con los menores de cada columna.
*/
int *minCol(int **matriz, int nFil, int nCol){

	int *vector;

		vector=(int*)malloc(nFil*sizeof(int));

		if(vector==NULL){

			printf("Error en la reserva de memoria\n");
			exit(-1);

		}

	int menor;

	for(int i=0; i<nCol;i++){

		menor=matriz[0][i];

		for(int j=0;j<nFil;j++){

			if((*(*(matriz+j)+i))<menor){menor=(*(*(matriz+j)+i));}

		}

		vector[i]=menor;

	}

	return vector;

}