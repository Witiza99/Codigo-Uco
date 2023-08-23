/*
 * RPONeighExplorer.h
 *s
 */

#ifndef INCLUDE_RPONEIGHEXPLORER_H_
#define INCLUDE_RPONEIGHEXPLORER_H_

#include <RPOSolution.h>
#include <RPOInstance.h>
#include <RPOChangeOperation.h>

/**
 * clase abstracta que define las operaciones de cualquier operador que explora la vecindad de una solución dada.
 */
class RPONeighExplorer {
public:

	/**
	 * Destructor
	 */
	virtual ~RPONeighExplorer(){}

	/**
	 * Función que busca una operación que aplicada a la solución devuelva otra solución vecina. Se utilizará para buscar una solución vecina que la mejore, o la mejor de las soluciones vecinas.
	 *
	 * @param[in] instance Instancia del problema de la múltiples mochilas cuadráticas
	 * @param[in] solution Solución cuya vecindad va a ser explorada
	 * @param[out] operation Operación que se devuelve al explorar la vecindad.
	 *
	 * @return Devuelve verdadero si ha encontrado una operación válida, que mejora la solution y que se ha almacenado en operation. Falso en otro caso
	 */
	virtual bool findOperation(RPOInstance &instance, RPOSolution &solution, RPOChangeOperation &operation) = 0;
};



#endif /* INCLUDE_RPONEIGHEXPLORER_H_ */
