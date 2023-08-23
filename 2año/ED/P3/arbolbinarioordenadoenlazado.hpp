#ifndef __ARBOLBINARIOORDENADO_HPP__
#define __ARBOLBINARIOORDENADOENLAZADO_HPP__

#include <iostream>
#include <cassert>
#include "arbolbinarioordenado.hpp"
#include "operadornodo.hpp"

using namespace std;
/*!
\brief Espacio de nombres para la asignatura Estructura de datos.
*/
namespace ed
{
	/*!\brief Interfaz para definir un ArbolBinario ordenado.

	Define una interfaz para definir un ArbolBinarioOrdenado.

	\arg G define el campo de información a contener en el arbol.
	\pre G debe tener definidos los operadores < y ==.
	*/
	template<class G>
	class ArbolBinarioOrdenadoEnlazado:public ArbolBinarioOrdenado<G>
	{
	private:

		/*!\brief Define un nodo del arbol binario.*/
		class NodoArbolBinario
		{
		private:
			G _info;  //Valor informativo almacenado en el nodo
			NodoArbolBinario * _izquierdo;  //Puntero al hijo izquierdo
			NodoArbolBinario * _derecho;  //Puntero al hijo derecho

		public:
			/*! 
			\brief Crea un nuevo nodo con la información de “info”
			\post El nodo creado no tiene hijos
			*/
			NodoArbolBinario (const G &info)
			{
				_info=info;
				_izquierdo=NULL;
				_derecho=NULL;

				#ifndef NDEBUG
				assert(_izquierdo==NULL);
				assert(_derecho==NULL);
			  	#endif //NDEBUG

			}

			/*! 
			\brief Crea un nuevo nodo a partir de otro nodo.
			\post El nodo creado es igual al nodo “n”.
			*/
			NodoArbolBinario (const NodoArbolBinario &n)
			{
				_info=n.getInfo();
				*_izquierdo=n.getIzquierdo();
				*_derecho=n.getDerecho();

				#ifndef NDEBUG
				assert(_info==n.getInfo());
				assert(_izquierdo==n.getIzquierdo());
				assert(_derecho==n.getDerecho());
			  	#endif //NDEBUG
			}

			/*!\brief Observadores.*/
			
			/*! 
			\brief Devuelve la información contenida en el nodo
			*/
			const G & getInfo() const
			{
				return _info;
			}

			/*! 
			\brief Devuelve el puntero al hijo izquierdo
			*/
			NodoArbolBinario *getIzquierdo() const
			{
				return _izquierdo;
			}

			/*! 
			\brief Devuelve el puntero al hijo derecho
			*/
			NodoArbolBinario *getDerecho() const
			{
				return _derecho;
			}

			/*! 
			\brief Comprueba si el nodo actual es hoja, es decir, no tiene hijo izquierdo ni derecho
			\return bool
			*/
			bool esHoja() const
			{
				if((_izquierdo==NULL)&&(_derecho==NULL)){return true;}
				return false;
			}

			/*! 
			\brief Aplica el operador “op” y delega sobre los hijos para realizar el recorrido en preorden
			*/
			void recorridoPreOrden (OperadorNodo<G> &operador) const
			{
				operador.aplicar(getInfo());//muestro la información
				if(this->getIzquierdo()!=NULL){//uso recursividad para realizar el recorrido
					this->getIzquierdo()->recorridoPreOrden(operador);	
				}
				if(this->getDerecho()!=NULL){//uso recursividad para realizar el recorrido
				this->getDerecho()->recorridoPreOrden(operador);
				}
			}

			/*! 
			\brief Aplica el operador “op” y delega sobre los hijos para realizar el recorrido en postorden
			*/
			void recorridoPostOrden (OperadorNodo<G> &operador) const
			{
				if(this->getIzquierdo()!=NULL){//uso recursividad para realizar el recorrido
					this->getIzquierdo()->recorridoPreOrden(operador);	
				}
				if(this->getDerecho()!=NULL){//uso recursividad para realizar el recorrido
				this->getDerecho()->recorridoPreOrden(operador);
				}
				operador.aplicar(getInfo());//muestro la información
			}

