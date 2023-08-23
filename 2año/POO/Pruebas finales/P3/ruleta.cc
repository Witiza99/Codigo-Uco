//Realizado por Antonio Gómez Giménez
//Este es el .c de la clase ruleta

#include <iostream>
#include "ruleta.h"
#include <fstream>
#include <cstring>

using namespace std;

bool Ruleta::setBanca(int n){

	if(n>=0){

		banca_=n;

		return true;

	}else{

		return false;

	}

}

bool Ruleta::setBola(int n){

	if((n>=0)&&(n<37)){

		bola_=n;

		return true;

	}else{

		return false;

	}

}

void Ruleta::setCrupier(Crupier ModCrupier){

	crupier_=ModCrupier;

}

bool Ruleta::addJugador(Jugador NewJugador){

	list<Jugador> :: iterator i;
	i=jugadores_.begin();

	while(i!=jugadores_.end()){//un loop que busca si el dni ya existía

		if((*i).getDNI()==NewJugador.getDNI()) {return false;}

		i++;

	}

	jugadores_.push_back(NewJugador);

	string fichero=(NewJugador.getDNI()+".txt");

	ifstream nuevo;

	nuevo.open(fichero.c_str());//mirar si existe

	if(nuevo.is_open()){

		nuevo.close();

		return true;

	}

	else{

		ofstream nuevo2;

		nuevo.close();

		nuevo2.open(fichero.c_str());//si no existe lo crea

		nuevo2.close();

		return true;

	}

}

int Ruleta::deleteJugador(string NIFJugador){

	if(jugadores_.empty()==1) {return -1;}

	list<Jugador> ::iterator i;
	i=jugadores_.begin();

	while(i!=jugadores_.end()){//es un loop de la lista

		if((*i).getDNI()==NIFJugador){//comprueba si el DNI esta en la lista

			jugadores_.erase(i);//si esta lo borra y devuelve -1

			return 1;

		}

	i++;

	}

	return -2;//si se sale del loop que busca al jugador significa que no esta en la lista y se devuelve -2

}

int Ruleta::deleteJugador(Jugador BorrarJugador){

	if(jugadores_.empty()==1) {return -1;}

	list<Jugador> ::iterator i;
	i=jugadores_.begin();

	while(i!=jugadores_.end()){//es un loop de la lista

		if((*i).getDNI()==BorrarJugador.getDNI()){//comprueba si el DNI esta en la lista

			jugadores_.erase(i);//si esta lo borra y devuelve -1

			return 1;

		}

	i++;

	}

	return -2;//si se sale del loop que busca al jugador significa que no esta en la lista y se devuelve -2

}


void Ruleta::escribeJugadores(){

	ofstream f1("jugadores.txt");//al abrirlo asi si habia algo se borra

	list<Jugador> :: iterator i;

	i=jugadores_.begin();

	while(i!=jugadores_.end()){//escribe en el fichero todos los datos disponibles de ese jugador

		f1 << (*i).getDNI() << ",";
		f1 << (*i).getCodigo() << ",";
		f1 << (*i).getNombre() << ",";
		f1 << (*i).getApellidos() << ",";
		f1 << (*i).getEdad() << ",";
		f1 << (*i).getDireccion() << ",";
		f1 << (*i).getLocalidad() << ",";
		f1 << (*i).getProvincia() << ",";
		f1 << (*i).getPais() << ",";
		f1 << (*i).getDinero() << endl;

		i++;

	}

	f1.close();

}

void Ruleta::leeJugadores(){

	jugadores_.clear();

	char dni[30], codigo[30], nombre[30], apellidos[30], direccion[30], localidad[30], provincia[30], pais[30], dinero[30];

	Jugador aux("DNI_a_borrar","Cod_a_borrar");

	ifstream f1("jugadores.txt");

	if(f1.is_open()){

		while(f1.getline(dni, 30, ',')) { //coge del fichero .txt los datos y los coloco en una clase auxiliar
	
			f1.getline(codigo, 30, ',');

			f1.getline(nombre, 30, ',');

			f1.getline(apellidos, 30, ',');

			f1.getline(direccion, 30, ',');

			f1.getline(localidad, 30, ',');

			f1.getline(provincia, 30, ',');

			f1.getline(pais, 30, ',');

			f1.getline(dinero, 30, '\n');

			aux.setDNI(dni);

			aux.setCodigo(codigo);

			aux.setNombre(nombre);

			aux.setApellidos(apellidos);

			aux.setDireccion(direccion);

			aux.setLocalidad(localidad);

			aux.setProvincia(provincia);

			aux.setPais(pais);

			aux.setDinero(atoi(dinero));

			jugadores_.push_back(aux);

		}

		f1.close();

	}else{printf("No se puede abrir el archivo\n");}

}

