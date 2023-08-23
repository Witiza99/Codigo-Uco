#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;


int main(int argc, char **argv){

	float suma;

	if(argc!=0){

		for(int i=1;i<argc;i++){

			suma=suma+stoi(argv[i]);

		}

		float media=suma/argc;

		cout<<"La media es:"<<media<<endl;

	}

	else{cout<<"Hay un error"<<endl;}

	cin.get();
	cin.ignore();

}

