/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 1
  \author Antonio Gómez Giménez
  \date   02/23/2019
*/


#ifndef _FUNCIONESAUXILIARES_HPP_
#define _FUNCIONESAUXILIARES_HPP_


namespace ed
{
	/*! 
		\brief   Muestra el menú del programa principal 
		\return  Devuelve el número de opción elegido
	*/
	int menu();
	/*! 
		\brief   Muestra el menú secundario del programa principal 
		\return  Devuelve el número de opción elegido
	*/
	int menu2();
	/*! 
		\brief   Realiza un test sobre la clase Monomio (métodos y constructores)
	*/
	void testMonomio();
	/*! 
		\brief   Realiza un test sobre los operadores Externos a la clase monomio
	*/
	void operadoresExternosMonomios();
	/*! 
		\brief   Realiza un test sobre las funciones creadas a parte por mí (función CPSG)
	*/
	void FuncionesExtras();
	/*! 
		\brief   Realiza un test sobre las funciones creadas a parte por mí (calcular derivadas)
	*/
	void FuncionesExtras1();
	/*! 
		\brief   Realiza un test sobre las funciones creadas a parte por mí (calcular integrales)
	*/
	void FuncionesExtras2();
	



} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FUNCIONESAUXILIARES_HPP_
#endif

