#ifndef __GRAFO_HPP__
#define __GRAFO_HPP__

#include <cassert>
#include <iostream>

using namespace std;

namespace ed
{

	template <class G_Nodo, class G_Lado>
	class Grafo
	{
	private:

		G_Lado **_lados;

		G_Nodo *_nodos;

		int _N;

	public:

		// constructores
		Grafo(){
			_lados=NULL;
			_nodos=NULL;
		}
		Grafo(int const &n){
			G_Lado **lados;
			G_Nodo *nodos;
			//reservo memoria lados
			lados= new G_Lado *[n];
			//reservo memoria nodos
			nodos=new G_Nodo [n];
			for (int i = 0; i < n; i++) {
				lados[i]= new G_Lado [n];
			}
			this->setLados(lados);		
			this->setNodos(nodos);
			this->setN(n);
		}
		Grafo(Grafo const &g){
			*this=g;
		}

		// destructor
		~Grafo(){
			this->borrarGrafo();
		}

		// funciones

		//observadores
		inline G_Lado **getLados()const{return _lados;}
		inline G_Nodo *getNodos()const{return _nodos;}
		inline int getN()const{return _N;}

		//modificadores
		inline void setLados(G_Lado **g){_lados=g;}
		inline void setNodos(G_Nodo *g){_nodos=g;}
		inline void setN(int n){_N=n;}

		//funciones

		Grafo &operator=(Grafo const &g){//operador igual para copiar grafo en grafo	
			
			G_Nodo *gNodos=g.getNodos();
			G_Lado **gLados=g.getLados();
			int n=sizeof(gNodos)/sizeof(G_Nodo);

			//reserva memoria
			G_Nodo *nodos;
			nodos=new G_Nodo [n];
			G_Lado **lados;
			lados=new G_Lado *[n];
			for (int i = 0; i < n; i++) {
				lados[i]=new G_Lado [n];
			}
			//relleno nodos y matri<
			for (int i = 0; i < n; i++) {
				nodos[i]=gNodos[i] ;
				for (int j = 0; j < n; j++) {
					lados[i][j]=gLados[i][j];
				}
			}
			this->setNodos(nodos);
			this->setLados(lados);
			this->setN(n);
			return *this;
		}

		void borrarGrafo() {	// funcion que borra todo el grafo
			G_Lado **lados=this->getLados();
			G_Nodo *nodos=this->getNodos();
			int n=sizeof(nodos)/sizeof(G_Nodo);
			for(int i=0; i<n;i++){
				delete [] lados[i];
			}
			delete [] lados;
			delete [] nodos;

			_lados=NULL;
			_nodos=NULL;
		}
	};
}

#endif