			/*! 
			\brief Aplica el operador “op” y delega sobre los hijos para realizar el recorrido en inorden
			*/
			void recorridoInOrden (OperadorNodo<G> &operador) const
			{
				if(this->getIzquierdo()!=NULL){//uso recursividad para realizar el recorrido
					this->getIzquierdo()->recorridoPreOrden(operador);	
				}
				operador.aplicar(getInfo());//muestro la información
				if(this->getDerecho()!=NULL){//uso recursividad para realizar el recorrido
				this->getDerecho()->recorridoPreOrden(operador);
				}		
			}

			/*!\brief Modificadores. */
			
			/*! 
			\brief Establece el valor informativo del nodo actua
			*/
			void setInfo(const G &info)
			{
				_info=info;
			}

			/*! 
			\brief Establece el puntero al hijo izquierdo del nodo actual
			*/
			void setIzquierdo(NodoArbolBinario *n)
			{
				_izquierdo=n;
			}

			/*! 
			\brief Establece el puntero al hijo derecho del nodo actual
			*/
			void setDerecho(NodoArbolBinario *n)
			{
				_derecho=n;
			}

			/*! 
			\brief Operador de asignación. Operador que copia el nodo “n” en el nodo actual
			\pre El nodo “n” debe ser diferente del nodo actual
			\post El nodo actual debe ser igual al nodo “n”
			\return NodoArbolBinario
			*/
			NodoArbolBinario & operator=(const NodoArbolBinario &n)
			{
				//aserto de precondicion
				#ifndef NDEBUG
				assert((_info==n.getInfo())||(*_izquierdo==n.getIzquierdo())||(*_derecho==n.getDerecho()));
			  	#endif //NDEBUG

				_info=n.getInfo();
				*_izquierdo=n.getIzquierdo();
				*_derecho=n.getDerecho();

				//aserto de postcondicion
				#ifndef NDEBUG
				assert(_info==n.getInfo());
				assert(_izquierdo==n.getIzquierdo());
				assert(_derecho==n.getDerecho());
			  	#endif //NDEBUG

			  	return *this;
			}

		}; //Fin clase NodoArbolBinario

		//Implementación de la raíz
		NodoArbolBinario * _raiz; /*!<La raiz del árbol*/
		NodoArbolBinario * _actual; /*!<Cursor al nodo actual*/
		NodoArbolBinario * _padre; /*!<Cursor al nodo actual*/
		NodoArbolBinario * _aux; //cursor auxiliar que mantiene la posición del nodo que quiero borrar (usado en función borrar)

		//observadores
		inline NodoArbolBinario *getRaiz()const{return _raiz;};
		inline NodoArbolBinario *getActual()const{return _actual;};
		inline NodoArbolBinario *getPadre()const{return _padre;};
		inline NodoArbolBinario *getAux()const{return _aux;};
		

		//modificadores de los punteros raíz,actual y padre para poder trabajar con los const
		inline void setRaiz(NodoArbolBinario * raiz){_raiz=raiz;};
		inline void setActual(NodoArbolBinario * actual){_actual=actual;};
		inline void setPadre(NodoArbolBinario * padre){_padre=padre;};
		inline void setAux(NodoArbolBinario * aux){_aux=aux;};

	public:

		/*! 
		\brief Crea un nuevo árbol vacío
		\post El árbol creado está vacío
		*/
		ArbolBinarioOrdenadoEnlazado ()
		{
			this->setRaiz(NULL); //La raiz del árbol
			this->setActual(NULL); //Cursor al nodo actual
			this->setPadre(NULL); //Cursor al padre

			//aserto de postcondicion
			#ifndef NDEBUG
			assert(this->estaVacio()==true);
		  	#endif //NDEBUG
		}

