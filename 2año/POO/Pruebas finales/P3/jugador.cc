//Realizado por Antonio Gómez Giménez
//Este es el .c de la clase jugador

#include <iostream>
#include "jugador.h"
#include <fstream>
#include <cstdlib>

	void Jugador::setCodigo(string Codigo){

		CodigoAlfan_=Codigo;

	}

	void Jugador::setDinero(int Dinero){

		dinero_=Dinero;

	}

	void Jugador::setApuestas(){

		lista.clear();

		Apuesta aux;

		string fichero=(getDNI()+".txt");

		ifstream entrada;

		entrada.open(fichero.c_str(),ios::in);

		if(!entrada) cout << "ERROR de apertura";

			string frase;

			while (! entrada.eof() ) {

          	 	getline (entrada,frase,',');

          	 	aux.tipo=atoi(frase.c_str());

				getline (entrada,frase,',');

				aux.valor=frase;

				getline (entrada,frase);

				aux.cantidad=atoi(frase.c_str());

				lista.push_back(aux);

			}

		lista.pop_back();

		entrada.close();

	}