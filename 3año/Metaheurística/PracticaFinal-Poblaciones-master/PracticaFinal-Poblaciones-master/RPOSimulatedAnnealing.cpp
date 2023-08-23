/*
 * RPOSimulatedAnnealing.cpp
 *
 * Fichero que define las funciones de la clase RPOSimulatedAnnealing. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include "RPOSimulatedAnnealing.h"
#include "RPOSolution.h"
#include "RPOSolGenerator.h"
#include <RPOEvaluator.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <RPOLocalSearch.h>

using namespace std;

void RPOSimulatedAnnealing::setSolution(RPOSolution* solution) {
	if (_T <= 0 || _annealingFactor <= 0){
		cerr << "Simulated annealing has not been initialised" << endl;
		exit(-1);
	}

	if (_solution != NULL){
		cerr << "No se debe invocar más de una vez el método RPOTabuSearch::setSolution" << endl;
		exit(1);
	}

	this->_solution = solution;

	if (_bestSolution == NULL){
		_bestSolution = new RPOSolution(*_instance);
	}

	_bestSolution->copy(*solution);
}

void RPOSimulatedAnnealing::run(RPOStopCondition& stopCondition) {

	if (_T <= 0 || _annealingFactor <= 0){
		cerr << "Simulated annealing has not been initialised" << endl;
		exit(-1);
	}

	if (_solution == NULL){
		cerr << "Simulated annealing has not been given an initial solution" << endl;
		exit(-1);
	}

	_results.clear();
	double *vec;
	double *aux = _solution->getSol();
	unsigned numIterations = 0;

	/**
	 * TODO
	 * Mientras que no se alcance la condición de parada
	 *   1. Generar aleatoriamente un objeto y una mochila (incluida la mochila 0)
	 *   2. Calcular la diferencia en fitness de aplicar dicho cambio sobre _solution
	 *   3. Consultar si se acepta el cambio
	 *   4. Actualizar la mejor solución hasta el momento.
	 *   5. Si se llevan _itsPerAnnealing tras el último enfriamiento, entonces enfriar
	 */
	while (!stopCondition.reached()){
		RPOLocalSearch::randomVectorSphere(*_instance, &vec, aux);
		double deltaFitness = RPOEvaluator::computeDeltaFitness(*_instance, *_solution, vec);

		if (accept(deltaFitness)){
			_solution->setSol(vec);
			_solution->setFitness(_solution->getFitness() + deltaFitness);

			if (RPOEvaluator::compare(_solution->getFitness(), _bestSolution->getFitness()) > 0){
				_bestSolution->copy(*_solution);
			}
		}
		numIterations++;
		_results.push_back(_solution->getFitness());

		if (numIterations % _itsPerAnnealing != 0){
			_T *= _annealingFactor;
		}

		stopCondition.notifyIteration();
	}
}
//#include <iostream>
bool RPOSimulatedAnnealing::accept(double deltaFitness) {
	/**
	 * TODO
	 * .Calcular la probabilidad de aceptar el cambio, que será la exponencial de (la diferencia de fitness dividido por la temperatura)
	 *
	 * .Si el problema es de minimización, entonces un delta fitness negativo es bueno. Hay que modificar "un poco" la función de aceptación para producir una probabilidad de aceptación superior a 1
	 *
	 * .Generar un aleatorio entre 0 y 1
	 * .Devolver true si el aleatorio es inferior a la probabilidad de aceptación.
	 *
	 * (piensa qué ocurre cuando la diferencia de fitness es positiva o cuando es negativa)
	 */
	double auxDeltaFitness = deltaFitness;

	if (RPOEvaluator::isToBeMinimised()){
		//para que la probabilidad salga positiva
		auxDeltaFitness*=-1;
	}

	double prob = exp(auxDeltaFitness/this->_T);
	double randSample = (((double)rand()) / RAND_MAX);
	//std::cerr << "prob= " <<prob<<", randSample="<<randSample<< '\n';
	if (randSample<prob) {
		return true;
	}
	return false;
}

void RPOSimulatedAnnealing::initialise(double initialProb, int numInitialEstimates, double annealingFactor, unsigned itsPerAnnealing, RPOInstance &instance) {
	_initialProb = initialProb;
	_annealingFactor = annealingFactor;
	_instance = &instance;
	_itsPerAnnealing = itsPerAnnealing;
	double averageFDiffs = 0.;

	/**
	 * Inicialización de la temperatura.
	 * Para ello, se generan una serie de soluciones iniciales y de vecinos. Se calcula la diferencia media de fitness hacia peores soluciones y se despeja la temperatura de la función de aceptación
	 */

	for (int i = 0; i < numInitialEstimates; i++){
		RPOSolution sol(instance);
		RPOSolGenerator::genRandomSol(instance, sol);
		sol.setFitness(RPOEvaluator::computeFitness(instance, sol));
		double *vec = RPOInstance::generateRandomVector(*_instance);
		double deltaFitness = RPOEvaluator::computeDeltaFitness(instance, sol, vec);
		averageFDiffs += max(fabs(deltaFitness),10.); //He puesto una diferencia mínima de 10 para evitar cambios en el fitness demasiado pequeños (por ejemplo, cuando se modifica una mochila que no es la de la máxima violación (este método se podría mejorar)
	}

	averageFDiffs /= numInitialEstimates;

	_T = -1. * averageFDiffs / log(initialProb);
}
