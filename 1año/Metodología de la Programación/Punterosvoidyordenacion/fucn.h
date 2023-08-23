#ifndef FUCN_H
#define FUCN_H

struct libros{
	char titulo[50];
	char autor[50];
	int cantidad;
};

int *reservamemorianumeros(int cantidad);
struct libros *reservamemoriaestructuras(int cantidad2);
void rellena(int *v,int cantidad);
void rellenaestructuras(struct libros *libro, int cantidad2);
int comparaEnteros(const void* e1 , const void* e2);	
int comparaEstructuras(const void* e1 , const void* e2);
void imprimenumeros(int *v,int cantidad);
void imprimeestructuras(struct libros *libro, int cantidad2);
int comparasegunnombre(const void *e1, const void* e2);
int comparatitulos(const void* e1, const void *e2);

#endif