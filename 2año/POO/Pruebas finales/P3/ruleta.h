//Realizado por Antonio Gómez Giménez
//Este código es la clase ruleta

#ifndef RULETA_H
#define RULETA_H

#include "crupier.h"
#include "jugador.h"

#include <list>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class Ruleta:public Crupier{

private:

int banca_;
int bola_;
list<Jugador> jugadores_;
Crupier crupier_; 

public:
	Ruleta(Crupier C):crupier_(C){ 

		bola_=-1;
		banca_=1000000;
		srand(time(NULL));

	};

inline int getBola() const {return bola_;};

inline int getBanca() const {return banca_;};

inline Crupier getCrupier() const {return crupier_;};

inline list<Jugador> getJugadores() const {return jugadores_;};

bool setBanca(int n);

bool setBola(int n);

void setCrupier(Crupier ModCrupier);

bool addJugador(Jugador NewJugador);//función que añade un jugador

int deleteJugador(string NIFJugador);//función que borra un jugador

int deleteJugador(Jugador BorrarJugador);//función igual que la anterior pero distintos parametros de entrada

void escribeJugadores();//función que escribe en un fichero los datos de los jugadores que apuestan

void leeJugadores();//función que pasa los datos del jugadores.txt a la lista jugadores_

inline void giraRuleta() {setBola(rand()%37);};//genero numero aleatorio y lo pongo en la bola

void getPremios();//funcion que reparte los premios

void jugadorApuesta(list <Jugador> ::iterator aux, int &gananciasBanca);//función auxiliar que comprueba las todas la apuestas de un jugador

};

#endif