/* 
Servidor que lee de una cola abierta para lectura una cadena de caracteres y la
imprime por pantalla.

Lo hace mientras que el valor de esa cadena sea distinto a la palabra exit.
*/
//-lrt cuidado


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>//para isprint
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <getopt.h>
#include <time.h>
#include <errno.h>
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

// Función que procesará el final
void finPrograma(int value);

// Función que controla el log
void funcionLog(char *mensaje);

void imprimir_uso() 
{
    printf("Uso del programa: ejercicio4-servidor [opciones]\n");
    printf("Opciones:\n");
    printf("-h, --help\t	Imprimir esta ayuda\n");
    printf("-r, --regex=CAD\t	Cadena a utilizar\n");
}

/*Enteros asociados a las macros de señales:
1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL
5) SIGTRAP      6) SIGABRT      7) SIGBUS       8) SIGFPE
9) SIGKILL     10) SIGUSR1     11) SIGSEGV     12) SIGUSR2
13) SIGPIPE     14) SIGALRM     15) SIGTERM     17) SIGCHLD
18) SIGCONT     19) SIGSTOP     20) SIGTSTP     21) SIGTTIN
22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO
30) SIGPWR      31) SIGSYS      ....*/

/*void mi_manejador_sigint(int signal)
{
	funcionLog("Se ha activado la señal sigint, 2");
    finPrograma(-1);
    return;
}

void mi_manejador_sigterm(int signal)
{
	funcionLog("Se ha activado la señal sigterm, 15");
    finPrograma(-1);
    return;
}*/


//arranca ./servidor-r argumento

