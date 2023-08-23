#include <stdio.h>
#include <stdlib.h>
#include "func.h"


struct lista *reservaelemento(){

	struct lista *nuevo=NULL;

	if((nuevo=(struct lista*)malloc(sizeof(struct lista)))==NULL){

		printf("Error al abrir el archivo\n");
		exit(-1);

	}

	return nuevo;

}
void insertarpordelante(struct lista **cabeza,int *n){

	struct lista *nuevo=NULL;

	nuevo=reservaelemento();

	nuevo->n=n;
	nuevo->sig=*cabeza;
	*cabeza=nuevo;

}
void imprimirlista(struct lista *cabeza){

	struct lista *aux=NULL;

	aux=cabeza;

	while(aux!=NULL){

		printf("%d\n",aux->n);

		aux=aux->sig;

	}
}

void imprimirlistainversa(struct lista *cabeza){

	if(cabeza!=NULL){

		imprimirlistainversa(cabeza->sig);
		printf("%d\n",cabeza->n);

	}

}

int buscarelemento(struct lista *cabeza, int *n){

	int encontrado=0;
	struct lista *aux=NULL;
	aux=cabeza;

	while((aux!=NULL)&&(encontrado==0)){

		if((aux->n)==(*n)){

			encontrado++;

		}else{

			aux=aux->sig;

		}

	}

	return encontrado;

}
void borrarelemento(struct lista **cabeza, int *n){

	struct lista *aux=NULL;
	struct lista *ant=NULL;

	aux=*cabeza

	while(aux->n!=(*n)){

		ant=aux;
		aux=aux->sig;

	}

	if(aux==*cabeza){

		*cabeza=aux->sig;
		free(aux);

	}else{

		ant->sig=aux->sig;
		free(aux);

	}

}
void borrarlista(struct lista **cabeza){

	struct lista *aux=NULL;
	struct lista *sig=NULL;
	aux=*cabeza;

	while(aux!=NULL){

		sig=aux->sig
		free(aux);
		aux=sig;

	}

	*cabeza=NULL;

}

void insertarordenrecursivo(struct lista **cabeza, int *n){

	if((*cabeza!=NULL)||(*cabeza->n>(*n))){

		struct lista *nuevo=NULL;

		nuevo=nuevoelemento();

		nuevo->n=n;
		nuevo->sig=*cabeza;
		*cabeza=nuevo;


	}else{insertarordenrecursivo(&((*cabeza)->sig),&n)}

}