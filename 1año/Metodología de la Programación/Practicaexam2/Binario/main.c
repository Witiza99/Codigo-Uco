#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include <ctype.h>

int main(int argc, char const *argv[]){
	
	if(argc!=2){

		printf("Ha ocurrido un error, debes introducir el nombre del fichero binario con el que deseas trabajar\n");
		exit(-1);

	}

	char fichero[50];

	strcpy(fichero,argv[1]);

	int aux=0; 

	int contador=0;

	char busqueda[50];

	while(aux!=7){

		printf("1.Contador de libros diferentes\n");
		printf("2.Buscar libro\n");
		printf("3.Nuevo libro\n");
		printf("4.Listar libros\n");
		printf("5.Vender un libro\n");
		printf("6.Borrar registros\n");
		printf("7.Salir del programa\n");

		scanf("%d",&aux);

		switch(aux){

			case 1:

			contador=contarlibrosdiferentes(fichero);

			printf("Hay %d libros diferentes\n",contador);

			break;

			case 2:

			printf("Introduce el libro que desear comprobar su existencia\n");
			setbuf(stdin,NULL);
			fgets(busqueda,50,stdin);

			if(busqueda[strlen(busqueda)-1]=='\n'){

				busqueda[strlen(busqueda)-1]='\0';

			}

			busqueda[0]=toupper(busqueda[0]);

			if((buscarlibro(fichero,busqueda))==0){

				printf("El libro no se ha encontrado\n");

			}else{

				printf("El libro se ha encontrado\n");

			}

			break;

			case 3:

			nuevolibro(fichero);

			break;

			case 4:

			listarlibros(fichero);

			break;

			case 5:

			venderlibro(fichero);

			break;

			case 6:

			borrarregistros(fichero);

			break;

			case 7:

				printf("Hasta luego\n");
				exit(-1);

			break;

			default:

				printf("El numero introducido no es valido introduce un numero que valga\n");

			break;

		}

	}


	return 0;
}