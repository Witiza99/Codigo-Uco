#ifndef FUNC_H
#define FUNC_H

struct lista{

	int n;
	struct lista *sig;

};

int buscarelemento(struct lista *cabeza,int n);
void insertardelante(struct lista **cabeza,int n);
struct lista *reservamemoria();
void imprimirlista(struct lista *cabeza);
void imprimirlistainversa(struct lista *cabeza);
void borrarelemento(struct lista **cabeza, int n);
void borrarlista(struct lista **cabeza);
void insertarordenrecursivo(struct lista **cabeza, int n);

#endif