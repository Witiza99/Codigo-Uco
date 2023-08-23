#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include <string.h>

int main(int argc, char const *argv[]){
	
	if(argc!=2){

		printf("Solo debe introducir un dato y este es el nombre del fichero\n");
		exit(-1);

	}

	char fichero[50];

	strcpy(fichero,argv[1]);

	int aux=0;
	int contador=0;

	while(aux!=7){

		printf("1.Busqueda de un libro.\n");
		printf("2.Introducir un nuevo libro en stock.\n");
		printf("3.Contar cuantos libros diferentes en stock hay.\n");
		printf("4.Listar los libros almacenados.\n");
		printf("5.Vender un libro.\n");//se refiere a quitar uno del stock
		printf("6.Borrar los registros vacios.\n");
		printf("7.Salir del programa.\n");

		scanf("%d",&aux);

		switch(aux){

			case 1:

			contador=buscarlibro(fichero);

			if(contador==0){

				printf("El libro no ha encontrado\n");

			}

			else{

				printf("el libro se ha encontrado\n");

			}

			contador=0;

			break;

			case 2:

			nuevolibro(fichero);

			break;

			case 3:

			contador=contarlibrosdiferentes(fichero);

			printf("Hay %d libros diferentes\n", contador);

			contador=0;

			break;

			case 4:

			break;

			case 5:

			break;

			case 6:

			break;

			case 7:

			printf("Hasta luego.\n");

			break;

			default:

			printf("Este valor no es valido introduce un valor correcto\n");

			break;


		}


	}

	return 0;
}