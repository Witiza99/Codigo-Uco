#ifndef CABALLOS_HPP
#define CABALLOS_HPP

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>

typedef struct Point{
	int a;
	int b;
}Point;

int Calculo_Caminos(int a, int b, std::vector <std::vector <Point> > &vpadre, std::vector <Point> vhijo);
void Parte1();
void Parte2();
void Parte3();
void Parte4();

#endif