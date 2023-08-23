#include <stdio.h>
#include <stdlib.h>
#include "fucn.h"
#include <string.h>

int main(){

	int cantidad;
	int cantidad2;

	int *v=NULL;
	struct libros *libro=NULL;

	printf("Introduce el tamaño de el vector de numeros y el de libros:\n");
	scanf("%d",&cantidad);
	scanf("%d",&cantidad2);

	v=(reservamemorianumeros(cantidad));
	libro=(reservamemoriaestructuras(cantidad2));

	rellena(v,cantidad);
	rellenaestructuras(libro,cantidad2);

	printf("Imprime los vectores sin ordenar.\n");

	imprimenumeros(v,cantidad);
	imprimeestructuras(libro,cantidad2);

	qsort((int*)v, cantidad, sizeof(int), &comparaEnteros);
	qsort((struct libros*)libro, cantidad2, sizeof(struct libros), &comparaEstructuras);

	printf("Imprime los vectores ordenados.\n");

	imprimenumeros(v,cantidad);
	imprimeestructuras(libro,cantidad2);

	printf("Comparo segun el nombre\n");

	qsort((struct libros*)libro, cantidad2, sizeof(struct libros), &comparasegunnombre);

	imprimeestructuras(libro,cantidad2);

	printf("Comparo segun el titulo\n");

	qsort((struct libros*)libro, cantidad2, sizeof(struct libros), &comparatitulos);

	imprimeestructuras(libro,cantidad2);

	free(v);
	free(libro);

	return 0;

}