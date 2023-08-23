#include "Quicksort.hpp"
#include "Multiplicacionmatrices.hpp"

using namespace::std;

int main()
{
	srand(time(NULL));
	int aux=0;

	while (aux!=3){

		cout << "Pulsa la opción que desee:"<<endl;
		cout <<"1.Ordenacion Quicksort"<<endl;
		cout <<"2.Producto de Matrices"<<endl;
		cout <<"3.Salir del programa"<<endl;

		cin >> aux;

		switch(aux){

			case 1:
			Parte1();
			break;
			case 2:
			Parte2();
			break;
			case 3:
			cout << "Cerrando el programa" << endl;
			break;
			default:
			cout <<"El valor introducido no es válido, introduzca un valor correcto."<<endl;
			break;
		}
	system("clear");

	}
}