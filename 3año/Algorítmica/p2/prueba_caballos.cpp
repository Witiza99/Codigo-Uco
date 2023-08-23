#include "caballos.hpp"

int Calculo_Caminos(int a, int b, std::vecor<std::vector<Point>> &vPadre, std::vector<Point> vhijo){
	if((a<1)||(a>8)||(b<1)||(b>8)){
		return 0;
	}

	Point p;
	p.a=a;
	p.b=b;
	vhijo.push_back(p);

	if(a==1){
		vPadre.push_back(vhijo);
		return 1;
	}
	return ((Calculo_Caminos(a-1,b-2,vPadre,vhijo))+(Calculo_Caminos(a-2,b-1,vPadre,vhijo))+(Calculo_Caminos(a-2,b+1,vPadre,vhijo))+(Calculo_Caminos(a-1,b+2,vPadre,vhijo)))
}

void Parte1(){

	std::vector<std::vector<Point>> vPadre;
	std::vector<Point> vhijo;
	int sol;
	int aux;

	std::cout<<"Introduce el lugar (1 a 8) donde quiere que llegue el caballo"<<std::endl;
	std::cin>>aux;

	while((aux<1)||(aux>8)){
		std::cout<<"El numero introducido no es valido, introduzca uno correcto"<<std::endl;
		std::cin>>aux;
	}

	sol=Calculo_Caminos(8,aux,vPadre,vhijo);

	std::cout<<"hay "<<sol<<" caminos, desea ver cuales son estos caminos: [SI=1/NO=0]"<<std::endl;
	std::cin>>aux;

	while((aux!=1)&&(aux!=0)){
		std::cout<<"El numero introducido no es valido, introduzca uno correcto"<<std::endl;
		std::cin>>aux;
	}
	std::cin.ignore();
	if(aux==1){
		for(unsigned i=0;i<vPadre.size();i++){
			std::cout<<"Camino "<<i<<": ";
			for(unsigned j=0;j<vPadre[i].size();j++){
				std::cout<<"("<<vPadre[i][j].a<<", "<<vPadre[i][j].b<<")";
			}
			std::cout<<std::endl;
			std::cout<<"Pulse para ver la siguiente solucion: "<<std::endl;
	    	std::cin.ignore();
		}
	}
}

void Parte2(){
	std::vector<std::vector<Point>> vPadre;
	std::vector<Point> vhijo;
	int sol;
	int aux;

	sol=Calculo_Caminos(9-1,9-2,vPadre,vhijo);

	std::cout<<"hay "<<sol<<" caminos posibles, desea ver cuales son estos caminos: [SI=1/NO=0]"<<std::endl;
	std::cin>>aux;

	while((aux!=0)&&(aux!=1)){
		std::cout<<"El numero introducido no es valido, introduzca uno correcto"<<std::endl;
		std::cin>>aux;
	}
	std::cin.ignore();

	if(aux==1){
		for(unsigned i=0;i<vPadre.size();i++){
			std::cout<<"camino "<<i<<": "<<std::endl;
			for(unsigned j=0;j<vPadre[i].size();j++){
				std::cout<<"("<<9-vPadre[i][j].a<<", "<<9-vPadre[i][j].b<<")";
			}
			std::cout<<std::endl;
			std::cout<<"Pulse para ver la siguiente solucion: "<<std::endl;
	    	std::cin.ignore();
		}
	}



}
void Parte3(){

}
void Parte4(){

}