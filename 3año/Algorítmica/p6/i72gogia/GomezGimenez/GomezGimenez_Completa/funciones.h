#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "backtracking.h"
#include "vegas.h"
#include "parte_practica1_funciones.hpp"
#include <vector>

using namespace std;

void funcionIntermediaBacktracking(bool mostrar, int n, vector<vector<int>> &soluciones);

void funcionIntermediaVegas(bool mostrar, int n, vector<vector<int>> &soluciones);

void parte_practica1(int min, int max, int incremento);

bool lugar(int k, vector<int>columnas);

void mostrar_resultado(vector<vector<int>> &soluciones);

#endif