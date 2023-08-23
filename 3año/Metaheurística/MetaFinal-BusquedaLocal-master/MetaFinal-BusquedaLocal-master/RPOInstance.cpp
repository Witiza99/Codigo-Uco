#include <RPOInstance.h>
#include <cstdlib>
#include <iostream>
#include <cmath>

#define NOCOMAPI 3141592653589793238
/*
generamos un vector cuyos valores se generan aleatoriamente alrededor de los valores de nuestro vector solución en
una esfera de radio el 10% del rango de valores de la función.
Si el valor se sale del rango se le impone el límite.
*/
void RPOInstance::randomVectorSphere(RPOInstance &instance, double **vec, double *sol){
  *vec = new double[instance.getNDims()];
  double number;
  switch (instance.getNumInstance()) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 14:
    for (int i = 0; i < instance.getNDims(); i++) {
      number = ((double)(rand()%2001)-1000)/100;
      number += sol[i];
      if (number > 100) {
        number = 100;
      }else if (number <-100) {
        number = -100;
      }
      vec[0][i] = number;
    }
    break;
    case 7:
    for (int i = 0; i < instance.getNDims(); i++) {
      number = ((rand()%12001)-6000)/100;
      number += sol[i];
      if (number > 600) {
        number = 600;
      }else if (number <0) {
        number = 0;
      }
      vec[0][i] = number;
    }
    break;
    case 8:
      for (int i = 0; i < instance.getNDims(); i++) {
        number = ((rand()%(641))-320)/100;
        number += sol[i];
        if (number > 32) {
          number = 32;
        }else if (number < -32) {
          number = -32;
        }
        vec[0][i] = number;
      }
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
      for (int i = 0; i < instance.getNDims(); i++) {
        number = ((rand()%(101))-50)/100;
        number += sol[i];
        if (number > 5) {
          number = 5;
        }else if (number < -5) {
          number = -5;
        }
        vec[0][i] = number;
      }
    break;
    case 11:
      for (int i = 0; i < instance.getNDims(); i++) {
        number = ((rand()%101)-50)/1000;
        number += sol[i];
        if (number > 0.5) {
          number = 0.5;
        }else if (number < -0.5) {
          number = -0.5;
        }
        vec[0][i] = number;
      }
    break;
    case 12:
      for (int i = 0; i < instance.getNDims(); i++) {
        number = (((rand()%(2*NOCOMAPI))-NOCOMAPI)/pow(10,34))/10;
        number += sol[i];
        if (number > NOCOMAPI/pow(10,34)) {
          number = NOCOMAPI/pow(10,34);
        }else if (number < -NOCOMAPI/pow(10,34)) {
          number = -NOCOMAPI/pow(10,34);
        }
        vec[0][i] = number;
      }
    break;
    case 13:
    for (int i = 0; i < instance.getNDims(); i++) {
      number = (((rand()%401)-300))/1000;
      number += sol[i];
      if (number > 0.5) {
        number = 0.5;
      }else if (number < -0.5) {
        number = -0.5;
      }
      vec[0][i] = number;
    }
    break;
    case 25:
    for (int i = 0; i < instance.getNDims(); i++) {
      number = ((rand()%301)+200)/1000;
      number += sol[i];
      if (number > 0.5) {
        number = 0.5;
      }else if (number < -0.5) {
        number = -0.5;
      }
      vec[0][i] = number;
    }
    break;
    default:
      std::cerr << "Error de función" << '\n';
      exit(-1);
  }
}

double *RPOInstance::generateRandomVector(RPOInstance &instance){
  double *sol = new double[instance.getNDims()];
  switch (instance.getNumInstance()) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 14:
    for (int i = 0; i < instance.getNDims(); i++) {
      sol[i] = ((double)(rand()%(20001))-10000)/100;
    }
    break;
    case 7:
    for (int i = 0; i < instance.getNDims(); i++) {
      sol[i] = (rand()%60001)/100;
    }
    break;
    case 8:
      for (int i = 0; i < instance.getNDims(); i++) {
        sol[i] = ((rand()%(6401))-3200)/100;
      }
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
      for (int i = 0; i < instance.getNDims(); i++) {
        sol[i] = ((rand()%(1001))-500)/100;
      }
    break;
    case 11:
      for (int i = 0; i < instance.getNDims(); i++) {
        sol[i] = ((rand()%1001)-500)/1000;
      }
    break;
    case 12:
      for (int i = 0; i < instance.getNDims(); i++) {
        sol[i] = ((rand()%(2*NOCOMAPI))-NOCOMAPI)/pow(10,34);
      }
    break;
    case 13:
    for (int i = 0; i < instance.getNDims(); i++) {
      sol[i] = (((rand()%401)-300))/100;
    }
    break;
    case 25:
    for (int i = 0; i < instance.getNDims(); i++) {
      sol[i] = ((rand()%301)+200)/100;
    }
    break;
    default:
      std::cerr << "Error de función" << '\n';
      exit(-1);
  }
  return sol;
}
