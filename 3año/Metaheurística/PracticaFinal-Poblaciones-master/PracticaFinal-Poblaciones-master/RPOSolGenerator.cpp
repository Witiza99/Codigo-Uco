/*
 * RPOSolGenerator.cpp
 *
 * Fichero que define los métodos de la clase RPOInstance.
 *
 * @author Rafael Hormigo Cabello
 * @author Andrés López Cárdenas
 * @author Antonio Gómez Giménez
 * @author Óscar Jr. Godoy Calderóns
 */


#include "include/RPOInstance.h"
#include "include/RPOSolGenerator.h"
#include "include/RPOSolution.h"
#include <cstdlib>
#include <cmath>
#include <iostream>


void RPOSolGenerator::genRandomSol(RPOInstance &instance, RPOSolution &solution){
  double *sol;
  sol = RPOInstance::generateRandomVector(instance);

  solution.setSol(sol);
}
