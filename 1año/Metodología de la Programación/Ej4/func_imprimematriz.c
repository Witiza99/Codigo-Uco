#include <stdio.h>

void imprimeMatriz(int **matriz, int nFil, int nCol){

	for(int i=0,i<nFil,i++){

		for(int j=0,j<nCol,j++){

			printf("%d"\n,matriz[i][j]);

		}

	}
	
}