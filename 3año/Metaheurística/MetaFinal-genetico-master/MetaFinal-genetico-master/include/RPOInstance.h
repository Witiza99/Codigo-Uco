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
  int _nDims=10;
  double _max;
  double _min;

public:
	/**
	 * Constructor por defecto
	 */
	inline RPOInstance(int numInstance, string extdatadir){
    setNumInstance(numInstance);
    setExtDataDir(extdatadir);
    setMinMax();
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

  void setMinMax();

  double inline getMax(){
    return _max;
  }

  double inline getMin(){
    return _min;
  }

  static double *generateRandomVector(RPOInstance &instance);

  static inline void randomVector(RPOInstance &instance, double **vec){
    *vec = generateRandomVector(instance);
  }

};

#endif
