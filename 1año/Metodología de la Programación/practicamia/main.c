#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int main(){

	int aux=0;
	struct lista *cabeza=NULL;
	int contador=0;
	int n;

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

			printf("Introduce el elemento a insertar:\n");

			scanf("%d",&n);

			if(buscarelemento(cabeza,&n)==0){

				insertarpordelante(&cabeza,&n);

			}else{

				printf("No puedes insertar algo que esta ya contenido\n");

			}

			else

			break;

			case 2:

			imprimirlista(cabeza);

			break;

			case 3:

			imprimirlistainversa(cabeza);

			break;

			case 4:

			printf("Introduce el elemento a buscar:\n");

			scanf("%d",&n);

			contador=buscarelemento(cabeza,&n);

			if(contador>0){

				printf("El elemento se ha encontrado.\n");

			}else{

				printf("El elemento no se ha encontrado\n");

			}

			break;

			case 5:

			printf("Introduce el elemento que quieres borrar\n");
			scanf("%d",&n);

			if(buscarelemento(cabeza,&n)==0){

				eliminarelemento(&cabeza,&n);

			}else{

				printf("No puedes eliminar algo que no tienes\n");
			}

			break;

			case 6:

			eliminarlista(&cabeza)

			break;

			case 7:

			printf("Introduce el elemento a insertar,solo funciona si los datos estan de menor a mayor:\n");

			scanf("%d",&n);

			if(buscarelemento(cabeza,&n)==0){

				insertarordenrecursivo(&cabeza,&n);

			}else{

				printf("No puedes insertar algo que esta ya contenido\n");

			}

			break;

			case 8:

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