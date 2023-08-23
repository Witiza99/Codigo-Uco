/*!
   \file operadoresExternosPolinomios.cpp
   \brief Fichero que contiene el código de las funciones de la clase Polinomio
*/


// Ficheros de cabecera
#include <iostream>

#include "operadoresExternosPolinomios.hpp"

#include "operadoresExternosMonomios.hpp"

// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed
{

bool operator==(ed::Polinomio const & p1, ed::Polinomio const & p2)
{
	if(p1.getPolinomio().size()==p2.getPolinomio().size()){
		list<Monomio> aux1=p1.getPolinomio();
		list<Monomio> aux2=p2.getPolinomio();
		list<Monomio> :: iterator i=aux1.begin();
		list<Monomio> :: iterator y=aux2.begin();

		while(i!=aux1.end()){
			if((*i)!=(*y)){

				#ifndef NDEBUG
				assert((*i)!=(*y));
			  	#endif //NDEBUG

				return false;}
			i++;
			y++;
		}

		#ifndef NDEBUG
		assert(p1.getPolinomio().size()==p2.getPolinomio().size());
	  	#endif //NDEBUG

		return true;

	}else{

		#ifndef NDEBUG
		assert(p1.getPolinomio().size()!=p2.getPolinomio().size());
	  	#endif //NDEBUG

		return false;
	}	
}

bool operator==(ed::Polinomio const & p, ed::Monomio const & m){
	if(p.getPolinomio().size()==1){
		if((p.getPolinomio().front().getGrado()!=m.getGrado())||(p.getPolinomio().front().getCoeficiente()!=m.getCoeficiente())){
				#ifndef NDEBUG
				assert((p.getPolinomio().front().getGrado()!=m.getGrado())||(!(std::abs(p.getPolinomio().front().getCoeficiente()-m.getCoeficiente())<COTA_ERROR)));
			  	#endif //NDEBUG

				return false;
		}

		#ifndef NDEBUG
		assert(p.getPolinomio().size()==1);
		assert(((p.getPolinomio().front().getGrado()==m.getGrado())&&(std::abs(p.getPolinomio().front().getCoeficiente()-m.getCoeficiente())<COTA_ERROR)));
	  	#endif //NDEBUG

		return true;

	}else{

		#ifndef NDEBUG
		assert(p.getPolinomio().size()!=1);
	  	#endif //NDEBUG

		return false;
	}	
}

bool operator==(ed::Monomio const & m, ed::Polinomio const & p){
	if(p==m){return true;}
	else{return false;}
}

bool operator==(ed::Polinomio const & p, double x){
	if(p.getPolinomio().size()==1){
		if((p.getGrado()!=0)||(p.getPolinomio().front().getCoeficiente()!=x)){

			#ifndef NDEBUG
			assert((p.getGrado()!=0)||(!(std::abs(p.getPolinomio().front().getCoeficiente()-x)<COTA_ERROR)));
		  	#endif //NDEBUG

			return false;
		}

		#ifndef NDEBUG
		assert(p.getPolinomio().size()==1);
		assert((p.getGrado()==0)&&(std::abs(p.getPolinomio().front().getCoeficiente()-x)<COTA_ERROR));
	  	#endif //NDEBUG

		return true;

	}else{

		#ifndef NDEBUG
		assert(p.getPolinomio().size()!=1);
	  	#endif //NDEBUG

		return false;
	}	
}

bool operator==(double x, ed::Polinomio const & p){
	if(p==x){return true;}
	else{return false;}
}


////////////////////////////////////////////////////////////////////////////////////
// Operadores de desigualdad

bool operator!=(ed::Polinomio const & p1, ed::Polinomio const & p2)
{
	if(p1.getPolinomio().size()==p2.getPolinomio().size()){
		list<Monomio> aux1=p1.getPolinomio();
		list<Monomio> aux2=p2.getPolinomio();
		list<Monomio> :: iterator i=aux1.begin();
		list<Monomio> :: iterator y=aux2.begin();

		while(i!=aux1.end()){
			if((*i)!=(*y)){

				#ifndef NDEBUG
				assert((*i)!=(*y));
			  	#endif //NDEBUG

				return true;}
			i++;
			y++;
		}

		#ifndef NDEBUG
		assert(p1.getPolinomio().size()==p2.getPolinomio().size());
	  	#endif //NDEBUG

		return false;

	}else{

		#ifndef NDEBUG
		assert(p1.getPolinomio().size()!=p2.getPolinomio().size());
	  	#endif //NDEBUG

		return true;
	}	
}

bool operator!=(ed::Polinomio const & p, ed::Monomio const & m){
	if(p.getPolinomio().size()==1){
		if((p.getPolinomio().front().getGrado()!=m.getGrado())||(p.getPolinomio().front().getCoeficiente()!=m.getCoeficiente())){
				#ifndef NDEBUG
				assert((p.getPolinomio().front().getGrado()!=m.getGrado())||(!(std::abs(p.getPolinomio().front().getCoeficiente()-m.getCoeficiente())<COTA_ERROR)));
			  	#endif //NDEBUG

				return true;
		}

		#ifndef NDEBUG
		assert(p.getPolinomio().size()==1);
		assert(((p.getPolinomio().front().getGrado()==m.getGrado())&&(std::abs(p.getPolinomio().front().getCoeficiente()-m.getCoeficiente())<COTA_ERROR)));
	  	#endif //NDEBUG

		return false;

	}else{

		#ifndef NDEBUG
		assert(p.getPolinomio().size()!=1);
	  	#endif //NDEBUG

		return true;
	}	
}

bool operator!=(ed::Monomio const & m, ed::Polinomio const & p){
	if(p!=m){return true;}
	else{return false;}
}

bool operator!=(ed::Polinomio const & p, double x){
	if(p.getPolinomio().size()==1){
		if((p.getGrado()!=0)||(p.getPolinomio().front().getCoeficiente()!=x)){

			#ifndef NDEBUG
			assert((p.getGrado()!=0)||(!(std::abs(p.getPolinomio().front().getCoeficiente()-x)<COTA_ERROR)));
		  	#endif //NDEBUG

			return true;
		}

		#ifndef NDEBUG
		assert(p.getPolinomio().size()==1);
		assert((p.getGrado()==0)&&(std::abs(p.getPolinomio().front().getCoeficiente()-x)<COTA_ERROR));
	  	#endif //NDEBUG

		return false;

	}else{

		#ifndef NDEBUG
		assert(p.getPolinomio().size()!=1);
	  	#endif //NDEBUG

		return true;
	}	
}

bool operator!=(double x, ed::Polinomio const & p){
	if(p!=x){return true;}
	else{return false;}
}


//////////////////////////////////////////////////////////////////////////////////////

// Operadores unarios

// COMPLETAR
ed::Polinomio & operator+(ed::Polinomio const & p)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(p);

	#ifndef NDEBUG
	assert(*nuevo==p);
	#endif //NDEBUG
	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator-(ed::Polinomio const & p){
		Polinomio aux;
		for (int i = 0; i <= p.getGrado(); i++) {
			if (p.existeMonomio(i)) {
				aux.insertarMonomio(-(p.getMonomio(i)));
			}
		}
		Polinomio *nuevo = new ed::Polinomio(aux);
		return *nuevo;
}


//////////////////////////////////////////////////////////////////////////////////////

// Operadores binarios de la suma
ed::Polinomio & operator+(ed::Polinomio const &p1,  ed::Polinomio const &p2)
{
	Polinomio aux(p1);
	aux+=p2;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator+(ed::Polinomio const &p,  ed::Monomio const &m)
{
	Polinomio aux(p);
	aux+=m;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator+(ed::Monomio const &m,  ed::Polinomio const &p)
{
	Polinomio aux(p);
	aux+=m;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator+(ed::Polinomio const &p,  double x)
{
	Polinomio aux(p);
	aux+=x;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}


ed::Polinomio & operator+(double x,  ed::Polinomio const &p)
{
	Polinomio aux(p);
	aux+=x;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}

	////////////
	// Resta

	ed::Polinomio & operator-(ed::Polinomio const &p1,  ed::Polinomio const &p2)
{
	Polinomio aux(p1);
	aux-=p2;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator-(ed::Polinomio const &p,  ed::Monomio const &m)
{
	Polinomio aux(p);
	aux-=m;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator-(ed::Monomio const &m,  ed::Polinomio const &p)
{
	Polinomio aux(p);
	aux-=m;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator-(ed::Polinomio const &p,  double x)
{
	Polinomio aux(p);
	aux-=x;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}


ed::Polinomio & operator-(double x,  ed::Polinomio const &p)
{
	Polinomio aux(p);
	aux-=x;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}


//////////////////
// Multiplicación

ed::Polinomio & operator*(ed::Polinomio const &p1,  ed::Polinomio const &p2)
{
	Polinomio aux(p1);
	aux*=p2;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator*(ed::Polinomio const &p,  ed::Monomio const &m)
{
	Polinomio aux(p);
	aux*=m;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator*(ed::Monomio const &m,  ed::Polinomio const &p)
{
	Polinomio aux(p);
	aux*=m;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator*(ed::Polinomio const &p,  double x)
{
	Polinomio aux(p);
	aux*=x;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}


ed::Polinomio & operator*(double x,  ed::Polinomio const &p)
{
	Polinomio aux(p);
	aux*=x;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}

////////////
// División

ed::Polinomio & operator/(ed::Polinomio const &p1,  ed::Polinomio const &p2)
{
	#ifndef NDEBUG
	assert(p2.getGrado()<=p1.getGrado());
	#endif //NDEBUG

	Polinomio aux(p1);
	aux/=p2;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator/(ed::Polinomio const &p,  ed::Monomio const &m)
{
	#ifndef NDEBUG
	assert(m.getGrado()<=p.getGrado());
	#endif //NDEBUG

	Polinomio aux(p);
	aux/=m;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator/(ed::Monomio const &m,  ed::Polinomio const &p)
{
	#ifndef NDEBUG
	assert(p.getGrado()<=m.getGrado());
	#endif //NDEBUG

	Polinomio aux;
	aux=m;
	aux/=p;

	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator/(ed::Polinomio const &p,  double x)
{
	#ifndef NDEBUG
	assert(x!=0);
	#endif //NDEBUG

	Polinomio aux(p);
	aux/=x;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}


ed::Polinomio & operator/(double x,  ed::Polinomio const &p)
{
	#ifndef NDEBUG
	assert(p.getGrado()==0);
	assert(std::abs(p.getMonomio(p.getGrado()).getCoeficiente())> 0.0);
	#endif //NDEBUG

	Polinomio aux(p);
	aux/=x;
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(aux);

	// Se devuelve el resultado
	return *nuevo;
}


////////////////////////////////////////////////////////////////////////////

// Sobrecarga del operador de entrada
istream &operator>>(istream &stream, Polinomio &p)
{
	int nPolinomio;
	Monomio m;
	int i=0;

	stream >> nPolinomio;

	do{
		stream >> m;//tenia pensado controlar la entrada como en monomio pero se me dijo en la primera practica que no lo hiciera
		p.insertarMonomio(m);
		i++;
	}while(i<nPolinomio);

	// Se devuelve el flujo de entrada
  return stream;
}

// Sobrecarga del operador de salida
ostream &operator<<(ostream &stream, Polinomio const &p)
{
	stream<<std::endl;
	stream<<p.getMonomio(p.getGrado());

	for(int i=p.getGrado()-1;i>=0;i--){
		if(p.existeMonomio(i)){
			if((p.getMonomio(i).getGrado()==0)&&(std::abs(p.getMonomio(i).getCoeficiente()-0.0)<COTA_ERROR)){
			}else{stream<<p.getMonomio(i);}
		}
	}
	
	// Se devuelve el flujo de salida
  return stream;
}


} // Fin del espacio de nombres ed
