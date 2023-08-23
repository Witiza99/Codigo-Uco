#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int main(){

	int n;
	int encontrado;
	int aux=0;
	struct lista *cabeza=NULL;

	while(aux!=8){

		printf("1.Insertar por delante:\n");
		printf("2.Imprimir lista\n");
		printf("3.Imprimir lista inversa\n");
		printf("4.Buscar elemento\n");
		printf("5.Borrar elemento\n");
		printf("6.Borrar lista\n");
		printf("7.Ordenar lista\n");
		printf("8.Salir\n");

		scanf("%d",&aux);

		system("clear");

		switch(aux){

			case 1:

			printf("Elemento a insertar\n");
			scanf("%d",&n);

			encontrado=buscarelemento(cabeza,n);

			if(encontrado==0){

			insertarpordelante(&cabeza,n);
			printf("Elemento insertado\n");

			}

			else{printf("No puedes insertar algo que ya esta.\n");}

			break;

			case 2:

			imprimirlista(cabeza);

			break;

			case 3:

			imprimirlistainversa(cabeza);

			break;

			case 4:

			printf("Elemento a buscar\n");
			scanf("%d",&n);

			encontrado=buscarelemento(cabeza,n);

			if(encontrado==1){

				printf("El elemento se ha encontrado\n");

			}

			else{

				printf("El elemento no se ha encontrado\n");

			}

			break;

			case 5:

			printf("Introduce el elemento que quieras borrar de la lista:\n");
			scanf("%d",&n);

			encontrado=buscarelemento(cabeza,n);

			if(encontrado==1){

			borrarelemento(&cabeza,n);

			}

			else{

				printf("No puedes borrar algo que no tienes.\n");

			}

			break;

			case 6:

			borrarlista(&cabeza);

			break;

			case 7:

			printf("Esta funcion solo funciona si los datos se han introducido ordenados de menor a mayor\n");
			printf("Introduce el nuevo numero\n");
			scanf("%d",&n);

			insertarordenrecursivo(&cabeza,n);

			break;

			case 8:

			free(cabeza);
			printf("Hasta luego.\n");
			exit(-1);

			break;

			default:

			printf("Error al introducir el archivo, ponga uno correcto\n");

			break;


		}

	}

	return 0;

}