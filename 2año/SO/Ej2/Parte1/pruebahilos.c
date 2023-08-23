#include <pthread.h>//para hilos
#include <semaphore.h>//para semaforos
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>//para srand y rand

#define NConsumidor 10
#define NProductor 10
#define N 10

//iniciadores de semaforos
sem_t mutex;
sem_t cons;
sem_t prod;

int bufer[N];//tamaño del vector global

//controladores para entrada y salida de datos
int indprod=0;
int indcons=0;

int main(){

	sem_init(&mutex,0,1);
	sem_init(&cons,0,0);
	sem_init(&prod,0,N);

	void *Productor();
	void *Consumidor();

	int i,j, v1[NConsumidor],v2[NProductor], status;

	pthread_t HConsumidor[NConsumidor];
	pthread_t HProductor[NProductor];

	int suma1=0;
	int suma2=0;

	int *r_value=NULL;

	srand(time(NULL));

	//Crear hilos
	for(i=0;i<NProductores;i++){

		if((status=pthread_create(&HProductor[i],NULL,(void*)Productor,NULL))!=0){
			exit(status);
		}
	}

	for(j=0;j<NConsumidor;j++){
		if(status=pthread_create(&HConsumidor[i],NULL,(void*)Consumidor,NULL)!=0){
			exit(status);
		}
	}

	//recoger hilos

	for(i=0;i<NProductor;i++){
		pthread_join(HProductor[i],(void**)&r_value);
		printf("El hilo %lu numero %d devuelve %d\n", HProductor[i],i,*r_value);
		v1[i]=*r_value;
	}

	for(j=0;j<NConsumidor;j++){
		pthread_join(HConsumidor[j],(void**)&r_value);
		printf("El hilo %lu numero %d devuelve %d\n", HConsumidor[j],j,*r_value);
		v2[j]=*r_value;
	}

	for(int x=0;x<NProductor;x++){
		suma1=suma1+v1[x];
	}
	printf("La suma total de los consumidores es %d\n", suma1);

	for(int x=0;x<NConsumidor;x++){
		suma2=suma2+v2[x];
	}
	printf("La suma total de los consumidores es %d\n", suma2);

	return 0;
}

void *Productor(){

	int *to_return=NULL;
	int valor;

	valor=rand()%11;

	sem_wait(&prod);
	sem_wait(&mutex);

	bufer[indprod]=valor;
	indprod=(indprod+1)%N;

	sem_post(&mutex);
	sem_post(&cons);

	to_return=malloc(sizeof(int));
	*to_return=valor;

	pthread_exit((void *)to_return);
}

void *Consumidor(){

	int *to_return=NULL;
	int valor;

	sem_wait(&cons);
	sem_wait(&mutex);

	valor=bufer[indcons];
	bufer[indcons]=-1;
	indcons=(indcons+1)%N;

	sem_post(&mutex);
	sem_post(&prod);

	to_return=malloc(sizeof(int));
	*to_return=valor;

	pthread_exit((void*)to_return);

}