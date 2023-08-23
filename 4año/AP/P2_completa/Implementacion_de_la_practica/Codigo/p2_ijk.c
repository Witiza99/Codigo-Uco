//cambiar a version ijk


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//#define NHILOS	4
#define TAMMATRIZ 4096
//#define TAMHILO TAMMATRIZ/(NHILOS/2) //como paralelizamos dos bucles en vez de uno es necesario dividir entre 2, si son 4 dos para i y dos para j
#define ITERACIONES_MATRICES 4000

struct valores {
	int inicio_de_i;
	int final_de_i;
	int inicio_de_j;
	int final_de_j;
};

float A[TAMMATRIZ][TAMMATRIZ];
float B[TAMMATRIZ][TAMMATRIZ];
float C[TAMMATRIZ][TAMMATRIZ];
float Cserie[TAMMATRIZ][TAMMATRIZ];

void *hilo(void *arg){

	struct valores *v=(struct valores*)arg;

	printf("v_i_inicio:%d, v_i_final:%d, v_j_inicio:%d, v_j_final:%d\n", v->inicio_de_i, v->final_de_i, v->inicio_de_j, v->final_de_j);

	for(int i=v->inicio_de_i;i<v->final_de_i;i++){
		for(int j=v->inicio_de_j;j<v->final_de_j;j++){
			for(int k=0;k<ITERACIONES_MATRICES;k++){
				C[i][j]+= A[i][k]*B[k][j];
			}
		}
	}
}

int main (int argc, char *argv[]) {

	if(argc!=2){
		printf("Numero de parametros erroneo, falta decir la cantidad de hilos\n");
		return -1;
	}

	int NHILOS=atoi(argv[1]);
	int TAMHILO=TAMMATRIZ/(NHILOS/2);

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

	/*printf("Realizando multiplicacion en serie: \n");

	start_t_serie = clock();
	for(int i=0;i<TAMMATRIZ;i++){
		for(int j=0;j<TAMMATRIZ;j++){
			for(int k=0;k<TAMMATRIZ;k++){
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

	int secciones=0;//esta variable nunca puede ser superior al numero de hilos
	for(int j=0;j<NHILOS/2;j++){//bucle para rellenar la parte de i
		for(int k=0;k<NHILOS/2;k++){//bucle para rellenar la parte de j
			v[secciones].inicio_de_i=j*TAMHILO;
			v[secciones].final_de_i=v[secciones].inicio_de_i+TAMHILO;
			v[secciones].inicio_de_j=k*TAMHILO;
			v[secciones].final_de_j=v[secciones].inicio_de_j+TAMHILO;
			secciones++;
		}
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
	
	/*for(int i=0;i<TAMMATRIZ;i++){
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
	printf("Tiempo total de CPU para paralelizacion: %f\n", total_t_paralelo  );

	return(0);
}