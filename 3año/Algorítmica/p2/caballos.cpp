#include "caballos.hpp"

int Calculo_Caminos(int a, int b, std::vector <std::vector <Point> > &vpadre, std::vector <Point> vhijo){

	if((b<1)||(b>8)||(a>8)||(a<1)){return 0;}//elemino opciones que se salen del tablero

	Point auxiliar;
	auxiliar.a=a;
	auxiliar.b=b;
	vhijo.push_back(auxiliar);

	if(a==1){
		vpadre.push_back(vhijo);
		return 1;
	}
	//llego a caso base
	return (int)(Calculo_Caminos(a-1,b-2,vpadre,vhijo)+Calculo_Caminos(a-2,b-1,vpadre,vhijo)+Calculo_Caminos(a-2,b+1,vpadre,vhijo)+Calculo_Caminos(a-1,b+2,vpadre,vhijo));
}

void Parte1(){

	int aux=0;
	int sol;
	std::vector <std::vector <Point> > vpadre;
	std::vector <Point> vhijo;
	do{
		std::cout<<"Introduce el el lugar (de 1 a 8) donde quiere que llegue el caballo"<<std::endl;
		std::cin>>aux;
		if((aux<1)||(aux>8)){
			std::cout<<"Numero erroneo introduzca uno correcto..."<<std::endl;
		}
	}while((aux<1)||(aux>8));

	sol=Calculo_Caminos(8,aux,vpadre, vhijo);
	vhijo.clear();

	std::cout<<"El numero de posible de caminos para (8,"<<aux<<") es de: "<<sol<<std::endl;
	std::cout<<"¿Desea representar en un tablero en modo texto las soluciones? [1=SI;0=NO]"<<std::endl;
	std::cin>>aux;

	for(unsigned int i=0;i<vpadre.size();i++){
		std::cout<<"Camino "<<i<<":";
		for(unsigned int j=0;j<vpadre[i].size();j++){
			std::cout<<"("<<vpadre[i][j].a<<", "<<vpadre[i][j].b<<")";
		}
		std::cout<<std::endl;

		if(aux==1){
			int t=0;
			for(int k=8;k>0;k--){
				for(int w=1;w<=8;w++){
					if(((int)k==vpadre[i][t].a)&&((int)w==vpadre[i][t].b)){
						std::cout<<"|_X_|";///mirar
						t++;
					}else{std::cout<<"|___|";}
				}
				std::cout<<std::endl;
			}
		}
		std::cout<<"Pulse para ver la siguiente solucion: "<<std::endl;
	    std::cin.ignore();
	}
	// Se elimina el salto de línea del flujo de entrada
    std::cin.ignore();
    std::cin.ignore();

}

void Parte2(){
	int sol;
	int aux=0;
	std::vector <std::vector <Point> > vpadre;
	std::vector <Point> vhijo;

	sol=Calculo_Caminos(9-1,9-2,vpadre, vhijo);
	vhijo.clear();

	std::cout<<"El numero de posible de caminos para (1, 2) es de: "<<sol<<std::endl;
	std::cout<<"¿Desea representar en un tablero en modo texto las soluciones? [1=SI;0=NO]"<<std::endl;
	std::cin>>aux;

	for(unsigned int i=0;i<vpadre.size();i++){
		vhijo.clear();
		std::cout<<"Camino "<<i<<":";
		for(unsigned int j=0;j<vpadre[i].size();j++){
			std::cout<<"("<<9-vpadre[i][j].a<<", "<<9-vpadre[i][j].b<<")";

			if(aux==1){
				Point auxiliar;
				auxiliar.a=9-vpadre[i][j].a;
				auxiliar.b=9-vpadre[i][j].b;
				vhijo.push_back(auxiliar);
			}
		}
		std::cout<<std::endl;

		if(aux==1){
			int t=vhijo.size()-1;
			for(int k=8;k>0;k--){
				for(int w=1;w<9;w++){
					if(((int)k==vhijo[t].a)&&((int)w==vhijo[t].b)){
						std::cout<<"|_X_|";///mirar
						t--;
					}else{std::cout<<"|___|";}
				}
							std::cout<<std::endl;
			}
		}
		std::cout<<"Pulse para ver la siguiente solucion: "<<std::endl;
	    std::cin.ignore();
	}

	// Se elimina el salto de línea del flujo de entrada
    std::cin.ignore();
    std::cin.ignore();
}

