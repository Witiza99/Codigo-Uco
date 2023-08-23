/*
 * RPOSimpleFirstImprovementNO.cpp
 *
 */

#include <RPOSimpleFirstImprovementNO.h>
#include <RPOInstance.h>
#include <RPOEvaluator.h>
#include <RPOObjectAssignmentOperation.h>
#include <stdlib.h>
#include <iostream>
#include <RPOLocalSearch.h>

using namespace std;

bool RPOSimpleFirstImprovementNO::findOperation(RPOInstance &instance, RPOSolution &solution, RPOChangeOperation &operation) {

	RPOObjectAssignmentOperation *oaOperation = dynamic_cast<RPOObjectAssignmentOperation*>(&operation);
	if (oaOperation == NULL){
		cerr << "RPOSimpleFirstImprovementNO::findOperation recibió un objeto operation que no es de la clase RPOObjectAssignmentOperation" << endl;
		exit(1);
	}

	//Crear una permutación de los índices de los objetos e inicializar algunas variables
	int numDims = instance.getNDims();
	double *vec = new double[numDims];
	double *sol = solution.getSol();
	for ( int i = 0; i < NUMVECTORS; i++) {
	 	RPOLocalSearch::randomVectorSphere(instance, &vec, sol);
		double deltaFitness = RPOEvaluator::computeDeltaFitness(instance, solution, vec);
		if (deltaFitness>0) {
			oaOperation->setValues(vec, deltaFitness);
			return true;
		}
 	}
	 return false;
}
