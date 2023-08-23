#include "Profesor.h"
#include "Agenda.h"
#include <list>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void Profesor::CargarInformacion(Agenda &p){

        ifstream f1("Fichero_Alumnos.bin", ios::in | ios::binary);
        if(f1.is_open()){
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
            cout << "Error al abrir el archivo" << endl;
        }
}
