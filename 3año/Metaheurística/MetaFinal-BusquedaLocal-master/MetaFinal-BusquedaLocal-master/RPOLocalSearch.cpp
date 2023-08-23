/*
 * RPOLocalSearch.cpp
 *
 * Fichero que define las funciones de la clase RPOLocalSearch. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <RPOLocalSearch.h>
#include <RPOInstance.h>
#include <RPOSolution.h>
#include <RPONeighExplorer.h>
#include <iostream>
#include <RPOObjectAssignmentOperation.h>

RPOLocalSearch::RPOLocalSearch() {
}

RPOLocalSearch::~RPOLocalSearch() {
}

void RPOLocalSearch::optimise(RPOInstance& instance,
		RPONeighExplorer& explorer, RPOSolution& solution) {

	_results.clear();
	_results.push_back(solution.getFitness());
	RPOObjectAssignmentOperation operation;

	/** TODO
	 * 1. Aplica una vez la exploración del vecindario y almacena si se ha conseguido o no mejorar la solución
	 *
	 * 2. Mientras se haya conseguido mejorar la solución
	 *   a. Aplica el cambio indicado en la exploración anterior
	 *   b. Almacena en _results el nuevo fitness de la solución
	 *   c. Aplica una nueva exploración del vecindario
	 */
	 bool improve = explorer.findOperation(instance, solution, operation);
	 while (improve) {
		 operation.apply(solution);
		 _results.push_back(solution.getFitness());
		 improve = explorer.findOperation(instance, solution, operation);
	 }
}
