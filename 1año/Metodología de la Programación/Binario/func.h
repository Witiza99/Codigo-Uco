#ifndef FUNC_H
#define FUNC_H

struct libros{

	char titulo[50];
	char autor[50];
	float precio;
	int cantidad;

};

int librosdiferentes(char fichero[50]);

void buscarlibro(char fichero[50]);

void nuevolibro(char fichero[50]);

void listarlibros(char fichero[50]);

struct libros *reservarmemoria(int cantidad);

void rellenarmemoria(struct libros *v,char fichero[50]);

void imprimirmemoria(struct libros *v,int cantidad);

void venderunlibro(char fichero[50]);

void borrarregistros(char fichero[50]);


#endif