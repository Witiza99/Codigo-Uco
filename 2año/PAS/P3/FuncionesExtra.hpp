/*! 
	\file FuncionesExtra.hpp
	\brief Fichero con los prototipos de las funciones extra de la clase Monomio
*/

#ifndef FUNCIONESEXTRA_HPP
#define FUNCIONESEXTRA_HPP

#include "Monomio.hpp"

// Espacio de nombre de la asignatura: ed
namespace ed
{
//////////////////////////////////////////////////////////////////////////////////////

	//Operadores externos que no pertenecen a la clase Monomio

	//! \name Funciones Extra creadas por mi

	/*! 
		\brief  Funcion que se le pasan tres monomios de grado 2,1 y 0 y un vector, modificando el mismo para dar la solución a un polinomio de segundo grado
		\pre La raiz nunca puede ser negativa, tiene que ser 0 o mas
	*/
	void CPSG(ed::Monomio const &m1, ed::Monomio const &m2, ed::Monomio const &m3,double *v,int x);

	/*! 
		\brief  Funcion que se le pasa un monomio y se realiza la derivada del mismo
		\pre El grado de monomio debe ser mayor que 0 para evitar que este quede con grado negativo
	*/
	void CalculaDerivada(ed::Monomio &m);

	/*! 
		\brief  Funcion que se le pasa un monomio y se realiza la integral del mismo
		\pre El grado de monomio debe ser mayor o igual que 0 para evitar dividir entre 0
	*/
	void CalculaIntegral(ed::Monomio &m);

}  // Fin de namespace ed.

#endif // _FuncionesExtra_HPP_