#ifndef FUNCIONES_BAJO_NIVEL
#define FUNCIONES_BAJO_NIVEL

#include <string>
using namespace::std;

//Esta función divide la cadena c en dos subcadenas c1 y c2, siendo ambas del mismo tamaño cuando el número de caracteres de c es par 
//y c1 tendrá un caracter más cuando c tenga un número impar de caracteres.
void partirCadena(string const &c, string &c1, string &c2);

//Esta función añade tantos ceros como indica nCeros al final del número almacenado en la cadena c
void agregarCerosFinal(string &c, int nCeros);

//Esta función añade tantos ceros como indica nCeros al principio del número almacenado en la cadena c
void agregarCerosDelante(string &c, int nCeros);

//Esta función elimina todos los ceros que hay al principio del número almacenado en la cadena c
void quitarCerosNoSignificativos(string &c);

//Esta función devuelve una cadena que contendrá el número resultante de multiplicar el número almacenado en la cadena c por 10 elevado a potencia.
string multiplicarPotencia10(string &c, int potencia);

#endif

