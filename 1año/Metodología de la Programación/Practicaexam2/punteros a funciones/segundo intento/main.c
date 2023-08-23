#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int main(){

	int cantidad;

	int *v;

	printf("Introduce el tamaño del vector\n");
	scanf("%d",&cantidad);

	v=reservamemoria(cantidad);

	rellenamemoria(v,cantidad);

	imprimememoria(v,cantidad);

	printf("Introduce si quieres que se ordene de mayor a menor(1) o de menor a mayor(2):\n");
	int aux;
	scanf("%d",&aux);

	if(aux==1){

		ordena(v,cantidad,&es_mayor);

	}else{

		if(aux==2){

			ordena(v,cantidad,&es_menor);

		}else{printf("Debes introducir un numero valido\n");}

	}

	
	imprimememoria(v,cantidad);

	liberamemoria(&v);

	return 0;
}

