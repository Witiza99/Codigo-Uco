/*
 * RPOLocalSearch.cpp
 *
 * Fichero que define las funciones de la clase RPOLocalSearch. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <RPOLocalSearch.h>
#include <RPOInstance.h>
#include <RPOSolution.h>
#include <RPONeighExplorer.h>
#include <iostream>
#include <RPOObjectAssignmentOperation.h>
#include <cmath>

RPOLocalSearch::RPOLocalSearch() {
}

RPOLocalSearch::~RPOLocalSearch() {
}

void RPOLocalSearch::optimise(RPOInstance& instance,
		RPONeighExplorer& explorer, RPOSolution& solution) {

	_results.clear();
	_results.push_back(solution.getFitness());
	RPOObjectAssignmentOperation operation;

	/** TODO
	 * 1. Aplica una vez la exploración del vecindario y almacena si se ha conseguido o no mejorar la solución
	 *
	 * 2. Mientras se haya conseguido mejorar la solución
	 *   a. Aplica el cambio indicado en la exploración anterior
	 *   b. Almacena en _results el nuevo fitness de la solución
	 *   c. Aplica una nueva exploración del vecindario
	 */
	 bool improve = explorer.findOperation(instance, solution, operation);
	 while (improve) {
		 operation.apply(solution);
		 _results.push_back(solution.getFitness());
		 improve = explorer.findOperation(instance, solution, operation);
	 }
}

/*
generamos un vector cuyos valores se generan aleatoriamente alrededor de los valores de nuestro vector solución en
una esfera de radio el 10% del rango de valores de la función.
Si el valor se sale del rango se le impone el límite.
*/
void RPOLocalSearch::randomVectorSphere(RPOInstance &instance, double **vec, double *sol){
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
