#include <unistd.h> //pipe, close, fork, usleep, read, write, getpid, getppid
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> //wait
#include <errno.h> //Control de errores
#include <string.h> //Para la funcion strerror(), que permite describir el valor de errno como cadena.

int main(){

int tubo1[2];
int tubo2[2];
pid_t flag, rf;
int status;
const int BSIZE = 100;
char buf[BSIZE];
ssize_t nbytes;
int a,b;

char primero[BSIZE];
char segundo[BSIZE];

// Creamos la tubería
status = pipe(tubo1);
if(status==-1)
{
	printf("\nERROR al crear la tubería.\n");
	exit(1);
}

// Creamos la segunda tubería
status = pipe(tubo2);
if(status==-1)
{
	printf("\nERROR al crear la tubería.\n");
	exit(1);
}
rf=fork();

switch(rf)
{
	case -1:
 		printf ("Proceso Padre, no he podido crear el proceso hijo \n");
	   	 	exit(EXIT_FAILURE);
	case 0 : // código que ejecuta el hijo
	     
	    if (close(tubo1[1]) == -1) //no se necesita escribir
		{
			perror("Error en close");
			exit(EXIT_FAILURE);
		}

		if (close(tubo2[0]) == -1)//no se necesita leer 
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}
	
		// Leer usando READ. Es una llamada bloqueante.
		nbytes = read(tubo1[0], buf, BSIZE);
		if (nbytes == -1)
		{
			perror("Error en read"); 
			exit(EXIT_FAILURE);
		}
		else if (nbytes == 0) //read() no ha leido nada -> Se llegaría a FEOF porque el padre habría cerrado la tuberia.
			printf("[HIJO]: Detecto que mi padre ha cerrado la tuberia 1\n"); 
		else
			printf("[HIJO]: Leido %s de la tuberia 1.\n", buf); 

		if (close(tubo1[0]) == -1) //Se termina de leer -> Cerramos tubo[0]
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}
		else{printf("[HIJO]: Tuberia [1] cerrada.\n");}

		strcpy(primero, strtok(buf,";"));
		strcpy(segundo, strtok(NULL,";" ));

	    a=atoi(primero);
	    b=atoi(segundo);
	    int aux1=0;
	    int aux2=0;
	    char resultado[50];

	    for(int i=1;i<=a;i++){

	    	if(a%i==0){aux1++;}

	    }

	    for(int i=1;i<=b;i++){

	    	if(b%i==0){aux2++;}

	    }

	    if((aux1==2)&&(aux2==2)){

	    	if((b==a+2)||(a==b+2)){strcpy(resultado,"gemelos");}
	    	else{strcpy(resultado,"primo");}

	    }else{strcpy(resultado,"no-primos");}

		// Escribimos datos en la tubería
		if (write(tubo2[1], resultado, BSIZE)==-1)
		{
			perror("Error en write"); 
			exit(EXIT_FAILURE);
		}

		printf("[HIJO]: He escrito en la tuberia 2.\n");

		if (close(tubo2[1]) == -1) 
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}
		else{printf("[HIJO]: Tuberia [2] cerrada.\n");}
		exit(EXIT_SUCCESS);
	
	default:// código del proceso padre

		// No se necesita leer
		if (close(tubo1[0]) == -1)//no se necesita leer 
		{
			perror("Error en close 1"); //entra aqui no se porque
			exit(EXIT_FAILURE);
		}

		// No se necesita escribir
		if (close(tubo2[1]) == -1) 
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}

	 	
	 	printf("[Padre]: Inserte dos números enteros:\n");
	 	scanf("%d",&a);
	 	sprintf(primero, "%d", a);
	 	scanf("%d",&b);
	 	sprintf(segundo, "%d", b);

	 	strcpy(primero,strcat(primero,";"));
	 	strcpy(primero,strcat(primero,segundo));

	 	// Escribimos datos en la tubería
		if (write(tubo1[1], primero, BSIZE)==-1)
		{
			perror("Error en write 1"); 
			exit(EXIT_FAILURE);
		}

		printf("[PADRE]: He escrito los dos números en la tuberia 1.\n");

		// El hijo verá FEOF si posterior a esta llamada close del padre hiciera una read.
		if (close(tubo1[1]) == -1) 
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}
		else{printf("[PADRE]: Tuberia [1] cerrada.\n");}

		// Leer usando READ. Es una llamada bloqueante.
		nbytes = read(tubo2[0], buf, BSIZE);
		if (nbytes == -1)
		{
			perror("Error en read"); 
			exit(EXIT_FAILURE);
		}
		else if (nbytes == 0) //read() no ha leido nada -> Se llegaría a FEOF porque el padre habría cerrado la tuberia.
			printf("[PADRE]: Detecto que mi hijo ha cerrado la tuberia 2\n"); 
		else
			printf("[PADRE]: Leido %s de la tuberia 2.\n", buf); 

		if (close(tubo2[0]) == -1) //Se termina de leer -> Cerramos filfes[0]
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}
		else{printf("[PADRE]: Tuberia [2] cerrada.\n");}
			
		while ( (flag=wait(&status)) > 0 ) //por si utilizo alguna señal
		{
			if (WIFEXITED(status)) 
			{
				printf("Proceso Padre, Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
			} else if (WIFSIGNALED(status)) {  //Para seniales como las de finalizar o matar
				printf("Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
			} else if (WIFSTOPPED(status)) { //Para cuando se para un proceso. Al usar wait() en vez de waitpid() no nos sirve.
				printf("Proceso Padre, Hijo con PID %ld parado al recibir la señal %d\n", (long int)flag,WSTOPSIG(status));
			} else if (WIFCONTINUED(status)){ //Para cuando se reanuda un proceso parado. Al usar wait() en vez de waitpid() no nos sirve.
				printf("Proceso Padre, Hijo con PID %ld reanudado\n",(long int) flag);		  
			}	
		}

		if (flag==(pid_t)-1 && errno==ECHILD)
		{
			printf("Proceso Padre, valor de errno = %d, definido como %s, no hay más hijos que esperar!\n", errno, strerror(errno));
		}
		else
		{
			printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
			exit(EXIT_FAILURE);
		}

		exit(EXIT_SUCCESS);

	}

}