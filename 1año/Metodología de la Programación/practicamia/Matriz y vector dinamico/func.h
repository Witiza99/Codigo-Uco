#ifndef FUNC_H
#define FUNC_H

	int **reservamemoriamatriz(int nFil,int nCol);

	void rellenamatriz(int **m,int *nFil,int *nCol);

	void imprimematriz(int **m,int *nFil,int *nCol);

	int *numerospequenos(int **m, int *nFil,int *nCol);

	void imprime(int *v,int *nFil);

	void liberamemoria(int ***m,int **v, int *nCol);

#endif 