#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include <string.h>

void Listarnuemrosalmacenados(char fichero[50]){

	FILE *f;
	int Cantidad;
	struct libros *libro=NULL;
	char cadena[50];

	if((f=fopen(fichero,"r"))==NULL){

		printf("Error al abrir el archivo %s\n",fichero);
		exit(-1);

	}

	Cantidad=contarlibrosdiferentes(fichero);

	libro=reserva_vector_dinamico(Cantidad);

	int i=0;

	while ((fgets(cadena,50,f))!=NULL){

		if(cadena[strlen(cadena)-1]=='\n'){

			cadena[strlen(cadena)-1]='\0';

		}

		strcpy(libro[i].titulo,cadena);

		if((fgets(cadena,50,f))!=NULL){

			if(cadena[strlen(cadena)-1]=='\n'){

				cadena[strlen(cadena)-1]='\0';

			}

		}

		strcpy(libro[i].autor,cadena);

		fscanf(f,"%f %d",&(libro[i].precio),&(libro[i].unidades));

		i++;

	}

	for(int i=0; i<sizeof(libro);i++){

		printf("%s\n", libro[i].titulo);
		printf("%s\n", libro[i].autor);
		printf("%f %d\n", libro[i].precio,libro[i].unidades);
		
	}

	free(libro);
	fclose(f);

}
