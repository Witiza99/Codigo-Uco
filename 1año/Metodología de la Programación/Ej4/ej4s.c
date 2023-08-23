/**
@file ej4s.c
@brief Este ejercicio repasa todo lo de matrices y doxygen

En concreto se nos pide hacer un punto h con sus respectivos .c como reservar memoria para matriz, rellenar matriz, imprimir matriz, funcion mincol,
yliberar memoria.

@author Antonio Gómez Giménez
@date Hoy

*/

#include <stdio.h>
#include <stdlib.h>
#include "func.h"

/**
@fn int main()
@brief funcion main

En esta funcion se llaman al resto de funciones
@return nada
*/
int main(){

	int nCol;///<@param nCol numero de columnas
	int nFil;///<@param nFil numero de filas
	int **matriz=NULL;///<@param **matriz matriz dinamica
	int *vector=NULL;///<@param *vector dinamico

	printf("Numero de filas de la matriz\n");
	scanf("%d", &nFil);

	printf("Numero de columnas de la matriz\n");
	scanf("%d", &nCol);

	matriz=reservarMemoria(nFil,nCol);
	rellenaMatriz(matriz,nFil, nCol);
	imprimeMatriz(matriz, nFil, nCol);
	vector=minCol(matriz, nFil, nCol);

	for(int i=0;i<nCol;i++){

		printf("%d\n", vector[i]);

	}

	liberarMemoria(matriz, nFil, vector, nCol);

	return(-1);

}
/**@mainpage Introduccion

Se presenta en esta pagina todos los parametros y funciones del ej4 aparte son brevemente explicados para su comprension
*/


