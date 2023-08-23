//dados.h
//this .h save the class, his name is dados

#ifndef DADOS_H
#define DADOS_H

 class Dados{ //la clase tiene dos lazamientos de dados

 private:

 	int d1_;
 	int d2_;
 	int contador1_;
 	int contador2_;
 	float media1_;
 	float media2_;
 	int suma1_;
 	int suma2_;
 	int vv1[5];
 	int vv2[5];

 public:

 	Dados(); //este es el constructor
 	int getDado1() const {return d1_;}; //devuelve el numero del dado 1
 	int getDado2() const {return d2_;}; //devuelve el numero del dado 2
 	bool setDado1(int n); //coloca en el dado 1 el valor del numero pasado
 	bool setDado2(int n); //coloca en el dado 2 el valor del numero pasado
 	int getSuma(); //devuelve la suma de los dos dados
 	void lanzamiento(); //nuevo valores para los dados
 	int getDiferencia(); //devuelve la diferencia entre el dado mayor y el menor
 	int getLanzamientos1() const; //devuelve la cantidad de lanzamientos del dado 1
 	int getLanzamientos2() const;//devuelve la cantidad de lanzamientos del dado 2
 	float getMedia1(); //devuelve la media del dado 1
 	float getMedia2(); //devuelve la media del dado 2
 	void getUltimos1(int *v1); //devuelve un vector de los 5 ultimos lanzamientos del dado 1
 	void getUltimos2(int *v2); //devuelve un vector de los 5 ultimos lanzamientos del dado 2

};

#endif 