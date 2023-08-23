//Realizado por Antonio Gómez Giménez
//Este es el .c de la clase persona

#include <iostream>
#include "persona.h"

	void Persona::setDNI(string cad){

		DNI_=cad;

	}


	void Persona::setNombre(string cad){

		Nombre_=cad;

	}

	void Persona::setApellidos(string cad){

		Apellidos_=cad;

	}

	bool Persona::setEdad(int n){

		if(n>=0){

			Edad_=n;

			return true;

		}else{return false;}

	}

	void Persona::setDireccion(string cad){

		Direccion_=cad;

	}

	void Persona::setLocalidad(string cad){

		Localidad_=cad;

	}

	void Persona::setProvincia(string cad){

		Provincia_=cad;

	}

	void Persona::setPais(string cad){

		Pais_=cad;

	}

	string Persona::getApellidosyNombre(){

		ApellidosyNombre_=Apellidos_+", "+Nombre_;

		return ApellidosyNombre_;

	}

	bool Persona::mayor(){

		if(Edad_>=18){

			return true;

		}else{return false;}

	}