/*
 * RPOSimpleBestImprovementNO.h
 *
 */

#ifndef INCLUDE_RPOSIMPLEBESTIMPROVEMENTNO_H_
#define INCLUDE_RPOSIMPLEBESTIMPROVEMENTNO_H_

#include <RPONeighExplorer.h>
#include <RPOSolution.h>
#include <RPOChangeOperation.h>
/**
 * Clase que se encarga de explorar el vecindario de una solución dada, devolviendo la mejor operación de asignación de un objeto a una mochila entre las operaciones posibles, devolverá FALSE si la operación devuelta no mejora a la solución actual
 */
class RPOSimpleBestImprovementNO : public RPONeighExplorer{

public:

	/**
	 * Destructor
	 */
	virtual ~RPOSimpleBestImprovementNO(){

	}

	/**
	 * Función que explora el vecindario de una solución dada, devolviendo la mejor operación de asignación de un objeto a una mochila entre las operaciones posibles, devolverá FALSE si la operación devuelta no mejora a la solución actual
	 * @param[in] instance Instancia del problema
	 * @param[in] solution Solución cuya vecindad se va a explorar
	 * @param[out] operation Operación tal que aplicada a la solución, devuelve una vecina.
	 *
	 * @return true si la operación devuelta mejora a solution; false, si no hay ninguna operación en la vecindad que pueda mejorar a solution
	 */
	virtual bool findOperation(RPOInstance &instance, RPOSolution &solution, RPOChangeOperation &operation);

};


#endif /* INCLUDE_RPOSIMPLEBESTIMPROVEMENTNO_H_ */
