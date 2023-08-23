#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//#define NHILOS	2
#define TAMMATRIZ 4096
//#define TAMHILO TAMMATRIZ/NHILOS
#define ITERACIONES_MATRICES 4000//solo tiene sentido si se introduce 4000 o 4096

struct valores {
	int inicio;
	int final;
};

float A[TAMMATRIZ][TAMMATRIZ];
float B[TAMMATRIZ][TAMMATRIZ];
float C[TAMMATRIZ][TAMMATRIZ];
float Cserie[TAMMATRIZ][TAMMATRIZ];

void *hilo(void *arg){

	struct valores *v=(struct valores*)arg;

	double start_temp, end_temp, total_temp;

	//printf("Inicio hilo: %d, Final hilo: %d\n", v->inicio, v->final  );

	start_temp = clock();

	for(int i=v->inicio;i<v->final;i++){
		for(int k=0;k<ITERACIONES_MATRICES;k++){
			for(int j=0;j<ITERACIONES_MATRICES;j++){
				C[i][j]+= A[i][k]*B[k][j];
			}
		}
	}

	end_temp = clock();

	total_temp = (end_temp - start_temp)/CLOCKS_PER_SEC;
	printf("C[0][0]: %f\n", C[0][0] );
	printf("Tiempo total de CPU para paralelizacion de HILO: %f\n", total_temp  );

}

int main (int argc, char *argv[]) {

	if(argc!=2){
		printf("Numero de parametros erroneo, falta decir la cantidad de hilos\n");
		return -1;
	}

	int NHILOS=atoi(argv[1]);
	int TAMHILO=TAMMATRIZ/NHILOS;

	pthread_t hilos[NHILOS];
	int status;
	struct valores v[NHILOS];

	srand (time(NULL)); 
	//double start_t_serie, end_t_serie, total_t_serie;
	double start_t_paralelo, end_t_paralelo, total_t_paralelo;

	//relleno las matrices con valores aleatorios 
	for(int i=0;i<ITERACIONES_MATRICES;i++){
		for(int j=0;j<ITERACIONES_MATRICES;j++){
			A[i][j]= rand() % 10000;
			B[i][j]= rand() % 10000;
			C[i][j]= 0;
			Cserie[i][j]= 0;
		}
	}

	//serie
	/*
	printf("Realizando multiplicacion en serie: \n");

	start_t_serie = clock();
	for(int i=0;i<TAMMATRIZ;i++){
		for(int k=0;k<TAMMATRIZ;k++){
			for(int j=0;j<TAMMATRIZ;j++){
				Cserie[i][j]+= A[i][k]*B[k][j];
			}
		}
	}
	end_t_serie = clock();

	total_t_serie = (end_t_serie - start_t_serie)/CLOCKS_PER_SEC;
	printf("C[0][0]: %f\n", Cserie[0][0] );
	printf("Tiempo total de CPU para paralelizacion: %f\n", total_t_serie  );*/

	//paralelo

	printf("Realizando multiplicacion en paralelo: \n");

	for(int i=0;i<NHILOS;i++){
		v[i].inicio=i*TAMHILO;
		v[i].final=v[i].inicio+TAMHILO;
	}

	// Create NHILOS threads
    for (int i = 0; i < NHILOS; i++) {
		if ((status = pthread_create(&hilos[i], NULL, hilo, (void *) &v[i]))){
		    exit(status);
		}
	}

	start_t_paralelo = clock();
	
	// Wait threads
    for (int i = 0; i < NHILOS; i++) {
		pthread_join(hilos[i], NULL);
    }

	end_t_paralelo = clock();

	//comprobacion si es correcto
	/*
	for(int i=0;i<TAMMATRIZ;i++){
		for(int j=0;j<TAMMATRIZ;j++){
			if(Cserie[i][j]!=C[i][j]){
				printf("Cserie[%d][%d]:%f, CParalelo[%d][%d]:%f", i,j,Cserie[i][j],i,j,C[i][j]);
				printf("Error multiplicando");
				exit(1);
			}
		}
	}*/

	total_t_paralelo = (end_t_paralelo - start_t_paralelo)/CLOCKS_PER_SEC;
	printf("C[0][0]: %f\n", C[0][0] );
	printf("Tiempo total Final de CPU para paralelizacion: %f\n", total_t_paralelo  );

	return(0);
}