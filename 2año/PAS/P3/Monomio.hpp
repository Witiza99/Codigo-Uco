/*! 
	\file Monomio.hpp
	\brief Definición de la clase Monomio
*/

#ifndef _MONOMIO_HPP_
#define _MONOMIO_HPP_

// Para usar la funciones pow y std::abs
#include <cmath>

// Para controlar las pre y post condiciones mediante asertos
#include <cassert>
#include <iostream>

#define COTA_ERROR 1.0e-6  //!< Cota de error para la comparación números reales

// Se incluye la clase Monomio dentro del espacio de nombre de la asigantura: ed
namespace ed
{
//!  Definición de la clase Monomio:  \f$ coeficiente \hspace{1ex} X^{grado} \f$ 
class Monomio
{
	//! \name Atributos privados de la clase Monomio
	private: 

	//número real que representa el coeficiente del monomio
	double coeficiente_;

	//número natural que representa el grado del monomio
	int grado_;

	//! \name Funciones o métodos públicos de la clase Monomio
	public:

	//! \name Constructores de la clase Monomio

	/*! 
		\brief   Crea un monomio a partir de un coeficiente y un grado
		\pre El grado es mayor o igual que 0
		\post El coeficiente del monomio es igual al valor del parámetro “coeficiente”
		\post El grado del monomio es igual al valor del parámetro “grado”.
	*/
	inline Monomio(double coeficiente = 0.0, int grado = 0){

		//se comprueba la precondicion

		#ifndef NDEBUG

			assert(grado >= 0);

		#endif // NDEBUG

			this->setCoeficiente(coeficiente);
			this->setGrado(grado);

		//se comprueban las postcondiciones

		#ifndef NDEBUG

			assert(std::abs(this->getCoeficiente()-coeficiente) < COTA_ERROR);
			assert(this->getGrado() == grado);

		#endif // NDEBUG

	}
	/*! 
		\brief   Crea un monomio a partir de un objeto de la clase Monomio
		\post El coeficiente del monomio creado es igual al coeficiente del monomio “m”
		\post El grado del monomio creado es igual al grado del monomio “m”
	*/
	inline Monomio(Monomio const &m){

		if(m.getGrado() >= 0){

		this->setCoeficiente(m.getCoeficiente());
		this->setGrado(m.getGrado());

		}

		#ifndef NDEBUG

			assert(std::abs(this->getCoeficiente()-m.getCoeficiente()) < COTA_ERROR);
			assert(this->getGrado() == m.getGrado());

		#endif // NDEBUG

	}


	//! \name Observadores: funciones de consulta de la clase Monomio

	/*! 
		\brief   Observador de la variable coeficiente_
		\return  double
	*/
	inline double getCoeficiente() const {return coeficiente_;};
	/*! 
		\brief   Observador de la variable coeficiente_
		\return int
	*/
	inline int getGrado() const {return grado_;};

	//! \name Funciones de modificación de la clase Monomio

	/*! 
		\brief   Modificador de la variable coeficiente_
		\post El coeficiente del monomio es igual al número real “x”
	*/
	inline void setCoeficiente(double coeficiente) {

		coeficiente_ = coeficiente;

		#ifndef NDEBUG

		assert(std::abs(this->getCoeficiente()-coeficiente) < COTA_ERROR);

		#endif //NDEBUG

	};

	/*! 
		\brief   Modificador de la variable grado_
		\pre El número entero “n” es mayor o igual que 0
		\post El grado del monomio es igual al número entero “n”
	*/
	inline void setGrado(int grado) {

		grado_ = grado;

		#ifndef NDEBUG

		assert(this->getGrado() == grado);

		#endif //NDEBUG

	};

	/////////////////////////////////////////////////

	//! \name Operadores de la clase Monomio

	// Operadores de asignación

		/*! 
		\brief   Operador = de la clase monomio pasandole como argumento un objeto de la clase monomio
		\return Objeto de la clase Monomio
		\post El coeficiente del monomio es igual al coeficiente del monomio “m”
		\post El grado del monomio es igual al grado del monomio “m”
		*/
		Monomio & operator=(Monomio const &m);

		/*! 
		\brief   Operador = de la clase monomio pasandole como argumento una variable de tipo double
		\return Objeto de la clase Monomio
		\post El grado del monomio es igual 0
		\post El coeficiente del monomio es igual al número real “x”
		*/
		Monomio & operator=(double const &x);


	// Operadores aritméticos y asignación

		/*! 
		\brief   Operador += de la clase monomio pasandole como argumento un objeto de la clase monomio
		\return Objeto de la clase Monomio
		\pre El monomio “m” tiene el mismo grado que el monomio actual
		\post El coeficiente del monomio actual se ha incrementado con el coeficiente del monomio “m”
		\post El grado del monomio actual no ha sido modificado
		*/
		Monomio & operator+=(Monomio const &m);

		/*! 
		\brief   Operador -= de la clase monomio pasandole como argumento un objeto de la clase monomio
		\return Objeto de la clase Monomio
		\pre El monomio “m” tiene el mismo grado que el monomio actual
		\post El coeficiente del monomio actual se ha decrementado con el coeficiente del monomio “m”
		\post El grado del monomio actual no ha sido modificado
		*/
		Monomio & operator-=(Monomio const &m);

		/*! 
		\brief   Operador *= de la clase monomio pasandole como argumento un objeto de la clase monomio
		\return Objeto de la clase Monomio
		\post El coeficiente del monomio actual se ha multiplicado por el coeficiente del monomio “m”
		\post El grado del monomio actual se ha incrementado con el grado del monomio “m”
		*/
		Monomio & operator*=(Monomio const &m);

		/*! 
		\brief   Operador /= de la clase monomio pasandole como argumento un objeto de la clase monomio
		\return Objeto de la clase Monomio
		\pre El grado del monomio “m” es igual o inferior al grado del monomio actual
		\pre El coeficiente del monomios “m” no es 0.0
		\post El coeficiente del monomio actual se ha decrementado con el coeficiente del monomio “m”
		\post El grado del monomio actual se ha incrementado con el grado del monomio “m”
		*/
		Monomio & operator/=(Monomio const &m);

		/*! 
		\brief   Operador *= de la clase monomio pasandole como argumento una variable de tipo double
		\return Objeto de la clase Monomio
		\post El coeficiente del monomio actual se ha multiplicado por el número real “x”
		\post El grado del monomio actual no ha sido modificado
		
		*/
		Monomio & operator*=(double &m);

		/*! 
		\brief   Operador /= de la clase monomio pasandole como argumento una variable de tipo double
		\return Objeto de la clase Monomio
		\pre El número real “x” no es 0.0
		\post El coeficiente del monomio actual se ha dividido por el número real “x”
		\post El grado del monomio actual no ha sido modificado
		*/
		Monomio & operator/=(double &m);


	/////////////////////////////////////////////////////////////////////////////////////

	//! \name Funciones lectura y escritura de la clase Monomio

	/*! 
		\brief   Funcion que permite la lectura de un Monomio
		\post El grado del monomio es mayor o igual que 0
	*/
	void leerMonomio();

	/*! 
		\brief   Funcion que permite la escritura de un Monomio
	*/
	void escribirMonomio();


	///////////////////////////////////////////////////////////////////////

	//! \name Métodos la clase Monomio

	/*! 
		\brief   Funcion que calcula el valor de un monomio
		\return double
	*/
	double calcularValor(int v);

	///////////////////////////////////////////////////////////////////////


};  // Fin de la definición de la clase Monomio

}  //  Fin de namespace ed.

// _MONOMIO_HPP_
#endif
