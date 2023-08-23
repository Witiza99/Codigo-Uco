#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

struct libros rellena_structura( ){

	struct libros libro;

	printf("Introduce el nombre del libro:\n");
	setbuf(stdin,NULL);
	fgets(libro.titulo,50,stdin);
	libro.titulo[strlen(libro.titulo)-1]='\0';


	printf("Introduce el nombre del autor:\n");
	setbuf(stdin,NULL);
	fgets(libro.autor,50,stdin);
	libro.autor[strlen(libro.autor)-1]='\0';


	printf("Introduce el valor del libro:\n");
	scanf("%f",&libro.precio);

	printf("Introduce la cantidad de libros que hay:\n");
	scanf("%d",&libro.unidades);

return libro;

}
