#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <signal.h>
#include "common.h"

// Apuntador al fichero de log
FILE *fLog = NULL;

// Cola del servidor
mqd_t mq_server = -1;

// Cola del cliente
mqd_t mq_client = -1;

// Nombre para las colas
char clientQueue[100];
char serverQueue[100];

// Función que procesará EL FINAL
void finPrograma(int value);

// Función que controla el log
void funcionLog(char *mensaje);

/*Ejemplo:
kill -SIGINT pid
kill -SIGKILL pid*/

/*Enteros asociados a las macros de señales:
1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL
5) SIGTRAP      6) SIGABRT      7) SIGBUS       8) SIGFPE
9) SIGKILL     10) SIGUSR1     11) SIGSEGV     12) SIGUSR2
13) SIGPIPE     14) SIGALRM     15) SIGTERM     17) SIGCHLD
18) SIGCONT     19) SIGSTOP     20) SIGTSTP     21) SIGTTIN
22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO
30) SIGPWR      31) SIGSYS      ....*/

void mi_manejador_sigint(int signal)
{
	printf("Recibido mensaje de finalización por parte del cliente por captura de señal SIGINT (2)\n");
	funcionLog("Recibido mensaje de finalización por parte del cliente por captura de señal SIGINT (2)\n");
    finPrograma(-1);
    return;
}

void mi_manejador_sigterm(int signal)
{
	printf("Recibido mensaje de finalización por parte del cliente por captura de señal TERM (15)\n");
	funcionLog("Recibido mensaje de finalización por parte del cliente por captura de señal TERM (15)\n");
    finPrograma(-1);
    return;
}


int main(int argc, char **argv)
{
	//pido el pid para poder usar las señales
	printf("%d\n", getpid());

	// Buffer para intercambiar mensajes
	char buffer[MAX_SIZE];

	// Buffer para mensajes
   char msgbuf[100];

	// Nombre para las colas
	sprintf(clientQueue, "%s-%s", CLIENT_QUEUE, getenv("USER"));
	sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER"));

	//modifico las señales
	if (signal(SIGINT, mi_manejador_sigint) == SIG_ERR)
        printf("No puedo asociar la señal SIGINT al manejador!\n");
    if (signal(SIGTERM, mi_manejador_sigterm) == SIG_ERR)
        printf("No puedo asociar la señal SIGTERM al manejador!\n");

	// Abrir la cola del servidor
	mq_server = mq_open(serverQueue, O_WRONLY);
	if( mq_server == (mqd_t)-1)
	{
     	perror("Error al abrir la cola del servidor");
     	funcionLog("Error al abrir la cola del servidor");
      exit(EXIT_FAILURE);
	}

	// Abrir la cola del cliente
	mq_client = mq_open(clientQueue, O_RDONLY);
	if( mq_client == (mqd_t)-1)
	{
    	perror("Error al abrir la cola del cliente");
    	funcionLog("Error al abrir la cola del servidor");
   	exit(EXIT_FAILURE);
	}

	// flag que indica cuando hay que parar
	int must_stop = 0;
	printf("Mandando mensajes al servidor (escribir \"%s\" para parar):\n", MSG_STOP);
	sprintf(msgbuf,"Mandando mensajes al servidor (escribir \"%s\" para parar):\n", MSG_STOP);
	funcionLog(msgbuf);


	do 
	{
		printf("> ");

		// Puede servirnos por si al hacer pruebas hemos cerrado nuestro cliente y servidor
		// y se han quedado caracteres en los bufferes de entrada/salida estandar
		fflush(stdout);                  // Limpiar buffer de salida
		memset(buffer, 0, MAX_SIZE);     // Poner a 0 el buffer

		/* Leer por teclado. Según la documentación, fgets lo hace de esta manera:
		It stops when either (n-1) characters are read, the newline character is read,
		or the end-of-file is reached, whichever comes first. 
		Automáticamente fgets inserta el fin de cadena '\0'
		*/
		fgets(buffer, MAX_SIZE, stdin);  

		/* //Descartar el \n del final
		if(buffer[strlen(buffer)-1] == '\n') 
			buffer[strlen(buffer)-1] = '\0';
		*/
		
		// Enviar y comprobar si el mensaje se manda
		if(mq_send(mq_server, buffer, MAX_SIZE, 0) != 0)
		{
			perror("Error al enviar el mensaje");
			funcionLog("Error al enviar el mensaje");
			exit(EXIT_FAILURE);
		}
	
		sprintf(msgbuf,"Enviado el mensaje: %s", buffer);
		funcionLog(msgbuf);
		if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
			must_stop=1;
		else
		{
			// Número de bytes leidos
			ssize_t bytes_read;
			// Recibir el mensaje
			bytes_read = mq_receive(mq_client, buffer, MAX_SIZE, NULL);
			// Comprobar que la recepción es correcto (bytes leidos no son negativos)
			if(bytes_read < 0)
			{
				perror("Error al recibir el mensaje");
				funcionLog("Error al recibir el mensaje");
				exit(EXIT_FAILURE);
			}
			
			// Cerrar la cadena
			//buffer[bytes_read] = '\0';  
			printf("Recibido el mensaje: %s\n", buffer);
			sprintf(msgbuf,"Recibido el mensaje: %s", buffer);
			funcionLog(msgbuf);
			if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
				must_stop=1;
		}
		// Iterar hasta escribir el código de salida
	}while (!must_stop);

	finPrograma(-1);
	mq_client = mq_server = -1;
	return 0;
}

