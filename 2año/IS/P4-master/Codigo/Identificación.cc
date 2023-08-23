#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include "Profesor.h"

using namespace std;

bool Profesor::Identificacion(string Usuario, string Contrasena){
  char auxs[20];
  string User;
  string Pass;
  bool Coord;
  ifstream file("Credenciales.bin", ios::binary);
  if(file.fail()){
    cout << "No se pudo abrir el fichero" <<endl;
    exit(1);
  }
  while(file.eof()!=1){
    file.read(auxs,sizeof(char[20]));
    User=auxs;
    file.read(auxs,sizeof(char[20]));
    Pass=auxs;
    file.read(auxs,sizeof(bool));
    Coord=atoi(auxs);
    if((Usuario==User)&&(Pass==Contrasena)){
      setCoordinador(Coord);
      system("clear");
      usuario_=User;
      contrasena_=Pass;
      return true;
    }
  }
  system("clear");
  return false;
}
