//juego.cc
//this is main of the programm

#include <iostream>
#include <cstdlib>
#include "dados.h"

int main(){

	Dados d;

	int n;

	int d1=d.getDado1();
	int d2=d.getDado2();

	std::cout << "dado 1 = " << d1 << "\n";//dice valor de d1
	std::cout << "dado 2 = " << d2 << "\n";//dice valor de d2

	std::cout << "La suma de los dos dados es " << d.getSuma() << "\n";//hace la suma de los dos dados

	std::cout << "La resta de los dos dados es " << d.getDiferencia() << "\n";//hace la resta de los dos dados

	std::cout << "Introduce el nuevo valor para Dado 1" << "\n";
	std::cin >> n;

	if((d.setDado1(n))==1){//comprueba si el numero es correcto o no

	std::cout <<"El valor introducido es correcto" << "\n";//n

	std::cout << "dado 1 = " << n << "\n";//dice valor de d1

	}else{

		std::cout <<"El valor introducido es incorrecto, no se ha aplicado" << "\n";

		std::cout << "dado 1 = " << d1 << "\n";//dice valor de d1

	}


	std::cout << "Introduce el nuevo valor para Dado 2" << "\n";
	std::cin >> n;
	
	if((d.setDado2(n))==1){//comprueba si el numero es correcto o no

	std::cout <<"El valor introducido es correcto" << "\n";//n

	std::cout << "dado 2 = " << n << "\n";//dice valor de d2

	}else{

		std::cout <<"El valor introducido es incorrecto, no se ha aplicado" << "\n";

		std::cout << "dado 1 = " << d2 << "\n";//dice valor de d1

	}

	std::cout << "La suma de los dos dados es " << d.getSuma() << "\n";//hace la suma de los dos dados

	std::cout << "La resta de los dos dados es " << d.getDiferencia() << "\n";//hace la resta de los dos dados

	std::cout << "Para unos valores nuevos" << "\n";

	d.lanzamiento();

	std::cout << "dado 1 = " <<d.getDado1() << "\n";//dice valor de d1
	std::cout << "dado 2 = " <<d.getDado2() << "\n";//dice valor de d2

	std::cout << "La suma de los dos dados es " << d.getSuma() << "\n";//hace la suma de los dos dados

	std::cout << "La resta de los dos dados es " << d.getDiferencia() << "\n";//hace la resta de los dos dados

	return 0;

}