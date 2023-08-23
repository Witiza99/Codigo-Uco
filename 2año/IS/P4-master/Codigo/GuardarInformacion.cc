#include <fstream>
#include "Profesor.h"
#include "Agenda.h"
#include <list>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

void Profesor::GuardarInformacion(Agenda p){

	ofstream f1("Fichero_Alumnos.bin", ios::out | ios::binary);
	if(f1.is_open()){
		list <Alumno> aux;
		aux=p.getAlumnos();
		list<Alumno> :: iterator l=aux.begin();
		char auxs[50];
    string str;
		while(l!=aux.end()){
      str=(*l).getDNI();
			strcpy(auxs,str.c_str());
	   	f1.write(auxs,sizeof(char[50]));
      str=(*l).getCorreo();
      strcpy(auxs,str.c_str());
      f1.write(auxs,sizeof(char[50]));
      str=(*l).getNombre();
      strcpy(auxs,str.c_str());
      f1.write(auxs,sizeof(char[50]));
      str=(*l).getApellido1();
      strcpy(auxs,str.c_str());
      f1.write(auxs,sizeof(char[50]));
      str=(*l).getApellido2();
      strcpy(auxs,str.c_str());
      f1.write(auxs,sizeof(char[50]));
      str=to_string((*l).getTelefono());
      strcpy(auxs,str.c_str());
      f1.write(auxs,sizeof(int));
      str=(*l).getDireccion();
      strcpy(auxs,str.c_str());
      f1.write(auxs,sizeof(char[50]));
      str=to_string((*l).getCurso());
      strcpy(auxs,str.c_str());
      f1.write(auxs,sizeof(int));
      str=(*l).getFechaNacimiento();
      strcpy(auxs,str.c_str());
      f1.write(auxs,sizeof(char[50]));
      str=to_string((*l).getEquipo());
      strcpy(auxs,str.c_str());
      f1.write(auxs,sizeof(int));
      str=to_string((*l).getLider());
      strcpy(auxs,str.c_str());
      f1.write(auxs,sizeof(bool));
			l++;
		}
		f1.close();
	}else{
		cout << "Error al abrir el archivo" << endl;
	}
}
