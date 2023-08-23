/**
 * RPOLocalSearch.h
 *
 */

#ifndef INCLUDE_RPOLOCALSEARCH_H_
#define INCLUDE_RPOLOCALSEARCH_H_

#include <RPOInstance.h>
#include <RPOSolution.h>
#include <RPONeighExplorer.h>
#include <vector>

using namespace std;
/**
 * Clase que implementa la optimización local repetitiva de una solución dada.
 */
class RPOLocalSearch{

	/**
	 * vector de doubles donde almacena la calidad de la última solución aceptada
	 */
	vector<double> _results;

public:
	/**
	 * Constructor
	 */
	RPOLocalSearch();

	/**
	 * Destructor
	 */
	~RPOLocalSearch();

	/**
	 * Función que optimiza una solución aplicado repetidamente la exploración de su vecindario hasta alcanzar un óptimo local.
	 * @param[in] instance Instancia del problema
	 * @param[in] explorer Operador de exploración del vecindario. La idea es que reciba un operador que bien explore el vecindario devolviendo la primera solución que mejora a la actual, o devolviendo el mejor cambio posible sobre la solución actual
	 * @param[in,out] solution Solución inicial que se optimiza localmente. El resultado final se devuelve en ella.
	 */
	void optimise(RPOInstance &instance, RPONeighExplorer &explorer, RPOSolution &solution);

	/**
	 * Función que devuelve el vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local
	 *
	 * @return vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local
	 */
	vector<double>& getResults() {
		return _results;
	}
};



#endif /* INCLUDE_RPOLOCALSEARCH_H_ */
