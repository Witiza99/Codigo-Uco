/*
 * RPOTabuSearch.cpp
 *
 * Fichero que define las funciones de la clase RPOTabuSearch. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 */

#include <RPOEvaluator.h>
#include <RPOObjectAssignmentOperation.h>
#include <RPOTabuSearch.h>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <RPOLocalSearch.h>


using namespace std;

void RPOTabuSearch::initialise(RPOInstance* instance, unsigned tabuTennure) {
	_instance = instance;
	_tabuTennure = tabuTennure;
}

void RPOTabuSearch::setSolution(RPOSolution* solution) {

	if (_solution != NULL){
		cerr << "No se debe invocar más de una vez el método RPOTabuSearch::setSolution" << endl;
		exit(1);
	}

	this->_solution = solution;

	if (_bestSolution == NULL) {
		_bestSolution = new RPOSolution(*_instance);
	}

	_bestSolution->copy(*solution);
}

void RPOTabuSearch::run(RPOStopCondition& stopCondition) {
	if (_solution == NULL) {
		cerr << "Tabu search has not been given an initial solution" << endl;
		exit(-1);
	}

	_results.clear();
	unsigned numIterations = 0;

	/**
	 * TODO
	 * Mientras no se alcance la condición de parada
	 *  1. Generar una permutación de objetos
	 *  2. Buscar la mejor operación no tabú de asignación de un objeto a una mochila (incluida la 0)
	 *  3. Aplicar la operación
	 *  4. Insertar el índice del objeto afectado en la memoria tabú
	 *  5. Actualizar la mejor solución hasta el momento
	 */

	while (!stopCondition.reached()) {

		double *vec;
		double aux[_instance->getNDims()];
		for (size_t i = 0; i < _instance->getNDims(); i++) {
			aux[i] = _solution->getSol()[i];
		}
		RPOLocalSearch::randomVectorSphere(*_instance, &vec, aux);
		double bestDeltaFitness = 0;
		double oldValue;
		unsigned bestIndex;
		bool initialisedDeltaFitness = false;
		RPOObjectAssignmentOperation bestOperation;

		//Buscar la mejor operación no tabú
		for (unsigned i = 0; i < _instance->getNDims(); i++) {
			unsigned index = i;

			//Si el objeto no es tabú (utilizar _shortTermMem_aux.find)
			if (_shortTermMem_aux.find(index) == _shortTermMem_aux.end()) {
				//Obtener la diferencia de fitness de aplicar dicha operación
				if (i>0) {
					aux[i-1] = oldValue;
				}
				oldValue = aux[i];
				aux[i] = vec[i];
				double deltaFitness = RPOEvaluator::computeDeltaFitness(*_instance, *_solution, aux);
				std::cerr << "deltaFitness= " <<deltaFitness<< '\n';
				//Si la diferencia de fitness es la mejor hasta el momento, apuntarla para aplicarla después
				if (deltaFitness > bestDeltaFitness) {
					initialisedDeltaFitness = true;
					bestDeltaFitness = deltaFitness;
					bestOperation.setValues(aux, deltaFitness);
					bestIndex = i;
				}
			}
		}

		//TODO Aplicar la operación y almacenarla en la memoria a corto plazo
		bestOperation.apply(*_solution);
		_shortTermMem.push(bestIndex);
		_shortTermMem_aux.emplace(bestIndex);


		//TODO Si hay demasiados elementos en la memoria, según la tenencia tabú, eliminar el más antiguo
		if (_shortTermMem.size() > _tabuTennure) {
			unsigned value = _shortTermMem.front();
			_shortTermMem.pop();
			_shortTermMem_aux.erase(value);
		}

		//Actualizar la mejor solución

		if (RPOEvaluator::compare(_solution->getFitness(), _bestSolution->getFitness()) > 0) {
			_bestSolution->copy(*_solution);
		}

		numIterations++;
		_results.push_back(_solution->getFitness());

		stopCondition.notifyIteration();
	}
}