//Función auxiliar, escritura de un log. 
void funcionLog(char *mensaje)
{
	int resultado;
	char nombreFichero[100];
	char mensajeAEscribir[300];
	time_t t;

	// Abrir el fichero
	sprintf(nombreFichero,"log-servidor.txt");
	if(fLog==NULL)
	{
		fLog = fopen(nombreFichero,"at");
		if(fLog==NULL)
		{
			perror("Error abriendo el fichero de log");
			exit(1);
		}
	}

	// Obtener la hora actual
	t = time(NULL);
	struct tm * p = localtime(&t);
	strftime(mensajeAEscribir, 1000, "[%Y-%m-%d, %H:%M:%S]", p);

	// Vamos a incluir la hora y el mensaje que nos pasan
	sprintf(mensajeAEscribir, "%s ==> %s\n", mensajeAEscribir, mensaje);
	
	// Escribir finalmente en el fichero
	resultado = fputs(mensajeAEscribir,fLog);
	if (resultado < 0)
		perror("Error escribiendo en el fichero de log");

	fclose(fLog);
	fLog=NULL;
}

void finPrograma(int value)
{
   char msgbuf[100];

    printf("Cerrando y eliminando las estructuras pertinentes. Fin del programa...\n");

	if(mq_client!=-1)
	{
		// Cerrar la cola del servidor
		if(mq_close(mq_client) == (mqd_t)-1)
		{
			perror("Error al cerrar la cola del cliente");
			funcionLog("Error al cerrar la cola del cliente");
			exit(EXIT_FAILURE);
		}
	}
	
	if(mq_server!=-1)
	{
		// Buffer para intercambiar mensajes
		char buffer[MAX_SIZE];
		strcpy(buffer,MSG_STOP);

		printf("\n");
		
		// Enviar y comprobar si el mensaje se manda
		if(mq_send(mq_server, buffer, MAX_SIZE, 0) != 0)
		{
			perror("Error al enviar el mensaje");
			funcionLog("Error al enviar el mensaje");
			exit(EXIT_FAILURE);
		}
		sprintf(msgbuf,"Enviado el mensaje: %s", buffer);
		funcionLog(msgbuf);

		// Cerrar la cola del servidor
		if(mq_close(mq_server) == (mqd_t)-1)
		{
			perror("Error al cerrar la cola del servidor");
			funcionLog("Error al cerrar la cola del servidor");
			exit(EXIT_FAILURE);
		}
	}
	mq_client = mq_server = -1;	
	exit(0);
}
