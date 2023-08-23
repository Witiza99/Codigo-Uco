//código creado por Antonio Gómez Giménez

//Este código viene a ser un modificación del caso 3_2.c

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define	NProductor 1
#define NConsumidor 1
//mirar caso N<que los max
#define N 100 //tamaño del bufer
//En este caso MaxP y MaxC no tiene sentido consumir menos que el productor produce, aparte tienen que ser iguales para evitar que el hilo consumidor se quede bloqueado
#define MaxP 100//máxima cantidad que puede producir el productor
#define MaxC 100//máxima cantidad que puede consumir el consumidor

sem_t mutex;
sem_t prod;
sem_t cons;
int bufer[N];
int indprod=0;
int indcons=0;

int main(){

	sem_init(&mutex, 0, 1);//creo el semaforo de zona crítica
	sem_init(&prod,0, N);/*creo semaforo que evita que los productores se pasen produciendo del bufer, 
	podría usarse una variable pero reciclo el semaforo*/
	sem_init(&cons,0, 0);//semaforo que evita que los consumidores consuman cuando no hay productos
	int status, i, j, v1[NProductor], v2[NConsumidor];
	pthread_t hilosProductores[NProductor];
	pthread_t hilosConsumidores[NConsumidor];
	void *consumidor();
	void *productor();
	int *r_value = NULL;
	int suma=0;
	int suma2=0;
	srand(time(NULL));

	// Crear hilos, en este caso 1 de cada
    for(i = 0; i < NProductor; i++){

		if ((status = pthread_create(&hilosProductores[i], NULL, (void *)productor, NULL)) != 0){

	   		exit(status);

   		}

	}

	for(j = 0; j < NConsumidor; j++){
	
		if((status = pthread_create(&hilosConsumidores[j], NULL, (void *)consumidor, NULL)) != 0){

			exit(status);

		}

	}

	//espera de hilos, en este caso 1
	for (i = 0; i < NProductor; i++) {

		pthread_join(hilosProductores[i], (void **) &r_value);
		printf("El hilo %lu devuelve: %d\n", hilosProductores[i], *r_value);
		v1[i] = *r_value;

    }

    for (j = 0; j < NConsumidor; j++) {

		pthread_join(hilosConsumidores[j], (void **) &r_value);
		printf("El hilo %lu devuelve: %d\n", hilosConsumidores[j], *r_value);
		v2[j] = *r_value;

    }

    //el resultado final de cada uno y de todos

    //productores

    /*printf("Valores totales de cada productor\n");//imprime todas las sumas de cada los productor

    for(int x = 1; x <= NProductor; x++){

    	printf("El Productor %d su suma total es %d\n", x,v1[x-1]);;

    }*/
    //no tenía sentido el mostrar uno a uno

    for(int z=0;z < NProductor; z++){

    	suma=suma+v1[z];

    }

    printf("El total de los productores es %d\n", suma);//imprime el total de todos los productores

    //consumidores

    /*printf("Valores totales de cada consumidor\n");

    for(int x = 1; x <= NConsumidor; x++){//imprime todas las sumas de cada los consumidor

    	printf("El Consumidor %d su suma total es %d\n", x,v2[x-1]);;

    }*/
    //no tenía sentido el mostrar uno a uno

    for(int z=0;z < NConsumidor; z++){

    	suma2=suma2+v2[z];

    }

    printf("El total de los consumidores es %d\n", suma2);//imprime el total de todos los consumidores

	return 0;

}

void *productor(){//los semaforos son parecidos para el 

	int valor;
	int suma=0;

	int *to_return = NULL;

	for(int w = 0; w < MaxP; w++){ //productor que rellena el bufer

	valor = rand()%1001;//se genera numero aleatorio

	sem_wait(&prod);//resto 1 del espacio total disponible

	sem_wait(&mutex);//aqui iria el semaforo de zona critica

	bufer[indprod]=valor;

	suma=suma+bufer[indprod];

	indprod=(indprod+1)%N;

	sem_post(&mutex);//salgo zona crítica
	
	sem_post(&cons);//sumo 1 para que los consumidores sepan que hay algo para consumir

	}

	to_return = malloc(sizeof(int));

    *to_return = suma;

    pthread_exit((void *) to_return);

}

void *consumidor(){

	int suma=0;
	//int valor;
	int *to_return = NULL;

	for(int w = 0; w < MaxC; w++){ //productor que rellena el bufer

	sem_wait(&cons);//compruebo si hay cosas que consumir

	sem_wait(&mutex);//entro en zona crítica

	suma=suma+bufer[indcons];
	
	bufer[indcons]= -1;//se consume el dato

	indcons=(indcons+1)%N;//se incrementa variable para siguiente consumidor

	sem_post(&mutex);//salgo de la zona crítica

	sem_post(&prod);//incremento el productor
	
	}

	to_return = malloc(sizeof(int));

    *to_return = suma;

    pthread_exit((void *) to_return);

}
