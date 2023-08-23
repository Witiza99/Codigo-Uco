/*
 * RPOObjectAssignmentOperation.cpp
 *
 * Fichero que define las funciones de la clase RPOObjectAssignmentOperation. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <RPOObjectAssignmentOperation.h>

RPOObjectAssignmentOperation::RPOObjectAssignmentOperation(){
	_deltaFitness = 0.0;
}

RPOObjectAssignmentOperation::~RPOObjectAssignmentOperation() {
}
void RPOObjectAssignmentOperation::apply(RPOSolution& solution) {
	solution.setSol(_vec);
	solution.setFitness(solution.getFitness()+_deltaFitness);

}

void RPOObjectAssignmentOperation::setValues(double* vec, double deltaFitness) {
	_vec = vec;
	_deltaFitness = deltaFitness;
}
