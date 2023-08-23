//guess.cc
//this program generate a number between 1 and 10 and ask a number

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){

	srand(time(NULL)); //tune(NULL)returns "UNIX Epoch"

	int n;
	int i=12;

	n=rand()%11; //the program take a random number

	while(i!=n){ //in this while, the program search the number between 1 and 10

		cout << "Introduce un numero emtre 0 y 10:";

		cin >> i;

		if(n<i){

			cout << "El numero introducido es mayor\n";

		}else{

			if(n>i){

				cout <<"El numero introducido es menor\n";

			}else{

				cout << "El numero es correcto\n"; //the program says that number is correct

			}

		}

	}

	return 0;

}; 