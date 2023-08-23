/*! 
   \file  operadoresExternosMonomios.cpp
	\brief Ficheros con el código de los operadores externos de la clase Monomio
*/


//  Ficheros de cabecera
#include <iostream>

#include "operadoresExternosMonomios.hpp"


//  Se incluyen los operadores sobrecargados dentro del espacio de nombres ed
namespace ed 
{
	// Operadores de igualdad

	bool operator==(ed::Monomio const & m1, ed::Monomio const & m2)
	{
		int valor=0;

		if((std::abs(m1.ed::Monomio::getCoeficiente()-m2.ed::Monomio::getCoeficiente()) < COTA_ERROR)&&(m1.ed::Monomio::getGrado()==m2.ed::Monomio::getGrado())){

			valor=1;

		}

		if(valor==1){

			#ifndef NDBUG

			assert(1==valor);

			#endif //NDEBUG

			return true;

		}else{

			#ifndef NDBUG

			assert(1!=valor);

			#endif //NDEBUG

			return false;
		}

	}

	bool operator==(ed::Monomio const & m1, double m){

		int valor=0;

		if((std::abs(m1.ed::Monomio::getCoeficiente()-m) < COTA_ERROR)&&(m1.ed::Monomio::getGrado()==0)){

			valor=1;

		}

		if(valor==1){

			#ifndef NDBUG

			assert(1==valor);

			#endif //NDEBUG

			return true;

		}else{

			#ifndef NDBUG

			assert(1!=valor);

			#endif //NDEBUG

			return false;
		}

	}

	bool operator==(double m, ed::Monomio const & m2){

		int valor=0;

		if((std::abs(m-m2.ed::Monomio::getCoeficiente()) < COTA_ERROR)&&(0==m2.ed::Monomio::getGrado())){

			valor=1;

		}

		if(valor==1){

			#ifndef NDBUG

			assert(1==valor);

			#endif //NDEBUG

			return true;

		}else{

			#ifndef NDBUG

			assert(1!=valor);

			#endif //NDEBUG

			return false;
		}

	}

	// Operadores de desigualdad

	// COMPLETAR
	bool operator!=(ed::Monomio const & m1, ed::Monomio const & m2)
	{
		int valor=0;

		if((std::abs(m1.ed::Monomio::getCoeficiente()-m2.ed::Monomio::getCoeficiente()) >= COTA_ERROR)||(m1.ed::Monomio::getGrado()!=m2.ed::Monomio::getGrado())){

			valor=1;

		}

		if(valor==1){

			#ifndef NDBUG

			assert(1==valor);

			#endif //NDEBUG

			return true;

		}else{

			#ifndef NDBUG

			assert(1!=valor);

			#endif //NDEBUG

			return false;
		}

	}

	bool operator!=(ed::Monomio const & m1, double m)
	{
		int valor=0;

		if((std::abs(m1.ed::Monomio::getCoeficiente()-m) >= COTA_ERROR)||(m1.ed::Monomio::getGrado()!=0)){

			valor=1;

		}

		if(valor==1){

			#ifndef NDBUG

			assert(1==valor);

			#endif //NDEBUG

			return true;

		}else{

			#ifndef NDBUG

			assert(1!=valor);

			#endif //NDEBUG

			return false;
		}

	}

	bool operator!=(double m, ed::Monomio const & m2)
	{
		int valor=0;

		if((std::abs(m-m2.ed::Monomio::getCoeficiente()) >= COTA_ERROR)||(0!=m2.ed::Monomio::getGrado())){

			valor=1;

		}

		if(valor==1){

			#ifndef NDBUG

			assert(1==valor);

			#endif //NDEBUG

			return true;

		}else{

			#ifndef NDBUG

			assert(1!=valor);

			#endif //NDEBUG

			return false;
		}

	}
	

	////////////////////////////////////////////////////////////

	// Operadores unarios prefijos 

	ed::Monomio & operator+(ed::Monomio const & m)
	{
		
		ed::Monomio *nuevo = new ed::Monomio();

		nuevo->setCoeficiente(m.getCoeficiente());
		nuevo->setGrado(m.getGrado());

		#ifndef NDEBUG

		assert(std::abs(m.getCoeficiente()-nuevo->getCoeficiente()) < COTA_ERROR);
		assert(m.getGrado()==nuevo->getGrado());

		#endif //NDEBUG
		
		return *nuevo;
	}

	ed::Monomio & operator-(ed::Monomio const & m)
	{
		
		ed::Monomio *nuevo = new ed::Monomio();

		nuevo->setCoeficiente(-m.getCoeficiente());
		nuevo->setGrado(m.getGrado());

		#ifndef NDEBUG

		assert(std::abs(m.getCoeficiente()+nuevo->getCoeficiente()) < COTA_ERROR);
		assert(m.getGrado()==nuevo->getGrado());

		#endif //NDEBUG
		
		return *nuevo;
	}

	////////////////////////////////////////////////////////////
	// Operadores aritméticos binarios

	// Suma
	ed::Monomio & operator+ (ed::Monomio const &m1, ed::Monomio const &m2)
	{

		ed::Monomio *nuevo = new ed::Monomio();

		#ifndef NDEBUG

		assert(m1.getGrado()==m2.getGrado());

		#endif //NDEBUG

		nuevo->setGrado(m1.getGrado());
		nuevo->setCoeficiente(m1.getCoeficiente()+m2.getCoeficiente());

		#ifndef NDEBUG

		assert(nuevo->getGrado()==m1.getGrado());
		assert(nuevo->getGrado()==m2.getGrado());
		assert(std::abs(nuevo->getCoeficiente()-(m1.getCoeficiente()+m2.getCoeficiente())) < COTA_ERROR);

		#endif //NDEBUG

		return *nuevo;
	}


