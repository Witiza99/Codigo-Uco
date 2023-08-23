#ifndef FUNC_H
#define FUNC_H

int **reservamemoria(int fil,int col);
void rellenamatriz(int **m,int fil,int col);
void imprimirmatriz(int **m, int fil, int col);
void liberamemoria(int ***m, int col);

#endif