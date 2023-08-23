/*
 * MQKPInstance.cpp
 *
 * Fichero que define los métodos de la clase MQKPInstance. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */


#include "include/MQKPSolution.h"
#include "include/MQKPInstance.h"
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <iostream>

MQKPInstance::MQKPInstance() {
	_numKnapsacks = 0;
	_numObjs = 0;
}

MQKPInstance::~MQKPInstance() {
	_profits.clear();
	_weights.clear();
	_capacities.clear();
}

double MQKPInstance::getMaxCapacityViolation(MQKPSolution &solution) {

	double *sumWeights = new double[this->_numKnapsacks + 1];

	for (int j = 1; j <= this->_numKnapsacks; j++) {
		sumWeights[j] = 0;
	}

	for (int i = 0; i < this->_numObjs; i++) {


		 int mochila = solution.whereIsObject(i);
		 if (mochila>0) {
		 	sumWeights[mochila] += _weights[i];
		 }

	}

	double maxCapacityViolation = 0; //Inicializamos la máxima violación de alguna mochila a 0, que significa que no hay ninguna violación

	for (int j = 1; j <= this->_numKnapsacks; j++) {


		 if ((sumWeights[j]-_capacities[j-1])>maxCapacityViolation) {
		 	maxCapacityViolation = sumWeights[j]-_capacities[j-1];
		 }
	}

	delete[] sumWeights;
	return maxCapacityViolation;
}

double MQKPInstance::getSumProfits(MQKPSolution &solution) {

	double sumProfits = 0.;


	 for (int i = 0; i < (int)_profits.size(); i++) {
		 if(solution.whereIsObject(i)>0){
			 sumProfits += _profits[i][i];
		 }
	 	for (int j = i+1; j < (int)_profits[i].size(); j++) {
	 		if (solution.whereIsObject(i) == solution.whereIsObject(j)) {
				sumProfits += _profits[i][j];
	 		}
	 	}
	 }

	return sumProfits;
}

void MQKPInstance::readInstance(char *filename, int numKnapsacks) {

	_numKnapsacks=numKnapsacks;
	ifstream in;
	in.open(filename);

	int numObjetos = 0,cont=0,line=0,col=1;
	char aux[1000];
	vector<double> individualProfits;
	while(in.getline(aux,1000)){
		if(cont == 1){
			numObjetos = atoi(aux);
			_numObjs=numObjetos;
			_profits.resize(numObjetos,vector<double>(numObjetos));//reserva de matriz
			_weights.resize(numObjetos);//reserva de pesos
			_capacities.resize(numObjetos);//reserva de capacidades
		}

		if (cont == 2) {
			char *tk;
			tk = strtok(aux," ");
			while(tk != NULL){
				individualProfits.push_back(atoi(tk));
				tk = strtok(NULL," ");
			}
		}

		//lee los valores de la matriz triangular
		if((cont >= 3) and (cont <= (numObjetos+2))){
			//leo la linea y los separo por espacio en blanco
			char *tk;
			tk = strtok(aux," ");
			_profits[line][line]=individualProfits[line];
			while(tk != NULL){
				_profits[line][col] = atoi(tk);
				col++;
				tk = strtok(NULL," ");
			}
			line++;
			col=line+1;
		}else if(cont == numObjetos+6){
			char *tk;
			tk = strtok(aux," ");
			while(tk != NULL){
				_weights.push_back(atof(tk));
				tk = strtok(NULL," ");
			}
		}
		cont++;
	}
	in.close();
	double suma=0;
	for(int i = 0; i<(int)_weights.size(); i++){
		suma += _weights[i];
	}
	suma *= 0.8;
	suma /=_numKnapsacks;
	for(int i = 0; i<(int)_capacities.size(); i++){
		_capacities[i] = suma;
	}
}