	////////////
	// Resta

	ed::Monomio & operator- (ed::Monomio const &m1, ed::Monomio const &m2)
	{

		ed::Monomio *nuevo = new ed::Monomio();

		#ifndef NDEBUG

		assert(m1.getGrado()==m2.getGrado());

		#endif //NDEBUG

		nuevo->setGrado(m1.getGrado());
		nuevo->setCoeficiente(m1.getCoeficiente()-m2.getCoeficiente());

		#ifndef NDEBUG

		assert(nuevo->getGrado()==m1.getGrado());
		assert(nuevo->getGrado()==m2.getGrado());
		assert(std::abs(nuevo->getCoeficiente()-(m1.getCoeficiente()-m2.getCoeficiente())) < COTA_ERROR);

		#endif //NDEBUG

		return *nuevo;
	}


	//////////////////
	// Multiplicación

	ed::Monomio & operator* (ed::Monomio const &m1, ed::Monomio const &m2)
	{

		ed::Monomio *nuevo = new ed::Monomio();

		nuevo->setGrado(m1.getGrado()+m2.getGrado());
		nuevo->setCoeficiente(m1.getCoeficiente()*m2.getCoeficiente());

		#ifndef NDEBUG

		assert(nuevo->getGrado()==(m1.getGrado()+m2.getGrado()));

		assert(std::abs(nuevo->getCoeficiente()-(m1.getCoeficiente()*m2.getCoeficiente())) < COTA_ERROR);

		#endif //NDEBUG

		return *nuevo;
	}

	ed::Monomio & operator* (ed::Monomio const &m1, double m)
	{

		ed::Monomio *nuevo = new ed::Monomio();

		nuevo->setGrado(m1.getGrado());
		nuevo->setCoeficiente(m1.getCoeficiente()*m);

		#ifndef NDEBUG

		assert(nuevo->getGrado()==m1.getGrado());

		assert(std::abs(nuevo->getCoeficiente()-(m1.getCoeficiente()*m)) < COTA_ERROR);

		#endif //NDEBUG

		return *nuevo;
	}

	ed::Monomio & operator* (double m, ed::Monomio const &m2)
	{

		ed::Monomio *nuevo = new ed::Monomio();

		nuevo->setGrado(m2.getGrado());
		nuevo->setCoeficiente(m2.getCoeficiente()*m);

		#ifndef NDEBUG

		assert(nuevo->getGrado()==m2.getGrado());

		assert(std::abs(nuevo->getCoeficiente()-(m2.getCoeficiente()*m)) < COTA_ERROR);

		#endif //NDEBUG

		return *nuevo;
	}

	////////////
	// División

	ed::Monomio & operator/ (ed::Monomio const &m1, ed::Monomio const &m2)//preguntar al profesor si no se cumple una precondicion
	{

		#ifndef NDEBUG

		assert(m1.getGrado() >= m2.getGrado());
		assert(std::abs(m2.getCoeficiente() )> COTA_ERROR);

		#endif //NDEBUG

		ed::Monomio *nuevo = new ed::Monomio();

		nuevo->setGrado(m1.getGrado()-m2.getGrado());
		nuevo->setCoeficiente(m1.getCoeficiente()/m2.getCoeficiente());

		#ifndef NDEBUG

		assert(nuevo->getGrado()==(m1.getGrado()-m2.getGrado()));

		assert(std::abs(nuevo->getCoeficiente()-(m1.getCoeficiente()/m2.getCoeficiente())) < COTA_ERROR);

		#endif //NDEBUG

		return *nuevo;
	}

	ed::Monomio & operator/ (ed::Monomio const &m1, double m)
	{

		#ifndef NDEBUG

		assert(m!=0);

		#endif //NDEBUG

		ed::Monomio *nuevo = new ed::Monomio();

		nuevo->setGrado(m1.getGrado());
		nuevo->setCoeficiente(m1.getCoeficiente()/m);

		#ifndef NDEBUG

		assert(nuevo->getGrado()==m1.getGrado());

		assert(std::abs(nuevo->getCoeficiente()-(m1.getCoeficiente()/m)) < COTA_ERROR);

		#endif //NDEBUG

		return *nuevo;
	}

	ed::Monomio & operator/ (double m, ed::Monomio const &m2)
	{

		#ifndef NDEBUG

		assert(m2.getGrado()==0);
		assert(m2.getCoeficiente()!=0);

		#endif //NDEBUG

		ed::Monomio *nuevo = new ed::Monomio();

		nuevo->setGrado(0);
		nuevo->setCoeficiente(m/m2.getCoeficiente());

		#ifndef NDEBUG

		assert(nuevo->getGrado()==0);
		assert(nuevo->getCoeficiente()-(m/m2.getCoeficiente()) < COTA_ERROR);

		#endif //NDEBUG

		return *nuevo;
	}


	/////////////////////////////////////////////////////////////////////////////

	//  Sobrecarga del operador de entrada
	istream &operator>>(istream &stream, ed::Monomio &m) 
	{	
		double coeficiente;
		int grado;
		do{

		stream >> coeficiente >> grado;

		if(grado<0){std::cout << "El numero introducido no es correcto intentalo de nuevo" << std::endl;}

		}while(grado<0);

		m.setCoeficiente(coeficiente);
		m.setGrado(grado);

		return stream;
	}


	//  Sobrecarga del operador de salida
	ostream &operator<<(ostream &stream, ed::Monomio const &m) 
	{
		stream << m.getCoeficiente() << " " << m.getGrado() << std::endl;

		return stream;
	}

}  // namespace ed