		/*! 
		\brief Crea un nuevo árbol a partir de otro árbol.
		\post El árbol creado es igual al árbol “a”.
		*/
		ArbolBinarioOrdenadoEnlazado (const ArbolBinarioOrdenadoEnlazado<G>& a)
		{
			this->setRaiz(NULL); //La raiz del árbol
			this->setActual(NULL); //Cursor al nodo actual
			this->setPadre(NULL); //Cursor al padre

			*this=a;
			//aserto de postcondicion
			#ifndef NDEBUG
			ArbolBinarioOrdenadoEnlazado<G> b;
			b=a;
			assert(this==b);
		  	#endif //NDEBUG
		}

		//destructor de clase
		~ArbolBinarioOrdenadoEnlazado ()
		{
			if (not estaVacio())
			borrarArbol();
			cout << "Destructor Usado \n";
		}

		ArbolBinarioOrdenadoEnlazado &operator=(const ArbolBinarioOrdenadoEnlazado& a)
		{
			//recorrer preorden y guardarlo en vector luego se lee y se va insertando 1 a 1
			AlmacenarNodo<G> operador;
			vector<G> v;
			a.recorridoPreOrden(operador);//recorro el arbol b
			v=operador.vectorNodos();//lo guardo en vector
			for(int i=0;i<sizeof(v);i++){//lo voy insertando 1 a 1
				this->insert(v[i]);
			}
		}

		/*! 
		\brief Inserta un elemento en el árbol, el cual deberá mantener el orden
		\post El elemento debe estar en el árbol
		\post El árbol debe estar ordenado
		
		\return bool
		*/
		bool insertar(const G &x)
		{
			

			//en el caso de que el arbol este vacío se añade directamente
			if(this->estaVacio()==true){
				this->setRaiz(new NodoArbolBinario (x));
				this->setActual(this->getRaiz());
				this->setPadre(NULL);

				//aserto postcondicion
				#ifndef NDEBUG
				//assert(this->buscar(x)==true);
			  	#endif //NDEBUG
				return true;
			}else{

				//para poder moverme por el arbol
				this->setPadre(NULL);
				this->setActual(this->getRaiz());
				while(1){
					//en el caso de que sea x mayor
					if(this->actual()<x){
						//comprobamos si el hijo derecho esta vacío para así añadirlo
						if(this->getActual()->getDerecho()==NULL){
							this->getActual()->setDerecho(new NodoArbolBinario(x));
							this->setActual(new NodoArbolBinario(x));

							//aserto postcondicion
							#ifndef NDEBUG
							assert(this->buscar(x)==true);
						  	#endif //NDEBUG
							return true;
						//sino se accede a él
						}else{
						this->setPadre(getActual());
						this->setActual(getActual()->getDerecho());
						}
					///procedimiento cuando la variable es menor
					}else if (this->actual()>x){
						//comprobamos si el hijo izquierdo esta vacío para así añadirlo
						if(this->getActual()->getIzquierdo()==NULL){
							this->getActual()->setIzquierdo(new NodoArbolBinario(x));
							this->setActual(new NodoArbolBinario(x));

							//aserto postcondicion
							#ifndef NDEBUG
							assert(this->buscar(x)==true);
						  	#endif //NDEBUG
							return true;
						//sino se accede a él
						}else{
						this->setPadre(getActual());
						this->setActual(this->getActual()->getIzquierdo());
						}
					//caso en el que este ya insertado
					}else{

						#ifndef NDEBUG
						assert(this->buscar(x)==true);
					  	#endif //NDEBUG

						return true;
					}
				}
			}
			return false;//nunca debería llegar aquí
		}

		/*! 
		\brief Elimina el árbol por completo
		\pre El árbol no puede estar vacío
		\post El árbol debe estar vacío
		
		\return bool
		*/
		void borrarArbol()
		{
			//aserto de precondicion
			#ifndef NDEBUG
			assert(this->getRaiz()!=NULL);
		  	#endif //NDEBUG
			this->setRaiz(NULL); //La raiz del árbol
			this->setActual(NULL); //Cursor al nodo actual
			this->setPadre(NULL); //Cursor al padre
			//aserto de postcondicion
			#ifndef NDEBUG
			assert(this->getRaiz()==NULL);
		  	#endif //NDEBUG
		}

