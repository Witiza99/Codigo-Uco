#ifndef FUNC_H
#define FUNC_H

struct lista{

	int n;
	struct lista *sig;

};

struct lista *reservaelemento();
void insertarpordelante(struct lista **cabeza,int *n);
void imprimirlista();
void imprimirlistainversa();
int buscarelemento(struct lista *cabeza, int *n);
void borrarelemento(struct lista **cabeza, int *n);
void borrarlista(struct lista **cabeza);
//void ordenarlista(struct lista *cabeza);//muy laborioso
void insertarordenrecursivo();
#endif