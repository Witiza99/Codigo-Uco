#ifndef __FUNCIONES_HPP
#define __FUNCIONES_HPP

#include <iostream>
#include <cstring>
#include <cstdlib> //Para usar system
#include <fstream> //Para trabajar con ficheros
#include <cstdio>

#include "grafo.hpp"
#include "algoritmosgrafos.hpp"

using namespace std;
using namespace ed;

int menu()
{
  int opcion;

  system("clear");
  cout << "  0. Salir................................\n";
  cout << "  1. Cargar grafo desde fichero...........\n";
  cout << "  2. Algoritmo de Floyd (GD y GND)......\n";

  cout << "Introduzca opcion...:";
  cin >> opcion;

  return opcion;
}

template <class G_Nodo, class G_Lado>
bool cargarGrafo(Grafo<G_Nodo, G_Lado> * &g)
{
  string ficheroMatriz, ficheroEtiquetas;

  cout << "Fichero de la matriz de conexion: ";
  cin >> ficheroMatriz;

  cout << "Fichero de las etiquetas: ";
  cin >> ficheroEtiquetas;

  ifstream f1(ficheroMatriz.c_str());
  ifstream f2(ficheroEtiquetas.c_str());
  char aux[100];
  int n=0;;

  if(f1.is_open()){
    if(f2.is_open()){

    while(f2.getline(aux,100,'\n')){n++;}

    g=new Grafo<G_Nodo,G_Lado>(n);

    G_Lado **matriz;
    G_Nodo *vector;
    vector=new G_Nodo [n];
    matriz=new G_Lado *[n];
    for (int i = 0; i < n; i++) {
      matriz[i]=new G_Lado [n];
    }

    //Relleno la matriz y vector
    int i=0;
    int j;
    while(i<n){
      j=0;
      while(j<(n-1)){
        f1.getline(aux,100,' ');
        matriz[i][j]=atoi(aux);
        j++;
      }
      f1.getline(aux,100);
      matriz[i][n-1]=atoi(aux);
      i++;
    }

    i=0;
    f2.clear();
    f2.seekg(0, f2.beg);
    while (!f2.eof()) {
      f2>>vector[i];
      i++;
     }

    g->setNodos(vector);
    g->setLados(matriz);

    f1.close();
    f2.close();

    return true;

  }else{printf("No se puede abrir el archivo\n");}
    }else{printf("No se puede abrir el archivo\n");}
 
  return false;

}

template <class G_Nodo, class G_Lado>
void algoritmoFloyd(Grafo<G_Nodo, G_Lado> &g)
{
  AlgoritmosGrafos <G_Nodo, G_Lado> x;

  //reservo todas la memoria necesaria
  G_Lado **W=g.getLados();
  int n=g.getN();

  G_Lado **D;
  D=new G_Lado *[n];
  for(int i=0; i<n; i++){
    D[i]=new G_Lado [n];
  }

  G_Lado **I;
  I=new G_Lado *[n];
  for(int i=0; i<n; i++){
    I[i]=new G_Lado [n];
  }

  x.Floyd(W,D,I,n);

  int aux;
  std::cout << "¿Quiere visualizar las matrices de Recorridos y Distancias?(0->NO,1->SÍ)" << std::endl;
  std::cin >> aux;

  
  if(aux==1){
    std::cout << "Matriz Inicial(la introducida por fichero)" << std::endl;
    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
        std::cout << W[i][j] << "   ";
      }
      std::cout << std::endl;
    }
  std::cout << "Matriz de Recorridos" << std::endl;
    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
        std::cout << I[i][j] << "   ";
      }
      std::cout << std::endl;
    }
    std::cout << "Matriz de Distancias" << std::endl;
    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
        std::cout << D[i][j] << "   ";
      }
      std::cout << std::endl;
    }
  }

  int origen=0;
  int destino=0;
  G_Nodo *lugares=g.getNodos();

  std::cout << "Ciudades: " << '\n'<<"0:Almeria"<< '\n'<<"1:Cádiz"<< '\n'<<"2:Córdoba"<< '\n'<<"3:Granada"<< '\n'<<"4:Huelva"<< '\n'<<"5:Jaen"<< '\n'<<"6:Málaga"<< '\n'<<"7:Sevilla"<<"\n";
  std::cout << "Ciudad origen(introduzca el número)" << '\n';
  do{
    if(origen>7||origen<0){std::cout << "Introduce un valor válido" << std::endl;}
    std::cin >> origen;
  }while((origen>7)||(origen<0));
  std::cout << "Ciudad destino(introduzca el número)" << '\n';
  do{
    if(destino>7||destino<0){std::cout << "Introduce un valor válido" << std::endl;}
    std::cin >> destino;
  }while((destino>7)||(destino<0));
  std::cout << "Distancia entre " <<lugares[origen]<< " y " <<lugares[destino]<< " es de: "<<D[origen][destino]<< '\n';

  std::cout << "Camino: "<<lugares[origen] << " -> ";
  while (I[origen][destino]!=-1) {
    std::cout << lugares[I[origen][destino]] << " -> ";
    origen=I[origen][destino];
  }
  std::cout << lugares[destino] << std::endl;
}

#endif