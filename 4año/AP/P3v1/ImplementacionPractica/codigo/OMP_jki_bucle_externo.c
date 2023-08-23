#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TAMMATRIZ 4000
#define ITERACIONES_MATRICES 4000


float A[TAMMATRIZ][TAMMATRIZ];
float B[TAMMATRIZ][TAMMATRIZ];
float Cparalelo[TAMMATRIZ][TAMMATRIZ];



int main (int argc, char *argv[]) {
	
	if(argc<2 || argc > 3){
		printf("Numero de parametros erroneo, falta decir si se especifica hilos y la cantidad de hilos\n");
		return -1;
	}

	if(argc == 2){
		if(atoi(argv[1]) == 1){
			printf("Faltan especifical los hilos\n");
			return -1;
		}
	}

	if(atoi(argv[1]) != 1 && atoi(argv[1]) != 0 ){
		printf("Modo no valido\n");
		return -1;
	}

	if(atoi(argv[1]) == 1){
		int NHILOS=atoi(argv[2]);
		omp_set_num_threads(NHILOS);
	}
	//int TamSegmento=TAMMATRIZ/(NHILOS);

	srand (time(NULL)); 
	double start_t_paralelo, end_t_paralelo, total_t_paralelo;

	//relleno las matrices con valores aleatorios 
	for(int i=0;i<ITERACIONES_MATRICES;i++){
		for(int j=0;j<ITERACIONES_MATRICES;j++){
			A[i][j]= rand() % 10000;
			B[i][j]= rand() % 10000;
			Cparalelo[i][j]= 0;
		}
	}

	//paralelo
	printf("Realizando multiplicacion en paralelo: \n");
 
	start_t_paralelo = omp_get_wtime();

	#pragma omp parallel
	{
	//#pragma omp for schedule (dynamic, TamSegmento) nowait
	#pragma omp for nowait
		for(int j=0;j<ITERACIONES_MATRICES;j++){
			for(int k=0;k<ITERACIONES_MATRICES;k++){
				for(int i=0;i<ITERACIONES_MATRICES;i++){
					Cparalelo[i][j]+= A[i][k]*B[k][j];
				}
			}
		}
	}

	end_t_paralelo = omp_get_wtime();

	total_t_paralelo = (end_t_paralelo - start_t_paralelo);
	printf("C[0][0]: %f\n", Cparalelo[0][0] );
	printf("Tiempo total de CPU para paralelizacion: %f\n", total_t_paralelo  );

	return(0);
}