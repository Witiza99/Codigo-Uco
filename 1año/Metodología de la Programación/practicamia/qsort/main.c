#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int	main(){

	int cantidad;

	int *v=NULL;

	printf("Introduce la cantidad\n");
	scanf("%d",&cantidad);

	v=reservavector(&cantidad);

	rellenavector(v,&cantidad);

	imprimevector(v,&cantidad);

	qsort((int *)v,cantidad,sizeof(int),&ordenavector);

	imprimevector(v,&cantidad);
	
	return 0;
	
}