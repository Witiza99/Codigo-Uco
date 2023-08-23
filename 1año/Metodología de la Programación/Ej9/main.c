#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int main(){

char fichero[50];
int aux=0;
int numero_libros;

printf("Introduce el nombre del fichero con el que vas a trabajar:\n");
scanf("%s",fichero);


while(aux!=7){


	printf("1.Busqueda de un libro.\n");
	printf("2.Introducir un nuevo libro en stock.\n");
	printf("3.Contar cuantos libros diferentes en stock hay.\n");
	printf("4.Listar los libros almacenados.\n");
	printf("5.Vender un libro.\n");//se refiere a quitar uno del stock
	printf("6.Borrar los registros vacios.\n");
	printf("7.Salir del programa.\n");

	scanf("%d",&aux);
	system("clear");

	switch(aux){

		case 1:

		break;

		case 2:

		break;

		case 3:

			numero_libros=contarlibrosdiferentes(fichero);

			printf("Hay %d libros diferentes\n\n", numero_libros);

		break;

		case 4:

		break;

		case 5:

		break;

		case 6:

		break;

		case 7:

			printf("Hasta Luego\n");

		break;

		default:

			printf("Introduzca un numero valido\n\n");

		}
	

	}
	
	return(0);

}