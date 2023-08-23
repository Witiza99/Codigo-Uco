/*! 
   \file  FuncionesExtra.cpp
	\brief Ficheros con el código de las funciones extra de la clase Monomio
*/


//  Ficheros de cabecera

#include "FuncionesExtra.hpp"

namespace ed
{
//////////////////////////////////////////////////////////////////////////////////////

	void CPSG(ed::Monomio const &m1, ed::Monomio const &m2, ed::Monomio const &m3,double *v,int x){

		#ifndef NDEBUG

		assert((pow(m2.getCoeficiente(), 2))>(4 * m1.getCoeficiente() * m3.getCoeficiente()));

		#endif //NDEBUG

		double x1=0;
		double x2=0;
		int n=2;

		x1 = ((-(m2.getCoeficiente()) + (sqrt(pow(m2.getCoeficiente(), n) - (4 * m1.getCoeficiente() * m3.getCoeficiente())))) / (2 * m1.getCoeficiente()));
	 	x2 = ((-(m2.getCoeficiente()) - (sqrt(pow(m2.getCoeficiente(), n) - (4 * m1.getCoeficiente() * m3.getCoeficiente())))) / (2 * m1.getCoeficiente()));

		v[0]=x1;
		v[1]=x2;

	}

	void CalculaDerivada(ed::Monomio &m){

		#ifndef NDEBUG

		assert(m.getGrado()>0);

		#endif //NDEBUG

		m.setCoeficiente(m.getCoeficiente()*m.getGrado());
		m.setGrado(m.getGrado()-1);

	}

	void CalculaIntegral(ed::Monomio &m){

		#ifndef NDEBUG

		assert(m.getGrado()>=0);

		#endif //NDEBUG

		m.setCoeficiente(m.getCoeficiente()/(m.getGrado()+1));
		m.setGrado(m.getGrado()+1);

	}

}