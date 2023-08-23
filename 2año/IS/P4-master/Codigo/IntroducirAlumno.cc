#include "Agenda.h"
#include "Alumno.h"
#include <iostream>
#include <list>

using namespace std;

void Agenda::IntroducirAlumno(){

	Alumno d("","","","","",0,"",0,"");//creo objeto alumno auxiliar para introducir todos los datos
	string cadena;
	int var;
	int elec;
	int j=0;

	while(j==0){
		cout << "Introduzca el dni del alumno:" << endl;
		cin>>cadena;
		if(BuscarAlumno(cadena,3).size()==0){//compruebo si existe el dni
			d.setDNI(cadena);
			j++;
		}else{
			cout << "El Dni introducido se encuentra ya en uso, no es posible poner tal dni" << endl;
		}
	}

	cout << "Introduzca el nombre:" << endl;
	cin>>cadena;
	d.setNombre(cadena);

	cout << "Introduzca el primer apellido:" << endl;
	cin>>cadena;
	d.setApellido1(cadena);

	cout << "Introduzca el segundo apellido:" << endl;
	cin>>cadena;
	d.setApellido2(cadena);

	cout << "Introduzca el teléfono de contacto:" << endl;
	cin>>var;
	d.setTelefono(var);

	j=0;
	while(j==0){
		cout << "Introduzca el correo:" << endl;
		cin >> cadena;
		if(BuscarAlumno(cadena,4).size()==0){//compruebo si el email existía previamente
			d.setCorreo(cadena);
			j++;
		}else{
			cout << "El correo introducido se encuentra ya en uso, no es posible poner tal email" << endl;
		}
	}

	cout << "Introduzca la dirección postal:" << endl;
	cin>>cadena;
	d.setDireccion(cadena);

	cout << "Introduzca el curso más alto matriculado:" << endl;
	cin>>var;
	d.setCurso(var);

	cout << "Introduzca la fecha de nacimiento:" << endl;
	cin>>cadena;
	d.setFechaNacimiento(cadena);

	cout << "Conteste '1' para sí o '0' para no" << '\n';
	cout << "Di si este alumno pertenece a algun grupo" << endl;//doy opción a no rellenar estos dos datos;
	cin>>elec;

	if(elec==1){//compruebo si ha introducido un si o un no
		cout << "Introduzca al equipo al que pertenece:" << endl;
		cin>>var;
		d.setEquipo(var);

		cout << "Conteste '1' para sí o '0' para no" << '\n';
		cout << "Introduzca si el alumno es lider:" << endl;
		cin>>elec;

		if(elec==1){//compruebo si ha introducido un si o un no
			list <Alumno> temporal;
			temporal=BuscarAlumno(d.getEquipo(),5);//copia lista con todos los integrantes del grupo
			list <Alumno> :: iterator i = temporal.begin();
			while(i!=temporal.end()){//recorro la lista para ver si hay algun lider
				if((*i).getLider()==true){//comprueba si hay un líder en ese grupo
					d.setLider(false);
					cout << "Ya había un líder así que este alumno no puede serlo, si usted quiere que este sea líder modifíquelo" << endl;
				}
				i++;
			}
			d.setLider(true);
		}else{
			if(elec==0){//no de si es lider
				d.setLider(false);
			}else{
				cout << "No ha introducido bien su respuesta" << endl;
			}
		}
	}else{
		if(elec==0){}//no de si no esta en grupo
		else{
			cout << "Valor introducido no válido, si usted desea decir al grupo que pertenece este alumno modifíquelo" << endl;
		}
	}
	alumnos_.push_back(d);
}
