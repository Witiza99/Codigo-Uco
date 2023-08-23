#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int main(){

	int aux=0;

	int n;

	int contador=0;

	struct lista *cabeza=NULL;

	while (aux!=8){

		printf("1.Insertar por delante:\n");
		printf("2.Imprimir lista\n");
		printf("3.Imprimir lista inversa\n");
		printf("4.Buscar elemento\n");
		printf("5.Borrar elemento\n");
		printf("6.Borrar lista\n");
		printf("7.Insertar orden recursivo\n");
		printf("8.Salir\n");

		scanf("%d",&aux);

		switch(aux){

			case 1:

			printf("Introduce el numero que deseas insertar por delante:\n");
			scanf("%d",&n);

			contador=buscarelemento(cabeza,n);

			if(contador==0){

				insertardelante(&cabeza,n);

			}else{printf("No puedes introducir un numero que ya esta introducido\n");}

			break;

			case 2:

			imprimirlista(cabeza);

			break;

			case 3:

			imprimirlistainversa(cabeza);

			break;

			case 4:

			printf("Introduce el elemento que desear buscar:\n");
			scanf("%d",&n);

			contador=buscarelemento(cabeza,n);

			if(contador==1){

				printf("El elemento se ha encontrado\n");

			}else{printf("El elemento no se ha encontrado\n");}

			break;

			case 5:

			printf("Introduce el numero que deseas borrar:\n");
			scanf("%d",&n);

			contador=buscarelemento(cabeza,n);

			if(contador==1){

				borrarelemento(&cabeza,n);

			}else{printf("No puedes borrar algo que no esta en la lista\n");}

			break;

			case 6:

			borrarlista(&cabeza);

			break;

			case 7:

			printf("Esta funcion solo funciona en caso de lista ordenada\n");

			printf("Introduce el numero que deseas insertar:\n");
			scanf("%d",&n);

			contador=buscarelemento(cabeza,n);

			if(contador==0){

				insertarordenrecursivo(&cabeza,n);

			}else{printf("No puedes introducir un numero que ya esta introducido\n");}

			break;

			case 8:

			borrarlista(&cabeza);

			free(cabeza);
			cabeza=NULL;

			printf("Hasta luego\n");

			break;

			default:

			printf("Introduce un numero correcto:\n");

		}

	}
	
	return 0;

}