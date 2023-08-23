//Realizado por Antonio Gómez Giménez
//Este código es la clase crupier

#ifndef CRUPIER_H
#define CRUPIER_H

#include "persona.h"
#include <string>

using namespace std;

class Crupier:public Persona {

	private:

		string Codigo_;

	public:

	Crupier(string DNI, string Codigo, string Nombre="", string Apellidos="", int Edad=0, string Direccion="" , string Localidad="", string Provincia="", string Pais="") : Persona(DNI, Nombre, Apellidos, Edad, Direccion, Localidad, Provincia, Pais) {
	
	 	Codigo_=Codigo;

	};

	string getCodigo() const {return Codigo_;};
	void setCodigo(string Codigo);

};

#endif