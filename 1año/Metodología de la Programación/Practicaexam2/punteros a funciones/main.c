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

	printf("Introduce 1 si quieres ordenar de mayor a menor y 2 de menor a mayor\n");
	int aux;
	scanf("%d",&aux);

	if(aux==1){

		ordena(v,cantidad,&es_mayor);

	}else{

		if(aux==2){

			ordena(v,cantidad,&es_menor);

		}else{printf("El numero no es correcto\n");}

	}	

	imprimememoria(v,cantidad);

	liberamemoria(&v);

	return 0;
}