#ifndef PARTE_PRACTICA1_FUNCIONES_HPP
#define PARTE_PRACTICA1_FUNCIONES_HPP

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include "ClaseTiempo.cpp"
#include "sistemaEcuaciones.hpp"
#include "funciones.h"

using namespace std;

void ajustefactorialN(const vector <int> &n, const vector <double> &tiemposReales, double &a0, double &a1);

//calculo los tiempos estimados
void calcularTiemposEstimadosfactorialN(const vector <int> &n, double &a0, double &a1, vector <double> &tiemposEstimados);

//vuelco la información en ficheros
void volcarTiemposFicheros(const vector <int> &n, const vector <double> &tiemposReales, const vector <double> &tiemposEstimados);

double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales,const vector <double> &tiemposEstimados);

void calculoTiempoEstimado(const double &a0, const double &a1);

double calcularTiemposEstimadosfactorialN(const double &N, const double &a0, const double &a1);

void extraccion_datos(int &min, int &max, int &incremento, vector <double> &tiemposReales, vector <int> &n);

void mostrar_grafica();

#endif