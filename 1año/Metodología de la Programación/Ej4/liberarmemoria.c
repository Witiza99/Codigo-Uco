/**
@file liberarmemoria.c
*/
#include <stdio.h>
#include <stdlib.h>
/**
@fn void liberarMemoria(int **matriz,int nFil,int *vector, int nCol)
@brief Esta funcion libera la memoria.

Esta funcion libera la memoria tanto de la matriz dinamica como del vector dinamico.
@param **matriz matriz de punteros a punteros a los elementos
@param nFil numero de filas.
@param nCol numero de columnas.
@return Nada
*/
void liberarMemoria(int **matriz,int nFil,int *vector, int nCol){

	for(int i=0; i<nFil; i++){

		free(matriz[i]); 

	}

free(matriz);

free(vector);

}