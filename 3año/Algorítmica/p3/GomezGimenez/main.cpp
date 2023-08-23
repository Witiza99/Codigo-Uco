#include "funciones.hpp"

using namespace::std;

int main()
{
	int aux=0;

	while (aux!=3){

		cout << "Pulsa la opción que desee:"<<endl;
		cout <<"1.Algoritmo de suma de numeros grandes: "<<endl;
		cout <<"2.Algoritmo de multiplicacion de numeros grandes: "<<endl;
		cout <<"3.Cerrar programa"<<endl;

		cin >> aux;

		switch(aux){

			case 1:
			Parte1();
			// Se elimina el salto de línea del flujo de entrada
		    std::cin.ignore();
		    std::cin.ignore();
			break;
			case 2:
			Parte2();
			// Se elimina el salto de línea del flujo de entrada
		    std::cin.ignore();
		    std::cin.ignore();
			break;
			case 3:
			cout << "Cerrando el programa" << endl;
			break;
			default:
			cout <<"El valor introducido no es válido, introduzca un valor correcto."<<endl;
			// Se elimina el salto de línea del flujo de entrada
		    std::cin.ignore();
		    std::cin.ignore();
			break;
		}
	system("clear");
	}
}