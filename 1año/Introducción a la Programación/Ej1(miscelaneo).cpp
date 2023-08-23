#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char **argv){

	if (stof(argv[1])>0){

		float resultado =sqrt(stof(argv[1]));

		cout<<"Su resultado es: "<<resultado<<endl;

	}

	else{cout<<"El numero introducido es negativo o no se ha introducido ningun valor"<<endl;}

	cin.get();
	cin.ignore();

}

