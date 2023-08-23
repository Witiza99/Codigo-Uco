#ifndef ENTERO_H
#define ENTERO_H

#include "funcionesbajonivel.hpp"
#include <iostream>
#include <string>
#include <math.h>

using namespace::std;

class Entero{

	

private:

	string entero_;
	int maximo_;

	inline void setEntero(string c){entero_=c;};
	inline string getEntero()const{return entero_;};
	inline int getMaximo()const{return maximo_;};


public:

	Entero(){
		this->maximo_=4;
	}
	Entero(Entero const &entero){
		this->setEntero(entero.getEntero());
		this->maximo_=4;
	}
	/////////////////////////////////////////////////////////////////////////////
	//operador de suma
	friend Entero &operator+(Entero const &l,Entero const &s);
	//operador de multiplicacion
	friend Entero &operator*(Entero const &l,Entero const &s);
	/////////////////////////////////////////////////////////////////////////////
	//  Sobrecarga del operador de entrada
	friend istream &operator>>(istream &stream, Entero &e);

	//  Sobrecarga del operador de salida
	friend ostream &operator<<(ostream &stream, Entero const &e);

};

#endif