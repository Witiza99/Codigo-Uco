#define <stdio.h>

int main(){


	int nFil;
	int nCol;

	printf("Introduce el numero de filas de la matriz\n");
	scanf("%d",nFil);

	printf("Introduce el numero de columnas de la matriz\n");
	scant("%d",nFil);

	int ** reservarMemoria(int nFil,int nCol);
	void rellenaMatriz(int **matriz,int nFil,int nCol);/*printf(matriz[%d][%d],nFil,nCol);*/
	void imprimeMatriz(int **matriz,int nFil,int nCol);
	int *minCol(int **matriz, int nFil, int nCol);
	/*printf(matriz[%d][%d],nFil,nCol); printf(%d,*minCol);*/
	void liberarMemoria(int **matriz, int nFil);/*printf(matriz[%d][%d],nFil,nCol);*/

	return -1;
}