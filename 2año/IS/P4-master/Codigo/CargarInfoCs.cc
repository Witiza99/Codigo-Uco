#include "Profesor.h"
#include "Agenda.h"
#include <list>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void Profesor::CargarInfoCs(Agenda &p){

	int i;
	cout << "Introduzca la copia de Seguridad que desea cargar" << endl;
	cin >> i;

	if(i>0){

		string cadena;
		cadena=to_string(i)+" Copia_Seguridad";
		ifstream f1(cadena.c_str(), ios::in | ios::binary);
    	if(f1.is_open()){
    		char fecha[10];
    		f1.read(fecha,sizeof(char[10]));
    		cout << "Se ha abierto la Copia de Seguridad " << i << " creada el " << fecha << endl;
    		list <Alumno> aux;
    		Alumno n("","","","","",0,"",0,"");
            char auxs[50];
            string str;
    		while(f1.eof()!=1){
                f1.read(auxs,sizeof(char[50]));
                    str=auxs;
                n.setDNI(str);
                f1.read(auxs,sizeof(char[50]));
                    str=auxs;
                n.setCorreo(str);
                f1.read(auxs,sizeof(char[50]));
                    str=auxs;
                n.setNombre(str);
                f1.read(auxs,sizeof(char[50]));
                    str=auxs;
                n.setApellido1(str);
                f1.read(auxs,sizeof(char[50]));
                    str=auxs;
                n.setApellido2(str);
                f1.read(auxs,sizeof(int));
                n.setTelefono(atoi(auxs));
                f1.read(auxs,sizeof(char[50]));
                    str=auxs;
                n.setDireccion(str);
                f1.read(auxs,sizeof(int));
                n.setCurso(atoi(auxs));
                f1.read(auxs,sizeof(char[50]));
                    str=auxs;
                n.setFechaNacimiento(str);
                f1.read(auxs,sizeof(int));
                n.setEquipo(atoi(auxs));
                f1.read(auxs,sizeof(bool));
                n.setLider(atoi(auxs));

                aux.push_back(n);
            }
				aux.pop_back();
    		p.setAlumnos(aux);
            cout << "La carga de Información se ha realizado con exito" << endl;
    		f1.close();
    	}else{
    		cout << "La copia de seguridad que ha elegido no existe" << endl;
    	}
	}else{cout << "El numero introducido no es válido" << endl;}
}
