#include "funciones.h"


bool lugar(int k, vector<int> columnas){
	for(int i=1; i<k; i++){
		if((columnas[i]==columnas[k])||(abs(columnas[i]-columnas[k])==abs(i-k))){
			return false;
		}
	}
	return true;
}

void mostrar_resultado(vector<vector<int>> &soluciones){
	if(soluciones.size()==1){
		cout<<"Hay "<<soluciones.size()<<" solucion, que es la siguiente: "<<endl;
	}else{
		cout<<"Hay "<<soluciones.size()<<" soluciones, que son las siguientes: "<<endl;
	}
	std::cin.ignore();  
	for(int i=0; i<soluciones.size(); i++){
		cout<<"Solución "<<i+1<<" ----> ";
		for(int j=1; j<soluciones[i].size(); j++){
			cout<<soluciones[i][j]<<" ";
		}
		cout<<endl;
	}
}

void funcionIntermediaBacktracking(bool mostrar, int n, vector<vector<int>> &soluciones){
	backtracking_reinas(n, soluciones);

	if(mostrar){
		mostrar_resultado(soluciones);
	}
}

void funcionIntermediaVegas(bool mostrar, int n, vector<vector<int>> &soluciones){
int contador=0;
	while(vegas_reinas(n, soluciones)==false){
		contador++;
	}
	cout<<"El algorítmo de las Vegas ha encotrado solucion tras "<<contador<<" intentos"<<endl;

	if(mostrar){
		mostrar_resultado(soluciones);
	}
}

void parte_practica1(int min, int max, int incremento){

	vector <double> tiemposReales, tiemposEstimados;
	vector <int> n;
	double a0, a1;
	bool mostrar=1;

	cout<<"Espere, se estan realizando los cálculos..."<<endl;

	extraccion_datos(min, max, incremento, tiemposReales, n);

	//ajusto la funcion para obtener los a
	ajustefactorialN(n,tiemposReales,a0, a1);

	//calculo los tiempos estimados
	calcularTiemposEstimadosfactorialN(n,a0,a1,tiemposEstimados);

	//vuelco la información en ficheros
	volcarTiemposFicheros(n, tiemposReales, tiemposEstimados);

	cout << "Ecuación de la curva ajustada con parametros a0 y a1: "<<a0<<"+"<<a1<<"*!n"<< endl;

	//calculo el coeficiente de Determinación
	double coef;
	coef=calcularCoeficienteDeterminacion(tiemposReales,tiemposEstimados);
	cout << "El coeficiente de Determinación es: " << coef << endl;

	//parte para ver si desea mostrar para cualquier n
	while(mostrar){
		cout<<"¿Desea calcular el tiempo Estimado para cualquier N?[SI=1/NO=0]"<<endl;
		cin>>mostrar;

		if(mostrar){
			calculoTiempoEstimado(a0, a1);
		}
	}

	cout<<"¿Desea ver la gráfica?[SI=1/NO=0]"<<endl;
	cin>>mostrar;

	if(mostrar){
		mostrar_grafica();
	}
}