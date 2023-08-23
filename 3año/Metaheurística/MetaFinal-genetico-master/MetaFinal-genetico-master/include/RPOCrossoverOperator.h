/*
 * RPOCrossoverOperator.h
 *
 * Fichero que define la clase RPOCrossoverOperator. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_RPOCROSSOVEROPERATOR_H_
#define INCLUDE_RPOCROSSOVEROPERATOR_H_

#include <RPOSolution.h>
#include <Solution.h>
#include <RPOInstance.h>
#include <vector>

using namespace std;

/**
 * Clase que implementa un operador de cruce uniforme para el problema RPO. Su idea es la misma que la de un cruce uniforme para codificación entera
 */
class RPOCrossoverOperator {

protected:
	/**
	 * Variables miembro de la clase:
	 *  - _instance Instancia de problema abordada. Se utiliza únicamente para crear nuevos objetos RPOSolution
	 *  - _numObjs almacena el número de objetos de la instancia abordada para reducir el número de consultas a la instancia
	 *  - _crossProb probabilidad de cruce
	 */
	RPOInstance *_instance;
	double _crossProb;
	int _nDims;
	double _alpha = 0.5;

	/**
	 * Función que cruza dos soluciones según su probabilidad de cruce. En caso de que no haya crucce, la solución devuelta será igual al primer padre
	 * @param[in] s1 primer padre
	 * @param[in] s2 segundo padre
	 * @return Nuevo objeto solución descendiente de haber cruzado s1 y s2. La solución se reserva dinámicamente en memoria. Es responsabilidad del invocador de gestionarla correctamente.
	 */
	RPOSolution *cross(Solution *s1, Solution *s2) {
		RPOSolution * child = new RPOSolution(*_instance);

		RPOSolution * sol1 = (RPOSolution *) s1;
		RPOSolution * sol2 = (RPOSolution *) s2;

		double randSample = (((double) rand()) / RAND_MAX);

		double* childVec = child->getSol();

		if (randSample < _crossProb) {
			double *vec1 = sol1->getSol();
			double *vec2 = sol2->getSol();
			for (unsigned i = 0; i < _nDims; i++) {
				double Cmax, Cmin, I;
				Cmax = std::max(vec1[i],vec2[i]);
				Cmin = std::min(vec1[i],vec2[i]);
				I = Cmax - Cmin;
				double min = Cmin - I * _alpha;
				double max = Cmax + I * _alpha;

				randSample = min+(max-min)*(((double) rand()) / RAND_MAX);
				childVec[i] = randSample;
			}
			child->setSol(childVec);
		}else{
			child->copy(*sol1);
		}

		return child;
	}

public:

	/**
	 * Constructor
	 * @param[in] crossProb Probabilidad de cruce
	 * @param[in] instance Instancia del problema abordada
	 */
	RPOCrossoverOperator(double crossProb, RPOInstance &instance) {
		_instance = &instance;
		_nDims = instance.getNDims();
		_crossProb = crossProb;
	}

	/**
	 * Función que aplica el cruce a una población de padres.
	 * @param[in] parents Vector de padres. El cruce se aplica entre cada dos padres consecutivos (1,2), (3,4)...
	 * @param[out] offspring Vector donde se almacenan los descendientes generados. IMPORTANTE: Esta función reserva memoria dinámicamente para las nuevas soluciones en offspring, por lo que es responsabilidad de quien la invoque de gestionar la memoria adecuadamente.
	 */
	void cross(vector<Solution*> &parents, vector<Solution*> &offspring) {

		unsigned numParents = (unsigned) parents.size();

		//TODO aplicar cruce entre cada dos padres consecutivos (1,2), (3,4), ...
		for (unsigned i = 0; i < numParents; i+=2) {
			if(i+1 < numParents){//Para controlar si hay un número impar de padres
				RPOSolution *sol = cross(parents[i], parents[i+1]);
				offspring.push_back(sol);
				sol = cross(parents[i], parents[i+1]);
				offspring.push_back(sol);
			}
		}
	}
};

#endif /* INCLUDE_RPOCROSSOVEROPERATOR_H_ */
