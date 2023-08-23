#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TAMMATRIZ 4000
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

	start_t_serie = omp_get_wtime();

	//#pragma omp parallel
	//{
	//#pragma omp for nowait
		for(int j=0;j<ITERACIONES_MATRICES;j++){
			for(int k=0;k<ITERACIONES_MATRICES;k++){
				for(int i=0;i<ITERACIONES_MATRICES;i++){
					Cserie[i][j]+= A[i][k]*B[k][j];
				}
			}
		}
	//}

	end_t_serie = omp_get_wtime();

	total_t_serie = (end_t_serie - start_t_serie);
	printf("C[0][0]: %f\n", Cserie[0][0] );
	printf("Tiempo total de CPU para paralelizacion: %f\n", total_t_serie  );

	return(0);
}