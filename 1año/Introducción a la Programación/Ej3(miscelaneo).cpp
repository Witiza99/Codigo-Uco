#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char **argv){

	if(argc!=0){

		if(argc==4){

			if((stoi(argv[4])%4)==0){cout<"Es bisiesto"<<endl;}

			else{cout<"No es bisiesto"<<endl;}

		}
	
	}

	else{cout<<"Hay un error"<<endl;}

	cin.get();
	cin.ignore();

}

