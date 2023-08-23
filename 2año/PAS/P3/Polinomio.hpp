/*!
   \file Polinomio.hpp
   \brief Definición de la clase Polinomio
*/

#ifndef _POLINOMIO_HPP_
#define _POLINOMIO_HPP_

// Control de asertos
#include <cassert>

// Vector de STL
#include <list>

// Para usar la función abs
#include <cmath>

#include "PolinomioInterfaz.hpp"
#include "Monomio.hpp"
#include "operadoresExternosMonomios.hpp"

using namespace std;

// Se incluye la clase Polinomio dentro del espacio de nombre de la asigantura: ed
namespace ed {

//!  Definición de la clase Polinomio que hereda de PolinomioInterfaz
class Polinomio: public ed::PolinomioInterfaz
{

  //! \name Atributos privados de la clase Polinomio
   private:
   	
 	list <Monomio> polinomio_;

   //! \name Funciones o métodos públicos de la clase Polinomio
   public:

   	//! \name Observadores: funciones de consulta de la clase Polinomio

	inline list <Monomio> getPolinomio() const {return polinomio_;};

	//! \name Mododificadores: funciones de modificación de la clase Polinomio

	inline void setPolinomio(list<Monomio> m) {polinomio_=m;};

	//! \name Constructores de la clase Polinomio

	/*! 
		\brief   Crea un nuevo monomio usando coeficiente 0.0 y grado 0
		\post El polinomio creado es nulo
	*/
  	Polinomio(){ //constructor simple

  		Monomio m;
  		polinomio_.push_back(m);

  		#ifndef NDEBUG

  		assert(this->esNulo());
  		assert(std::abs((polinomio_.front()).getCoeficiente()-0.0)<COTA_ERROR);
  		assert((polinomio_.front()).getGrado()==0);

  		#endif //NDEBUG

  	}

  	/*! 
		\brief Crea un nuevo polinomio a partir de otro polinomio
		\post El polinomio creado es igual al polinomio “p”
	*/
  	Polinomio(Polinomio const &p){ //constructor copia

  		this->setPolinomio(p.getPolinomio());

  		#ifndef NDEBUG

  		//assert(this->getPolinomio()==p.getPolinomio());

  		#endif //NDEBUG

  	}

  	//! \name Observadores: funciones de consulta de la clase Polinomio


  	/*! 
		\brief Comprueba si el Polinomio es igual al monomio de coeficiente 0.0 y grado 0
		\return bool
	*/
  	inline bool esNulo() const{

  		if((this->getPolinomio().size()>1)||(this->getPolinomio().size()==0))
  			return false;
  		else if(std::abs((this->getPolinomio().front().getCoeficiente()-0.0)<COTA_ERROR)&&(this->getPolinomio().front().getGrado()==0)&&(this->getPolinomio().size()==1))
  			return true;

  		return false;

  	}

  	/*! 
		\brief Obtiene el grado del polinomio
		\pre Los monomios están ordenados de mayor a menor grado
		\return int
	*/
  	inline int getGrado() const {return this->getPolinomio().front().getGrado();};

  	/*! 
		\brief Obtiene el número de monomios del polinomio
		\return int
	*/
	inline int getNumeroMonomios() const {

		if(std::abs((this->getPolinomio().back().getCoeficiente()-0.0)<COTA_ERROR)){return (this->getPolinomio().size())-1;}
  		else{return (this->getPolinomio().size());}

  	}

	/*! 
		\brief Comprueba si existe el monomio de grado indicado
		\pre El polinomio debe existir
		\return bool
	*/
	inline bool existeMonomio(int const &n) const {
		list <Monomio> aux=this->getPolinomio();
		list <Monomio> :: iterator i=aux.begin();
		while (i!=aux.end()) {
			if((*i).getGrado()==n)
			return true;
			i++;
		}
		return false;
	}

	/*! 
		\brief Obtiene el monomio de grado indicado
		\pre El polinomio debe existir
		\return Monomio
	*/
	inline Monomio getMonomio (int grado) const{
		Monomio m;
		list<Monomio> aux=this->getPolinomio();
		list<Monomio> :: iterator i=aux.begin();

		while(i!=aux.end()){
			if(grado==((*i).getGrado())){m=(*i);}
			i++;
		}
		return m;
	}


	//! \name Funciones de modificación de la clase Polinomio


 	////////////////////////////////////////////////////////////////

   //! \name Operadores de la clase Polinomio

	/*! 
		\brief Operador  de  asignación.  Operador  que  copia  un  polinomio  en  el  polinomio actual
		\pre El polinomio “p” debe ser diferente del polinomio actual.
		\post El polinomio actual debe ser igual al polinomio “p”.
		\return Polinomio
	*/
	Polinomio & operator=(Polinomio const &p);

	/*! 
		\brief Operador de asignación. Operador que copia un monomio en el polinomio actual
		\post El polinomio actual debe tener un único monomio que será igual al monomio “m”.
		\return Polinomio
	*/
	Polinomio & operator=(Monomio const &m);

	/*! 
		\brief Operador de asignación. Operador que copia un número en el polinomio actual
		\post El polinomio actual debe ser igual al número “x”.
		\return Polinomio
	*/
	Polinomio & operator=(double const &x);

  	// Operadores aritméticos y asignación

	/*! 
		\brief Operador de incremento y asignación con otro polinomio.
		\return Polinomio
	*/
	Polinomio & operator+=(Polinomio const &p);

	/*! 
		\brief Operador de incremento y asignación con un monomio.
		\return Polinomio
	*/
	Polinomio & operator+=(Monomio const &m);

