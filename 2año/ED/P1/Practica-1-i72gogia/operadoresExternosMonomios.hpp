/*! 
	\file operadoresExternosMonomios.hpp
	\brief Ficheros con los prototipos de los operadores externos de la clase Monomio
*/

#ifndef _OperadoresExternosMonomios_HPP_
#define _OperadoresExternosMonomios_HPP_

// Facilita la entrada y salida
#include <iostream>

#include "Monomio.hpp"

// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

// Espacio de nombre de la asignatura: ed
namespace ed
{
//////////////////////////////////////////////////////////////////////////////////////
	// Operadores externos que no pertenecen a la clase Monomio

	//! \name Operadores de igualdad  

	/*! 
		\brief   Operador == externo de la clase monomio que pasandole dos argumentos objeto de la clase monomio comprueba que uno es igual a otro
		\return bool
		\post El valor devuelto es verdadero si los dos monomios tienen el mismo grado y el mismo coeficiente
		\post El valor devuelto es falso, en caso contrario
	*/
	bool operator==(ed::Monomio const & m1, ed::Monomio const & m2);

	/*! 
		\brief   Operador == externo de la clase monomio que pasandole un argumento objeto de la clase monomio y un double comprueba que uno es igual a otro
		\return bool
		\post El valor devuelto es verdadero si el monomio tiene grado 0 y su coeficiente es igual al número “x”
		\post El valor devuelto es falso, en caso contrario
	*/
	bool operator==(ed::Monomio const & m1, double m);

	/*! 
		\brief   Operador == externo de la clase monomio que pasandole un double y un argumento objeto de la clase monomio comprueba que uno es igual a otro
		\return bool
		\post El valor devuelto es verdadero si el monomio tiene grado 0 y su coeficiente es igual al número “x”
		\post El valor devuelto es falso, en caso contrario
	*/
	bool operator==(double m, ed::Monomio const & m2);


	//! \name Operadores de desigualdad 

	/*! 
		\brief   Operador != externo de la clase monomio que pasandole dos argumentos objeto de la clase monomio comprueba que uno es diferente a otro
		\return bool
		\post El valor devuelto es verdadero si los dos monomios no tienen el mismo grado o no tienen el mismo coeficiente
		\post El valor devuelto es falso, en caso contrario
	*/
	bool operator!=(ed::Monomio const & m1, ed::Monomio const & m2);

	/*! 
		\brief   Operador != externo de la clase monomio que pasandole un argumento objeto de la clase monomio y un double comprueba que uno es diferente a otro
		\return bool
		\post El valor devuelto es verdadero si el monomio no tiene grado 0 o si su coeficiente no es igual al número “x”
		\post El valor devuelto es falso, en caso contrario
	*/
	bool operator!=(ed::Monomio const & m1, double m);

	/*! 
		\brief   Operador != externo de la clase monomio que pasandole un double y un argumento objeto de la clase monomio comprueba que uno es diferente a otro
		\return bool
		\post El valor devuelto es verdadero si el monomio no tiene grado 0 o si su coeficiente no es igual al número “x”
		\post El valor devuelto es falso, en caso contrario
	*/
	bool operator!=(double m, ed::Monomio const & m2);

	///////////////////////////////////////////////////

	//! \name Operadores unarios prefijos

	/*! 
		\brief   Operador + externo de la clase monomio que pasandole un argumento objeto de la clase monomio añade el monomio a el mismo
		\return Objeto de clase monomio
		\post El monomio devuelto es igual al monomio “m”, es decir, tiene el mismo grado y el mismo coeficiente
	*/
	ed::Monomio & operator+(ed::Monomio const & m);

	/*! 
		\brief   Operador - externo de la clase monomio que pasandole un argumento objeto de la clase monomio añade el monomio a el mismo pero con el coeficiente negativo
		\return Objeto de clase monomio
		\post El monomio devuelto tiene el mismo grado que el monomio “m” pero su coeficiente es el opuesto
	*/
	ed::Monomio & operator-(ed::Monomio const & m);

	//////////////////////////////////////////////////////////

	//! \name Operador binario de la suma 

	/*! 
		\brief   Operador + externo de la clase monomio que pasandole dos argumentos objeto de la clase monomio los suma entre si
		\return Objeto de clase monomio
		\pre Los monomios m1 y m2 tienen el mismo grado
		\post El monomio devuelto tiene el mismo grado que los monomios m1 y m2
		\post El monomio devuelto tiene y su coeficiente es la suma de los coeficientes de los monomios
	*/
	ed::Monomio & operator+ (ed::Monomio const &m1, ed::Monomio const &m2);


