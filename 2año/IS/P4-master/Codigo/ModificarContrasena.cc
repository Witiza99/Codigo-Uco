//ModificarContrasena.cc
#include <fstream>
#include "Profesor.h"
#include <list>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdio>//necesaria para rename y remove

using namespace std;

void Profesor::ModificarContrasena(string Contrasena){//funcion de modificar Contraseña

	ifstream f1("Credenciales.bin", ios::in |	ios::binary);//abro fichero en modo lectura
	ofstream f2("Aux.bin", ios::out | ios::binary);//abro fichero en modo lectura
	if(f1.is_open()){
		if(f2.is_open()){
			char Contrasenac[20];
			strcpy(Contrasenac,Contrasena.c_str());
			string str;
			char auxs[20];
			string Usuario=getUsuario();
			f1.seekg(0, ios::beg);//pongo el cursor al princio
			while(f1.read(auxs,sizeof(char[20]))){//con este while voy leyendo el fichero de 3 en 3, ya sea con la contraseña pedida o no
				f2.write(auxs,sizeof(char[20]));
				str=auxs;
				if(str==Usuario){
					f1.read(auxs,sizeof(char[20]));//Contraseña
					f2.write(Contrasenac,sizeof(char[20]));//modificar contraseña
					cout << "Modificado con éxito" << endl;
					f1.read(auxs,sizeof(bool));//si es coordinador o no
					f2.write(auxs,sizeof(bool));
				}else{
				f1.read(auxs,sizeof(char[20]));//contraseña
				f2.write(auxs,sizeof(char[20]));
				f1.read(auxs,sizeof(bool));//si es coordinador o no
				f2.write(auxs,sizeof(bool));
				}
			}
			f2.close();
		}else{cout << "Error al abrir el archivo" << endl;}
	f1.close();
	}else{cout << "Error al abrir el archivo" << endl;}
	if( remove("Credenciales.bin") != 0 ){
   		cout <<	"Error fatal al borrar archivo" << endl;;//por si ocurriera algun extraño error
	}
	rename("Aux.bin","Credenciales.bin");
}
