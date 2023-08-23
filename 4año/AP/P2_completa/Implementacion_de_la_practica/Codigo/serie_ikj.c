#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define TAMMATRIZ 4096
#define ITERACIONES_MATRICES 4000


float A[TAMMATRIZ][TAMMATRIZ];
float B[TAMMATRIZ][TAMMATRIZ];
float Cserie[TAMMATRIZ][TAMMATRIZ];



int main () {


	srand (time(NULL)); 
	double start_t_serie, end_t_serie, total_t_serie;

	//relleno las matrices con valores aleatorios 
	for(int i=0;i<ITERACIONES_MATRICES;i++){
		for(int j=0;j<ITERACIONES_MATRICES;j++){
			A[i][j]= rand() % 10000;
			B[i][j]= rand() % 10000;
			Cserie[i][j]= 0;
		}
	}

	//serie
	printf("Realizando multiplicacion en serie: \n");

	start_t_serie = clock();
	for(int i=0;i<ITERACIONES_MATRICES;i++){
		for(int k=0;k<ITERACIONES_MATRICES;k++){
			for(int j=0;j<ITERACIONES_MATRICES;j++){
				Cserie[i][j]+= A[i][k]*B[k][j];
			}
		}
	}
	end_t_serie = clock();

	total_t_serie = (end_t_serie - start_t_serie)/CLOCKS_PER_SEC;
	printf("C[0][0]: %f\n", Cserie[0][0] );
	printf("Tiempo total de CPU para paralelizacion: %f\n", total_t_serie  );

	return(0);
}