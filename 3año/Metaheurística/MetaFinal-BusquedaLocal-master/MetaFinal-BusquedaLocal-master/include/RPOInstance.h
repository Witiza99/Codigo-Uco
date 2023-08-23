/**
 * RPOInstance.h
 *
 * Fichero que define la clase RPOInstance.
 *
 * @author Rafael Hormigo Cabello
 * @author Andrés López Cárdenas
 * @author Antonio Gómez Giménez
 * @author Óscar Jr. Godoy Calderón
 */

#ifndef __RPOINSTANCE_H__
#define __RPOINSTANCE_H__

#include <string>

using namespace std;

class RPOInstance {
protected:

  int _numInstance;
  string _extdatadir;
  //Duda cuantas dimensiones?
  int _nDims=10;

public:
	/**
	 * Constructor por defecto
	 */
	inline RPOInstance(int numInstance, string extdatadir){
    setNumInstance(numInstance);
    setExtDataDir(extdatadir);
  };

	/**
	 * Destructor
	 */
	inline ~RPOInstance(){

  };

  inline void setNumInstance(int numInstance){
    _numInstance = numInstance;
  }

  inline int getNumInstance() const {
    return _numInstance;
  }

  inline int getNDims() const {
    return _nDims;
  }

  inline void setExtDataDir(string extdatadir){
    _extdatadir=extdatadir;
  }

  inline string getExtDataDir(){
    return _extdatadir;
  }

  static double *generateRandomVector(RPOInstance &instance);

  static inline void randomVector(RPOInstance &instance, double **vec){
    *vec = generateRandomVector(instance);
  }

  static void randomVectorSphere(RPOInstance &instance, double **vec, double *sol);
};

#endif
