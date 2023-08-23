#ifndef FUNC_H
#define FUNC_H

int *reservamemoria(int cantidad);
void rellenamemoria(int *v,int cantidad);
void liberamemoria(int **v);
void imprimememoria(int *v,int cantidad);
void ordena(int *v,int cantidad,int (*comparacion)(int, int));
int es_mayor(int a, int b);
int es_menor(int a, int b);

#endif