	/*! 
		\brief Operador de incremento y asignación con un número real.
		\return Polinomio
	*/
	Polinomio & operator+=(double const &x);

	/*! 
		\brief Operador de decremento y asignación con otro polinomio.
		\return Polinomio
	*/
	Polinomio & operator-=(Polinomio const &p);

	/*! 
		\brief Operador de decremento y asignación con un monomio.
		\return Polinomio
	*/
	Polinomio & operator-=(Monomio const &m);

	/*! 
		\brief Operador de decremento y asignación con un número real.
		\return Polinomio
	*/
	Polinomio & operator-=(double const &x);

	/*! 
		\brief Operador de multiplicación y asignación por otro polinomio.
		\return Polinomio
	*/
	Polinomio & operator*=(Polinomio const &p);

	/*! 
		\brief Operador de multiplicación y asignación por un monomio.
		\return Polinomio
	*/
	Polinomio & operator*=(Monomio const &m);

	/*! 
		\brief Operador de multiplicación y asignación por un número real.
		\return Polinomio
	*/
	Polinomio & operator*=(double const &x);

	/*! 
		\brief Operador de división y asignación por otro polinomio.
		\pre El grado de polinomio actual es mayor o igual que el grado del polinomio “p”.
		\pre El polinomio “p” no es nulo.
		\return Polinomio
	*/
	Polinomio & operator/=(Polinomio const &p);

	/*! 
		\brief Operador de división y asignación por un monomio.
		\pre El grado del monomio debe ser menor o igual que el grado del polinomio actual.
		\pre El polinomio actualno es nulo.
		\return Polinomio
	*/
	Polinomio & operator/=(Monomio const &m);

	/*! 
		\brief Operador de división y asignación por un número real.
		\return Polinomio
	*/
	Polinomio & operator/=(double const &x);



	// COMPLETAR EL RESTO DE OPERADORES


  /////////////////////////////////////////////////////////////////////////////////////

	//! \name Funciones lectura y escritura de la clase Polinomio


	/*! 
		\brief Lee desde el teclado un polinomio.
	*/
	void leerPolinomio();

	/*! 
		\brief Escribe por pantalla el polinomio donde cada monomio tiene el formato:
	*/
	void escribirPolinomio();


	///////////////////////////////////////////////////////////////////////

	//! \name Funciones auxiliares de la clase Polinomio

	/*! 
		\brief Calcula el valor del polinomio para un número real “x”
		\return double
	*/
	inline double calcularValor(double valor) const {

		double sol=0;

		list<Monomio> aux=this->getPolinomio();
		list<Monomio> :: iterator i=aux.begin();

		while(i!=aux.end()){

			sol=sol+(pow(((*i).getCoeficiente()*valor),(double)(*i).getGrado()));

			i++;
		}

		return sol;
	}

	// Función auxiliar para comprobar la consistencia de la clase
	/*! 
		\brief Comprueba que el polinomio esta ordenado
		\return bool
	*/
	inline bool esta_ordenado(){

	list<Monomio> aux1=this->getPolinomio();
	list<Monomio> :: iterator i=aux1.begin();
	int aux=(*i).getGrado();

	if(aux1.size()==1){return true;}
	i++;

	while(i!=aux1.end()){
		if(aux<(*i).getGrado()){return false;}
		aux=(*i).getGrado();

		i++;
	}
	
	return true;
	}	


	// Función auxiliar para insertar un Monomio a la lista del polinomio
	/*! 
		\brief Añade un monomio a la lista del polinomio
	*/
	/*inline */void insertarMonomio(Monomio const &m);
/*
		Monomio m;
		m=z;
		list<Monomio> aux=this->getPolinomio();
		list<Monomio> :: iterator i=aux.begin();
		int contador=0;

		while(i!=aux.end()){
			if(m.getGrado()==(*i).getGrado()){
				(*i).setCoeficiente(m.getCoeficiente()+(*i).getCoeficiente());
				contador++;
			}
			i++;
		}
		if(contador==0){
			list<Monomio> aux2=this->getPolinomio();
			list<Monomio> :: iterator y=aux2.rbegin();
			while((y!=aux2.rend())&&(contador!=0)){
				if(m.getGrado()>(*y).getGrado()){
					aux2.insert(y,m);
					contador++;
				}
				y++;
			}

			this->setPolinomio(aux2);

		}else{this->setPolinomio(aux);}
*/
		/*list <Monomio> aux;
		if (m.getGrado()>this->getGrado()) {
			for (int i = 0; i <= this->getGrado(); i++) {
				if (this->existeMonomio(i)) {
					aux.push_front(this->getMonomio(i));
				}
			}
			aux.push_front(m);
		}else{
			for (int i = 0; i <= this->getGrado(); i++) {
				if ((this->existeMonomio(i))&&(m.getGrado()==this->getMonomio(i).getGrado())){
					aux.push_front(this->getMonomio(i)+m);
					if ((aux.front().getCoeficiente()-0.0)<COTA_ERROR) {
						aux.pop_front();
					}
				}else if((this->existeMonomio(i))&&!(m.getGrado()==this->getMonomio(i).getGrado()))
					aux.push_front(this->getMonomio(i));
				else if(!(this->existeMonomio(i))&&(i==m.getGrado()))
					aux.push_front(m);
			}
		}
		this->setPolinomio(aux);
	}*/
}; // Fin de la definición de la clase Polinomio


} // \brief Fin de namespace ed.

//  _POLINOMIO_HPP_
#endif
