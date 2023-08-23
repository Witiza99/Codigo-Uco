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
#include <Solution.h>


class RPOSolution : public Solution{
protected:
	double *_sol;
	int _nDims;
	int _numInstance;
	double _fitness;
	bool _fitnessAssigned;

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
		_fitnessAssigned = false;
  }

  inline double* getSol() const{
    return _sol;
  }

	inline void setFitness(double fitness){
		_fitness = fitness;
		_fitnessAssigned = true;
	}

	virtual double getFitness() const{
		return _fitness;
	}

	inline int getNDims(){
		return _nDims;
	}

	/**
	 * Función que copia la información de otra solución
	 * @param[in] solution La solución de donde copiar la información
	 */
	virtual void copy(Solution &sol){
		RPOSolution &solution = (RPOSolution&) sol;
		_nDims = solution._nDims;
		for (int i = 0; i < _nDims; i++)
			_sol[i] = solution._sol[i];

		_numInstance = solution._numInstance;;
		_fitness = solution._fitness;
		_fitnessAssigned = solution._fitnessAssigned;
	}

	/**
	 * Función que indica si el fitness de la solución es válido (deja de serlo si se cambia un objeto de mochila; y se convierte en válido cuando se le asigna)
	 *
	 * TODO LEER he creado este método para ahorrarnos las evaluaciones de soluciones que son copias de otras
	 */
	bool hasValidFitness(){
		return _fitnessAssigned;
	}

};

#endif
