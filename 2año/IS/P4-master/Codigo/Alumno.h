//Alumno.h

#ifndef ALUMNO_H
#define ALUMNO_H

#include <string>

using namespace std;

class Alumno{
private:
	string DNI_;
	string Nombre_;
	string Apellido1_;
	string Apellido2_;
	int Telefono_;
	string Correo_;
	string Direccion_;
	int Curso_;
	string FechaNacimiento_;
	int Equipo_;
	bool Lider_;

public:
	Alumno(string DNI, string Correo, string Nombre, string Apellido1, string Apellido2, int Telefono, string Direccion, int Curso, string FechaNacimiento, int Equipo=0, bool Lider=false)
		{
			DNI_=DNI;
			Correo_=Correo;
			Nombre_=Nombre;
			Apellido1_=Apellido1;
			Apellido2_=Apellido2;
			Telefono_=Telefono;
			Direccion_=Direccion;
			Curso_=Curso;
			FechaNacimiento_=FechaNacimiento;
			Equipo_=Equipo;
			Lider_=Lider;
		};

	inline void setDNI(string NuevoDNI){ DNI_=NuevoDNI;};
	inline string getDNI() const {return DNI_;};

	inline void setNombre(string NombreNuevo){ Nombre_=NombreNuevo;};
	inline string getNombre() const {return Nombre_;};


	inline void setApellido1(string NuevoApellido1){ Apellido1_=NuevoApellido1;};
	inline string getApellido1() const {return Apellido1_;};

	inline void setApellido2(string NuevoApellido2){ Apellido2_=NuevoApellido2;};
	inline string getApellido2() const {return Apellido2_;};

	inline void setTelefono(int NuevoTelefono){ Telefono_=NuevoTelefono;};
	inline int getTelefono() const {return Telefono_;};

	inline void setCorreo(string NuevoCorreo){ Correo_=NuevoCorreo;};
	inline string getCorreo() const {return Correo_;};

	inline void setDireccion(string NuevaDireccion){ Direccion_=NuevaDireccion;};
	inline string getDireccion() const {return Direccion_;};

	inline void setCurso(int NuevoCurso){ Curso_=NuevoCurso;};
	inline int getCurso() const {return Curso_;};

	inline void setFechaNacimiento(string NuevaFecha){ FechaNacimiento_=NuevaFecha;};
	inline string getFechaNacimiento() const {return FechaNacimiento_;};

	inline void setEquipo(int NuevoEquipo){ Equipo_=NuevoEquipo;};
	inline int getEquipo() const {return Equipo_;};

	inline void setLider(bool NuevoLider){ Lider_=NuevoLider;};
	inline bool getLider() const {return Lider_;};

};


#endif
