//Agenda.h

#ifndef AGENDA_H
#define AGENDA_H

#include <list>
#include <string>
#include "Alumno.h"

using namespace std;

class Agenda{
private:
	list <Alumno> alumnos_;

public:

	void IntroducirAlumno();

	inline list <Alumno> BuscarAlumno(int var, int elec){
		string cad=to_string(var);
		return BuscarAlumno(cad,elec);};

	list <Alumno> BuscarAlumno(string cadena, int elec);

	void ModificarAlumno(list <Alumno> lista);

	void MostrarAlumnos(list <Alumno> lista, int n);

	void OrdenarAlumnos(list <Alumno> &lista, int elec, int asc);

	void BorrarAlumno(list <Alumno> lista);
	inline void BorrarTodos() {alumnos_.clear();};

	inline void setAlumnos(list <Alumno> lista){ alumnos_=lista;};
	inline list <Alumno> getAlumnos() const {return alumnos_;};

	void ModificarLider(int equipo, int n);

};

#endif
