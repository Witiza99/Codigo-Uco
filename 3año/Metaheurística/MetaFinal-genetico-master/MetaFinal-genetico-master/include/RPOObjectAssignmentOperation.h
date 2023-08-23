/* RPOObjectAssignmentOperation.h
 *
 */

#ifndef __RPOOBJECTASSIGNMENTOPERATION_H__
#define __RPOOBJECTASSIGNMENTOPERATION_H__

#include <RPOChangeOperation.h>
#include <RPOSolution.h>

/**
 * Clase que codifica una operación de asignación de un objeto a una mochila, pudiendo ser ésta la mochila 0, es decir, sacarlo de la mochila en la que se encuentre
 */
class RPOObjectAssignmentOperation : public RPOChangeOperation {

protected:

	 double *_vec;
	 double _deltaFitness;

public:

	/**
	 * Constructor
	 */
	RPOObjectAssignmentOperation();

	/**
	 * Destructor
	 */
	virtual ~RPOObjectAssignmentOperation();

	/**
	 * Función que aplica el cambio que define el propio objeto sobre la solución que recibe como argumento.
	 * @param[in, out] solution Objeto solución sobre el que se aplicará el cambio
	 */
	virtual void apply(RPOSolution &solution);

	/**
	 * Función que asigna los valores la operación
	 * @param[in] indexObject El índice del objeto que se va a cambiar de mochila
	 * @param[in] indexKnapsack El índice de la mochila donde se insertará el objeto
	 * @param[in] deltaFitness La diferencia en fitness de aplicar dicha operación de asignación de un objeto a una mochila (siempre que la solución actual no se hubiese cambiado cuando se calculo dicha diferencia)
	 */
	void setValues(double *vec, double deltaFitness);

	/**
	 * Función que devuelve la diferencia en fitness de la operación,
	 * @return Diferencia en fitness de la operación (siempre que la solución actual no se hubiese cambiado cuando se calculo dicha diferencia)
	 */
	double getDeltaFitness(){
		return _deltaFitness;
	}

	/**
	 * Función que devuelve el vector de la operaración
	 * @return vector 
	 */
	double *getVec(){
		return _vec;
	}

};

#endif
