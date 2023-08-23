	#ifndef FUNC_H
	#define FUNC_H


struct libros{

	char titulo[50];
	char autor[50];
	float precio;
	int cantidad;

};

struct libros *reservarmemoria(int cantidad);
int *reservav(int cantidad);

#endif