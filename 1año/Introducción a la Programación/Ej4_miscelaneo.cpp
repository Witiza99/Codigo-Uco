#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char **argv){

	if(argc>1){

		float aux=stof(argv[1]);
		string suma="-sum";
		string mult="-mult";
		string div="-div";
		string raiz="-sqrt";

		for (int i=1; i<argc; i++){

			if(argv[i]==suma){aux=aux+stof(argv[i+1]);}

			if(argv[i]==div){aux=aux/stof(argv[i+1]);}

			if(argv[i]==mult){aux=aux*stof(argv[i+1]);}

			if(argv[i]==raiz){

				if(aux>=0){

					aux=sqrt(aux);

				}else{cout<<"No se puede hacer la raiz de un numero negativo"<<endl;}

			}

		}

		cout<<"Su resultado es: "<<aux<<endl;

	}else{cout<<"Hay un error"<<endl;}

	cin.get();
	cin.ignore();

}

