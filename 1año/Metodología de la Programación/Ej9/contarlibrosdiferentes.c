#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contarlibrosdiferentes(char fichero[50]){
	
	FILE *F;
	char cadena[50];
	int contador=0;

	if((F=fopen(fichero,"r"))==NULL){

		printf("Error al abrir el archivo %s\n",fichero);
		exit(-1);

	}

	while ((fgets(cadena,50,F))!=NULL){

		if((fgets(cadena,50,F))!=NULL){

			if((fgets(cadena,50,F))!=NULL){

				contador++;

			}

		}

	}

	fclose(F);
	return contador;

}