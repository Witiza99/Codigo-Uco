//codigo creado por Antonio Gómez Giménez
//esta clase consiste en el uso de operadores

#ifndef CONTADOR_H
#define CONTADOR_H

#include <cstdlib>
#include <iostream>
#include <list>

using namespace std;

class Contador{

private:
	int valor_;
	int max_;
	int min_;
	int contador_;
	list<int> auxiliar_;

public:
	Contador(int valor=0, int min=0, int max=1000){

		contador_=0;
		valor_=valor;
		min_=min;
		max_=max;
		if(min_<max_){
			if((valor_<min_)||(valor_>max_)){valor_=0;}		
		}else{
			valor_=0;
			min_=0;
			max_=1000;
		}
		contador_++;
		auxiliar_.push_back(valor_);
	}
	inline void setNum(int valor){valor_=valor;};//para poner un numero
	inline int getMax()const{return max_;};//ver máximo
	inline void setMax(int max){max_=max;};//poner máximo
	inline int getMin()const{return min_;};//ver mínimo
	inline void setMin(int min){min_=min;};//poner mínimo
	inline int getcontador()const{return contador_;};//ver contador

	inline Contador operator=(int valor){//poner un valor
		valor_=valor;
		if((valor_<min_)||(valor_>max_)){
			if(valor_<min_){valor_=min_;}
			else{valor_=max_;}
		}
		contador_++;
		auxiliar_.push_back(valor_);
		return *this;
	};
	inline Contador operator=(const Contador &p){//poner una clase
		valor_=p.valor_;
		min_=p.min_;
		max_=p.max_;
		contador_++;
		auxiliar_.push_back(valor_);
		return *this;
	};
	Contador operator++(void);//para ++c
	Contador operator--(void);//para --c
	Contador operator++(int);//para c++
	Contador operator--(int);//para c--
	friend Contador operator+(int i, const Contador &p);//para realizar suma entero+clase contatador devolviendo una clase contador
	friend Contador operator+(const Contador &p, int i);//igual que el anterior pero inverso
	friend Contador operator-(int i, const Contador &p);//para realizar suma entero-clase contatador devolviendo una clase contador
	friend Contador operator-(const Contador &p, int i);//igual que el anterior pero inverso
	bool undo(int n=1);//permite deshacer operaciones sobre la clase contador;
	inline int get()const {return valor_;};
};
#endif