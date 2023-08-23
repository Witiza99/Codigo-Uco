#include "nReinasBacktracking.hpp"
#include "funcionesComunes.hpp"

#include <iostream>

void nReinasBacktracking(int n, vector<vector<int> > &soluciones){
	vector<int> filas(n+1);
	int columna;

	filas[1] = 0;
	columna = 1;

	while(columna > 0){
		filas[columna] = filas[columna] + 1;
		
		while(filas[columna] <= n and Lugar(columna, filas)==false){
			filas[columna] = filas[columna] + 1;
		}

		if(filas[columna] <= n){
			if(columna == n){
				soluciones.push_back(filas);
			}
			else{
				columna++;
				filas[columna] = 0;
			}
		}
		else{
			columna--;
		}
	
	}

//	cout<<"Numero de soluciones(Matriz): "<<soluciones.size()<<endl;

}