		/*! 
		\brief Elimina el nodo apuntado por “_actual”
		\pre “_actual” debe apuntar a algún nodo
		\post El elemento borrado no debe existir
		\return bool
		*/
		bool borrar()
		{
			//aserto de precondicion
			#ifndef NDEBUG
			assert(this->existeActual()==true);
		  	#endif //NDEBUG
			
			int contador=0;
			//comprobación de que es el nodo actual
			if((this->getActual()==this->getRaiz())&&(this->getRaiz()->esHoja()==true)) {contador=0;}
			else if((this->getActual()->getDerecho()!=NULL)&&(this->getActual()->getIzquierdo()!=NULL)){contador=1;}
			else if(this->getActual()->esHoja()){contador=2;}
			else if(this->getActual()->getDerecho()==NULL){contador=3;}
			else if(this->getActual()->getIzquierdo()==NULL){contador=4;}

			//variable usada en los asertos de postcondiciones
			#ifndef NDEBUG
			G z=actual();
		  	#endif //NDEBUG

			switch(contador){

				// ========================================
				// CASO 0 ---> Raíz sin hijos
				// ========================================
				case 0:

				this->borrarArbol();//es un caso muy raro pero se podría llegar a dar
			  	return true;
				break;

				// ========================================
				// CASO 1 ---> NODO con dos hijos
				// ========================================
				case 1:

				this->setAux(this->getActual());
				this->setPadre(this->getActual());
				this->setActual(this->getActual()->getDerecho());
				//busco el nodo más a la izquierda tras ir uno a la derecha
				while(this->getActual()->getIzquierdo()!=NULL){
					this->setPadre(this->getActual());
					this->setActual(this->getActual()->getIzquierdo());
				}
				//cambiamos la información del nodo candidato con el nodo ha borrar
				this->getAux()->setInfo(this->getActual()->getInfo());
				//borramos el nodo que ha sustituido al borrado, al llamar a la función borrará en el caso de que sea hoja o tenga derecha
				this->borrar();
				// Ponemos punteros actual y padre a NULL
				this->setActual(NULL);
				this->setPadre(NULL);

				//aserto de postcondición
				#ifndef NDEBUG
				assert(this->buscar(z)==false);
			  	#endif //NDEBUG

			  	return true;
				break;

				// ========================================
				// CASO 2 ---> NODO Hoja
				// ========================================
				case 2:

				//compruebo si actual es el derecho o el izquierdo del padre y lo elimino
				if(this->getPadre()->getIzquierdo()==getActual()){this->getPadre()->setIzquierdo(NULL);}
				else{this->getPadre()->setDerecho(NULL);}
				//Ponemos punteros actual y padre a NULL
				this->setActual(NULL);
				this->setPadre(NULL);

				//aserto de postcondición
				#ifndef NDEBUG
				assert(this->buscar(z)==false);
			  	#endif //NDEBUG

			  	return true;
				break;

				// ========================================
				// CASO 3 ---> NODO con solo hijo izquierdo
				// ========================================
				case 3:

				if(this->getPadre()->getIzquierdo()==getActual()){this->getPadre()->setIzquierdo(this->getActual()->getIzquierdo());}//el hijo izquierdo del padre será el hijo izquierdo del actual por tanto se pierde el puntero al actual
				else{this->getPadre()->setDerecho(this->getActual()->getIzquierdo());}//el caso de que el hijo sea derecho
				
				//Ponemos punteros actual y padre a NULL
				this->setActual(NULL);
				this->setPadre(NULL);

				//aserto de postcondición
				#ifndef NDEBUG
				assert(this->buscar(z)==false);
			  	#endif //NDEBUG

			  	return true;
				break;

				// ========================================
				// CASO 4 ---> NODO con solo hijo derecho
				// ========================================
				case 4:

				if(this->getPadre()->getIzquierdo()==this->getActual()){this->getPadre()->setIzquierdo(this->getActual()->getDerecho());}//en caso de borrar el izquierdo
				//el hijo derecho del padre será el hijo derecho del actual por tanto se pierde el puntero al actual
				else{this->getPadre()->setDerecho(this->getActual()->getDerecho());}
				//Ponemos punteros actual y padre a NULL
				this->setActual(NULL);
				this->setPadre(NULL);

				//aserto de postcondición
				#ifndef NDEBUG
				assert(this->buscar(z)==false);
			  	#endif //NDEBUG

			  	return true;
				break;

			}
			return false;//no debería de llegar aquí
		}

