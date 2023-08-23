/*!
   \file Polinomio.cpp
   \brief Fichero que contiene el código de las funciones de la clase Polinomio
*/


// Ficheros de cabecera
#include <iostream>

#include "Polinomio.hpp"

// Operadores de asignación

// COMPLETAR


/////////////////////////////////////////////////////////////

ed::Polinomio & ed::Polinomio::operator=(ed::Polinomio const &p)
{
	#ifndef NDEBUG

  	assert(this->getPolinomio()!=p.getPolinomio());

  	#endif //NDEBUG

  	this->setPolinomio(p.getPolinomio());

	#ifndef NDEBUG

	assert(this->getPolinomio()==p.getPolinomio());

	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;
}


ed::Polinomio & ed::Polinomio::operator=(ed::Monomio const &m)
{
	
	Polinomio p;
	list<Monomio> aux=p.getPolinomio();
	aux.pop_back();
	aux.push_front(m);
	p.setPolinomio(aux);
	this->setPolinomio(p.getPolinomio());

	#ifndef NDEBUG

	assert(std::abs((this->getPolinomio().front()).getCoeficiente()-m.getCoeficiente())<COTA_ERROR);
  	assert((this->getPolinomio().size())==1);

	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;
}


ed::Polinomio & ed::Polinomio::operator=(double const &x)
{
	
	Monomio m(x);
	Polinomio p;
	list<Monomio> aux=p.getPolinomio();
	aux.pop_back();
	aux.push_front(m);
	p.setPolinomio(aux);
	this->setPolinomio(p.getPolinomio());

	#ifndef NDEBUG

	assert(std::abs(this->getPolinomio().front().getCoeficiente()-x)<COTA_ERROR);
  	assert((this->getPolinomio().front().getGrado())==0);

  	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;
}

//////////////////////////////////////////////////////////////

ed::Polinomio & ed::Polinomio::operator+=(ed::Polinomio const &p)
{
	Polinomio aux;
	if (this->getGrado()>=p.getGrado()) {
		for (int i = 0; i <= this->getGrado(); i++) {
			if (this->existeMonomio(i) and p.existeMonomio(i))
				aux.insertarMonomio(this->getMonomio(i)+p.getMonomio(i));
			else if (this->existeMonomio(i) and  not p.existeMonomio(i))
				aux.insertarMonomio(this->getMonomio(i));
			else if (not this->existeMonomio(i) and p.existeMonomio(i))
					aux.insertarMonomio(p.getMonomio(i));
		}
	}else{
		for (int i = 0; i <= p.getGrado(); i++) {
			if (this->existeMonomio(i) and p.existeMonomio(i))
				aux.insertarMonomio(this->getMonomio(i)+p.getMonomio(i));
			else if (this->existeMonomio(i) and  not p.existeMonomio(i))
				aux.insertarMonomio(this->getMonomio(i));
			else if (not this->existeMonomio(i) and p.existeMonomio(i))
					aux.insertarMonomio(p.getMonomio(i));
		}
	}
	*this=aux;

	#ifndef NDEBUG
	assert(esta_ordenado());
  	#endif //NDEBUG

	return *this;
}


ed::Polinomio & ed::Polinomio::operator+=(Monomio const &m){

	this->insertarMonomio(m);

	#ifndef NDEBUG
	assert(esta_ordenado());
  	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;

}

ed::Polinomio & ed::Polinomio::operator+=(double const &x){

	Monomio m(x);
	this->insertarMonomio(m);

	#ifndef NDEBUG
	assert(esta_ordenado());
  	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;
}

///////////////////////////////////////////////////////////////////////

ed::Polinomio & ed::Polinomio::operator-=(ed::Polinomio const &p)
{
	Polinomio aux;
	if (this->getGrado()>=p.getGrado()) {
		for (int i = 0; i <= this->getGrado(); i++) {
			if (this->existeMonomio(i) and p.existeMonomio(i))
				aux.insertarMonomio(this->getMonomio(i)-p.getMonomio(i));
			else if (this->existeMonomio(i) and  not p.existeMonomio(i))
				aux.insertarMonomio(this->getMonomio(i));
			else if (not this->existeMonomio(i) and p.existeMonomio(i))
					aux.insertarMonomio(-(p.getMonomio(i)));
		}
	}else{
		for (int i = 0; i <= p.getGrado(); i++) {
			if (this->existeMonomio(i) and p.existeMonomio(i))
				aux.insertarMonomio(this->getMonomio(i)-p.getMonomio(i));
			else if (this->existeMonomio(i) and  not p.existeMonomio(i))
				aux.insertarMonomio(this->getMonomio(i));
			else if (not this->existeMonomio(i) and p.existeMonomio(i))
					aux.insertarMonomio(-(p.getMonomio(i)));
		}
	}
	*this=aux;

	#ifndef NDEBUG
	assert(esta_ordenado());
  	#endif //NDEBUG
  	
	return *this;
}

ed::Polinomio & ed::Polinomio::operator-=(Monomio const &m){

	Polinomio p;
  	p=m;
  	*this-=p;
	return *this;

	#ifndef NDEBUG
	assert(esta_ordenado());
  	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;
}

ed::Polinomio & ed::Polinomio::operator-=(double const &x){

	Monomio m(-x);
	this->insertarMonomio(m);

	#ifndef NDEBUG
	assert(esta_ordenado());
  	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;

}

///////////////////////////////////////////////////////////////////////

