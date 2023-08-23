/*
 * RPOMutationOperator.h
 *
 * Fichero que define la clase RPOMutationOperator. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_RPOMUTATIONOPERATOR_H_
#define INCLUDE_RPOMUTATIONOPERATOR_H_

#include <RPOSolution.h>
#include <vector>
#include <cstdlib>

using namespace std;

/**
 * Clase que define un operador de mutación para el RPO. Se basa en recorrer todos los genes de la solución y cambiarlos por un valor aleatorio según una probabilidad
 */
class RPOMutationOperator{

protected:
	/**
	 * Variables miembro de la clase
	 * _mutProb Probabilidad de mutación
	 * _max
	 * _min
	 */
	double _mutProb;
	double _min;
	double _max;

	/**
	 * Función que muta una solución
	 * @param[in,out] sol Solución a mutar
	 */
	void mutate(Solution* sol){
		RPOSolution *s = (RPOSolution*) sol;
		double *vec = s->getSol();

		double prob = (((double) rand()) / RAND_MAX);
		for (int i = 0; i < s->getNDims(); i++) {
			if (prob < _mutProb) {
				vec[i] = _min+(_max-_min)*(((double) rand()) / RAND_MAX);
			}
			prob = (((double) rand()) / RAND_MAX);
		}
		s->setSol(vec);
		sol = s;
	}

public:
	/**
	 * Constructor
	 * @param[in] mutProb Probabilidad de mutación
	 * @param[in] instance Instancia del problema a abordar
	 */
	RPOMutationOperator(double mutProb, RPOInstance &instance){
		_mutProb = mutProb;
		_max = instance.getMax();
		_min = instance.getMin();
	}

	/**
	 * Función que muta un conjunto de soluciones
	 * @param[in,out] sols Soluciones a mutar
	 */
	void mutate(vector<Solution*> &sols){

		for (Solution* sol : sols){
			mutate(sol);
		}
	}
};



#endif /* INCLUDE_RPOMUTATIONOPERATOR_H_ */
