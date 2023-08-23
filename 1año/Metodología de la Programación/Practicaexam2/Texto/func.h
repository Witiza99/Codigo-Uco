#ifndef FUNC_H
#define FUNC_H

struct libros{

	char titulo[50];
	char autor[50];
	float precio;
	int cantidad;
};

int contarlibros(char fichero[50]);
void nuevolibro(char fichero[50]);
int buscarlibro(char fichero[50],char busqueda[50]);
void listarlibros(char fichero[50]);
struct libros *reservarmemoria(int *cantidad);
void rellenarmemoria(char fichero[50],struct libros *v);
void imprimirmemoria(struct libros *v,int cantidad);
void venderlibro(char fichero[50],char busqueda[50]);
void borrarregistros(char fichero[50]);

#endif