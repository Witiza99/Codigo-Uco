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

#include <RPOInstance.h>
#include <RPOSolution.h>

/**
 * Clase que calcula el fitness de una solución al problema RPO
 */
class RPOEvaluator {

protected:
	/**
	 * Variable donde se contabiliza el número de soluciones que se evalúan a través de  computeFitness o computeDeltaFitness
	 */
	static unsigned _numEvaluations;

public:
	/**
	 * Función que calcula el fitness de una solución
	 * @param[in] instance Referencia a un objeto con la información de la instancia del problema RPO
	 * @param[in] solution Referencia a un objeto que representa una solución al problema.
	 *
	 * @return Fitness de la solución.
	 */
	static double computeFitness(RPOInstance &instance, RPOSolution &solution);

	static double computeDeltaFitness(RPOInstance &instance, RPOSolution &solution, double *vec);

	static void resetNumEvaluations();

	/**
	 * Función que devuelve el número de veces que se ha evaluado alguna solución
	 */
	static unsigned getNumEvaluations() {
		return _numEvaluations;
	}

	/**
	 * Función que realiza la comparación entre dos valores de fitness (sirve para especificar si es un problema de maximización o minimización)
	 * @param[in] f1 primer valor de fitness a comparar
	 * @param[in] f2 segundo valor de fitness a comparar
	 * @return Un valor positivo si el primer valor es mejor que el segundo, negativo en caso contrario, y 0 si son indistinguibles
	 */
	static double compare(double f1, double f2){
		//TODO corregir lo que hay que devolver
		if (f1>f2) {
			return 1;
		}else if(f2>f1){
			return -1;
		}
		return 0;
	}

	/**
	 * Función que indica si el problema es de minimización o de maximización
	 * @return Devuelve true si el problema es de minimización o false, si es de maximización
	 */
	static bool isToBeMinimised(){
		return (compare(0,1) > 0);
	}
};

#endif
