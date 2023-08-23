//reservar memoria para matriz
//rellena matriz
//imprime matriz
//vector dinamico que devuelve los menores de cada columna
//funcion paraliberarmemoria de los dos

#include <stdlib.h>
#include <stdio.h>

int	main(){

	int nFil, nCol;

	int **m=NULL;
	int *v=NULL;

	printf("Introduce el numero de filas:\n");
	scanf("%d",&nFil);

	printf("Introduce el numero de columnas:\n");
	scanf("%d",&nCol);

	m=(reservamemoriamatriz(nFil,nCol));

	rellenamatriz(m,&nFil,&nCol);

	imprimematriz(m,&nFil,&nCol);

	v=numerospequenos(m,&nFil,&nCol);

	imprime(v,&nFil);

	liberamemoria(&m,&v,&nCol);

	return 0;

}