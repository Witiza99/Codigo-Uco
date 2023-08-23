/*!
	\file operadoresExternosPolinomios.hpp
	\brief Ficheros con operadores de monomios y polinomios
*/

#ifndef _OperadoresPolinomios_HPP_
#define _OperadoresPolinomios_HPP_

// Facilita la entrada y salida
#include <iostream>

#include "Polinomio.hpp"

using std::istream;
using std::ostream;

// Espacio de nombre de la asigantura: ed
namespace ed
{

////////////////////////////////////////////////////////////////////////////
	// Funciones y operadores que no pertenecen a la clase Polinomio


	////////////////////////////////////////////////////////////
	//! \name Operadores de igualdad

	/*! 
		\brief Comprueba  si  dos  polinomios  son  iguales: p1  ==  p2.Si  tienen  los  mismos monomios
		\post El valor devuelto es verdadero si los dos polinomios tienen los mismos monomios
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	bool operator==(ed::Polinomio const & p1, ed::Polinomio const & p2);

	/*! 
		\brief Comprueba  si  el  polinomio  “p”  es  igual  al  monomio  “m”,  es  decir,  si  el polinomio “p” tiene un único monomio que es igual a “m
		\post El valor devuelto es verdadero si el polinomio tiene un único monomio que es igual a “m”
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	bool operator==(ed::Polinomio const & p, ed::Monomio const & m);

	/*! 
		\brief Comprueba  si  el  polinomio  “p”  es  igual  al  monomio  “m”,  es  decir,  si  el polinomio “p” tiene un único monomio que es igual a “m
		\post El valor devuelto es verdadero si el polinomio tiene un único monomio que es igual a “m”
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	bool operator==(ed::Monomio const & m, ed::Polinomio const & p);

	/*! 
		\brief 	Comprueba si el polinomio “p” es igual al número “x”, es decir, si el polinomio “p” tiene un único monomio que es igual a “x”
		\post El valor devuelto es verdadero verdadero si el polinomio tiene un único monomio que es igual a “x”
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	bool operator==(ed::Polinomio const & p, double x);

	/*! 
		\brief 	Comprueba si el polinomio “p” es igual al número “x”, es decir, si el polinomio “p” tiene un único monomio que es igual a “x”
		\post El valor devuelto es verdadero verdadero si el polinomio tiene un único monomio que es igual a “x”
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	bool operator==(double x, ed::Polinomio const & p);


	////////////////////////////////////////////////////////////////////////////////////
	//! \name Operadores de desigualdad

	/*! 
		\brief CComprueba si dos polinomios no son iguales: p1 !=p2.Si no tienen los mismos monomios.
		\post El valor devuelto es verdadero si los dos polinomios no tienen los mismos monomios
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	bool operator!=(ed::Polinomio const & p1, ed::Polinomio const & p2);

	/*! 
		\brief Comprueba  si  el  polinomio  “p”  es  no  igual  al  monomio  “m”,  es  decir,  si  el polinomio “p” no tiene un único monomio que es igual a “m”
		\post verdadero  si  el  polinomio  no  tiene  un  único  monomio  que  es  igual  a “m”
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	bool operator!=(ed::Polinomio const & p, ed::Monomio const & m);

	/*! 
		\brief Comprueba  si  el  polinomio  “p”  no  es  igual  al monomio  “m”,  es  decir,  si  el polinomio “p” no tiene un único monomio que es igual a “m”
		\post El valor devuelto es verdadero  si  el  polinomio  no  tiene  un  único  monomio  que  es  igual  a “m”
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	bool operator!=(ed::Monomio const & m, ed::Polinomio const & p);

	/*! 
		\brief 	Comprueba  si  el  polinomio  “p”  no  es  igual  al  número  “x”,  es  decir,  si  el polinomio “p” no tiene un único monomio que es igual a “x”
		\post El valor devuelto es verdadero si  el  polinomio  no  tiene  un  único  monomio  que  es  igual  a “x”
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	bool operator!=(ed::Polinomio const & p, double x);

	/*! 
		\brief 	Comprueba  si  el  polinomio  “p”  no  es  igual  al  número  “x”,  es  decir,  si  el polinomio “p” no tiene un único monomio que es igual a “x”
		\post El valor devuelto es verdadero  si  el  polinomio  no  tiene  un  único  monomio  que  es  igual  a “x”
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	bool operator!=(double x, ed::Polinomio const & p);

//////////////////////////////////////////////////////////////////////////////////////

	//! \name Operadores unarios

	/*! 
		\brief Devuelve una copia del Polinomio “p”: +p
		\post El polinomio devuelto es igual al polinomio “p”, es decir, tiene los mismos monomios
		\return Polinomio
	*/
	ed::Polinomio & operator+(ed::Polinomio const & p);

	/*! 
		\brief Devuelve el opuesto del Polinomio “p”: -p
		\post El  polinomio  devuelto  tiene  todos  sus  monomios  opuestos,  es  decir,  el mismo grado pero su coeficiente opuesto.
		\return Polinomio
	*/
	ed::Polinomio & operator-(ed::Polinomio const & p);


//////////////////////////////////////////////////////////////////////////////////////

	//! \name Operadores binarios de la suma

	/*! 
		\brief Devuelve otro polinomio que es la suma de dos polinomios:  p1 + p2
		\return Polinomio
	*/
	ed::Polinomio & operator+(ed::Polinomio const &p1, ed::Polinomio const &p2);

