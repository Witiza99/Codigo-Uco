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
		contador1_=0;
		contador2_=0;
		suma1_=0;
		suma2_=0;

		for(int i=0;i<5;i++){

			vv1[i]=0;
			vv2[i]=0;

		}

	}

 	bool Dados::setDado1(int n){

 		if((n<=6)&&(n>=1)){

 			d1_=n;

 			contador1_++;

 			suma1_=suma1_+d1_;

 			for(int i=1;i<5;i++){

 				vv1[i]=vv1[i+1];

 			}

 			vv1[5]=d1_;

 			return true;

 		}else{return false;}

 	}

 	bool Dados::setDado2(int n){

 		if((n<=6)&&(n>=1)){

 			d2_=n;

 			contador2_++;

 			suma2_=suma2_+d2_;

 			for(int i=1;i<5;i++){

 				vv2[i]=vv2[i+1];

 			}

 			vv2[5]=d2_;

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

		contador1_++;
		contador2_++;

		suma1_=suma1_+d1_;
		suma2_=suma2_+d2_;

		for(int i=0;i<4;i++){

 				vv1[i]=vv1[i+1];

 			}

 		vv1[5]=d1_;

 		for(int i=1;i<4;i++){

 			vv2[i]=vv2[i+1];

 		}

 		vv2[5]=d2_;

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

 	int Dados::getLanzamientos1() const{

 		return contador1_;

 	}

 	 int Dados::getLanzamientos2() const{

 		return contador2_;
 		
 	}

 	float Dados::getMedia1(){

 		if(contador1_!=0){

 		media1_=(float)suma1_/(float)contador1_;

 		return (float)media1_;

 	}else {return 0;}

 	}

 	float Dados::getMedia2(){

	if(contador2_!=0){

 		media2_=(float)suma2_/(float)contador2_;

 		return (float)media2_;

 	}else {return 0;}

 	}

 	void Dados::getUltimos1(int *v1){

 		for(int i=5;i>0;i--){

 			v1[5-i]=vv1[i];

 		}
 
 	}

 	void Dados::getUltimos2(int *v2){

		for(int i=5;i>0;i--){

 			v2[5-i]=vv2[i];

 		}
 		
 	}