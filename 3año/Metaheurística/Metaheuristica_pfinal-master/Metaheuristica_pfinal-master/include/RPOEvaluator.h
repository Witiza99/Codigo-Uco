/**
 * RPOEvaluator.h
 *
 * Fichero que define la clase RPOEvaluator.
 *
 * @author Rafael Hormigo Cabello
 * @author Andrés López Cárdenas
 * @author Antonio Gómez Giménez
 * @author Óscar Jr. Godoy Calderóns
*/

#ifndef __RPOEvaluator_H__
#define __RPOEvaluator_H__

#include "RPOInstance.h"
#include "RPOSolution.h"
#include <time.h>
#include <stdlib.h>

/**
 * Clase que calcula el fitness de una solución al problema RPO
 */
class RPOEvaluator {

public:
	/**
	 * Función que calcula el fitness de una solución
	 * @param[in] instance Referencia a un objeto con la información de la instancia del problema RPO
	 * @param[in] solution Referencia a un objeto que representa una solución al problema.
	 *
	 * @return Fitness de la solución.
	 */
	static double computeFitness(RPOInstance &instance, RPOSolution &solution);
};

#endif
