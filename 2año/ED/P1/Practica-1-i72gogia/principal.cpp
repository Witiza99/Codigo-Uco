/*!
 \mainpage Implementación de un monomio
 \brief		\f$ coeficiente X^{grado}\f$
 \author   Antonio Gómez Giménez
 \date     02/23/2019
 \version  1.0
*/

/*!

	\file principal.cpp
	\brief Programa principal de la practica 1 de ED: monomios
*/

#include <iostream>

#include "funcionesAuxiliares.hpp"

#include "macros.hpp"

/*! 
	\brief   Función principal de la práctica 1
	\return  int
*/
int main()
{
	int opcion;

	do{

		// Se elige la opción del menún
		opcion = ed::menu();		

		std::cout << CLEAR_SCREEN;
		PLACE(3,1);

		// Se ejecuta la opción del menú elegida
		switch(opcion)
		{
			case 0: 
				PLACE(3,1);
				std::cout << BIYELLOW;
				std::cout << "[0] Fin del programa" << std::endl << std::endl;
				std::cout << RESET;
				break;

			case 1: 
			   	std::cout << BIBLUE;
				std::cout << "[1] Test de la clase Monomio" << std::endl;
				std::cout << RESET;

				ed::testMonomio();
				break;

			case 2: 
			   	std::cout << BIBLUE;
				std::cout << "[2] Operadores externos de la clase Monomio " << std::endl;
				std::cout << RESET;

				ed::operadoresExternosMonomios();
				break;

			case 3: 
			   	std::cout << BIPURPLE;
				std::cout << "[3] Funciones extra que usa la clase Monomio " << std::endl;
				std::cout << RESET;

				do{

					// Se elige la opción del menú
					opcion = ed::menu2();		

					std::cout << CLEAR_SCREEN;
					PLACE(3,1);

					// Se ejecuta la opción del menú elegida
					switch(opcion)
					{
					case 0: 
						PLACE(3,1);
						std::cout << BIYELLOW;
						std::cout << "[0] Volver a menú anterior" << std::endl << std::endl;
						std::cout << RESET;
						break;

					case 1: 
						PLACE(3,1);
						std::cout << ICYAN;
						std::cout << "[1] Calculadora de polinomios de segundo grado:" << std::endl << std::endl;
						std::cout << RESET;

						ed::FuncionesExtras();
						break;

					case 2: 
						PLACE(3,1);
						std::cout << ICYAN;
						std::cout << "[2] Calculadora de Derivada de Monomios:" << std::endl << std::endl;
						std::cout << RESET;

						ed::FuncionesExtras1();
						break;

					case 3: 
						PLACE(3,1);
						std::cout << ICYAN;
						std::cout << "[3] Calculadora de Integrales de Monomios:" << std::endl << std::endl;
						std::cout << RESET;

						ed::FuncionesExtras2();
						break;

						default:
							std::cout << BIRED;
							std::cout << "Opción incorrecta ";
							std::cout << RESET;
							std::cout << "--> ";
						  	std::cout << ONIRED;
							std::cout << opcion << std::endl;
							std::cout << RESET;
			     	}

				    if (opcion !=0)
				    {
						std::cout << "Para mostrar el ";
						std::cout << BIGREEN ;
						std::cout << "menú, "; 
						std::cout << RESET;
						std::cout << "pulse ";
						std::cout << INVERSE ;
						std::cout << "ENTER";
						std::cout << RESET;

						// Pausa
						std::cin.ignore();

						std::cout << CLEAR_SCREEN;
				    }
					}while(opcion!=0);

				opcion=3;

				break;

			default:
				std::cout << BIRED;
				std::cout << "Opción incorrecta ";
				std::cout << RESET;
				std::cout << "--> ";
			  	std::cout << ONIRED;
				std::cout << opcion << std::endl;
				std::cout << RESET;
     	}
  
    if (opcion !=0)
    {
		std::cout << "Para mostrar el ";
		std::cout << BIGREEN ;
		std::cout << "menú, "; 
		std::cout << RESET;
		std::cout << "pulse ";
		std::cout << INVERSE ;
		std::cout << "ENTER";
		std::cout << RESET;

		// Pausa
		std::cin.ignore();

		std::cout << CLEAR_SCREEN;
    }
	  }while(opcion!=0);

	return 0;
}


