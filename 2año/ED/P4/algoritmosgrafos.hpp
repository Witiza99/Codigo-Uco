#ifndef __ALGORITMOSGRAFOS_H__
#define __ALGORITMOSGRAFOS_H__
#include <iostream>

#include "grafo.hpp"
using namespace ed;
using namespace std;

template <class G_Nodo, class G_Lado>
class AlgoritmosGrafos
{
public:

void Floyd(G_Lado **W, G_Lado **D,G_Lado **I, int n){
	 for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        D[i][j]=W[i][j];
      }
    }
    for (int i = 0; i < n; i++) {
      D[i][i]=0;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        I[i][j]=-1;
      }
	}
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(D[i][k]+D[k][j]<D[i][j]){
					D[i][j]=D[i][k]+D[k][j];
					I[i][j]=k;
				}
			}	
		}
	}
}

};

#endif
