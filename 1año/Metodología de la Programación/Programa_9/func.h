#ifndef FUNC_H
#define FUNC_H

struct libros{
char titulo[50];//titulo del libro
char autor[50];//nombre del autor
float precio;//precio del libro
int unidades;//numero de unidades
};

void existe_libro(char fichero[50]);
int contarlibrosdiferentes(char fichero[50]);
void introducir_nuevo(char fichero[50]);
void Listarlibros(char fichero[50]);
struct libros *reservarmemoria(int cantidad);
void rellenavector(struct libros *v, char fichero[100]);
void imprimevector(struct libros *v, int cantidad);
void venderlibro(char fichero[50]);
void borrarlibros(char fichero[50]);

#endif