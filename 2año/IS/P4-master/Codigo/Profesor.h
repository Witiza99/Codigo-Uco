//Profesor.h

#ifndef PROFESOR_H
#define PROFESOR_H

#include <string>
#include "Agenda.h"

using namespace std;

class Profesor{
private:
	string usuario_;
	string contrasena_;
	bool Coordinador_;

public:

	bool Identificacion(string Usuario, string Contrasena);

	void ModificarContrasena(string NuevaContrasena);

	inline void CerrarSesion(Agenda a) { GuardarInformacion(a); system("clear"); };

	void GuardarInformacion(Agenda a);
	void CargarInformacion(Agenda &p);
	void GuardarInfoCs(Agenda p);
	void CargarInfoCs(Agenda &p);

	inline void setCoordinador(bool Coordinador){ Coordinador_=Coordinador;};
	inline bool getCoordinador() const {return Coordinador_;};
	inline void setUsuario(string Usuario){usuario_=Usuario;};
	inline string getUsuario(){return usuario_;};
	inline void setContrasena(string contrasena){contrasena_=contrasena;};
	inline string getContrasena(){return contrasena_;};


};

#endif
