#include <stdio.h>
#include <stdlib.h>
#include "func.h"

struct libros *reserva_vector_dinamico(int cantidad){

struct libros *libro=NULL;

if((libro=(struct libros*)malloc(cantidad*sizeof(struct libros)))==NULL){

	printf("No se pudo reservar\n");
	exit(-1);
}

return libro;

}