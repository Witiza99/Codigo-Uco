/*Crear juego del Domino (en C)
	-Crear Estructura para las ficha X
	-Crear todas las fichas X
		-Primera y última ficha
		-Vector de fichas jugadas
	-Revolver todas las fichas del monton X
	-Mostrar fichas X
	-Función girar ficha
	-Crear estructura para jugador X //uso la estructura mesa para jugador
	-Crear a los jugadores X
	-Quitar ficha X
	-Agregar ficha X
	-Buscar ficha con una valor en una mesa X
	-Jugar con dos jugadores
	-Ver que jugador empieza
	-Buscar ficha doble X
	-Mostrar mesa X
	-Buscar en la MESA la primera y última (los valores)

*/

#ifndef DOMINO_H
#define DOMINO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>//libreria que uso para poder usar bool
#include <time.h>//libreria que uso a la hora de generar numeros aleatorios

#define DOMINO 28

struct ficha{//estructura de cada ficha
	int valores[2];
};

struct mesa{//estructura de la mesa, contiene un puntero de fichas, con acceso a primer y ultimo elemento más el total de elementos
	struct ficha **fichas;
	struct ficha *primero;
	struct ficha *ultimo;
	int total;
};

struct ficha *crear_ficha(int a, int b);
/*reserva memoria y se crea ficha, los valores entrantes son los valores de la ficha
	param 1: valor 1 de la ficha
	param 2: valor 2 de la ficha
	devuelve: devuelve un puntero a la estructura ficha
*/
void revolver(struct ficha *monton);
/*desordena el monton de fichas
	param 1: puntero al vector de fichas,(debe ser el monton)
	devuelve: vacio
*/
struct mesa *reserva_memoria_mesa();
/*reserva memoria para la mesa
	no hay parametros
	devuelve: un puntero al espario reservado para la estructura mesa
*/
char *imprimir_vector_fichas(struct ficha **jugador);
/*imprime las fichas del vector dado
	param 1: puntero a vector de fichas que se desea mostrar sus fichas
	devuelve: una cadena con todas las fichas de ese vector
*/
char *imprimir_mesa(struct mesa *m);
/*imprime las fichas de la mesa dada
	param 1: puntero a estructura mesa que se desea mostrar
	devuelve: una cadena con todas las fichas de ese mesa
*/
void agregar_ficha(struct ficha **jugador, struct ficha *f);
/*reserva memoria y añade una ficha del monton a el jugador
	param 1: puntero a vector de estructura fichas,(debe ser el jugador)
	param 2: puntero a vector de estructura fichas,(debe ser el monton)
	devuelve: vacio
*/
void agregar_ficha_mesa(struct mesa *m, struct ficha *f);
/*reserva memoria y añade una ficha a una mesa(se usa solo para añadir la primera ficha)
	param 1: puntero a una mesa
	param 2: puntero a una estructura ficha
	devuelve: vacio
*/
struct ficha *quitar_ficha_jugador(struct ficha **jugador, int lugar_ficha);
/*se quita una ficha del jugador dado con la posicion de la misma ajustando la memoria y devolviendo el puntero a la ficha quitada
	param 1: puntero a vector de estructuras ficha(debe ser el jugador)
	param 2: entero con la posicion de la ficha
	devuelve: puntero a estructura ficha
*/
int buscar_valor_jugador(struct ficha **jugador, int valor);
/*busca si se encuentra el valor dado en el jugador pasado(puntero a vector de estructuras ficha)
	param 1: puntero a vector de estructuras ficha(debe ser el jugador)
	param 2: entero con el valor a buscar
	devuelve: devuelve -1 si no lo encuentra y si lo encuentra devuelve la posicion donde lo ha encontrado
*/
int buscar_valor_mesa(struct mesa *m, int valor);
/*busca si se encuentra el valor dado en la mesa pasada(puntero a estructura mesa)
	param 1: puntero a estructura mesa
	param 2: entero con el valor a buscar
	devuelve: devuelve -1 si no lo encuentra y si lo encuentra devuelve la posicion donde lo ha encontrado
*/
int buscar_doble(struct ficha **jugador, int valor);
/*busca si se encuentra el doble dado en el vector de fichas dado
	param 1: puntero a estructura de fichas
	param 2: entero con el valor del doble a buscar
	devuelve: devuelve -1 si no lo encuentra y si lo encuentra devuelve la posicion donde lo ha encontrado
*/
int buscar_ficha_jugador(struct ficha **jugador, int valor0, int valor1);
/*busca si se encuentra una ficha dada en el vector de jugadores pasada(puntero a vector de estructura ficha)
	param 1: puntero a vector de estructuras ficha(debe ser el jugador)
	param 2: entero con un valor de la ficha
	param 3: entero con otro valor de la ficha
	devuelve: devuelve -1 si no lo encuentra y si lo encuentra devuelve la posicion donde lo ha encontrado
*/
int buscar_ficha_mesa(struct mesa *m, int valor0, int valor1);
/*busca si se encuentra una ficha dada en la mesa pasada(puntero a estructura mesa)
	param 1: puntero a estructura mesa(puntero a estructura mesa)
	param 2: entero con un valor de la ficha
	param 3: entero con otro valor de la ficha
	devuelve: devuelve -1 si no lo encuentra y si lo encuentra devuelve la posicion donde lo ha encontrado
*/
void rotar_ficha(struct ficha *f);
/*rota la ficha, es decir, cambia los valores de posición
	param 1: puntero a estructura ficha
	devuelve: vacio
*/
struct ficha *consultar_valores(struct mesa *m);//consultamos los valores extremos de la mesa
/*consulta los valores extremos de la mesa y devuelve una ficha con el valor de la izquiera y el valor de la derecha
	param 1: puntero a la estructura mesa
	devuelve: puntero a estructura ficha
*/
void agregar_ficha_esquina(struct mesa *m, struct ficha *f, bool posicion);
/*agrego ficha a la mesa al principio o al final
	param 1: puntero a la estructura mesa
	param 2: puntero a la estructura ficha
	param 3: bool con true izquierda y false derecha
	devuelve: vacio
*/
void crear_monton(struct ficha *monton);
/*reservo memoria para el monton, lo relleno y lo revuelvo
	param 1: puntero a vector de estructuras ficha(debe ser el monton)
	devuelve: vacio
*/
void rellenar_jugadores(struct ficha **jugador1, struct ficha **jugador2, struct ficha *monton, int *i);
/*entrego las fichas del monton a cada jugador(!son punteros al mismo por eso no se puede borrar el monton)
	param 1: puntero a vector de estructuras ficha(debe ser el jugador1)
	param 2: puntero a vector de estructuras ficha(debe ser el jugador2)
	param 3: puntero a vector de estructuras ficha(debe ser el monton)
	param 4: entero que se va incrementando cada vez que se extrae una ficha del monton
	devuelve: vacio
*/
int empezar_turno(struct mesa *m, struct ficha **jugador1, struct ficha **jugador2);
/*devuelve el jugador que empieza turno, es decir, da el turno al siguiente jugador tras insertar en la mesa la ficha del jugador que poseia el doble y sino
hay dobles el que tuviera la ficha mayor. Si coloca jugador uno el doble el jugador 2 empieza el turno
	param 1: puntero a la estructura mesa
	param 2: puntero a vector de estructuras ficha(debe ser el jugador1)
	param 3: puntero a vector de estructuras ficha(debe ser el jugador2)
	devuelve: devuelve -1 si ocurre un error fatal y si no devuelve 1 si empieza el jugador 2 y viceversa
*/
bool poner_ficha_jugador_a_mesa(struct mesa *m, struct ficha **jugador, struct ficha *ficha, bool posicion);
/*introduce una ficha de un jugador a la mesa en la posicion izquierda o derecha en el caso de que sea posible
	param 1: puntero a la estructura mesa
	param 2: puntero a vector de estructuras ficha(debe ser el jugador)
	param 3: puntero a estructura ficha que se desea insertar
	param 4: bool con la posicion donde se quiere poner la ficha, izquierda true y derecha false 
	devuelve: devuelve false si no se puede insertar la ficha en la mesa y true si lo ha insertado correctamente
*/
bool pasar_turno(struct mesa *m, struct ficha **jugador);
/*comprueba si puede el jugador pasar turno o no
	param 1: puntero a la estructura mesa
	param 2: puntero a vector de estructuras ficha(debe ser el jugador)
	devuelve: devuelve false si no puede pasar turno y true si puede pasar turno
*/
bool robar_ficha(struct mesa *m, struct ficha **jugador, struct ficha *monton, int *i);
/*comprueba si puede robar ficha o no y en el caso de que si se incrementa la i y se añade un puntero al monton
	param 1: puntero a la estructura mesa
	param 2: puntero a vector de estructuras ficha(debe ser el jugador)
	param 3: puntero a vector de estructuras ficha(debe ser el monton)
	param 4: entero que se va incrementando cada vez que se extrae una ficha del monton
	devuelve: devuelve false si no puede robar ficha y true si puede robar ficha
*/
int hay_ganador(struct mesa *m, struct ficha **jugador1, struct ficha **jugador2);
/*comprueba si hay ganador ya sea por que no tiene fichas o por que al bloquearse el juego tiene mas puntos
	param 1: puntero a la estructura mesa
	param 2: puntero a vector de estructuras ficha(debe ser el jugador1)
	param 3: puntero a vector de estructuras ficha(debe ser el jugador2)
	devuelve: -1 sino gana nadie, 1 si gana el jugador 1, 2 si gana el jugador 2 y 3 si ocurre un empate donde los dos jugadores tienen los mismos puntos
*/

#endif