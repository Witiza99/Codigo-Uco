#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <math.h>

#include "funcionesbajonivel.hpp"

void partirCadena(string const &c, string &c1, string &c2)
{
	int n;
	n = c.size();
	
	if (n % 2 == 0) //n es par
	{
		c1=c.substr(0,n/2);
		c2=c.substr(n/2, n);
	}
	else
	{
		c1=c.substr(0,(n+1)/2);
		c2=c.substr(((n+1)/2), n);
	}
}

void agregarCerosFinal(string &c, int nCeros)
{
	string Ceros;

	for(int i=0; i<nCeros;i++){
		Ceros=Ceros+'0';
	}
	c=c+Ceros;
}

void agregarCerosDelante(string &c, int nCeros)
{
	string Ceros;

	for(int i=0; i<nCeros;i++){
		Ceros='0'+Ceros;
	}
	c=Ceros+c;
}

void quitarCerosNoSignificativos(string &c)
{
	int contador=0;
	int aux=0;

	for(unsigned i=0; i<c.size();i++){
		if(c[i]=='0' && aux==0)
		{
			contador++;
		}else
		{
			aux=1;
		}
	}

	c=c.substr(contador,c.size());
}

string multiplicarPotencia10(string const &c, int potencia)
{
	string aux;
	aux=c;
	agregarCerosFinal(aux, potencia);
	return aux;
}
