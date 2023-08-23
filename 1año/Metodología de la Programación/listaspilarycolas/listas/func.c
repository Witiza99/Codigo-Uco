#include <stdio.h>
#include <stdlib.h>
#include "func.h"

struct lista *reservaelemento(){

	struct lista *v=NULL;

	if((v=(struct lista*)malloc(sizeof(struct lista)))==NULL){

		printf("Error al abrir el archivo\n");

	}

	return v;

}

int buscarelemento(struct lista *cabeza, int n){

	int encontrado=0;
	struct lista *aux=NULL;
	aux=cabeza;

	while((aux!=NULL)&&(encontrado==0)){

		if(aux->n==n){

			encontrado=1;

		}

		else{

			aux=aux->sig;

		}

	}

	return encontrado;

}

void insertarpordelante(struct lista **cabeza, int n){

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

void imprimirlistainversa(struct lista *elemento){

	if(elemento!=NULL){

		imprimirlistainversa(elemento->sig);
		printf("%d\n",elemento->n);

	}

}

void borrarelemento(struct lista **cabeza,int n){

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

	}

	else{

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

	if((*cabeza==NULL)||((*cabeza)->n>n)){

		struct lista *nuevo=NULL;

		nuevo=reservaelemento();

		nuevo->n=n;
		nuevo->sig=(*cabeza);
		*cabeza=nuevo;

	}

	else{

		insertarordenrecursivo(&((*cabeza)->sig), n);

	}

}