	/*! 
		\brief Devuelve otro polinomio que es la suma de un polinomio y un monomio.
		\return Polinomio
	*/
	ed::Polinomio & operator+(ed::Polinomio const &p, ed::Monomio const &m);

	/*! 
		\brief Devuelve otro polinomio que es la suma de un polinomio y un monomio.
		\return Polinomio
	*/
	ed::Polinomio & operator+(ed::Monomio const &m, ed::Polinomio const &p);

	/*! 
		\brief Devuelve otro polinomio que es la suma de un polinomio y un número real.
		\return Polinomio
	*/
	ed::Polinomio & operator+(ed::Polinomio const &p, double x);

	/*! 
		\brief Devuelve otro polinomio que es la suma de un polinomio y un número real.
		\return Polinomio
	*/
	ed::Polinomio & operator+(double x, ed::Polinomio const &p);

		
	//////////////////////////////////////////////////////////
	//! \name Operador binario de la resta

	/*! 
	\brief Devuelve otro polinomio que es la resta de dos polinomios:  p1 -p2
	\return Polinomio
	*/
	ed::Polinomio & operator-(ed::Polinomio const &p1, ed::Polinomio const &p2);

	/*! 
		\brief Devuelve otro polinomio que es la resta de un polinomio y un monomio.
		\return Polinomio
	*/
	ed::Polinomio & operator-(ed::Polinomio const &p, ed::Monomio const &m);

	/*! 
		\brief Devuelve otro polinomio que es la resta de un polinomio y un polinomio
		\return Polinomio
	*/
	ed::Polinomio & operator-(ed::Monomio const &m, ed::Polinomio const &p);

	/*! 
		\brief Devuelve otro polinomio que es la resta de un polinomio y un número real.
		\return Polinomio
	*/
	ed::Polinomio & operator-(ed::Polinomio const &p, double x);

	/*! 
		\brief Devuelve otro polinomio que es la resta de un número real y un polinomio
		\return Polinomio
	*/
	ed::Polinomio & operator-(double x, ed::Polinomio const &p);


	///////////////////////////////////////////////////////////////////////////
	//! \name Operadores binarios de la multiplicación

	/*! 
		\brief Devuelve otro polinomio que es la multiplicación de dos polinomios:  p1 * p2
		\return Polinomio
	*/
	ed::Polinomio & operator*(ed::Polinomio const &p1, ed::Polinomio const &p2);

	/*! 
		\brief Devuelve  otro  polinomio  que  es  la  multiplicación  de  un  polinomio  y  un monomio.
		\return Polinomio
	*/
	ed::Polinomio & operator*(ed::Polinomio const &p, ed::Monomio const &m);

	/*! 
		\brief Devuelve  otro  polinomio  que  es  la  multiplicación  de  un  polinomio  y  un polinomio.
		\return Polinomio
	*/
	ed::Polinomio & operator*(ed::Monomio const &m, ed::Polinomio const &p);

	/*! 
		\brief Devuelve  otro  polinomio  que  es  la  multiplicación  de  un  polinomio  y  un número real
		\return Polinomio
	*/
	ed::Polinomio & operator*(ed::Polinomio const &p, double x);

	/*! 
		\brief Devuelve  otro  polinomio  que  es la  multiplicación  de  un  número  real  y  un polinomio.
		\return Polinomio
	*/
	ed::Polinomio & operator*(double x, ed::Polinomio const &p);

	///////////////////////////////////////////////////////////////////////////

	//! \name Operadores binarios de la división

	/*! 
		\brief Devuelve otro polinomio que es la división de dos polinomios:  p1 / p2
		\preEl grado de p2es menor o igual que el grado de p1
		\return Polinomio
	*/
	ed::Polinomio & operator/(ed::Polinomio const &p1, ed::Polinomio const &p2);

	/*! 
		\brief Devuelve otro polinomio que es la división de un polinomio y un monomio.
		\pre El grado del monomio es menor o igual que el grado del polinomio
		\return Polinomio
	*/
	ed::Polinomio & operator/(ed::Polinomio const &p, ed::Monomio const &m);

	/*! 
		\brief Devuelve otro polinomio que es la división de un polinomio y un polinomio.
		\pre El grado del polinomio es menor o igual que el grado del monomio
		\return Polinomio
	*/
	ed::Polinomio & operator/(ed::Monomio const &m, ed::Polinomio const &p);

	/*! 
		\brief Devuelve otro polinomio que es la división de un polinomio y un número real.
		\pre El número “x” no es 0.0
		\return Polinomio
	*/
	ed::Polinomio & operator/(ed::Polinomio const &p, double x);

	/*! 
		\brief Devuelve otro polinomio que es la división de un número real y un polinomio
		\pre El polinomio tiene grado 0 y su coeficiente no es 0.0
		\return Polinomio
	*/
	ed::Polinomio & operator/(double x, ed::Polinomio const &p);

	/////////////////////////////////////////////////////////////////////////////

   //! \name Sobrecarga de los operadores de flujo de la clase Polinomio.

    /*! 
		\brief Lee desde el flujo de entrada un polinomio
		\return Stream
	*/
    ostream &operator<<(ostream &stream, ed::Polinomio const &p);

    /*! 
		\brief Escribe en el flujo de el polinomio
		\return Stream
	*/
    istream &operator>>(istream &stream, ed::Polinomio &p);

}  // Fin de namespace ed.

#endif // _OperadoresPolinomios_HPP_
