#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include <string.h>

void existe_libro(char fichero[50]){

	struct libros libro;

	printf("Introduce el nombre del libro que quieres buscar:\n");
	setbuf(stdin,NULL);
	fgets(libro.titulo,50,stdin);
	libro.titulo[strlen(libro.titulo)-1]='\0';

	FILE *F;
	char cadena[50];
	int contador=0;

	if((F=fopen(fichero,"r"))==NULL){

		printf("Error al abrir el archivo %s\n",fichero);
		exit(-1);

	}

	while ((fgets(cadena,50,F))!=NULL){

		if(cadena[strlen(cadena)-1]=='\n'){

			cadena[strlen(cadena)-1]='\0';

		}

		if(strlen(libro.titulo)==strlen(cadena)){

			if(strstr(libro.titulo,cadena)!=NULL){

				contador=contador+1;

			}

		}

	}

	if(contador>0){printf("El libro %s se ha encontrado %i\n", libro.titulo, contador);}
	else{printf("El libro %s no se ha encontrado\n", libro.titulo);}

}