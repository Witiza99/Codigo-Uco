#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char **argv){

	if(argc!=1){

		if(argc==4){

			if(((stoi(argv[3])%4)==0)&&((stoi(argv[3])%100)!=0)||((stoi(argv[3])%400)==0)){cout<<"Es bisiesto"<<endl;}

			else{cout<<"No es bisiesto"<<endl;}

		}else{cout<<"No has introducido dia, mes y ano"<<endl;}	
	}

	else{cout<<"No has introducido datos"<<endl;}

	cin.get();
	cin.ignore();

}

