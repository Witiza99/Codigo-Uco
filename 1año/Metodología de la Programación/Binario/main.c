#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int main(int argc, char const *argv[]){
	
	if(argc!=2){

		printf("La entrada de datos es incorrecta solo debe de entrar un dato, el nombre del fichero binario.\n");
		exit(-1);

	}

	char fichero[50];

	strcpy(fichero,argv[1]);

	int valor=0;

	while(valor!=7){

		printf("1.Busqueda de un libro.\n");
		printf("2.Introducir un nuevo libro en stock.\n");
		printf("3.Contar cuantos libros diferentes en stock hay.\n");
		printf("4.Listar los libros almacenados.\n");
		printf("5.Vender un libro.\n");//se refiere a quitar uno del stock
		printf("6.Borrar los registros vacios.\n");
		printf("7.Salir del programa.\n");

		scanf("%d",&valor);

		switch(valor){

			case 1:

			buscarlibro(fichero);

			break;

			case 2:

			nuevolibro(fichero);

			break;

			case 3:

			printf("Hay %d libros diferentes\n",librosdiferentes(fichero));

			break;

			case 4:

			listarlibros(fichero);

			break;

			case 5:

			venderunlibro(fichero);

			break;

			case 6:

			borrarregistros(fichero);

			break;

			case 7:

			printf("Hasta luego\n");
			exit(-1);

			default:

			printf("Este numero no es valido.\n");

		}


	}

	
	return 0;

}