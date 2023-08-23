#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;


int main(int argc, char **argv){

	float suma=0;

	if(argc!=1){

		for(int i=1;i<argc;i++){

			suma=suma+stof(argv[i]);

		}

		float media=suma/(argc-1);

		cout<<"La media es:"<<media<<endl;

	}

	else{cout<<"No has introducido numeros"<<endl;}

	cin.get();
	cin.ignore();

}

