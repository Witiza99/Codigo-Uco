/*
 * RPOIteratedGreedy.h
 *
 * Fichero que define la clase RPOIteratedGreedy. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_RPOITERATEDGREEDY_H_
#define INCLUDE_RPOITERATEDGREEDY_H_

#include <RPOMetaheuristic.h>
#include <RPOSolution.h>
#include <RPOObjectAssignmentOperation.h>
#include <vector>

/**
 * Clase que implementa la metaheurística Iterated Greedy para el RPO, en la variante en la que la destrucción se aplica siempre sobre la mejor solución y no se aplica búsqueda local
 */
class RPOIteratedGreedy : public RPOMetaheuristic{
protected:

	/**
	 * Variables miembro de la clase
	 * _alpha guarda la probabilidad con que los objetos se sacan de sus mochilas correspondientes.
	 * _instance tiene un puntero a la instancia del problema abordada
	 * _sol tiene la solución sobre la que trabaja Iterated Greedy durante las destrucciones y construcciones
	 */
	double _alpha;
	RPOInstance *_instance;
	RPOSolution *_sol;
	double *_oldSol;

	/**
	 * vector de doubles donde almacena la calidad de la última solución aceptada
	 */
	vector<double> _results;

	/**
	 * Función que devuelve la mejor operación de asignación de un objeto sin asignar a una mochila
	 * @param[out] operation Operación de asignación de un objeto a mochila seleccionada
	 */
	void chooseOperation(RPOObjectAssignmentOperation &operation);

	/**
	 * Función que reconstruye la solución _sol. Para ello, invoca repetidamente a la función chooseOperation hasta que no encuentra ninguna otra operación de asignación que mejore la solución actual.
	 * Los cambios se van almacenando en la variable miembro _sol.
	 */
	void rebuild();

	/**
	 * Función que destruye parcialmente la solución _sol. Para ello, saca objetos de sus mochilas correspondientes con probabilidad _alpha
	 */
	void destroy();

public:
	/**
	 * Constructor
	 */
	RPOIteratedGreedy(){
		_alpha = 0.;
		_instance = NULL;
		_sol = NULL;
		_oldSol = NULL;
	}

	/**
	 * Destructor
	 */
	virtual ~RPOIteratedGreedy(){

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}

		if (_sol != NULL){
			delete _sol;
			_sol = NULL;
		}

		if (_oldSol != NULL){
			delete _oldSol;
			_sol = NULL;
		}
	}

	/**
	 * Función que inicializa ciertos parámetros de la metaheurística.
	 * En particular, las variables miembro _sol y _bestSolution y la probabilidad alpha
	 * @param[in] alpha Probabilidad entre 0 y 1 de sacar objetos de sus mochilas en la fase de destrucción
	 * @param[in] instance Instancia del problema que se va a abordar
	 */
	void initialise(double alpha, RPOInstance &instance);

	/**
	 * Función que ejecuta la metaheurística hasta alcanzar la condición de parada
	 * @param[in] stopCondition Condición de parada para la metaheurística
	 */
	virtual void run(RPOStopCondition &stopCondition);

	/**
	 * Función que devuelve el vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local
	 *
	 * @return vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local
	 */
	vector<double>& getResults() {
		return _results;
	}
};



#endif /* INCLUDE_RPOITERATEDGREEDY_H_ */