void Parte3(){
	int sol;
	int aux=0;
	std::vector <std::vector <Point> > vpadre;
	std::vector <Point> vhijo;

	sol=Calculo_Caminos(9-1,9-7,vpadre, vhijo);
	vhijo.clear();

	std::cout<<"El numero de posible de caminos para (1, 2) es de: "<<sol<<std::endl;
	std::cout<<"¿Desea representar en un tablero en modo texto las soluciones? [1=SI;0=NO]"<<std::endl;
	std::cin>>aux;

	for(unsigned int i=0;i<vpadre.size();i++){
		vhijo.clear();
		std::cout<<"Camino "<<i<<":";
		for(unsigned int j=0;j<vpadre[i].size();j++){
			std::cout<<"("<<9-vpadre[i][j].a<<", "<<9-vpadre[i][j].b<<")";

			if(aux==1){
				Point auxiliar;
				auxiliar.a=9-vpadre[i][j].a;
				auxiliar.b=9-vpadre[i][j].b;
				vhijo.push_back(auxiliar);
			}
		}
		std::cout<<std::endl;

		if(aux==1){
			int t=vhijo.size()-1;
			for(int k=8;k>0;k--){
				for(int w=1;w<9;w++){
					if(((int)k==vhijo[t].a)&&((int)w==vhijo[t].b)){
						std::cout<<"|_X_|";///mirar
						t--;
					}else{std::cout<<"|___|";}
				}
							std::cout<<std::endl;
			}
		}
		std::cout<<"Pulse para ver la siguiente solucion: "<<std::endl;
	    std::cin.ignore();
	}

	// Se elimina el salto de línea del flujo de entrada
    std::cin.ignore();
    std::cin.ignore();

}
void Parte4(){
	int sol;
	int aux=0;
	std::vector <std::vector <Point> > vpadre;
	std::vector <Point> vhijo;

	do{
		std::cout<<"Introduce el el lugar (de 1 a 8) donde quiere que salga el caballo: "<<std::endl;
		std::cin>>aux;
		if((aux<1)||(aux>8)){
			std::cout<<"Numero erroneo introduzca uno correcto..."<<std::endl;
		}
	}while((aux<1)||(aux>8));

	aux=9-aux;

	sol=Calculo_Caminos(8,aux,vpadre, vhijo);
	vhijo.clear();

	std::cout<<"El numero de posible de caminos para (1, "<<aux<<") es de: "<<sol<<std::endl;
	std::cout<<"¿Desea representar en un tablero en modo texto las soluciones? [1=SI;0=NO]"<<std::endl;
	std::cin>>aux;

	for(unsigned int i=0;i<vpadre.size();i++){
		vhijo.clear();
		std::cout<<"Camino "<<i<<":";
		for(unsigned int j=0;j<vpadre[i].size();j++){
			std::cout<<"("<<9-vpadre[i][j].a<<", "<<9-vpadre[i][j].b<<")";

			if(aux==1){
				Point auxiliar;
				auxiliar.a=9-vpadre[i][j].a;
				auxiliar.b=9-vpadre[i][j].b;
				vhijo.push_back(auxiliar);
			}
		}
		std::cout<<std::endl;

		if(aux==1){
			int t=vhijo.size()-1;
			for(int k=8;k>0;k--){
				for(int w=1;w<9;w++){
					if(((int)k==vhijo[t].a)&&((int)w==vhijo[t].b)){
						std::cout<<"|_X_|";///mirar
						t--;
					}else{std::cout<<"|___|";}
				}
							std::cout<<std::endl;
			}
		}
		std::cout<<"Pulse para ver la siguiente solucion: "<<std::endl;
	    std::cin.ignore();
	}

	// Se elimina el salto de línea del flujo de entrada
    std::cin.ignore();
    std::cin.ignore();
}