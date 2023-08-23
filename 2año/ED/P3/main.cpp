#include <iostream>
#include <cstdlib> //para usar srand()

#include "arbolbinarioordenadoenlazado.hpp"
#include "operadornodo.hpp"
#include "persona.hpp"
#include "generarpersona.hpp"

using namespace ed;

void pausa(){//funcion para ir parando el programa
	std::cout<<"Pulsa enter para continuar:"<<endl;
	std::cin.ignore();//paro para poder ver lo anterior
	std::cin.ignore();
}

int main(){
	srand(time(0));
	ArbolBinarioOrdenadoEnlazado<Persona> a;
	int contador=0;
	Persona auxiliar;//esta persona es auxiliar para la busqueda e insercion

	//Permite salir del menu
	while(contador!=6){

		system("clear");//limpio la terminal
		////////////////////////////////////////////////////////
	  	std::cout<<"1.Insertar personas"<<std::endl;
	  	std::cout<<"2.Buscar persona"<<std::endl;
	  	std::cout<<"3.Mostrar arbol en preorden, postorden y preorden"<<std::endl;
	  	std::cout<<"4.Borrar persona"<<std::endl;
	  	std::cout<<"5.Borrar todo el arbol"<<std::endl;
	  	std::cout<<"6.Salir del programa"<<std::endl;

	  	std::cin>>contador;

	  	switch(contador){

	  		case 1:
	  		system("clear");//limpia la terminal
	  		int n;
	  		std::cout<<"Introduzca el numero de personas que desea insertar en el arbol"<<std::endl;//pido la cantidad de personas
	  		std::cin>>n;
	  		std::cout<<"Introduciendo datos..."<<std::endl;
	  		for(int i=0;i<n;i++){
	  			auxiliar=generarDatosPersonales();//les doy valores
	  			a.insertar(auxiliar);//las introduzco en el arbol
	  		}
	  		std::cout<<"Los datos se han introducido satisfactoriamente"<<std::endl;
	  		pausa();
	  		break;

	  		case 2:
	  		system("clear");
	  		std::cout<<"Introduzca todos los datos de la persona que busca (nombre, apellido, dni)"<<std::endl;//pido datos de la persona que busco
	  		std::cin>>auxiliar;
  			if(a.buscar(auxiliar)==true){//busco la persona en el arbol
  				std::cout<<"La persona se ha encontrado en el arbol"<<std::endl;
  			}else{std::cout<<"La persona no se ha encontrado en el arbol"<<std::endl;}
	  		pausa();
	  		break;

	  		case 3:
	  		system("clear");
	  		for(int i=0;i<1;i++){//no entiendo el porque pero cuando creo un Persona tengo que crearla dentro del for sino no me compila
	  			EscribirNodo<Persona> operador;//en vez de usar operadornodo uso el que me interesa
		  		std::cout<<"Arbol en recorrido preorden:"<<std::endl;
		  		a.recorridoPreOrden(operador);
		  		std::cout<<"Arbol en recorrido postorden:"<<std::endl;
		  		a.recorridoPostOrden(operador);
		  		std::cout<<"Arbol en recorrido inorden:"<<std::endl;
		  		a.recorridoInOrden(operador);
	  		}
	  		pausa();
	  		break;

	  		case 4:
	  		system("clear");
	  		
	  		std::cout<<"Introduzca todos los datos de la persona que desea borrar (nombre, apellido, dni)"<<std::endl;//pido datos de la persona que busco
	  		std::cin>>auxiliar;
  			if(a.buscar(auxiliar)==true){//busco la persona en el arbol
  				a.borrar();
  				std::cout<<"La persona se ha borrado con exito"<<std::endl;
  			}else{std::cout<<"La persona que querías borrar no se ha encontrado en el arbol"<<std::endl;}
	  		pausa();
	  		break;

	  		case 5:
	  		system("clear");
	  		std::cout<<"Borrando el arbol..."<<std::endl;
	  		a.borrarArbol();
	  		std::cout<<"Arbol borrado con exito"<<std::endl;
	  		pausa();
	  		break;

	  		case 6:
	  		system("clear");
	  		std::cout<<"Hasta luego"<<std::endl;
	  		break;

	  		//para cuando introduzca un numero erroneo
	  		default:
	  		system("clear");
	  		std::cout<<"El numero introducido no es valido, ponga uno valido por favor."<<endl;
	  		pausa();
	  		break;
	  	}
	}
	return 0;
}