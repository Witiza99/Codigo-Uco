#include "Agenda.h"
#include "Alumno.h"
#include <list>
#include <iostream>

using namespace std;

void Agenda::BorrarAlumno(list <Alumno> lista){ //función que borra a un alumno de la lista
	int salir=0;
	if (lista.size()!=0){
		list<Alumno> :: iterator i=alumnos_.begin();
      	while((i!=alumnos_.end())&&(salir!=1)){
        	if((*i).getDNI()==lista.begin()->getDNI()){
          		alumnos_.erase(i);
							salir=1;
       		}
					i++;
       	}

	}else{
		cout<<"No hay alumnos disponibles para borrar"<<endl;
	}

}
