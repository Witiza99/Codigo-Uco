#ifndef FUNC_H
#define FUNC_H

struct libros{

	char titulo[100];
	char autor[100];
	float precio;
	int cantidad;

};

int contarlibrosdiferentes(char fichero[50]);
void nuevolibro(char fichero[50]);
int buscarlibro(char fichero[50]);



#endif