		/*! 
		\brief Realiza el recorrido preorden del árbol aplicando el operador “op”.
		*/
		void recorridoPreOrden (OperadorNodo<G> &operador) const
		{
			if(estaVacio()!=true){//compruebo que no este vacío
				this->getRaiz()->recorridoPreOrden(operador);//llamo a función ya realizada
			}
		}

		/*! 
		\brief Realiza el recorrido postorden del árbol aplicando el operador “op”.
		*/
		void recorridoPostOrden (OperadorNodo<G> &operador) const
		{
			if(estaVacio()!=true){//compruebo que no este vacío
				this->getRaiz()->recorridoPostOrden(operador);//llamo a función ya realizada
			}
		}

		/*! 
		\brief Realiza el recorrido inorden del árbol aplicando el operador “op”.
		*/
		void recorridoInOrden (OperadorNodo<G> &operador) const
		{
			if(estaVacio()!=true){//compruebo que no este vacío
				this->getRaiz()->recorridoInOrden(operador);//llamo a función ya realizada
			}
		}

		/*! 
		\brief Busca un elemento en el árbol y actualiza el cursor de “_actual” y “_padre” si lo encuentra.
		\post “_actual” debe apuntar al nodo encontrado, si lo encuentra.
		\return bool
		*/
		bool buscar(const G& x)
		{
		this->setPadre(NULL);
		this->setActual(this->getRaiz());
		//me permite ir comprobando en profundidad
			while(1){
				//procedimento cuando la variable es mayor
				if(this->actual()<x){
					this->setPadre(this->getActual());
					this->setActual(this->getActual()->getDerecho());
					if(this->existeActual()==false){return false;}
				///procedimiento cuando la variable es menor
				}else if (this->actual()>x){
					this->setPadre(this->getActual());
					this->setActual(this->getActual()->getIzquierdo());
					if(this->existeActual()==false){return false;}
				//se encuentra la variable
				}else{
				//caso en el que ya este insertada la variable
				#ifndef NDEBUG
				assert(this->actual()==x);
			  	#endif //NDEBUG

				return true;
				}
			}
		}

		/*! 
		\brief Comprueba si el árbol está vacío	
		\return bool
		*/
		bool estaVacio() const
		{
			if((this->getRaiz()==NULL) and (this->getActual()==NULL) and (this->getPadre()==NULL)){return true;}
			return false;
		}

		/*! 
		\brief Obtiene el dato almacenado en la raíz
		\pre El árbol no puede estar vacío	
		\return G
		*/
		G raiz() const
		{
			//aserto de precondicion
			#ifndef NDEBUG
			assert(this->estaVacio()==false);
		  	#endif //NDEBUG

		  	return this->getRaiz()->getInfo();
		}

		/*! 
		\brief Comprueba si “_actual” está apuntando a algún nodo
		\pre El árbol no puede estar vacío
		\return bool
		*/
		bool existeActual() const
		{
			//aserto de precondicion
			#ifndef NDEBUG
			assert(estaVacio()==false);
		  	#endif //NDEBUG

		  	if(this->getActual()==NULL){return false;}
			else{return true;}
		}

		/*! 
		\brief Devuelve el dato almacenado por el nodo “_actual”
		\pre El árbol no puede estar vacío
		\return G
		*/
		G actual() const
		{
			//aserto de precondicion
			#ifndef NDEBUG
			assert(this->existeActual()==true);
		  	#endif //NDEBUG

			return this->getActual()->getInfo();
		}
		/*!@}*/
	};
} //namespace ed

#endif //__ARBOLORDENADO_HPP__
