//codigo creado por Antonio Gómez Giménez
//funciones de la clase contador

#include "contador.h"

Contador Contador::operator++(void){//para ++c
	valor_++;
	if(valor_>max_){valor_=max_;}
	contador_++;
	auxiliar_.push_back(valor_);//añado el valor en mi vector por si lo necesito para undo
	return *this;
}
Contador Contador::operator--(void){//para --c
	valor_--;
	if(valor_<min_){valor_=min_;}
	contador_++;
	auxiliar_.push_back(valor_);
	return *this;
}
Contador Contador::operator++(int){//para c++
	Contador aux=*this;//creo clase auxiliar para pasar la clase sin modificar aunque esta este modificada
	valor_++;
	if(valor_>max_){valor_=max_;}
	contador_++;
	auxiliar_.push_back(valor_);
	return aux;
}
Contador Contador::operator--(int){//para c--
	Contador aux=*this;//creo clase auxiliar para pasar la clase sin modificar aunque esta este modificada
	valor_--;
	if(valor_<min_){valor_=min_;}
	aux.contador_++;
	aux.auxiliar_.push_back(aux.valor_);
	return aux;
}
Contador operator+(int i, const Contador &p){//para realizar suma entero+clase contatador devolviendo una clase contador
	Contador aux(p);
	aux.valor_=i+p.valor_;
	if(aux.valor_<aux.getMin()||aux.valor_>aux.getMax()){
		if(aux.valor_<aux.getMin()){aux.valor_=aux.getMin();}
		else{aux.valor_=aux.getMax();}
	}
	aux.contador_++;
	aux.auxiliar_.push_back(aux.valor_);
	return aux;
}
Contador operator+(const Contador &p, int i){//igual que el anterior pero inverso
	Contador aux(p);
	aux.valor_=p.valor_+i;
	if(aux.valor_<aux.getMin()||aux.valor_>aux.getMax()){
		if(aux.valor_<aux.getMin()){aux.valor_=aux.getMin();}
		else{aux.valor_=aux.getMax();}
	}
	aux.contador_++;
	aux.auxiliar_.push_back(aux.valor_);
	return aux;
}
Contador operator-(int i, const Contador &p){//para realizar suma entero-clase contatador devolviendo una clase contador
	Contador aux(p);
	aux.valor_=i-p.valor_;
	if(aux.valor_<aux.getMin()||aux.valor_>aux.getMax()){
		if(aux.valor_<aux.getMin()){aux.valor_=aux.getMin();}
		else{aux.valor_=aux.getMax();}
	}
	aux.contador_++;
	aux.auxiliar_.push_back(aux.valor_);
	return aux;
}
Contador operator-(const Contador &p, int i){//igual que el anterior pero inverso
	Contador aux(p);
	aux.valor_=p.valor_-i;
	if(aux.valor_<aux.getMin()||aux.valor_>aux.getMax()){
		if(aux.valor_<aux.getMin()){aux.valor_=aux.getMin();}
		else{aux.valor_=aux.getMax();}
	}
	aux.contador_++;
	aux.auxiliar_.push_back(aux.valor_);
	return aux;
}
bool Contador::undo(int n){//permite deshacer operaciones sobre la clase contador;
	if(n<1||n>=contador_){return false;}
	for(int i=0; i< n; i++){
		auxiliar_.pop_back();//voy eliminado aquellas operaciones que no se quieren
	}
	valor_=auxiliar_.back();//me quedo con el valor pedido
	return true;
}