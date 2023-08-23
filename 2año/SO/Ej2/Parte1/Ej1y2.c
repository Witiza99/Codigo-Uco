//En este ejercicio se pretende usar el algoritmo de lamport para solucionar los problemas en la sección crítica
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

double counter = 0;

#define ITER	1000
#define NHILOS	4

int Numero[NHILOS];
int Eligiendo[NHILOS];

int main()
{
    pthread_t hilos[NHILOS];
    int status, i, v[NHILOS];
    extern double counter;
    void *adder(void *);
    double *r_value;

    // Create NHILOS threads
    for (i = 0; i < NHILOS; i++) {
	v[i] = i;
	if ((status = pthread_create(&hilos[i], NULL, adder, (void *) &v[i])))
	    exit(status);
    }

    // Wait threads
    for (i = 0; i < NHILOS; i++) {
	pthread_join(hilos[i], (void **) &r_value);
	printf("Value returned by %lu thread: %lf\n", hilos[i], *r_value);
    }

    // Final result
    fprintf(stdout, "%f\n", counter);

    return 0;
}

void *adder(void *p)
{
    double l, *to_return;
    extern double counter;
    int *id, i;

    id = (int *) p;

    while(1){

    	Eligiendo[*id]=1;

    	int maximo=Numero[0];

    	for(int i=1; i < NHILOS; i++){

    		if(maximo < Numero[i]){

    			maximo=Numero[i];

    		}

    	}

    	Numero[*id]=maximo+1;

    	Eligiendo[*id]=0;

    	for(int j=0; j<NHILOS; j++){

    		while (Eligiendo[j]);

    		while ((Numero[j]!=0) && ((Numero[j])<(Numero[*id])));

    	}

  	 	//seccion crítica

  		  for (i = 0; i < ITER; i++) {
			l = counter;
			fprintf(stdout, "Hilo %d: %f\n", *id, counter);
			l++;
			counter = l;
  	 	 }

  		  //fin de la sección crítica

    	Numero[*id]=0;

    	to_return = malloc(sizeof(double));

   	 *to_return = counter;

    pthread_exit((void *) to_return);

	}

}
