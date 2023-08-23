/**
@file func.h
@brief Este es el punto h de la funcion

En este punto h se encuentran las llamadas a funcion para que el main pueda buscarlos dentro de nuestro fichero.
*/	
	#ifndef func
	#define func

	int ** reservarMemoria(int nFil,int nCol);
	void rellenaMatriz(int **matriz,int nFil,int nCol);
	void imprimeMatriz(int **matriz,int nFil,int nCol);
	int *minCol(int **matriz, int nFil, int nCol);
	void liberarMemoria(int **matriz, int nFil, int *vector, int nCol);

	#endif