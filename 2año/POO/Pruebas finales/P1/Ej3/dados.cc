//dados.cc
//Methots of the class Dados

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "dados.h"



	Dados::Dados(){

		srand(time(NULL));
		d1_=1;
		d2_=1;

	}

 	int Dados::getDado1(){
;
 		return d1_;

 	}

 	int Dados::getDado2(){

 		return d2_;

 	}

 	bool Dados::setDado1(int n){

 		if((n<=6)&&(n>=1)){

 			d1_=n;

 			return true;

 		}else{return false;}

 	}

 	bool Dados::setDado2(int n){

 		if((n<=6)&&(n>=1)){

 			d2_=n;

 			return true;

 		}else{return false;}


 	}

 	int Dados::getSuma(){

 		int suma;

 		suma=d1_+d2_;

		return suma;

 	}

 	void Dados::lanzamiento(){

 		d1_=(rand()%6)+1;
		d2_=(rand()%6)+1;

 	}

 	int Dados::getDiferencia(){

 		int n;

 		if(d1_<d2_){

 			n=d2_-d1_;

 		}else{

 			n=d1_-d2_;

 		}

 		return n;
 		
 	}