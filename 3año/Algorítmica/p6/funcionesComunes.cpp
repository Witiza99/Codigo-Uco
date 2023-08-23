#include "funcionesComunes.hpp"
#include <iostream>
#include <algorithm>

bool Lugar(int columna, vector<int> filas){
	for(int i=1; i<columna; i++){
		if(filas[i] == filas[columna] or abs(filas[i] - filas[columna]) == abs(i - columna)){
			return false;
		}
	}
	return true;
}

void verSoluciones(vector<vector<int> > soluciones){
	for(int i=0; i<(int)soluciones.size(); i++){
		cout<<i+1<<" ->> ";
		for(int j=1; j<(int)soluciones[i].size(); j++){
			std::cout<<soluciones[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
}