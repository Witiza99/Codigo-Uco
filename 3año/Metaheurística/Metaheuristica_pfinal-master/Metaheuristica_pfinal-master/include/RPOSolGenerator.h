/**
 * RPOSolGenerator.h
 *
 * Fichero que define la clase RPOSolGenerator.
 *
 * @author Rafael Hormigo Cabello
 * @author Andrés López Cárdenas
 * @author Antonio Gómez Giménez
 * @author Óscar Jr. Godoy Calderón
 */

#ifndef __RPOSOLGENERATOR_H__
#define __RPOSOLGENERATOR_H__

#include "RPOInstance.h"
#include "RPOSolution.h"
#include <stdlib.h>

/**
 * Clase que genera una solución aleatoria al problema RPO
 *
 * Sobre la representación de soluciones:
 * La representación de las soluciones será un vector de número enteros: de 1 a M para objetos que están en alguna de las M mochilas y 0 para objetos que no están en ninguna mochilas
 */
class RPOSolGenerator {

public:

	/**
	 * Función que genera una solución aleatoria para el problema de las múltiples mochilas cuadráticas
	 * @param[in] instance Referencia a un objeto con la información de la instancia del problema RPO
	 * @param[out] solution Referencia a un objeto que representa una solución al problema. 
	 */
	static void genRandomSol(RPOInstance &instance, RPOSolution &solution);
};

#endif
