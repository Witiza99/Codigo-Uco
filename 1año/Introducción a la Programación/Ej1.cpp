#include <cstdio>
#include <cstdlib>
#include <iostream>
#include<cmath>
using namespace std;

struct Point2d{//creo la estructura poin2d con sus dos variables que usare en el siguiente programa

	float x=0, y=0;

};


float distance(Point2d a, Point2d b){//esta funcion me calcula la distancia entre dos puntos y lo devuelve al main

	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));

}

Point2d suma(Point2d a, Point2d b){//esta funcion me hace la suma de dos puntos

	Point2d res;

	res.x=a.x+b.x;
	res.y=a.y+b.y;

	return res;

}

void set(Point2d &p, float x, float y){//esta funcion me fija los valores del punto

	p.x=x;
	p.y=y;

}

void setdos(float vx, float vy){//esta funcion me fija los valores x e y

	x=vx;
	y=vy;

}

float dist(){//esta funcion me calcula la distancia entre estos dos puntos 

	return sqrt(x*x+y*y);

}


int main(){//este main recoge todos los main que aparecen el en temario

	Point2d p1, p2;

	p1.x=12;
	p1.y=4;

	cin>>p2.x>>p2.y;

	float d=distance(p1,p2);

	cout<<"d="<<d<<endl;

	Point2d p3, p4, p5;

	set(p3, 1, 2);
	set(p4, 5, 6);

	p5=suma (p3, p4);

	Point2d v[10];

	for(int i=0;i<10; i++){

	v[i].x=i;
	v[i].y=(i+1)*2;

	}

	Point2d p6, p7;

	p6.setdos(1,2);
	p7.setdos(3,4);

	cout<<p6.dist()<<endl;
	cout<<p7.dist()<<endl;

	cin.get();	
	cin.ignore();

}

