/*
 * RPOIteratedGreedy.cpp
 *
 * Fichero que define las funciones de la clase RPOIteratedGreedy. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <RPOIteratedGreedy.h>
#include <RPOObjectAssignmentOperation.h>
#include <RPOSolution.h>
#include <RPOLocalSearch.h>
#include <iostream>

using namespace std;

void RPOIteratedGreedy::chooseOperation(RPOObjectAssignmentOperation& operation) {

	double *vec;
	double *sphereVec;
	double *bestVec;
	double bestDensity;
	double bestDeltaFitness;
	bool initialisedBestDensity = false;

	vec = _sol->getSol();
	_oldSol = vec;
	RPOLocalSearch::randomVectorSphere(*_instance, &sphereVec, vec);

	for (unsigned i = 0; i < _instance->getNDims() ; i++) {
		vec[i] = sphereVec[i];

		double deltaFitness = RPOEvaluator::computeDeltaFitness(*_instance, *_sol, vec); //TODO obtener la mejora en fitness de dicha operación
		//?
		double density = deltaFitness/1; //TODO calcular la densidad

		//TODO actualizar si resulta ser la mejor
		if (density > bestDensity || initialisedBestDensity == false) {
			initialisedBestDensity = true;
			bestVec = vec;
			bestDeltaFitness = deltaFitness;
		}
	}

	operation.setValues(bestVec,	bestDeltaFitness);
}

void RPOIteratedGreedy::rebuild() {

	/** Seleccionar la primera operación */
	RPOObjectAssignmentOperation operation;
	chooseOperation(operation);

	/** TODO
	 * Mientras la operación tenga un incremento de fitness positivo, operation.getDeltaFitness(),
	 *  1. aplicar la operación en _sol
	 *  2. Almacenar el fitness de la solución en _result (para las gráficas)
	 *  3. seleccionar una nueva operación
	 */
	while (operation.getDeltaFitness() > 0) {
		operation.apply(*_sol);
		_results.push_back(_sol->getFitness());
		chooseOperation(operation);
	}
}

void RPOIteratedGreedy::destroy() {

	/**
	 * TODO
	 * Recorrer los objetos y sacarlos de su mochila con probabilidad _alpha
	 */
	double *vec = _sol->getSol();

	unsigned nDims = _instance->getNDims();

	for (unsigned i = 0; i < nDims; i++){

		double randSample = (((double)rand()) / RAND_MAX);

	if (randSample<_alpha){
			vec[i] = _oldSol[i];
		}
	}
	_sol->setSol(vec);
	double fitness = RPOEvaluator::computeFitness(*_instance, *_sol);
	_sol->setFitness(fitness);
	_results.push_back(_sol->getFitness());
}

void RPOIteratedGreedy::initialise(double alpha, RPOInstance& instance) {
	_sol = new RPOSolution(instance);
	_bestSolution = new RPOSolution(instance);
	_bestSolution->copy(*_sol);
	_instance = &instance;
	_alpha = alpha;
}

void RPOIteratedGreedy::run(RPOStopCondition& stopCondition) {

	if (_sol == NULL) {
		cerr << "IG was not initialised" << endl;
		exit(-1);
	}

	/** Crear la primera solución */
	std::cerr << "rebuild1" << '\n';
	rebuild();
	std::cerr << "rebuild2" << '\n';

	if (RPOEvaluator::compare(_sol->getFitness(), _bestSolution->getFitness()) > 0)
		_bestSolution->copy(*_sol);

	/**
	 * TODO
	 * Mientras no se alcance la condición de parada
	 *  1. Destruir parcialmente la solución
	 *  2. Reconstruir la solución
	 *  3. Almacenar el nuevo fitness en _results para las gráficas
	 *  4. Actualizar la mejor solución y volver a ella si la nueva es peor
	 */

	while (!stopCondition.reached()) {
		std::cerr << "destroy1" << '\n';
		destroy();
		std::cerr << "destroy2" << '\n';
		rebuild();
		std::cerr << "rebuild3" << '\n';
		_results.push_back(_sol->getFitness());
		std::cerr << "a" << '\n';
		if (RPOEvaluator::compare(_sol->getFitness(), _bestSolution->getFitness()) > 0){
			std::cerr << "b" << '\n';
			_bestSolution->copy(*_sol);
			std::cerr << "c" << '\n';
		}else
			_sol->copy(*_bestSolution);

		std::cerr << "d" << '\n';
		stopCondition.notifyIteration();
	}
	std::cerr << "me salgo" << '\n';
}
