/**
 * RPOSolution.h
 *
 * Fichero que define la clase RPOSolution.
 *
 * @author Rafael Hormigo Cabello
 * @author Andrés López Cárdenas
 * @author Antonio Gómez Giménez
 * @author Óscar Jr. Godoy Calderóns
 */

#ifndef __RPOSOLUTION_H__
#define __RPOSOLUTION_H__

#include <RPOInstance.h>


class RPOSolution {
protected:
	double *_sol;
	int _nDims;
	int _numInstance;
	double _fitness;

public:
	/**
	 * Constructor
	 * @param[in] instance Referencia a un objeto con la información de la instancia del problema RPO
	 */
	inline RPOSolution(RPOInstance &instance){
		_nDims = instance.getNDims();
    _sol = new double[_nDims];
    _numInstance = instance.getNumInstance();
  }

	/**
	 * Destructor
	 */
	inline ~RPOSolution(){
    delete _sol;
  };

  inline void setSol(double *sol){
    _sol=sol;
  }

  inline double* getSol(){
    return _sol;
  }

	inline void setFitness(double fitness){
		_fitness = fitness;
	}

	inline double getFitness(){
		return _fitness;
	}

	/**
	 * Función que copia la información de otra solución
	 * @param[in] solution La solución de donde copiar la información
	 */
	void copy(RPOSolution &solution){
		_nDims = solution._nDims;
		for (int i = 0; i < _nDims; i++)
			_sol[i] = solution._sol[i];

		_numInstance = solution._numInstance;;
		_fitness = solution._fitness;
	}

};

#endif