int main(int argc, char **argv)
{
	// Atributos de la cola
	struct mq_attr attr;

	// Buffer para intercambiar mensajes
	char buffer[MAX_SIZE];
	
	// flag que indica cuando hay que parar
	int must_stop = 0;
	
	// Inicializar los atributos de la cola
	attr.mq_maxmsg = 10;        // Maximo número de mensajes
	attr.mq_msgsize = MAX_SIZE; // Maximo tamaño de un mensaje

	// Nombre para las colas
	sprintf(clientQueue, "%s-%s", CLIENT_QUEUE, getenv("USER"));
	sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER"));

	char msgbuf[100];

	/* Variables para el getopt */
	int eflag = 0;
	char *regexValue = NULL;
	int c;
	int option_index;
	static struct option long_options[] =
	{
		/* Opciones que no van a actuar sobre un flag */
		/* "opcion", recibe o no un argumento, 0,
		   identificador de la opción */
		{"regex",  required_argument,	   0, 'r'},
		{"help",     no_argument,	   0, 'h'},
		/* Necesario para indicar el final de las opciones */
		{0, 0, 0, 0}
	};

   	opterr = 0;

	while ((c = getopt_long (argc, argv, "hr:",long_options, &option_index))!=-1)
		switch (c)
		{
			case 'h':
				eflag=1;
				imprimir_uso();
				exit(EXIT_SUCCESS);			
				break;
			case 'r':
				regexValue = optarg;
				break;
			case '?':
				if (optopt == 'r')
					fprintf (stderr, "La opción -%c requiere un argumento.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Opción desconocida `-%c'.\n", optopt);
				else
					fprintf (stderr, "Carácter de opción desconocido `\\x%x'.\n", optopt);
					imprimir_uso();
			default:			
				exit(EXIT_SUCCESS);
		}

	if((regexValue==NULL)&&(eflag==0))
	{
	   imprimir_uso();
	   exit(EXIT_SUCCESS);
	}

	printf("Valor de regexvalue en servidor:%s\n",regexValue);
	sprintf(msgbuf,"Valor de regexvalue en servidor:%s\n",regexValue);
	funcionLog(msgbuf);

//modifico las señales
	/* if (signal(SIGINT, mi_manejador_sigint) == SIG_ERR)
        printf("No puedo asociar la señal SIGINT al manejador!\n");
    if (signal(SIGTERM, mi_manejador_sigterm) == SIG_ERR)
        printf("No puedo asociar la señal SIGTERM al manejador!\n");*/

	/* Apertura de la cola
			   O_CREAT: si no existe, se crea
			   O_RDWR: lectura/escritura
			   O_RDONLY: solo lectura
			   O_WRONLY: solo escritura
			   0644: permisos rw-r--r--  
			         permisos de lectura y escritura para el propietario, y de sólo lectura para el grupo y para otros
			   attr: estructura con atributos para la cola  */

	// Crear la cola de mensajes del servidor
	mq_server = mq_open(serverQueue, O_CREAT | O_RDONLY, 0644, &attr);
	if( mq_server == (mqd_t)-1)
	{
     	perror("Error al abrir la cola del servidor");
     	funcionLog("Error al abrir la cola del servidor");
   	exit(EXIT_FAILURE);
	}

	// Crear la cola de mensajes del cliente
	mq_client = mq_open(clientQueue, O_CREAT | O_WRONLY, 0644, &attr);
	if( mq_client == (mqd_t)-1)
	{
     	perror("Error al abrir la cola del cliente");
     	funcionLog("Error al abrir la cola del cliente");
   	exit(EXIT_FAILURE);
	}

	do 
	{
		// Número de bytes leidos
		ssize_t bytes_read;

		// Recibir el mensaje
		bytes_read = mq_receive(mq_server, buffer, MAX_SIZE, NULL);
		// Comprobar que la recepción es correcta (bytes leidos no son negativos)
		if(bytes_read < 0)
		{
			perror("Error al recibir el mensaje");
			funcionLog("Error al abrir la cola del servidor");
			exit(-1);
		}
		// Cerrar la cadena
		//buffer[bytes_read] = '\0';

		// Comprobar el fin del bucle
		if (strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
			must_stop = 1;
		else{
			printf("Recibido el mensaje: %s\n", buffer);
			sprintf(msgbuf,"Recibido el mensaje: %s\n", buffer);
			funcionLog(msgbuf);

			if(strstr(buffer,regexValue)==NULL){

				strcpy(buffer,"No empareja");
				funcionLog("No empareja");
					
			}else{
				strcpy(buffer,"Empareja");
				funcionLog("Empareja");;
			}
			printf("> %s\n", buffer);

			// Enviar y comprobar si el mensaje se manda
			if(mq_send(mq_client, buffer, MAX_SIZE, 0) != 0)
			{
				perror("Error al enviar el mensaje");
				funcionLog("Error al enviar el mensaje");
				exit(-1);
			}
			sprintf(msgbuf,"Enviado el mensaje: %s", buffer);
			funcionLog(msgbuf);
		}

	} while (!must_stop); 	// Iterar hasta que llegue el código de salida, es decir, la palabra exit

	// Cerrar el programa
	finPrograma(-1);	
	
	mq_client = mq_server = -1;
	exit(EXIT_SUCCESS);
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
		// Buffer para intercambiar mensajes
		char buffer[MAX_SIZE];
		strcpy(buffer,MSG_STOP);
		
		// Enviar y comprobar si el mensaje se manda
		if(mq_send(mq_client, buffer, MAX_SIZE, 0) != 0)
		{
			perror("Error al enviar el mensaje");
			funcionLog("Error al enviar el mensaje)");
			exit(EXIT_FAILURE);
		}
		sprintf(msgbuf,"Enviado el mensaje: %s", buffer);
		funcionLog(msgbuf);


		// Cerrar la cola del servidor
		if(mq_close(mq_client) == (mqd_t)-1)
		{
			perror("Error al cerrar la cola del cliente");
			funcionLog("Error al cerrar la cola del cliente");
			exit(EXIT_FAILURE);
		}
		// Eliminar la cola del cliente
		if(mq_unlink(clientQueue) == (mqd_t)-1)
		{
			perror("Error al eliminar la cola del cliente");
			funcionLog("Error al eliminar la cola del cliente");
			exit(EXIT_FAILURE);
		}
	}
	
	if(mq_server!=-1)
	{
		// Cerrar la cola del servidor
		if(mq_close(mq_server) == (mqd_t)-1)
		{
			perror("Error al cerrar la cola del servidor");
			funcionLog("Error al cerrar la cola del servidor");
			exit(EXIT_FAILURE);
		}
		// Eliminar la cola del servidor
		if(mq_unlink(serverQueue) == (mqd_t)-1)
		{
			perror("Error al eliminar la cola del servidor");
			funcionLog("Error al eliminar la cola del servidor");
			exit(EXIT_FAILURE);
		}
	}
	
	mq_client = mq_server = -1;
	
	exit(EXIT_SUCCESS);
}
