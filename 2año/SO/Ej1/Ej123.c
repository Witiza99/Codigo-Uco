#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

#define CHILDREN 3
#define Ok 100


int main()
{
    int shmid, status;
    key_t key;
    int *counter;
    void func1();
    void func2();
    void func3();

    // Guardar memoria
    key = ftok("Ej123.c", 1);
    if ((shmid = shmget(key,100*sizeof(int), IPC_CREAT | 0777)) == -1)
	exit(1);

    counter = (int *) shmat(shmid, NULL, 0);

    srand(time(NULL));

    for(int j=0;j<100;j++){//rellenado el vector en el padre

    	counter[j]=rand()%11;

    }

    if (!fork()) {

	    func1();

	    exit(0);

	}

	if (!fork()) {

	    func2();

	    exit(0);

	}

	if (!fork()) {

	    func3();

	    exit(0);

	}

    for (int i=0; i < CHILDREN; i++){//proceso de espera de los hijos

	pid_t pid = wait(&status);

	printf("\nHijo %d termina con el estatus %d\n", pid, WEXITSTATUS(status));

    }

    //Borrar memoria
    shmdt(counter);

    return 0;

}

void func1(){//funcion para cambiar datos del vector

	int n;

	int lugar;

	int shmid;

	int *counter;

	key_t key;
	key = ftok("Ej123.c", 1);
    if ((shmid = shmget(key,100*sizeof(int), 0)) == -1)
	exit(1);

	counter=(int *)shmat(shmid,NULL,0);

	for(int i=0;i<10;i++){

		printf("Introduce el lugar del vector que deseas cambiar: \n");
		scanf("%d",&lugar);

		printf("Introduce el numero nuevo: \n");
		scanf("%d",&n);

		counter[lugar]=n;

	}

	exit(Ok);

}

void func2(){//funcion que cambia numeros aleatoriamente del vector cada segundo

	int aleatorio;

	int shmid;

	int *counter;

	key_t key;
	key = ftok("Ej123.c", 1);
    if ((shmid = shmget(key,100*sizeof(int), 0)) == -1)
	exit(1);

	counter=(int *)shmat(shmid,NULL,0);

	for(int i=0;i<100;i++){

		aleatorio=rand()%101;

		counter[aleatorio]=rand()%11;

		sleep(1);

	}

	exit(Ok);

}

void func3(){//funcion que suma el vector cada cierto tiempo

	int suma=0;

	int shmid;

	int *counter;

	key_t key;
	key = ftok("Ej123.c", 1);
    if ((shmid = shmget(key,100*sizeof(int),0)) == -1)
	exit(1);

	counter=(int *)shmat(shmid,NULL,0);

	for(int i=0;i<5;i++){

		for(int j=0;j<100;j++){
			
			suma=suma+counter[j];

		}

		printf("El resultado de la suma es %d\n",suma);

		suma=0;

		sleep(30);

	}

	exit(Ok);

}