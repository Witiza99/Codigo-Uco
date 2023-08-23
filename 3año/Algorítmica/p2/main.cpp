#include "caballos.hpp"

using namespace::std;

int main()
{
	int aux=0;

	while (aux!=5){

		cout << "Pulsa la opción que desee:"<<endl;
		cout <<"1.Calculo de caminos posibles introducido por usuario"<<endl;
		cout <<"2.Caminos para (1,2)"<<endl;
		cout <<"3.Caminos para (1,7)"<<endl;
		cout <<"4.Caminos para cualquier valor inicial"<<endl;
		cout <<"5.Cerrar programa"<<endl;

		cin >> aux;

		switch(aux){

			case 1:
			Parte1();
			break;
			case 2:
			Parte2();
			break;
			case 3:
			Parte3();
			break;
			case 4:
			Parte4();
			break;
			case 5:
			cout << "Cerrando el programa" << endl;
			break;
			default:
			cout <<"El valor introducido no es válido, introduzca un valor correcto."<<endl;
			break;
		}
	system("clear");
	}
}