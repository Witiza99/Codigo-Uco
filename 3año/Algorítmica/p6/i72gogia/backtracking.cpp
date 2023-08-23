#include "backtracking.h"

void backtracking_reinas(int n, vector<vector<int>> &soluciones){

	vector<int> columnas(n+1);
	columnas[1]=0;
	int k=1;

	while(k>0){
		columnas[k]=columnas[k]+1;

		while((columnas[k]<=n)&&(lugar(k, columnas)==false)){
			columnas[k]=columnas[k]+1;
		}

		if(columnas[k]<=n){
			if(k==n){
				//escribir
				soluciones.push_back(columnas);
			}else{
				k=k+1;
				columnas[k]=0;
			}
		}else{
			k=k-1;
		}
	}
}	