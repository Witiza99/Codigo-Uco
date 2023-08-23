/** 
  @file 3.2.h
  @brief Este archivo es otro ejemplo (breve)
 
  Esta es la descripcion detallada del archivo
*/

#define Pi 3.14       /**<Definicion detallada de la constante pi */
typedef int booleano; /**<Documentacion detallada de un typedef*/


/**
@typedef entero
@brief Definicion breve del typedef

Definicion detallada del typedef 
*/
typedef int entero;

/**
@def e
@brief Definicion breve del numero e

Definicion detallada del nuero e
*/
#define e 2.7182

/** 
 @struct punto
 @brief Definicion breve de una estructura de tipo punto
*/
struct punto
{
   float x; /**<Coordenada x del punto descripcion detallada*/
   float y;  ///<Coordenada y del punto descripcion breve
};

/**
 @fn void suma (int a, int b)
 @brief Funcion que suma (d. breve)
 @param a sumando 1
 @param b sumando 2
 @return Devuelve la suma a+b
 
 Esta es la descripción detallada de la función suma
*/
int suma(int a, int b);
