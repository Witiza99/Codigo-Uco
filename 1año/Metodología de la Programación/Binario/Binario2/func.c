#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include <string.h>

int contarlibrosdiferentes(char fichero[50]){

	FILE *F;
	int contador=0;

	if((F=fopen(fichero,"rb"))==NULL){

		printf("Error al abrir el fichero\n");
		exit(-1);

	}

	fseek(F,0L,SEEK_END);

	contador=ftell(F)/sizeof(struct libros);

	fclose(F);

	return contador;

}

void nuevolibro(char fichero[50]){

	FILE *F;
	struct libros libro;

	if((F=fopen(fichero,"a+b"))==NULL){

		printf("Error al abrir el fichero\n");
		exit(-1);

	}

	fseek(F,0L,SEEK_END);

	printf("Introduce el titulo\n");
	setbuf(stdin,NULL);
	fgets(libro.titulo,100,stdin);

	if(libro.titulo[strlen(libro.titulo)-1]=='\n'){

		libro.titulo[strlen(libro.autor)-1]='\0';
	}

	printf("Introduce el autor\n");
	scanf("%s",libro.autor);

	printf("Introduce el precio\n");
	scanf("%f",&libro.precio);

	printf("Introduce la cantidad\n");
	scanf("%d",&libro.cantidad);

	fwrite(&libro,sizeof(struct libros),1,F);

	fclose(F);

}

int buscarlibro(char fichero[50]){

	FILE *F;
	int contador=0;
	struct libros libro;
	char busqueda[100];

	if((F=fopen(fichero,"rb"))==NULL){

		printf("Error al abrir el fichero\n");
		exit(-1);

	}

	printf("Introduce el libro que deseeas ver si esta\n");
	setbuf(stdin,NULL);
	fgets(busqueda,100,stdin);

	if(busqueda[strlen(busqueda)-1]=='\n'){

		busqueda[strlen(busqueda)-1]='\0';
	}

	fseek(F,0L,SEEK_SET);

	while((fread(&libro,sizeof(struct libros),1,F)==1)&&(contador==0)){

		if(strcmp(busqueda,libro.titulo)==0){

			if((strstr(busqueda,libro.titulo))!=NULL){

				contador++;

			}

		}

	}

	fclose(F);

	return contador;

}
