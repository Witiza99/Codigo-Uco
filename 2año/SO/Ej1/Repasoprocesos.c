#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define CHILDREN 3
#define N 100
#define OK 5

int main(){
	
	int shmid,status;
	int *ptr;
	key_t key;
	void func1();
	void func2();
	void func3();

	//hacer zona de memoria compartida
	key=ftok("Repasoprocesos.c",1);//creo llave
	if((shmid=shmget(key,100*sizeof(int),IPC_CREAT|0777))==-1){//creo zona
		printf("Error al hacer el espacio de memorias\n");
		exit(1);
	}
	ptr=(int*)shmat(shmid,NULL,0);//puntero para zona
	//fin de zona de memoria

	srand(time(NULL));
	for(int i=0;i<N;i++){
		ptr[i]=rand()%11;
	}

	//creo procesos hijos
	if(!fork()){
		func1();
		exit(0);
	}

	if(!fork()){
		func2();
		exit(0);
	}
	if(!fork()){
		func3();
		exit(0);
	}

	//espera de los hijos
	for(int i=0;i<CHILDREN;i++){
		pid_t PID=wait(&status);
		printf("El proceso %d ha terminado y con resultado %d\n",PID,WEXITSTATUS(status));
	}

	//borrar memoria
	shmdt(ptr);

	return 0;
}

void func1(){

	//voy a usar memoria compartida
	int shmid;
	key_t key;
	int *ptr;

	key=ftok("Repasoprocesos.c",1);//creo clave
	if((shmid=shmget(key,100*sizeof(int),IPC_CREAT|0777))==-1){//creo zona/busco
		printf("Error al reservar memoria\n");
		exit(1);
	}
	ptr=(int*)shmat(shmid,NULL,0);//creo puntero

	int n,valor;//aqui ya empieza la función 1
	for(int i=0;i<10;i++){
		printf("Introduzca el indice del vector a modificar:\n");
		scanf("%d",&n);
		printf("Introduzca el valor nuevo\n");
		scanf("%d",&valor);
		ptr[n]=valor;
	}

	exit(OK);
}

void func2(){

	int shmid;
	key_t key;
	int *ptr;

	key=ftok("Repasoprocesos.c",1);
	if((shmid=shmget(key,100*sizeof(int),IPC_CREAT|0777))==-1){
		printf("Error al crear la zona compartida\n");
		exit(1);
	}
	ptr=(int*)shmat(shmid,NULL,0);
	int n;
	int valor;
	for(int i=0;i<100;i++){
		n=rand()%101;
		valor=rand()%11;
		ptr[n]=valor;
		sleep(1);
	}

	exit(OK);
}

void func3(){

	//busco la memoria compartida
	int shmid;
	key_t key;
	int *ptr;

	key=ftok("Repasoprocesos.c",1);//creo la clave
	if((shmid=shmget(key,100*sizeof(int),IPC_CREAT|0777))==-1){//busco la zona
		printf("Error al crear la zona de memoria compartidad\n");
		exit(1);
	}
	ptr=(int*)shmat(shmid,NULL,0);//creo puntero

	//funcion 3
	int suma=0;

	for(int i=0;i<5;i++){

		for(int j=0;j<100;j++){

			suma=suma+ptr[j];
		}
		printf("La suma total es %d\n",suma);
		suma=0;
		sleep(30);

	}

	exit(OK);
}