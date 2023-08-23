#include "Profesor.h"
#include "Agenda.h"
#include <list>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

void Profesor::GuardarInfoCs(Agenda p){
	char auxs[50];
	string str;

	time_t tiempo = time(NULL);//variables donde guardo el valor de la funcion time.
    struct tm *tlocal = localtime(&tiempo); //estructura donde obtengo el tiempo
    char fecha[10]; //donde guardo la fecha
    strftime(fecha,10,"%d/%m/%y",tlocal);
    int i=1;
    int contador=0;
    string cadena;
    while(contador==0){
    	cadena=to_string(i)+" Copia_Seguridad";
    	ifstream f1(cadena.c_str(), ios::in | ios::binary);
    	if(f1.is_open()){
    		i++;
    		f1.close();
    	}else{
    		contador=1;
    	}
    }

	ofstream f1(cadena.c_str(), ios::out | ios::binary);
	if(f1.is_open()){
		list <Alumno> aux=p.getAlumnos();
		list <Alumno> :: iterator  l=aux.begin();
		f1.write(fecha,sizeof(char[10]));
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
        cout << "La Información ha sido guardada con éxito" << endl;
		f1.close();
	}else{
		cout << "Error al abrir el archivo" << endl;
	}
}
