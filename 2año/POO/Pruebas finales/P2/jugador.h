//Realizado por Antonio Gómez Giménez
//Este código es la clase jugador

#ifndef JUGADOR_H
#define JUGADOR_H

#include "persona.h"
#include <string>
#include <list> 

using namespace std;

	struct Apuesta{

		int tipo;
		string valor;
		int cantidad;

	};

class Jugador:public Persona {

	private:

		string CodigoAlfan_;
		int dinero_;

		/*struct Apuesta{

			int tipo;
			string valor;
			int cantidad;

		};*/

		list<Apuesta> lista;

	public:


	Jugador(string DNI, string Codigo, string Nombre="", string Apellidos="", int Edad=0, string Direccion="" , string Localidad="", string Provincia="", string Pais="") : Persona(DNI, Nombre, Apellidos, Edad, Direccion, Localidad, Provincia, Pais) {
	
	 	CodigoAlfan_=Codigo;
	 	dinero_=1000;
	 	lista.clear();

	}

	string getCodigo() const {return CodigoAlfan_;};
	void setCodigo(string Codigo);
	int getDinero() const {return dinero_;};
	void setDinero(int Dinero);
	list<Apuesta> getApuestas() const {return lista;};
	void setApuestas();

};

#endif