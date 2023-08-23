#include "funciones.h"
#include <iostream>
#include <cstdlib>


using namespace std;

int main(int argc, char *argv[])
{
   int aux=0;

   while (aux!=4){

      cout << "Pulsa la opción que desee:"<<endl;
      cout <<"1.Backtracking para las n reinas: "<<endl;
      cout <<"2.Vegas para las n reinas: "<<endl;
      cout <<"3.Parte de la práctica 1: "<<endl;
      cout <<"4.Cerrar programa"<<endl;

      cin >> aux;

      int n, min, max, incremento;
      bool mostrar=0;
      vector<vector<int>> soluciones;

      switch(aux){

         case 1:
            cout<<"Introduce la cantidad de reinas en el tablero"<<endl;
            cin>>n;

            cout<<"¿Desea ver todas las soluciones?[SI=1/NO=0]"<<endl;
            cin>>mostrar;
            
            funcionIntermediaBacktracking(mostrar, n, soluciones);
         break;

         case 2:
         	cout<<"Introduce la cantidad de reinas en el tablero"<<endl;
            cin>>n;

            cout<<"¿Desea ver la solucion?[SI=1/NO=0]"<<endl;
            cin>>mostrar;
            
			funcionIntermediaVegas(mostrar, n, soluciones);
         break;

         case 3:
         //Se piden por teclado las variables necesarias
			cout<<"Introduce el máximo número de elementos"<<endl;
			cin>>max;
			cout<<"Introduce el mínimo número de elementos"<<endl;
			cin>>min;
			cout<<"Introduce por cuanto vas a querer incrementar n"<<endl;
			cin>>incremento;
         	parte_practica1(min, max, incremento);
         break;
       
         case 4:
            cout << "Cerrando el programa" << endl;
         break;

         default:
            cout <<"El valor introducido no es válido, introduzca un valor correcto."<<endl;
                     
         break;
      }
      cin.ignore();
      cin.ignore();  
      system("clear");
   }
        
   return 0;
}
