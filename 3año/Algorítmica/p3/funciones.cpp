#include "funciones.hpp"

void Parte1(){
	Entero n1;
	Entero n2;
	Entero n3;

	std::cout<<"Introduce un numero: "<< std::endl;
	cin >> n1;

	std::cout<<"Introduce otro numero: "<< std::endl;
	cin >> n2;

	n3=n1+n2;

	std::cout<<"El resultado de la suma de "<<n1<<" con "<<n2<<" es "<<n3<<std::endl;

}

void Parte2(){

	Entero n1;
	Entero n2;
	Entero n3;

	std::cout<<"Introduce un numero: "<< std::endl;
	cin >> n1;

	std::cout<<"Introduce otro numero: "<< std::endl;
	cin >> n2;

	n3=n1*n2;

	std::cout<<"El resultado de la multiplicacion de "<<n1<<" con "<<n2<<" es "<<n3<<std::endl;
}