	//////////////////////////////////////////////////////////
	//! \name Operador binario de la resta 

	/*! 
		\brief   Operador - externo de la clase monomio que pasandole dos argumentos objeto de la clase monomio los resta entre si
		\return Objeto de clase monomio
		\pre Los monomios m1 y m2 tienen el mismo grado.
		\post El monomio devuelto tiene el mismo grado que los monomios m1 y m2
		\post El coeficiente del monomio es la resta de los coeficientes de los monomios m1 y m2
	*/
	ed::Monomio & operator- (ed::Monomio const &m1, ed::Monomio const &m2);


	///////////////////////////////////////////////////////////////////////////
	//! \name Operadores binarios de la multiplicación 

	/*! 
		\brief   Operador * externo de la clase monomio que pasandole dos argumentos objeto de la clase monomio los multiplica entre si
		\return Objeto de clase monomio
		\post El monomio devuelto tiene un grado que es la suma de los grados de los monomios m1 y m2
		\post El coeficiente del monomio es el producto de los coeficientes de los monomios m1 y m2
	*/
	ed::Monomio & operator* (ed::Monomio const &m1, ed::Monomio const &m2);

	/*! 
		\brief   Operador * externo de la clase monomio que pasandole un argumentos objeto de la clase monomio y un double los multiplica entre si
		\return Objeto de clase monomio
		\post El monomio devuelto tiene el mismo grado que el monomio “m”
		\post El coeficiente del monomio es el producto del coeficiente del monomio “m” por el número “x”
	*/
	ed::Monomio & operator* (ed::Monomio const &m1, double m);

	/*! 
		\brief   Operador * externo de la clase monomio que pasandole un double y un argumento objeto de la clase monomio los multiplica entre si
		\return Objeto de clase monomio
		\post El monomio devuelto tiene el mismo grado que el monomio “m”
		\post El coeficiente del monomio es el producto del coeficiente del monomio “m” por el número “x”
	*/
	ed::Monomio & operator* (double m, ed::Monomio const &m2);

	///////////////////////////////////////////////////////////////////////////

	//! \name Operadores binarios de la división 

	/*! 
		\brief   Operador / externo de la clase monomio que pasandole dos argumentos objeto de la clase monomio los divide entre si
		\return Objeto de clase monomio
		\pre El grado del monomio m2 es menor o igual que el grado del monomio m1
		\pre El coeficiente del monomio m2 no es 0.0
		\post El monomio devuelto tiene un grado que es la resta de los grados de los monomios m1 y m2
		\post El coeficiente del monomio es la división de los coeficientes de los monomios m1 y m2
	*/
	ed::Monomio & operator/ (ed::Monomio const &m1, ed::Monomio const &m2);

	/*! 
		\brief   Operador / externo de la clase monomio que pasandole un argumento objeto de la clase monomio y un double los multiplica entre si
		\return Objeto de clase monomio
		\pre El número “x” no es 0.0
		\post El monomio devuelto tiene el mismo grado que el monomio “m”
		\post El coeficiente del monomio es la división del coeficiente del monomio “m” por el número “x”
	*/
	ed::Monomio & operator/ (ed::Monomio const &m1, double m);

	/*! 
		\brief   Operador / externo de la clase monomio que pasandole un double y un argumento objeto de la clase monomio los divide entre si
		\return Objeto de clase monomio
		\pre El grado del monomio es 0 y su coeficiente es distinto de 0.0
		\post El monomio devuelto tiene grado igual a 0
		\post El coeficiente del monomio es la división del número “x” por el coeficiente del monomio “m”
	*/
	ed::Monomio & operator/ (double m, ed::Monomio const &m2);


	/////////////////////////////////////////////////////////////////////////////

	//! \name Sobrecarga de los operadores de entrada y salida 

	/*! 
		\brief   Operador >> externo de la clase monomio que pasandole un stream y un argumento objeto de la clase monomio permite introducirlo en un monomio
		\return stream
	*/
	istream &operator>>(istream &stream, ed::Monomio &m);

	/*! 
		\brief   Operador << externo de la clase monomio que pasandole un stream y un argumento objeto de la clase monomio permite escribir un monomio
		\return stream
	*/
	ostream &operator<<(ostream &stream, ed::Monomio const &m);

}  // Fin de namespace ed.

#endif // _OperadoresExternosMonomios_HPP_


