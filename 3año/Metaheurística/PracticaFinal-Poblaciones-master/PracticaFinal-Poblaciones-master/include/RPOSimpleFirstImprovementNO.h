/*
 * RPOSimpleFirstImprovementNO.h
 *
 */

#ifndef INCLUDE_RPOSIMPLEFIRSTIMPROVEMENTNO_H_
#define INCLUDE_RPOSIMPLEFIRSTIMPROVEMENTNO_H_

#include <RPONeighExplorer.h>
#include <RPOSolution.h>
#include <RPOChangeOperation.h>
/**
 * Clase que se encarga de explorar el vecindario de una solución dada, devolviendo la primera operación de asignación de un objeto a una mochila que encuentre que mejore la calidad de la solución recibida. En caso de que no exista ninguna operación que mejore la calidad de la solución recibida, entonces devolverá FALSE
 */
class RPOSimpleFirstImprovementNO : public RPONeighExplorer{

public:

	/**
	 * Destructor
	 */
	virtual ~RPOSimpleFirstImprovementNO(){

	}

	/**
	 * Función que explora el vecindario de una solución dada, devolviendo la primera operación de asignación de un objeto a una mochila que encuentre que mejora la solución actual, devolverá FALSE si la operación devuelta no mejora a la solución actual
	 * @param[in] instance Instancia del problema
	 * @param[in] solution Solución cuya vecindad se va a explorar
	 * @param[out] operation Operación tal que aplicada a la solución, devuelve una vecina.
	 *
	 * @return true si la operación devuelta mejora a solution; false, si no hay ninguna operación en la vecindad que pueda mejorar a solution
	 */
	virtual bool findOperation(RPOInstance &instance, RPOSolution &solution, RPOChangeOperation &operation);
};


#endif /* INCLUDE_RPOSIMPLEFIRSTIMPROVEMENTNO_H_ */