void Ruleta::getPremios(){

	list<Jugador> :: iterator i;

	i=jugadores_.begin();

	int gananciasBanca=0;//contador con lo que gana o pierde la banca

	while(i!=jugadores_.end()){//loop para recorrer el vector de jugadoress

		jugadorApuesta(i, gananciasBanca);//mirar

		i++;

	}

	setBanca(getBanca()+gananciasBanca);//actualizo el valor de la banca

	escribeJugadores();//escribo la lista jugadores en un fichero.txt

}

void Ruleta::jugadorApuesta(list<Jugador> ::iterator aux, int &gananciasBanca){

	string fichero=(*aux).getDNI()+".txt";

	ifstream f1(fichero.c_str());

	if(f1.is_open()){//abro el archivo de apuestas del usuario

		char tipo[30], valor[30], cantidad[30];

		int premio=0;

		while(f1.getline(tipo, 30, ',')){

			f1.getline(valor, 30, ',');

			f1.getline(cantidad, 30, '\n');

			switch(atoi(tipo)){//compruebo el tipo de caso en el que me encuentro

				case 1: {//caso de apostar por un solo valor

					if(atoi(valor)==getBola()){

						premio=premio+atoi(cantidad)*35;
						gananciasBanca=gananciasBanca-atoi(cantidad)*35;

					}else{

						premio=premio-atoi(cantidad);
						gananciasBanca=gananciasBanca+atoi(cantidad);

					}

				}break;

				case 2: {//caso de apostar por los colores

					if(getBola()==0){

						premio=premio-atoi(cantidad);
						gananciasBanca=gananciasBanca+atoi(cantidad);

					}else{

						string color;

						if(getBola()==(1||3||5||7||9||12||14||16||18||19||21||23||25||27||30||32||34||36)){

							color="rojo";

						}else{color="negro";}

						if(strcmp(valor,color.c_str())==0){

							premio=premio+atoi(cantidad);
							gananciasBanca=gananciasBanca-atoi(cantidad);

						}else{

							premio=premio-atoi(cantidad);
							gananciasBanca=gananciasBanca+atoi(cantidad);

						}

					}

				}break;

				case 3: {//caso de apostar por par o impar

					if(getBola()==0){

						premio=premio-atoi(cantidad);
						gananciasBanca=gananciasBanca+atoi(cantidad);

					}else{

						string resultado;

						if(getBola()%2==0){

							resultado="par";

						}else{resultado="impar";}

						if(strcmp(valor,resultado.c_str())==0){

							premio=premio+atoi(cantidad);
							gananciasBanca=gananciasBanca-atoi(cantidad);

						}else{

							premio=premio-atoi(cantidad);
							gananciasBanca=gananciasBanca+atoi(cantidad);
						}

					}
				

				} break;

				case 4: {//caso de apostar mayor o menor

					if(getBola()==0){

						premio=premio-atoi(cantidad);
						gananciasBanca=gananciasBanca+atoi(cantidad);

					}else{

						string mitad;

						if(getBola()<=18){

							mitad="bajo";

						}else{mitad="alto";}

						if(strcmp(valor,mitad.c_str())==0){

							premio=premio+atoi(cantidad);
							gananciasBanca=gananciasBanca-atoi(cantidad);

						}else{

							premio=premio-atoi(cantidad);
							gananciasBanca=gananciasBanca+atoi(cantidad);

						}

					}

				} break;

				default: {//no debería de ocurrir nunca

					printf("Ha ocurrido un error extraño\n");

					exit(EXIT_FAILURE);

				} break;

			}

		}

		(*aux).setDinero((*aux).getDinero()+premio);//actualizo el dinero del usuario

		f1.close();

	}else{

		printf("El archivo no se ha podido abrir\n");
		exit(EXIT_FAILURE);

	}

}