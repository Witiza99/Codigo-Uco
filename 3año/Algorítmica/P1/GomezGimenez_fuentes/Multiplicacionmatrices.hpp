#ifndef MULTIPLICACIONMATRICES_HPP
#define MULTIPLICACIONMATRICES_HPP

#include <vector>
#include <ctime>
#include <cstdlib>
#include "sistemaEcuaciones.hpp"
#include <fstream>
#include <cassert>
#include <cmath>
#include "Quicksort.hpp"

#define REPM 1

using namespace std;

void rellenarMatriz(vector<vector <double> > &v);
void ajustePolinomico(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a);
double sumatorio(const vector <double> &n, int valor);
void calcularTiemposEstimadosPolinomico(const vector <double> &n, vector <double> &tiemposEstimados,const vector <double> &a);
double calcularTiempoEstimadoPolinomico(const double &n, const vector <double> &a);
void Parte2();

#endif