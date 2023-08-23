/**
 * RPOSimpleBestImprovementNO.cpp
 *
 * Fichero que define las funciones de la clase RPOSimpleBestImprovementNO. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <RPOSimpleBestImprovementNO.h>
#include <RPOInstance.h>
#include <RPOSolution.h>
#include <RPOObjectAssignmentOperation.h>
#include <RPOEvaluator.h>
#include <stdlib.h>
#include <RPOLocalSearch.h>
#include <iostream>
using namespace std;

bool RPOSimpleBestImprovementNO::findOperation(RPOInstance &instance, RPOSolution &solution, RPOChangeOperation &operation) {

	RPOObjectAssignmentOperation *oaOperation = dynamic_cast<RPOObjectAssignmentOperation*>(&operation);
	if (oaOperation == NULL){
		cerr << "RPOSimpleFirstImprovementNO::findOperation recibió un objeto operation que no es de la clase RPOObjectAssignmentOperation" << endl;
		exit(1);
	}

	int numDims = instance.getNDims();
	double *vec = new double[numDims];
	double *sol = solution.getSol();
	double bestDeltaFitness = 0;
	for ( int i = 0; i < NUMVECTORS; i++) {
	 	RPOLocalSearch::randomVectorSphere(instance, &vec, sol);
		double newDeltaFitness = RPOEvaluator::computeDeltaFitness(instance, solution, vec);
		if (newDeltaFitness > bestDeltaFitness) {
			bestDeltaFitness = newDeltaFitness;
			oaOperation->setValues(vec, bestDeltaFitness);
		}
 	}
	 if (bestDeltaFitness>0) {
		return true;
	}else{
		return false;
	}
}
