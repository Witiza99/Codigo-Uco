#include <RPOInstance.h>
#include <cstdlib>
#include <iostream>
#include <cmath>

#define PI 3.141592653589793238


double *RPOInstance::generateRandomVector(RPOInstance &instance){
  double *sol = new double[instance.getNDims()];
  for (unsigned i = 0; i < instance.getNDims(); i++) {
    sol[i] = instance._min+(instance._max-instance._min)*(((double) rand()) / RAND_MAX);
  }
  return sol;
}

void RPOInstance::setMinMax(){
  switch (this->getNumInstance()) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 14:
    _max = 100;
    _min = -100;
    break;
    case 7:
    _max = 600;
    _min = 0;
    break;
    case 8:
    _max = 32;
    _min = -32;
    break;
    case 9:
    case 10:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    _max = 5;
    _min = -5;
    break;
    case 11:
    _max = 0.5;
    _min = -0.5;
    break;
    case 12:
    _max = PI;
    _min = -PI;
    break;
    case 13:
    _max = 1;
    _min = -3;
    break;
    case 25:
    _max = 5;
    _min = 2;
    break;
    default:
      std::cerr << "Error de función" << '\n';
      exit(-1);
  }
}
