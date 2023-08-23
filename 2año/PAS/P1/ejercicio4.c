#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <sys/wait.h>
#include <errno.h> //Control de errores
#include <string.h> //Para la funcion strerror()
#include <getopt.h>
#include <regex.h>
#include <ctype.h>//para isprint



#define MAX_SIZE    1024
#define QUEUE_NAME  "/cola"
#define MSG_STOP "exit"

void imprimir_uso() 
{
    printf("Uso del programa: ejercicio4-servidor [opciones]\n");
    printf("Opciones:\n");
    printf("-h, --help\t	Imprimir esta ayuda\n");
    printf("-r, --regex=EXPR\t	Expresión regular a utilizar\n");
}

int main(int argc, char **argv) 
{
	// Descriptor de la cola
	mqd_t mq;
	// Buffer para la lectura/escritura
	char buffer[MAX_SIZE];
	// Atributos de la cola
	struct mq_attr attr;
	// Para realizar el fork
	pid_t rf, flag;
	int status;

	char serverQueue[100];
	sprintf(serverQueue, "%s-%s", QUEUE_NAME, getenv("USER"));

	// flag que indica cuando hay que parar
	int must_stop = 0;

	/* Variables para la regex */
	regex_t regex;
	int reti;
	char msgbuf[100];

	// Inicializar los atributos de la cola. 
	attr.mq_maxmsg = 10;        // Maximo número de mensajes
	attr.mq_msgsize = MAX_SIZE; // Maximo tamaño de un mensaje. Tener en cuenta que debe incluir el '/0'

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

	/* Compilar la expresión regular */
	reti = regcomp(&regex, regexValue, 0);			
	if( reti )
	{
		fprintf(stderr, "No pude compilar la expresión regular\n");
		exit(EXIT_FAILURE);
	}

	// Realizar el fork
	rf = fork();
	switch (rf)
	{
		// Error
		case -1:
			printf ("No he podido crear el proceso hijo \n");
			exit(1);
		
		case 0: // Hijo.

		mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);

		if(mq==-1)
		{
			perror("[HIJO]: Error en la apertura de la cola");
			exit(-1);
		}

		//printf ("[HIJO]: mi PID es %d y mi PPID es %d\n", getpid(), getppid());

		// flag que indica cuando hay que parar
		printf("[HIJO]: Mandando mensajes al servidor (escribir \"%s\" para parar):\n", MSG_STOP);

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
			if(mq_send(mq, buffer, MAX_SIZE, 0) != 0)
			{
				perror("[HIJO]: Error al enviar el mensaje");
				exit(EXIT_FAILURE);
			}
			sprintf(msgbuf,"[HIJO]: Enviado el mensaje: %s", buffer);

			if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
				must_stop=1;
			else
			{
				// Número de bytes leidos
				ssize_t bytes_read;
				// Recibir el mensaje
				bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
				// Comprar que la recepción es correcto (bytes leidos no son negativos)
				if(bytes_read < 0)
				{
					perror("[HIJO]: Error al recibir el mensaje");
					exit(EXIT_FAILURE);
				}
				
				// Cerrar la cadena
				//buffer[bytes_read] = '\0';  
				printf("[HIJO]: Recibido el mensaje: %s\n", buffer);
				sprintf(msgbuf,"[HIJO]: Recibido el mensaje: %s", buffer);
	
				if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
					must_stop=1;
				
			}

			// Iterar hasta escribir el código de salida
		}while (!must_stop);

		// Cerrar la cola
		if(mq_close(mq) == -1)
		{
			perror("[HIJO]: Error cerrando la cola");
			exit(-1);
		}
		exit(EXIT_SUCCESS);

		break; //Saldría del switch()

		default://padre

		// Crear la cola
		mq = mq_open(serverQueue, O_CREAT | O_RDWR , 0644, &attr);
		if( mq == (mqd_t)-1)
		{
	     	perror("[PADRE]: Error al abrir la cola");
	  	 	exit(EXIT_FAILURE);
		}

		do {
		// Número de bytes leidos
		ssize_t bytes_read;

		// Recibir el mensaje
		bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
		// Comprar que la recepción es correcto (bytes leidos no son negativos)
		if(bytes_read < 0)
		{
			perror("[PADRE]: Error al recibir el mensaje");
			exit(EXIT_FAILURE);
		}

		// Cerrar la cadena
		//buffer[bytes_read] = '\0'; 
		
		// Comprobar el fin del bucle
		if (strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
			must_stop = 1;
		else
		{
			printf("[PADRE]: Recibido el mensaje: %s\n", buffer);

			/* Comprobar la expresión regular sobre la cadena pasada como argumento */
			reti = regexec(&regex, buffer, 0, NULL, 0);
			
		   // Puede servirnos, UNA VEZ COMPROBADA LA EXPRESION, por si al hacer pruebas hemos cerrado nuestro 
		   // cliente y servidor, y se han quedado caracteres en los bufferes de entrada/salida estandar
		   fflush(stdout);                  // Limpiar buffer de salida
		   memset(buffer, 0, MAX_SIZE);     // Poner a 0 el buffer		  
		  
			if(reti == 0)
			{
				strcpy(buffer,"Empareja");
			}
			else if( reti == REG_NOMATCH )
			{
				strcpy(buffer,"No Empareja");
			}
			else
			{
				regerror(reti, &regex, msgbuf, sizeof(msgbuf));
				fprintf(stderr, "[PADRE]: Falló el matching de la expresión regular: %s\n", msgbuf);
				strcpy(buffer,MSG_STOP);
			}
			
			// Enviar y comprobar si el mensaje se manda
			if(mq_send(mq, buffer, MAX_SIZE, 0) != 0)
			{
				perror("[PADRE]: Error al enviar el mensaje");
				exit(-1);
			}
			sprintf(msgbuf,"[PADRE]: Enviado el mensaje: %s", buffer);

		}

		// Iterar hasta que llegue el código de salida
		} while (!must_stop);

		// Cerrar la cola
		if(mq_close(mq) == -1)
		{
			perror("[PADRE]: Error cerrando la cola");
			exit(-1);
		}
		printf("[PADRE]: Cola cerrada.\n");

		break;

	}

	// Eliminar la cola
		if(mq_unlink(QUEUE_NAME) == -1)
		{
			perror("[PADRE]: Error eliminando la cola");
			exit(-1);
		}

	/*Espera del padre a los hijos*/
	while ( (flag=wait(&status)) > 0 ) 
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
