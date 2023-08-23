#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char **argv){

	if(argc==2){

		if (stof(argv[1])>0){

			float resultado =sqrt(stof(argv[1]));

			cout<<"Su resultado es: "<<resultado<<endl;

		}

		else{cout<<"El numero introducido es negativo"<<endl;}

	}

	else{cout<<"Hay un error"<<endl;}

	cin.get();
	cin.ignore();

}

