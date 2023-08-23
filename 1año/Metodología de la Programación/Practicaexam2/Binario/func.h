#ifndef FUNC_H
#define FUNC_H

struct libros{

	char titulo[50];
	char autor[50];
	float precio;
	int cantidad;

};

int contarlibrosdiferentes(char fichero[50]);
int buscarlibro(char fichero[50],char libropedido[50]);
void nuevolibro(char fichero[50]);
void listarlibros(char fichero [50]);
struct libros *reservarmemoria(int contador);
void rellenarvector(char fichero [50],struct libros *v);
void imprimirvector(struct libros *v,int contador);
void venderlibro(char fichero[50]);
void borrarregistros(char fichero[50]);

#endif