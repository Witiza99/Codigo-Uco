#include <cstdio>
#include <cstdlib>
#include <iostream>
#include<cmath>
using namespace std;

struct Point2d{//creo la estructura poin2d con sus dos variables que usare en el siguiente programa

	float x=0, y=0;

};


void set(float vx, float vy){//esta funcion me fija los valores x e y

	x=vx;
	y=vy;

}

float dist(){//esta funcion me calcula la distancia entre estos dos puntos 

	return sqrt(x*x+y*y);

}


int main(){


	Point2d p1, p2;

	p1.set(1,2);
	p2.set(3,4);

	cout<<p1.dist()<<endl;
	cout<<p2.dist()<<endl;


    system("pause");
}

