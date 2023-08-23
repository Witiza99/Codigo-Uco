#include <stdio.h>
#include <stdlib.h>
#include "fucn.h"
#include <string.h>
#include <time.h>
#include <ctype.h>


int *reservamemorianumeros(int cantidad){

	int *v=NULL;

	if((v=(int*)malloc(cantidad*sizeof(int)))==NULL){

		printf("Error al reservar memoria\n");

	}

	return v;

}


struct libros *reservamemoriaestructuras(int cantidad2){

	struct libros *libro=NULL;
	
	if((libro=(struct libros*)malloc(cantidad2*sizeof(struct libros)))==NULL){

		printf("Error al reservar memoria\n");

	}

	return libro;

}


void rellena(int *v, int cantidad){

	srand(time(NULL));

	for(int i=0;i<cantidad;i++){

		v[i]=(rand()%11);

	}

}

void rellenaestructuras(struct libros *libro, int cantidad2){

	for(int i=0;i<cantidad2;i++){

		printf("Introduce titulo:\n");
		setbuf(stdin,NULL);
		fgets(libro[i].titulo,50,stdin);

		if((libro[i].titulo[sizeof(libro[i].titulo)-1])=='\n'){

			libro[i].titulo[sizeof(libro[i].titulo)-1]='\0';

		}

		libro[i].titulo[0]=toupper(libro[i].titulo[0]);

		printf("Introduce autor:\n");
		setbuf(stdin,NULL);
		fgets(libro[i].autor,50,stdin);

		if((libro[i].autor[sizeof(libro[i].autor)-1])=='\n'){

			libro[i].autor[sizeof(libro[i].autor)-1]='\0';

		}

		libro[i].autor[0]=toupper(libro[i].autor[0]);

		printf("Introduce la cantidad\n");
		scanf("%d",&libro[i].cantidad);

	}

}

void imprimenumeros(int *v, int cantidad){

	for(int i=0;i<cantidad;i++){

		printf("%d\n",v[i]);

	}

}

void imprimeestructuras(struct libros *libro, int cantidad2){

	for(int i=0;i<cantidad2;i++){

		printf("%s",libro[i].titulo);
		printf("%s",libro[i].autor);
		printf("%d\n",libro[i].cantidad);

	}

}

int comparaEnteros(const void* e1 , const void* e2){

  int* a, *b;

  a = (int*)e1;
  b = (int*)e2;

  if(*a<*b)

    return (-1);

  else if(*a==*b)

    return(0);

  else

    return(1);

}

int comparaEstructuras(const void *e1 , const void *e2)
{
  struct libros *a, *b;

  a = (struct libros*)e1;
  b = (struct libros*)e2;

  if(a->cantidad<b->cantidad)

    return (-1);

  else if(a->cantidad==b->cantidad)

    return(0);

  else

    return(1);  
  	
}

int comparasegunnombre(const void *e1, const void *e2){

	struct libros *a, *b;

	a=((struct libros*)e1);
	b=((struct libros*)e2);

	if(strcmp(a->autor, b->autor)<0)

		return -1;

		if(strcmp(a->autor, b->autor)==0)

			return 0;

		else

			return 1;

}

int comparatitulos(const void *e1, const void *e2){

	struct libros *a, *b;

	a=(struct libros*)e1;
	b=(struct libros*)e2;

	if(strcmp(a->titulo,b->titulo)<0)

		return (-1);

	else if(strcmp(a->titulo,b->titulo)==0)

		return 0;

	else 

		return 1;

}