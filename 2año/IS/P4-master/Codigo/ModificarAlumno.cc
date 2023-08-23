#include "Agenda.h"
#include "Alumno.h"
#include <iostream>
#include <list>

using namespace std;

void Agenda::ModificarAlumno(list <Alumno> auxiliar){//función que modifica un alumno de la lista alumnos_

	int elector=1;
	string cadena;
	int var;
	int aux;

	list<Alumno> :: iterator i=alumnos_.begin();

	while(i!=alumnos_.end()){//recorro la lista en busca del mismo dni
		if(auxiliar.begin()->getDNI()==(*i).getDNI()){//comprueba la posición en la que se encuentra
			while(elector!=11){
				cout << "Elige el dato que deseas modificar:" << endl;//informo al usuario de las opciones para modificar
				cout << "1.DNI" << endl;
				cout << "2.Nombre" << endl;
				cout << "3.Apellidos" << endl;
				cout << "4.Teléfono de contacto" << endl;
				cout << "5.Correo electrónico" << endl;
				cout << "6.Dirección postal" << endl;
				cout << "7.Curso más alto matriculado" << endl;
				cout << "8.Fecha de nacimiento" << endl;
				cout << "9.Equipo al que pertenece el alumno" << endl;
				cout << "10.Líder" << endl;
				cout << "11.Finalizar modificación" << endl;
				cin>>elector;

				switch(elector){

					case 1:
					cout << "Introduzca el nuevo DNI:" << endl;
					cin>>cadena;
					if(BuscarAlumno(cadena,3).size()!=0)//compruebo si existe el dni
						(*i).setDNI(cadena);
					else
						cout << "El DNI introducido se encuentra ya en uso, no es posible poner tal dni" << endl;
					break;

					case 2:
						cout << "Introduzca el nuevo nombre:" << endl;
						cin>>cadena;
						(*i).setNombre(cadena);
					break;

					case 3:
						cout << "Introduzca el primer apellido:" << endl;
						cin>>cadena;
						(*i).setApellido1(cadena);
						cout << "Introduzca el segundo apellido:" << endl;
						cin>>cadena;
						(*i).setApellido2(cadena);
					break;
					cin>>cadena;

					case 4:
						cout << "Introduzca el nuevo teléfono de contacto:" << endl;
						cin>>var;
						(*i).setTelefono(var);
					break;

					case 5:
						cout << "Introduzca el nuevo correo:" << endl;
						cin >> cadena;
						if(BuscarAlumno(cadena,4).size()!=0)//compruebo si el email existía previamente
							(*i).setCorreo(cadena);
						else
							cout << "El correo introducido se encuentra ya en uso, no es posible poner tal email" << endl;
					break;

					case 6:
						cout << "Introduzca la nueva dirección postal:" << endl;
						cin>>cadena;
						(*i).setDireccion(cadena);
					break;

					case 7:
						cout << "Introduzca el nuevo curso más alto matriculado:" << endl;
						cin>>var;
						(*i).setCurso(var);
					break;

					case 8:
						cout << "Introduzca la nueva fecha de nacimiento:" << endl;
						cin>>cadena;
						(*i).setFechaNacimiento(cadena);
					break;

					case 9:
						cout << "Introduzca al nuevo equipo al que pertenece:" << endl;
						cin>>var;
						aux=(*i).getEquipo();//guardo el equipo anterior
						(*i).setEquipo(var);//actualizo nuevo equipo
						if((*i).getLider()==true){//con esto evito problemas si era líder anterior
							(*i).setLider(false);
							ModificarLider(aux,1);//pongo lider aleatorio del grupo anterior
						}
					break;

					case 10:
						cout << "Introduzca 's' para hacerlo líder y 'n' para que no sea líder:" << endl;
						cin>>cadena;
						if(cadena=="s"||cadena=="S"){//compruebo si ha introducido un si o un no
							ModificarLider((*i).getEquipo(),2);
							(*i).setLider(true);
						}else{
							if(cadena=="N"||cadena=="n"){
								if((*i).getLider()==true){//con esto se busca que si era un antiguo lider pase ahora a no serlo
				                    aux=(*i).getEquipo();
				                    (*i).setLider(false);
				                    (*i).setEquipo(-1);
				                    ModificarLider(aux,1);//se coge aleatoriamente un nuevo lider donde no se incluye este alumno
				                    (*i).setEquipo(aux);
								}
							}else{
								cout << "No ha introducido bien su respuesta" << endl;
							}
						}
					break;

					default:
					cout << "El numero que se ha introducido no es correcto" << endl;
					break;

				}
			}
		}
		i++;
	}
}
