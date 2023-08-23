#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include <vector>
#include <ctime>
#include <cstdlib>
#include "sistemaEcuaciones.hpp"
#include <fstream>
#include <cassert>
#include <cmath>

#define REP 5

using namespace std;

void rellenarVector(vector <float> &v);
void estaOrdenado(const vector <float> &v);
void quicksort(int izq, int der, vector <float> &v );
void ajusteNlogN(const vector <double> &n, const vector <double> &tiemposReales, double &a0, double &a1);
void calcularTiemposEstimadosNlogN(const vector <double> &n, const double &a0, const double &a1, vector <double> &tiemposEstimados);
double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales,const vector <double> &tiemposEstimados);
double calcularTiempoEstimadoNlogN(const double &n, const double &a0, const double &a1);
void Parte1();

#endif