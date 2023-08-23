#include "Entero.hpp"

/////////////////////////////////////////////////////////////////////////////
	//operador de suma
	Entero &operator+(Entero const &l, Entero const &s){

		string suma, valor, a1, a2;
		int x, y, aux;
		int acumulador = 0;
		Entero *nuevo = new Entero();
		Entero u(l);
		Entero v(s);

		//veo el mayor e igualo cadenas
		if((u.getEntero()).size()>(v.getEntero()).size())
		{
			valor = v.getEntero();
			agregarCerosDelante(valor, ((u.getEntero()).size())-((v.getEntero()).size()));
			v.setEntero(valor);
		}else if((u.getEntero()).size()!=(v.getEntero()).size()){
			valor = u.getEntero();
			agregarCerosDelante(valor, ((v.getEntero()).size())-((u.getEntero()).size()));
			u.setEntero(valor);
		}

		while((u.getEntero()).size()!=0){

			a1 = u.getEntero().back();
			a2 = v.getEntero().back();
			x = atoi(a1.c_str());
			y = atoi(a2.c_str());

			a1 = u.getEntero();
			a2 = v.getEntero();
			a1.pop_back();
			a2.pop_back();
			u.setEntero(a1);
			v.setEntero(a2);

			aux = x + y + acumulador;

			if (aux < 10)
			{
				valor = to_string(aux);
				suma= valor + suma;
				acumulador = 0;
			}
			else
			{
				valor = to_string(aux % 10);
				suma = valor + suma;
				acumulador = 1;
			}
		}
		quitarCerosNoSignificativos(suma);
		nuevo->setEntero(suma);

		return *nuevo;
	}
	//operador de multiplicacion
	Entero &operator*(Entero const &l,Entero const &s){

		Entero *nuevo = new Entero();
		Entero u(l);
		Entero v(s);
		string a1, a2, valor;
		int aux;

		//veo el mayor e igualo cadenas
		if((u.getEntero()).size()>(v.getEntero()).size())
		{
			valor = v.getEntero();
			agregarCerosDelante(valor, ((u.getEntero()).size())-((v.getEntero()).size()));
			v.setEntero(valor);
		}else if((u.getEntero()).size()!=(v.getEntero()).size()){
			valor = u.getEntero();
			agregarCerosDelante(valor, ((v.getEntero()).size())-((u.getEntero()).size()));
			u.setEntero(valor);
		}

		//compruebo si es lo suficientemente pequeño
		if((u.getEntero().size())<=(unsigned)u.getMaximo())
		{
			//si lo es realizo la multiplicacion normal
			a1 = u.getEntero();
			a2 = v.getEntero();
			aux = atoi(a1.c_str())*atoi(a2.c_str());
			valor = to_string(aux);
			nuevo->setEntero(valor);
			return *nuevo;
		}
		//sino aplico algoritmo
		else
		{
			Entero w;
			Entero x;
			Entero y;
			Entero z;
			Entero var1;
			Entero var2;
			Entero var3;
			int s=(u.getEntero().size())/2;

			partirCadena(u.getEntero(), a1, a2);
			w.setEntero(a1);
			x.setEntero(a2);
			partirCadena(v.getEntero(), a1, a2);
			y.setEntero(a1);
			z.setEntero(a2);

			valor = (w*y).getEntero();
			agregarCerosFinal(valor,2*s);
			var1.setEntero(valor);

			valor = ((w*z)+(x*y)).getEntero();
			agregarCerosFinal(valor,s);
			var2.setEntero(valor);

			var3.setEntero((x*z).getEntero());

			nuevo->setEntero((var1+var2+var3).getEntero());
			return *nuevo;
		}

	}
/////////////////////////////////////////////////////////////////////////////
	//  Sobrecarga del operador de entrada
	istream &operator>>(istream &stream, Entero &e) 
	{	
		string valor;

		stream >> valor;

		e.setEntero(valor);

		return stream;
	}


	//  Sobrecarga del operador de salida
	ostream &operator<<(ostream &stream, Entero const &e) 
	{
		stream << e.getEntero();

		return stream;
	}
	/////////////////////////////////////////////////////////////////////////////