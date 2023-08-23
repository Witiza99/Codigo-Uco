/*
 * RPOMetaheuristic.h
 *
 * Fichero que define la clase RPOMetaheuristic. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 */

#ifndef INCLUDE_RPOMETAHEURISTIC_H_
#define INCLUDE_RPOMETAHEURISTIC_H_

#include <RPOSolution.h>
#include <RPOStopCondition.h>
#include <cstdlib>

/**
 * Clase abstracta que define los métodos comunes para las metaheurísticas para el RPO.
 */
class RPOMetaheuristic {

protected:
	RPOSolution *_bestSolution;

public:
	/**
	 * Constructor
	 */
	RPOMetaheuristic(){
		_bestSolution = NULL;
	}

	/**
	 * Destructor
	 */
	virtual ~RPOMetaheuristic(){

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}
	};

	/**
	 * Función que ejecuta la metaheurística hasta alcanzar la condición de parada
	 * @param[in] stopCondition Condición de parada para la metaheurística
	 */
	virtual void run (RPOStopCondition &stopCondition) = 0;


	/**
	 * Función que devuelve la mejor solución encontrada hasta el momento.
	 * Es responsabilidad de cada metaheurística concreta el mantener actualizada la variable _bestSolution
	 * @return La mejor solución encontradas hasta el momento
	 */
	RPOSolution*& getBestSolution(){
		return _bestSolution;
	}
};



#endif /* INCLUDE_RPOMETAHEURISTIC_H_ */
