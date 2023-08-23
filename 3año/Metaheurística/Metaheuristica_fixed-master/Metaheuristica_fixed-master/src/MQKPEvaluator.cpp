/*
 * MQKPEvaluator.cpp
 *
 * Fichero que define los métodos de la clase MQKPEvaluator. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include "./include/MQKPEvaluator.h"
#include "include/MQKPSolution.h"
#include "include/MQKPInstance.h"

double MQKPEvaluator::computeFitness(MQKPInstance &instance, MQKPSolution &solution){

	 if(instance.getMaxCapacityViolation(solution)>0){
		 return instance.getMaxCapacityViolation(solution)*(-1);
	 }
	 else{
		 return instance.getSumProfits(solution);
	 }
}
