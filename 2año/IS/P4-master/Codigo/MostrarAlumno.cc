#include "Agenda.h"
#include <string>
#include <iostream>
#include <list>

using namespace std;

void Agenda::MostrarAlumnos(list <Alumno> aux, int n){

	list<Alumno> :: iterator l=aux.begin();

	if(n==0){//imprime lista pequeña
			while(l!=aux.end()){
			cout << "DNI: "<< (*l).getDNI() << " ";
			cout << ",Nombre: " << (*l).getNombre() << " ";
			cout << ",Apellidos: "<< (*l).getApellido1() <<" "<< (*l).getApellido2() << " ";
			cout << ",Correo: "<< (*l).getCorreo() << endl;
			l++;
		}
	}else{
		while(l!=aux.end()){//imprime toda la lista ya ordenada o sin ordenar
			cout << "DNI: "<< (*l).getDNI()<<" ";
			cout << ",Nombre: " << (*l).getNombre()<<" ";
			cout << ",Apellidos: "<< (*l).getApellido1() <<" "<< (*l).getApellido2() << " ";
			cout << ",Teléfono: " << (*l).getTelefono() << " ";
			cout << ",Correo: "<< (*l).getCorreo() << " ";
			cout << ",Dirección: " << (*l).getDireccion() << " ";
			cout << ",Curso: "<< (*l).getCurso() << " ";
			cout << ",Fecha de Nacimiento: " << (*l).getFechaNacimiento() << " ";
			cout << ",Equipo: "<< (*l).getEquipo() << " ";
			cout << ",Líder: " << (*l).getLider() << endl;
			l++;
		}
	}
}
