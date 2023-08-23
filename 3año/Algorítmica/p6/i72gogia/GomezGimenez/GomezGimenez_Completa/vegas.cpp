#include "vegas.h"
#include<time.h>

bool vegas_reinas(int n, vector<vector<int>> &soluciones){

	srand(time(NULL));
	int posion_aleatoria;
	vector<int> columnas(n+1);
	vector<int> ok(n+1);
	int aleatorio;
	int contador;

	for(int i=1; i<n; i++){
		columnas[i]=0;
	}

	for(int k=1; k<=n; k++){
		contador=0;
		ok.clear();
		ok.push_back(0);

		for(int j=1;j<=n;j++){
			columnas[k]=j;
			if(lugar(k,columnas)==true){
				contador=contador+1;
				ok[contador]=j;
			}
		}
		if(contador==0){
			k=n;
		}else{
			posion_aleatoria=1+rand()%contador;//saco el uniforme de 1 hasta contador
			aleatorio=ok[posion_aleatoria];
			columnas[k]=aleatorio;
		}
	}

	if(contador==0){
		return false;
	}else{
		soluciones.push_back(columnas);
		return true;
	}
}