
#include <vector>    // necesario para el contenedor vector
#include "algorithm.hpp"
#include "dynamicprogrammingmethod.hpp"
#include "digitalcurve.hpp"
//#include "heapvectorMasood.hpp"
//#include "nodoMasood.hpp"



using namespace std;

/* Functions for Collinear suppression method */

//Constructor.

DynamicProgrammingMethod::DynamicProgrammingMethod(char *fileName, int numberPointsPolygonalApproximation)
{
  //A digital curve is created to load the digital curve in file
	DigitalCurve dc(fileName);
  
  //Digital curve as saved as original curve
  setOriginalCurve(dc);

  //Set the number of points of the polygonal approximation
  setNumberPointsPolygonalApproximation(numberPointsPolygonalApproximation);
}

//Destructor
DynamicProgrammingMethod::~DynamicProgrammingMethod()
{
}

void DynamicProgrammingMethod::apply()
{
	//(541/20)=720
	//(n de 2 a 541/m de 2 a 20)=Error va desde 0 en los dos casos para evitar salir por delante
	//(puntos del fichero/puntos nuestros para la curva=Error total optima)
	//de 0 a n-1
	//en los limites de 0 a n-1
	//E(n/m)=min{E(j,m-1)+e(Pj,Pj-1),Pn(Pn-1))}
	//father reservarla con n+1 y m+1
	//father[i,j]=j (!no ha j-1 eso sera al final para evitar cargarte los father) se puede guardar en vector de dominantes y restarle a todos -1 al final
	//%N te permite hacerlo circular
	this->calculateSummations();  

	int m_total=this->getNumberPointsPolygonalApproximation();//puntos de nuestra curva
	m_total=m_total+1;//arreglo problema con los puntos pero no llego antender el fallo
	int n_total=this->getOriginalCurve().getNumberPointsDigitalCurve();//puntos del fichero

	vector <vector <int> > father;//father reservarla con n+1 y m+1
	father = vector <vector <int> >(n_total+1,vector <int>(m_total+1));
	vector <vector <double> > Error;
	Error = vector <vector <double> >(n_total,vector <double>(m_total));
	for(int i = 2; i < Error.size(); i++){//inicializo en infinito
		Error[i][1]=400000000;
	}

	Error[1][1]=0;
	for(int m = 2; m < m_total; m++){
		for(int n =m; n < n_total; n++){
			int min=Error[m-1][m-1]+calculateISEValue(m-2,n-1);
			father[n][m]=m-1;

			for(int j = m; j<n; j++){
				if(min>(Error[j][m-1]+calculateISEValue(j-1,n-1))){
					min=Error[j][m-1]+calculateISEValue(j-1,n-1);
					father[n][m]=j;
				}
			}
			Error[n][m]=min;
		}
	}

	vector<int> resultado;
	int aux=n_total-1;
	resultado.insert(resultado.begin(),n_total-1);
	//cout<<"resultado["<<6<<"]= "<<resultado[0]<<endl;
	for(int i=m_total-1; i>1;i--){
		resultado.insert(resultado.begin(),(father[aux][i])-1);
		//cout<<"resultado["<<i<<"]= "<<resultado[0]<<endl;
		aux=(father[aux][i]);
	}

	this->setDominantPointsPosition(resultado);
	this->calculatePolygonalApproximation();
}