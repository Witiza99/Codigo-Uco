/*! 
   \file  Monomio.cpp
   \brief Fichero que contiene el código de las funciones de la clase Monomio
*/


//  Ficheros de cabecera
#include <iostream>

#include "Monomio.hpp"

// Operadores de asignación

ed::Monomio & ed::Monomio::operator=(ed::Monomio const &m)
{
	this->setCoeficiente(m.getCoeficiente());
	this->setGrado(m.getGrado());

	#ifndef NDEBUG

	assert(std::abs(this->getCoeficiente()-m.getCoeficiente()) < COTA_ERROR);
	assert(this->getGrado() == m.getGrado());

	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;
}


ed::Monomio & ed::Monomio::operator=(double const &x)
{
	int valor = 0;
	this->setGrado(valor);
	this->setCoeficiente(x);

	#ifndef NDEBUG

	assert(this->getGrado() == 0);
	assert(std::abs(this->getCoeficiente()-x)< COTA_ERROR);

	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;
}

//////////////////////////////////////////////////////////////

// Operadores aritméticos y asignación

ed::Monomio & ed::Monomio::operator+=(ed::Monomio const &m)
{
	#ifndef NDEBUG

	assert(this->getGrado()==m.getGrado());

	int auxi;
	double auxd;

	auxi=this->getGrado();
	auxd=this->getCoeficiente();

	#endif //NDEBUG

	this->setCoeficiente(this->getCoeficiente() + m.getCoeficiente());

	#ifndef NDEBUG

	assert(std::abs((this->getCoeficiente()-m.getCoeficiente()) - auxd) < COTA_ERROR);
	assert(auxi == getGrado());

	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;
}

ed::Monomio & ed::Monomio::operator-=(ed::Monomio const &m)
{
	#ifndef NDEBUG

	assert(this->getGrado()==m.getGrado());

	int auxi;
	double auxd;

	auxi=this->getGrado();
	auxd=this->getCoeficiente();

	#endif //NDEBUG

	this->setCoeficiente(this->getCoeficiente() - m.getCoeficiente());

	#ifndef NDEBUG

	assert(std::abs((this->getCoeficiente()+m.getCoeficiente()) - auxd) < COTA_ERROR);
	assert(auxi == getGrado());

	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;
}

ed::Monomio & ed::Monomio::operator*=(ed::Monomio const &m)
{
	#ifndef NDEBUG

	int auxi;
	double auxd;

	auxi=this->getGrado();
	auxd=this->getCoeficiente();

	#endif //NDEBUG

	this->setCoeficiente(this->getCoeficiente() * m.getCoeficiente());
	this->setGrado(this->getGrado() + m.getGrado());

	#ifndef NDEBUG

	assert(std::abs((this->getCoeficiente()/m.getCoeficiente()) - auxd) < COTA_ERROR);
	assert((this->getGrado()-m.getGrado()) == auxi);

	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;
}

ed::Monomio & ed::Monomio::operator/=(ed::Monomio const &m)
{
	#ifndef NDEBUG

	assert(m.getCoeficiente()!=0);

	int auxi;
	double auxd;

	auxi=this->getGrado();
	auxd=this->getCoeficiente();

	#endif //NDEBUG

	this->setCoeficiente(this->getCoeficiente() / m.getCoeficiente());
	this->setGrado(this->getGrado() - m.getGrado());

	#ifndef NDEBUG

	assert(std::abs((this->getCoeficiente()*m.getCoeficiente()) - auxd) < COTA_ERROR);
	assert((this->getGrado()+m.getGrado()) == auxi);

	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;
}

ed::Monomio & ed::Monomio::operator*=(double &m)
{

	#ifndef NDEBUG

	int auxi;
	double auxd;

	auxi=this->getGrado();
	auxd=this->getCoeficiente();

	#endif //NDEBUG

	this->setCoeficiente(this->getCoeficiente() * m);

	#ifndef NDEBUG

	assert(std::abs((this->getCoeficiente()/m) - auxd) < COTA_ERROR);
	assert(this->getGrado()==auxi);

	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;
}

ed::Monomio & ed::Monomio::operator/=(double &m)
{
	#ifndef NDEBUG

	assert(m!=0);

	int auxi;
	double auxd;

	auxi=this->getGrado();
	auxd=this->getCoeficiente();

	#endif //NDEBUG

	this->setCoeficiente(this->getCoeficiente() / m);

	#ifndef NDEBUG

	assert(std::abs((this->getCoeficiente()*m) - auxd) < COTA_ERROR);
	assert(this->getGrado() == auxi);

	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;
}

///////////////////////////////////////////////////////////////////////

// Funciones lectura y escritura de la clase Monomio

void ed::Monomio::leerMonomio(){
	int auxi;
	double auxd;

	std::cout << "Introduce el coeficiente del monomio" << std::endl;
	std::cin >> auxd;
	this->setCoeficiente(auxd);

	do{
	std::cout << "Introduce el grado del monomio" << std::endl;
	std::cin >> auxi;
	
	if(auxi<0){std::cout << "El numero introducido no es correcto intentalo de nuevo" << std::endl;}

	}while(auxi<0);

	this->setGrado(auxi);

	#ifndef NDEBUG

	assert(this->getGrado() >= 0);

	#endif //NDEBUG
}

 void ed::Monomio::escribirMonomio(){

 	if(this->getCoeficiente()==-1){

 		std::cout << "-";

 	}else{

 		if(this->getCoeficiente()==1){

 		}
 	}

 	if(this->getGrado()!=1){

 		std::cout << this->getCoeficiente();

 		if(this->getGrado()!=0){

 			std::cout << "X^" << this->getGrado();

 		}

 	}else{std::cout << "X";}

 }


///////////////////////////////////////////////////////////////////////

// Funciones auxiliares de la clase Monomio

double ed::Monomio::calcularValor(int v){

	double resultado;

	resultado=pow(v,this->getGrado());

	resultado=resultado*this->getCoeficiente();

	return resultado;
}
