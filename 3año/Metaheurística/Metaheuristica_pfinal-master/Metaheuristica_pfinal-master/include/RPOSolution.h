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


class RPOSolution {
protected:
	double *_sol;
	int _numInstance;
	double _fitness;

public:
	/**
	 * Constructor
	 * @param[in] instance Referencia a un objeto con la información de la instancia del problema RPO
	 */
	inline RPOSolution(RPOInstance &instance){
    _sol = new double[instance.getNDims()];
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

};

#endif
