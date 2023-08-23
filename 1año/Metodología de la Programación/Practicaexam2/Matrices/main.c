#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "func.h"

int main(){

	int col;
	int fil;
	int **m=NULL;

	printf("Introduce el numero de columnas\n");
	scanf("%d",&col);

	printf("Introduce el numero de filas\n");
	scanf("%d",&fil);

	m=(reservamemoria(col,fil));

	rellenamatriz(m,fil,col);

	imprimirmatriz(m,fil,col);

	liberamemoria(&m,col);

	return 0;

}