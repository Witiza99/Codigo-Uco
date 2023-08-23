//Código creado por Antonio Gómez Giménez
//este código es prácticamente una mezcla del código del caso3_1 con el productor y el caso3_2 donde su usan los consumidores


//usar if para comprobar que hay otro hilos consumidores si no hacer consumicion
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define	NProductor 1
#define NConsumidor 3
#define N 10 //tamaño del bufer
#define MaxP 10//máxima cantidad que puede producir el productor
#define MaxC 10//máxima cantidad que puede consumir el consumidor, no tiene sentido coger mas datos de los que se producen

//mirar caso en que Los Max superen a N ya que puede dar fallo al no usar variable global

sem_t mutex;
sem_t prod;
sem_t cons;
sem_t varaux;
int bufer[N];
//indices que controlan la entrada y salida de datos en mi bufer
int indprod=0;
//int indcons=0;//no puedo ponerlo ya que sino no lo leen todos
int aux=0;//compruebo los consumidores que hay en sc

int main(){

	sem_init(&mutex, 0, 1);//creo el semaforo de zona crítica
	sem_init(&prod,0, N);//creo semaforo que evita que el productor se pase produciendo del bufer
	sem_init(&cons,0, 0);//semaforo que evita que los consumidores consuman cuando no hay productos
	sem_init(&varaux,0,1);//semaforo que evita que se incremente mi variable por dos consumidores a la vez
	int status, i, j, v1[NProductor], v2[NConsumidor];
	pthread_t hilosProductores[NProductor];
	pthread_t hilosConsumidores[NConsumidor];
	void *consumidor();
	void *productor();
	int *r_value = NULL;
	int suma=0;
	int suma2=0;
	srand(time(NULL));

	// Crear hilos, en este caso uno productor y varios consumidores
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

	//espera de hilos
	for (i = 0; i < NProductor; i++) {
		pthread_join(hilosProductores[i], (void **) &r_value);
		printf("Productor\n");
		printf("El hilo %lu devuelve: %d\n", hilosProductores[i], *r_value);
		v1[i] = *r_value;

    }

    for (j = 0; j < NConsumidor; j++) {
		pthread_join(hilosConsumidores[j], (void **) &r_value);
		printf("Consumidor\n");
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

    printf("El total del productor es %d\n", suma);//imprime el total de todos los productores

    //consumidores

    printf("Valores totales de cada consumidor\n");

    for(int x = 1; x <= NConsumidor; x++){//imprime todas las sumas de cada los consumidor

    	printf("El Consumidor %d su suma total es %d\n", x,v2[x-1]);;

    }

    for(int z=0;z < NConsumidor; z++){

    	suma2=suma2+v2[z];

    }

    printf("El total de los consumidores sumando cada uno de ellos es es %d\n", suma2);//imprime el total de todos los consumidores

	return 0;

}

void *productor(){//los semaforos son parecidos para el 

	int valor;
	int suma=0;
	int *to_return = NULL;

	for(int w = 0; w < MaxP; w++){ //productor que rellena el bufer

		valor = rand()%1001;//se genera numero aleatorio
		printf("El nuevo valor es %d \n",valor );
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

		sem_wait(&varaux);

		aux++;

		if(aux==1){

			sem_wait(&mutex);

		}

		sem_post(&varaux);

		suma=suma+bufer[w];
		printf("recojo %d\n", bufer[w]);
		//indcons=(indcons+1)%N;
	
		//bufer[w]=-1;//esto significa que consume el dato pero en este caso no lo puedo hacer ya que el resto tambien lo tiene que consumir

		sem_post(&prod);//incremento el productor(quiza tiene fallo mirar mejor)

		sem_post(&cons);//de esta forma permite a los demas consumidores consumir el elemento que acaba de consumir

		sem_wait(&varaux);

		aux--;

		if(aux==0){

			sem_post(&mutex);

		}

		sem_post(&varaux);

	}

	to_return = malloc(sizeof(int));

    *to_return = suma;

    pthread_exit((void *) to_return);

}
