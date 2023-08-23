/*!
   \file PolinomioInterfaz.hpp
   \brief Definición de la interfaz de la clase Polinomio
*/

#ifndef _POLINOMIOINTERFAZ_HPP_
#define _POLINOMIOINTERFAZ_HPP_

#include "Monomio.hpp"

// Se incluye la clase PolinomioInterfaz dentro del espacio de nombre de la asigantura: ed
namespace ed {

//!  Definición de la clase PolinomioInterfaz
class PolinomioInterfaz
{

   //! \name Funciones o métodos públicos de la clase
   public:

	//! \name Observadores: funciones de consulta

	/*! 
		\brief Comprueba si el Polinomio es igual al monomio de coeficiente 0.0 y grado 0
		\return bool
	*/
	//virtual bool esNulo() const = 0;

  	/*! 
		\brief Comprueba si existe el monomio de grado indicado
		\pre El polinomio debe existir
		\return bool
	*/
	//virtual int getGrado()const = 0;

  	/*! 
		\brief Obtiene el número de monomios del polinomio
		\return int
	*/
	//virtual int getNumeroMonomios()const = 0;


  	/*! 
		\brief Comprueba si existe el monomio de grado indicado
		\pre El polinomio debe existir
		\return bool
	*/
	//virtual bool existeMonomio(int n)const = 0;


  	/*! 
		\brief Obtiene el monomio de grado indicado
		\pre El polinomio debe existir
		\return Monomio
	*/
	//virtual ed::Monomio & getMonomio(int n) = 0;



}; // Fin de la definición de la clase PolinomioInterfaz


} // \brief Fin de namespace ed.

//  _POLINOMIOINTERFAZ_HPP_
#endif
