/*
 * MQKPSolution.cpp
 *
 * Fichero que define los métodos de la clase MQKPSolution. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */


#include "include/MQKPSolution.h"
#include "include/MQKPInstance.h"

MQKPSolution::MQKPSolution(MQKPInstance &instance) {
	_sol.resize(instance.getNumObjs());
	_numObjs = instance.getNumObjs();
	_fitness = 0;
}

MQKPSolution::~MQKPSolution() {
	_sol.clear();
}

void MQKPSolution::putObjectIn(int object, int knapsack){
	_sol[object]=knapsack;
}

int MQKPSolution::whereIsObject(int object){
	if (object>_numObjs or object<0) {
		return -1;
	}
	return _sol[object];
}
