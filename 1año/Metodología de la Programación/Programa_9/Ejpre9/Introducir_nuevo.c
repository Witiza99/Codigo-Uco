#include <stdio.h>
#include <stdlib.h>
#include "func.h"

void introducir_nuevo(char fichero[50]){

	struct libros libro;

	FILE *F;

	if((F=fopen(fichero,"a"))==NULL){

		printf("Error al abrir el archivo %s\n",fichero);
		exit(-1);

	}

	libro=rellena_structura( );

	fprintf(F,"%s\n%s\n%f %d\n",libro.titulo,libro.autor,libro.precio,libro.unidades);

	fclose(F);

}

