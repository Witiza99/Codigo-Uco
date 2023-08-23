//Realizado por Antonio Gómez Giménez
//Este código es la clase persona 
//En la linea de comandos pwd sirve para ver la ruta

#ifndef PERSONA_H
#define PERSONA_H

#include <string>

using namespace std;

class Persona{

private:

	string DNI_;
	string Nombre_;
	string Apellidos_;
	int Edad_;
	string Direccion_;
	string Localidad_;
	string Provincia_;
	string Pais_;
	string ApellidosyNombre_;


public:

	Persona(string DNI, string Nombre="", string Apellidos="", int Edad=0, string Direccion="" , string Localidad="", string Provincia="", string Pais=""){

 		DNI_=DNI;
 		Nombre_=Nombre;
 		Apellidos_=Apellidos;
 		if(Edad>=0){

			Edad_=Edad;

		}else{

			Edad_=0;

		}
		Direccion_=Direccion;
		Localidad_=Localidad;
		Provincia_=Provincia;
		Pais_=Pais;

	}

	void setDNI(string cad);
	void setNombre(string cad);
	void setApellidos(string cad);
	bool setEdad(int n);
	void setDireccion(string cad);
	void setLocalidad(string cad);
	void setProvincia(string cad);
	void setPais(string cad);
	string getDNI() const {return DNI_;};
	string getNombre() const {return Nombre_;};
	string getApellidos() const {return Apellidos_;};
	int getEdad() const {return Edad_;};
	string getDireccion() const {return Direccion_;};
	string getLocalidad() const {return Localidad_;};
	string getProvincia() const {return Provincia_;};
	string getPais() const {return Pais_;};
	string getApellidosyNombre();
	bool mayor();

};

#endif