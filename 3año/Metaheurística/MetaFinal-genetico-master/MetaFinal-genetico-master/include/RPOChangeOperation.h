/*
 * RPOChangeOperation.h
 *
 * Fichero que declara la clase RPOChangeOperation. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef __RPOCHANGEOPERATION_H__
#define __RPOCHANGEOPERATION_H__

#define NUMVECTORS 10000

#include <RPOSolution.h>

/**
 * Clase abstracta para representar cualquier operación de modificación sobre una solución.
 */
class RPOChangeOperation{
public:

	/**
	 * Destructor
	 */
	virtual ~RPOChangeOperation(){
	}

	/**
	 * Función que aplica el cambio que define el objeto sobre la solución que recibe como argumento
	 * @param[in,out] solution Objeto solución sobre el que se aplicará el cambio
	 */
	virtual void apply(RPOSolution &solution) = 0;
};

#endif
