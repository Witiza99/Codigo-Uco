#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int buscarelemento(struct lista *cabeza,int n){

	int contador=0;

	struct lista *aux=NULL;

	aux=cabeza;

	while((aux!=NULL)&&(contador==0)){

		if(aux->n==n){

			contador=1;

		}

		aux=aux->sig;

	}

	return contador;

}

struct lista *reservamemoria(){

	struct lista *nuevo=NULL;

	if((nuevo=(struct lista*)malloc(sizeof(struct lista)))==NULL){

		printf("Error al reservar memoria\n");
		exit(-1);

	}

	return nuevo;

}

void insertardelante(struct lista **cabeza,int n){

	struct lista *nuevo=NULL;

	nuevo=reservamemoria();

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

void borrarelemento(struct lista **cabeza, int n){

	struct lista *ant=NULL;
	struct lista *aux=NULL;

	aux=*cabeza;

	while(aux->n!=n){

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

		sig=aux->sig;
		free(aux);
		aux=sig;

	}

	*cabeza=NULL;

}

void insertarordenrecursivo(struct lista **cabeza, int n){

	if(((*cabeza)==NULL)||((*cabeza)->n>n)){

		struct lista *nuevo=NULL;

		nuevo=reservamemoria();

		nuevo->n=n;
		nuevo->sig=*cabeza;
		*cabeza=nuevo;

	}

	else{

		insertarordenrecursivo(&((*cabeza)->sig),n);

	}

}

