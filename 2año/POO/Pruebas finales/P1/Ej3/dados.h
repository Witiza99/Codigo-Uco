//dados.h
//this .h save the class, his name is dados

#ifndef DADOS_H
#define DADOS_H

 class Dados{ //la clase tiene dos lazamientos de dados

 private:

 	int d1_;
 	int d2_;

 public:

 	Dados(); //este es el constructor
 	int getDado1(); //devuelve el numero del dado 1
 	int getDado2(); //devuelve el numero del dado 2
 	bool setDado1(int n); //coloca en el dado 1 el valor del numero pasado
 	bool setDado2(int n); //coloca en el dado 2 el valor del numero pasado
 	int getSuma(); //devuelve la suma de los dos dados
 	void lanzamiento(); //nuevo valores para los dados
 	int getDiferencia(); //devuelve la diferencia entre el dado mayor y el menor

};

#endif 