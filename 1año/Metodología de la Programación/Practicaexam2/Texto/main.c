#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "func.h"
#include <ctype.h>

int main(int argc, char const *argv[]){
	
	if(argc!=2){

		printf("Error al abrir el programa se debe introducir solo un dato el nombre del fichero que se desea abrir\n");
		exit(-1);

	}

	char fichero[50];

	strcpy(fichero,argv[1]);

	int aux=0;
	int contador=0;
	char busqueda[50];

	while (aux!=7){

		printf("1.Contar libros diferentes\n");
		printf("2.Nuevo libro\n");
		printf("3.Buscar libro\n");
		printf("4.Listar libros\n");
		printf("5.Vender un libro\n");
		printf("6.Borrar registros\n");
		printf("7.Salir del programa\n");

		scanf("%d",&aux);

		switch(aux){

			case 1:

			contador=(contarlibros(fichero));

			printf("Hay %d libros diferentes\n",contador);

			contador=0;

			break;

			case 2:

			nuevolibro(fichero);

			break;

			case 3:

			printf("Introduce el libro que deseas buscar\n");

			setbuf(stdin,NULL);
			fgets(busqueda,50,stdin);

			if((busqueda[strlen(busqueda)-1])=='\n'){

				busqueda[strlen(busqueda)-1]='\0';

			}

			busqueda[0]=toupper(busqueda[0]);

			contador=buscarlibro(fichero,busqueda);

			if(contador==0){

				printf("El libro no se ha encontrado\n");

			}else{printf("El libro se ha encontrado\n");}


			break;

			case 4:

			listarlibros(fichero);

			break;

			case 5:

			printf("Introduce el nombre del libro que quieres vender\n");

			setbuf(stdin,NULL);
			fgets(busqueda,50,stdin);

			if((busqueda[strlen(busqueda)-1])=='\n'){

				busqueda[strlen(busqueda)-1]='\0';

			}

			busqueda[0]=toupper(busqueda[0]);

			venderlibro(fichero,busqueda);

			break;

			case 6:

			borrarregistros(fichero);

			break;

			case 7:

			printf("Hasta luego\n");
			exit(-1);

			break;

			default:

			printf("Introduce un numero correcto como los anteriores dichos\n");

			break;

		}

	}

	return 0;
}