#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int	main(){

	struct libros *v=NULL;
	int *l=NULL;
	int cantidad;

	printf("Introduce cantidad\n");
	scanf("%d",&cantidad);

	v=(reservarmemoria(cantidad));
	l=(reservav(cantidad));

	free(v);
	free(l);
	return 0;

}