ed::Polinomio & ed::Polinomio::operator*=(ed::Polinomio const &p)
{

	Polinomio aux;
	Monomio m;
	for (int i = 0; i <= p.getGrado(); i++) {
		if(p.existeMonomio(i)) {
			for (int j = 0; j <= this->getGrado(); j++) {
				if (this->existeMonomio(i)) {
				m=(this->getMonomio(i)*p.getMonomio(j));
				aux.insertarMonomio(m);
				}
			}
		}
	}
	*this=aux;
	#ifndef NDEBUG
	assert(this->esta_ordenado());
  	#endif //NDEBUG
  	// Se devuelve el objeto actual
	return *this;
}

ed::Polinomio & ed::Polinomio::operator*=(Monomio const &m){

	Polinomio aux;
	Monomio x;
	for (int i = 0; i <= this->getGrado(); i++) {
		if(this->existeMonomio(i)) {
			x=(this->getMonomio(i)*m);
			aux.insertarMonomio(x);
		}
	}
	*this=aux;

	#ifndef NDEBUG
	assert(esta_ordenado());
  	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;

}

ed::Polinomio & ed::Polinomio::operator*=(double const &x){

	Polinomio aux;
	Monomio m;
	for (int i = 0; i <= this->getGrado(); i++) {
		if(this->existeMonomio(i)) {
			m=(this->getMonomio(i)*x);
			aux.insertarMonomio(m);
		}
	}
	*this=aux;

	#ifndef NDEBUG
	assert(esta_ordenado());
  	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;

}
///////////////////////////////////////////////////////////////////////

ed::Polinomio & ed::Polinomio::operator/=(ed::Polinomio const &p)
{
	#ifndef NDEBUG
	assert(this->getGrado()>=p.getGrado());
	assert(not(p.esNulo()));
  	#endif //NDEBUG

	Polinomio aux;
	Monomio m;
	for (int i = 0; i <= p.getGrado(); i++) {
		if(p.existeMonomio(i)) {
			for (int j = 0; j <= this->getGrado(); j++) {
				if (this->existeMonomio(i)) {
				m=(this->getMonomio(i)/p.getMonomio(j));
				aux.insertarMonomio(m);
				}
			}
		}
	}
	*this=aux;
	#ifndef NDEBUG
	assert(this->esta_ordenado());
  	#endif //NDEBUG
  	// Se devuelve el objeto actual
	return *this;
}

ed::Polinomio & ed::Polinomio::operator/=(Monomio const &m){

	#ifndef NDEBUG

	assert(m.getGrado()<=this->getGrado());
	assert(not(this->esNulo()));

  	#endif //NDEBUG

	Polinomio aux;
	Monomio x;
	for (int i = 0; i <= this->getGrado(); i++) {
		if(this->existeMonomio(i)) {
			x=(this->getMonomio(i)/m);
			aux.insertarMonomio(x);
		}
	}
	*this=aux;

	#ifndef NDEBUG
	assert(esta_ordenado());
  	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;

}

ed::Polinomio & ed::Polinomio::operator/=(double const &x){

	Polinomio aux;
	Monomio m;
	for (int i = 0; i <= this->getGrado(); i++) {
		if(this->existeMonomio(i)) {
			m=(this->getMonomio(i)/x);
			aux.insertarMonomio(m);
		}
	}
	*this=aux;

	#ifndef NDEBUG
	assert(esta_ordenado());
  	#endif //NDEBUG

	// Se devuelve el objeto actual
	return *this;

}

///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////

// Funciones lectura y escritura de la clase Polinomio

void ed::Polinomio::leerPolinomio(){//revisar

	Polinomio p;
	int n;
	Monomio m;
	int caso0=0;

	do{
		std::cout<<"Introduzca cuantos monomios desea insertar"<<std::endl;
		std::cin>>n;
		if(n<=0)
		std::cout<<"El numero introducido no es valido"<<std::endl;
	}while(n<=0);
	for(int z=0;z<n;z++){
		m.leerMonomio();
		list<Monomio> aux=this->getPolinomio();
		list<Monomio> :: iterator i=aux.begin();
		int contador=0;
		while(i!=aux.end()){
			if(m.getGrado()==(*i).getGrado()){
				contador++;
				if((m.getGrado()==0)&&(caso0==0)){
					contador--;
					caso0=1;
				}
			}
			i++;
		}
		if(contador>0){
		std::cout<<"El monomio introducido no es valido, ya existe un monomio con ese grado, introdúcelo de nuevo"<<std::endl;
			z--;
		}else{
			if(m.getGrado()==0){
				aux.pop_back();//se me repetiria el 0;
			}
			aux.push_front(m);
			this->setPolinomio(aux);
			p.insertarMonomio(m);
		}
	}

	this->setPolinomio(p.getPolinomio());

	if((this->getPolinomio().back().getGrado()==0)&&(this->getPolinomio().back().getCoeficiente()==0)){
		list<Monomio> aux=this->getPolinomio();
		aux.pop_back();
		this->setPolinomio(aux);
	}
}

void ed::Polinomio::escribirPolinomio(){

	list<Monomio> aux=this->getPolinomio();
	list<Monomio> :: iterator i=aux.begin();

	while(i!=aux.end()){
		(*i).escribirMonomio();
		std::cout<<" ";
		i++;
	}
 
}


///////////////////////////////////////////////////////////////////////

// Funciones auxiliares de la clase Polinomio

void ed::Polinomio::insertarMonomio(Monomio const &m){
	list <Monomio> aux;
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
				if (aux.front().getCoeficiente()==0.0) {
					aux.pop_front();
				}
			}else if((this->existeMonomio(i))&&!(m.getGrado()==this->getMonomio(i).getGrado()))
				aux.push_front(this->getMonomio(i));
			else if(!(this->existeMonomio(i))&&i==m.getGrado())
				aux.push_front(m);
		}
	}
	this->setPolinomio(aux);
}
