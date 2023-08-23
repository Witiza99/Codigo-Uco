
#include <vector>    // necesario para el contenedor vector
#include "algorithm.hpp"
#include "greedymethod.hpp"
#include "digitalcurve.hpp"
//#include "heapvectorMasood.hpp"
//#include "nodoMasood.hpp"



using namespace std;

/* Functions for Collinear suppression method */

//Constructor.

GreedyMethod::GreedyMethod(char *fileName, int numberPointsPolygonalApproximation)
{
  //A digital curve is created to load the digital curve in file
	DigitalCurve dc(fileName);
  
  //Digital curve as saved as original curve
  setOriginalCurve(dc);

  //Set the number of points of the polygonal approximation
  setNumberPointsPolygonalApproximation(numberPointsPolygonalApproximation);
}

//Destructor
GreedyMethod::~GreedyMethod()
{
}

void GreedyMethod::apply()
{
	//Summations are calculated
	this->calculateSummations();

	//Collinear points are eliminated
	this->collinearPointsElimination();

	int desplazamiento = (int)(this->getDominantPointsPosition().size()/(this->getNumberPointsPolygonalApproximation()-1));
	vector<int> aux = this->getDominantPointsPosition();
	vector<int> Dominantes;

	for(int i=0; i< aux.size()-1;i=i+desplazamiento){
		Dominantes.push_back(aux[i]);
	}
	Dominantes.push_back(aux.size()-1);

	long double Error_total;
	long double Error_punto1;
	long double Error_punto2;
	int cantidad = Dominantes.size();

	for(int x=1;x<cantidad-2;x++){
		Error_total=calculateISEValue(Dominantes[x-1],Dominantes[x])+calculateISEValue(Dominantes[x],Dominantes[x+1]);
		cout<<x<<endl;
		for(int j=1;j<desplazamiento;j++){
			Error_punto1=calculateISEValue(Dominantes[x-1],aux[(x*desplazamiento)+j])+calculateISEValue(aux[(x*desplazamiento)+j],Dominantes[x+1]);
			Error_punto2=calculateISEValue(Dominantes[x-1],aux[(x*desplazamiento)-j])+calculateISEValue(aux[(x*desplazamiento)-j],Dominantes[x+1]);
			if(Error_punto1<Error_total){
				Dominantes[x]=aux[(x*desplazamiento)+j];
			}
			if(Error_punto2<Error_total){
				Dominantes[x]=aux[(x*desplazamiento)-j];
			}
		}
	}
	/*
	Error_total=calculateISEValue(Dominantes[cantidad-2],Dominantes[cantidad-1])+calculateISEValue(Dominantes[0],Dominantes[1]);
	for(int j=1;j<desplazamiento;j++){
		Error_punto1=calculateISEValue(Dominantes[cantidad-2],aux[(0*desplazamiento)+j])+calculateISEValue(aux[(0*desplazamiento)+j],Dominantes[1]);
		Error_punto2=calculateISEValue(Dominantes[cantidad-2],aux[(cantidad-1*desplazamiento)-j])+calculateISEValue(aux[(cantidad-1*desplazamiento)-j],Dominantes[1]);
		if(Error_punto1<Error_total){
			Dominantes[0]=aux[(cantidad-1*desplazamiento)+j];
			Dominantes[cantidad-1]=aux[(Dominantes[0]*desplazamiento)+j];
		}
		if(Error_punto2<Error_total){
			Dominantes[0]=aux[(cantidad-1*desplazamiento)-j];
			Dominantes[cantidad-1]=aux[(cantidad-1*desplazamiento)-j];
		}
	}*/

	this->setDominantPointsPosition(Dominantes);
	this->calculatePolygonalApproximation();
}

