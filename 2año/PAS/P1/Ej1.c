//a tener en cuenta la variables con argunmentos, estas deben ir solas ya que si estan vacias asi -u -i coge como argumento -i y peta.
//necesitaria usar las banderas antes de switch para evitar que falle al entrar en la primera opción

//librerias necesarias para realizar el ejercicio
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
//libreria necesaria para getoptlog
#include <getopt.h>
//para buscar subcadena en cadena
#include <string.h>
//librerias para sacar la informacion, grupo y usuario
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

void imprimir_uso() 
{
    printf("Opciones disponibles:\n");
    printf("-u, --username\t	Especifica el nombre de un usuario del sistema\n");
    printf("-i, --useruid\t	  Especifica el identificador de un usuario del sistema\n");
    printf("-g, --groupname\t	  Especifica el nombre de un grupo del sistema\n");
    printf("-d, --groupuid\t	  Especifica el identificador de un grupo del sistema\n");
    printf("-s, --allgroups\t	  Se muestra todos los grupos del sistema, junto con su identificador\n");
    printf("-a, --allinfo\t	Especifica el nombre del usuario del sistema y toda su información\n");
    printf("-b, --bactive\t	Buscar e imprime la información del grupo del usuario ACTUAL\n");
    printf("-h, --help\t	Imprimir esta ayuda\n");

}

void allinfo()
 {
 // Declaracion de las estructuras que almacenaran la informarcion de un usuario y de un grupo
    struct passwd *pw;
    struct group *gr;

    // En el caso de que no se ha introducido ningún nombre de usuario,
    // por defecto en lgn almacenara el usuario que ha ejecutado este programa
    
    // OJO, NO USAR getlogin() porque no funciona en determinados sistemas, depende del 
    // terminal y unos ficheros asociados a el, es mejor coger el usuario actual a partir
    // de la variable de entorno USER (getenv("USER")) y pasarselo a getpwnam(). Modifique el programa para ello.
    //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO

    if ((pw = getpwnam(getenv("USER"))) == NULL)
    {
        printf("El usuario no existe y no se puede poner el login\n");
    }else{

		//Aqui ya se dispone de la estructura que contiene informacion del usuario
		printf("Nombre: %s\n", pw->pw_gecos); //No es lo mismo el nombre de usuario asociado a un login que el propio login
		printf("Login: %s\n", pw->pw_name);
		printf("Password: %s\n", pw->pw_passwd);
		printf("UID: %d\n", pw->pw_uid);
		printf("Home: %s\n", pw->pw_dir);
		printf("Número de grupo principal: %d\n", pw->pw_gid);

		// Obtenemos la estructura de información del grupo a través del número de grupo al que pertenece el usuario
		gr = getgrgid(pw->pw_gid);

		printf("Nombre del grupo principal: %s\n", gr->gr_name);
		printf("Contraseña del grupo principal: %s\n", gr->gr_passwd);
		printf("GUID del grupo principal: %i\n", gr->gr_gid);
		/*for(int i=0;i<sizeof(gr->gr_mem);i++){//preguntar a rafa
			printf("Integrante %d del grupo principal: %s\n",i, gr->gr_mem[i]);
		}*/
	}
}

void parteinfogrup(){

	struct passwd *pw;
    struct group *gr;

     if ((pw = getpwnam(getenv("USER"))) == NULL)
    {
        printf("El usuario no existe y no se puede poner el login\n");
    }else{

    	printf("Número de grupo principal: %d\n", pw->pw_gid);

		// Obtenemos la estructura de información del grupo a través del número de grupo al que pertenece el usuario
		gr = getgrgid(pw->pw_gid);

		//Se imprime el campo de la estructura que nos interesa
		printf("Nombre del grupo principal: %s\n", gr->gr_name);

	}
}

void allinfousuario(char const *uvalue){

	// Declaracion de las estructuras que almacenaran la informarcion de un usuario y de un grupo
    struct passwd *pw;
    struct group *gr;

    // En el caso de que no se ha introducido ningún nombre de usuario,
    // por defecto en lgn almacenara el usuario que ha ejecutado este programa
    
    // OJO, NO USAR getlogin() porque no funciona en determinados sistemas, depende del 
    // terminal y unos ficheros asociados a el, es mejor coger el usuario actual a partir
    // de la variable de entorno USER (getenv("USER")) y pasarselo a getpwnam(). Modifique el programa para ello.
    //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO

    if ((pw = getpwnam(uvalue)) == NULL)
    {
        printf("El usuario no existe\n");
    }else{

	//Aqui ya se dispone de la estructura que contiene informacion del usuario
	printf("Nombre: %s\n", pw->pw_gecos); //No es lo mismo el nombre de usuario asociado a un login que el propio login
	printf("Login: %s\n", pw->pw_name);
	printf("Password: %s\n", pw->pw_passwd);
	printf("UID: %d\n", pw->pw_uid);
	printf("Home: %s\n", pw->pw_dir);
	printf("Número de grupo principal: %d\n", pw->pw_gid);

	// Obtenemos la estructura de información del grupo a través del número de grupo al que pertenece el usuario
	gr = getgrgid(pw->pw_gid);

	//Se imprime el campo de la estructura que nos interesa
	printf("Nombre del grupo principal: %s\n", gr->gr_name);
	}

}

void allinfouid(char const *ivalue){

	// Declaracion de las estructuras que almacenaran la informarcion de un usuario y de un grupo
    struct passwd *pw;
    struct group *gr;
    uid_t uid=atoi(ivalue);

    // En el caso de que no se ha introducido ningún nombre de usuario,
    // por defecto en lgn almacenara el usuario que ha ejecutado este programa
    
    // OJO, NO USAR getlogin() porque no funciona en determinados sistemas, depende del 
    // terminal y unos ficheros asociados a el, es mejor coger el usuario actual a partir
    // de la variable de entorno USER (getenv("USER")) y pasarselo a getpwnam(). Modifique el programa para ello.
    //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO

    if ((pw = getpwuid(uid)) == NULL)
    {
        printf("El usuario no existe\n");
    }else{

	//Aqui ya se dispone de la estructura que contiene informacion del usuario
	printf("Nombre: %s\n", pw->pw_gecos); //No es lo mismo el nombre de usuario asociado a un login que el propio login
	printf("Login: %s\n", pw->pw_name);
	printf("Password: %s\n", pw->pw_passwd);
	printf("UID: %d\n", pw->pw_uid);
	printf("Home: %s\n", pw->pw_dir);
	printf("Número de grupo principal: %d\n", pw->pw_gid);

	// Obtenemos la estructura de información del grupo a través del número de grupo al que pertenece el usuario
	gr = getgrgid(pw->pw_gid);

	//Se imprime el campo de la estructura que nos interesa
	printf("Nombre del grupo principal: %s\n", gr->gr_name);
	}

}

void allinfonombregrup(char const *gvalue){

    struct group *gr;
    

    if ((gr = getgrnam(gvalue)) == NULL)
    {
        printf("El grupo no existe\n");
    }else{

		printf("Nombre del grupo principal: %s\n", gr->gr_name);
		printf("Contraseña del grupo principal: %s\n", gr->gr_passwd);
		printf("GUID del grupo principal: %i\n", gr->gr_gid);
		/*for(int i=0;i<sizeof(gr->gr_mem);i++){//preguntar a rafa
		printf("Integrante %d del grupo principal: %s\n",i, gr->gr_mem[i]);
		}*/

	}
}

void allinfogidgrup(char const *dvalue){

    struct group *gr;
    gid_t gid=atoi(dvalue);

    if ((gr = getgrgid(gid)) == NULL)
    {
        printf("El grupo no existe\n");
    }else{

		printf("Nombre del grupo principal: %s\n", gr->gr_name);
		printf("Contraseña del grupo principal: %s\n", gr->gr_passwd);
		printf("GUID del grupo principal: %i\n", gr->gr_gid);
		/*for(int i=0;i<sizeof(gr->gr_mem[]);i++){//preguntar a rafa
		printf("Integrante  del grupo principal: %s\n",i, gr->gr_mem[i]);
		}*/

	}
}

void allgroups(){

	FILE *f;

	if((f=fopen("/etc/group", "r"))!=NULL)
	{
		char cadena[100];
		char *aux = NULL;

		while(fgets(cadena, 100, f)!=NULL){

			aux=strtok(cadena,":");
			allinfonombregrup(aux);
		}
		
	}else{printf("Error al abrir el archivo\n");}

	fclose(f);

}

int main(int argc, char *argv[])
{
	int c;

	/* Estructura a utilizar por getoptlong */
	static struct option long_options[] =
	{
		/* "opcion", recibe o no un argumento, 0,
		   identificador de la opción */
		{"username", required_argument, 0, 'u'},
		{"useruid",  required_argument, 0, 'i'},
		{"groupname",required_argument, 0, 'g'},
		{"groupuid", required_argument, 0, 'd'},
		{"allgroups",no_argument, 0, 's'},
		{"allinfo",  no_argument, 0, 'a'},
		{"bactive",  no_argument, 0, 'b'},
		{"help",     no_argument, 0, 'h'},
		/* Necesario para indicar el final de las opciones */
		{0, 0, 0, 0}
	};

	int aflag=0;
	int bflag=0;
	int hflag=0;
	int sflag=0;
	char *dvalue = NULL;
	char *gvalue = NULL;
	char *ivalue = NULL;
	char *uvalue = NULL;
	int aux=0;

	int option_index = 0;


	opterr = 0;

	//en este caso no usamos getopt  while ((c = getopt (argc, argv, "abc:")) != -1) por que usamos la version extendida que es con getopt_long

	while ((c = getopt_long (argc, argv, "u:i:g:d:abhs", long_options, &option_index))!=-1){

		// El usuario ha terminado de introducir opciones 
		/*if (c == -1){
			break;
		}creo que no hace falta*/

		// Podemos observar qué pasa con las variables externas que va gestionando
        //   getopt() durante las sucesivas llamadas. 
        //   - optind: Indice del siguiente elemento a procesar del vector argv[]
        //   - optarg: recoge el valor del argumento obligario de una opcion.
        //   - optopt: recoge el valor de la opcion cuando es desconocida (?) o INCOMPLETA respecto a las opciones indicadas.  
		switch (c)
		{		
			case 'a':
				printf("Opción -a\n");
				aflag=1;
				if((dvalue==NULL)&&(gvalue==NULL)&&(ivalue==NULL)&&(uvalue==NULL)){allinfo();}
				else{printf("No se puede activar -a con -d, -u, -g, -i\n");}
				break;

			case 'b':
				printf("Opción -b\n");
				bflag=1;
				if((dvalue==NULL)&&(gvalue==NULL)&&(ivalue==NULL)&&(uvalue==NULL)){parteinfogrup();}
				else{printf("No se puede activar -b con -d, -u, -g, -i\n");}
				break;

			case 'h':
				printf("Opción -h\n");
				hflag=1;
				imprimir_uso();
				break;

			case 'd'://algo raro por culpa del is digit
				printf("Opción -d con valor '%s'\n", optarg);
				dvalue = optarg;
				if(isdigit(*dvalue)){
					if((gvalue==NULL)&&(aflag==0)&&(bflag==0)&&(uvalue==NULL)&&(ivalue==NULL)){allinfogidgrup(dvalue);}
					else{printf("La opcion -d es incompatible con -g, con -a y con -b\n");}
				}else{printf("No has introducido un numero correcto\n");}
				break;

			case 'g':
				printf("Opción -g con valor '%s'\n", optarg);
				gvalue = optarg;
				if((dvalue==NULL)&&(aflag==0)&&(bflag==0)&&(uvalue==NULL)&&(ivalue==NULL)){allinfonombregrup(gvalue);}
				else{printf("La opcion -g es incompatible con -d, con -a y con -b\n");}
				break;

			case 'i'://algo raro por culpa del is digit
				printf("Opción -i con valor '%s'\n", optarg);
				ivalue = optarg;
				if(isdigit(*ivalue)){
					if((uvalue==NULL)&&(aflag==0)&&(bflag==0)&&(gvalue==NULL)&&(dvalue==NULL)){allinfouid(ivalue);}
					else{printf("El valor -i es incompatible con -u, con -a y con -b\n");}
				}else{printf("No has introducido un numero correcto\n");}
				break;

			case 'u':
				printf("Opción -u con valor '%s'\n", optarg);
				uvalue = optarg;
				if((aflag==0)&&(ivalue==NULL)&&(bflag==0)&&(gvalue==NULL)&&(dvalue==NULL)){allinfousuario(uvalue);}
				else{printf("No es compatible la opción -u con -a ni -i ni con -b\n");}
				break;


			case 's':
				printf("Opción -s con valor '%s'\n", optarg);
				sflag = 1;
				allgroups();
				break;


			case '?':
				/* getopt_long ya imprime su mensaje de error, no es necesario hacer nada */
				/* Si queremos imprimir nuestros propios errores, debemos poner opterr=0,
				 y hacer algo como lo que se expone a continuacion. Pruebe a hacer sus propios errores.*/
				if (optopt == 'u' || optopt=='i'|| optopt=='g'|| optopt=='d'){//comprueba que no recibe un argumento
					fprintf (stderr, "La opción -%c requiere un argumento, la ayuda es la siguiente.\n", optopt);
					imprimir_uso();
					aux=1;

				}
				else if (isprint (optopt)){
					fprintf (stderr, "Opción desconocida `-%c', la ayuda es la siguiente.\n", optopt);
					imprimir_uso();
					aux=1;
				}
				else{
					fprintf (stderr, "Carácter de opción desconocido `\\x%x'.\n", optopt);
					imprimir_uso();
					aux=1;
				}
				break;

			default:

				abort ();
		}

	}

	/* Imprimir el resto de argumentos de la línea de comandos que no son opciones con "-" */
	if (optind < argc)
	{
		printf("Argumentos ARGV que no son opciones: ");
		while (optind < argc)
			printf("%s ", argv[optind++]);
		putchar ('\n');
		printf("La ayuda es la siguiente: \n");
		imprimir_uso();
	}

	if(aflag==0 && bflag==0 && hflag==0 && sflag==0 && dvalue == NULL && gvalue == NULL && ivalue == NULL && uvalue == NULL && aux==0){

	char *value = NULL;
	char *lang = "LANG";
	value = getenv(lang);
	 
	    if (strstr(value,"ES")){

	    	allinfo();

		}else{

			struct passwd *pw;
	   		struct group *gr;

			if ((pw = getpwnam(getenv("USER"))) == NULL)
		    {
		        printf("El usuario no existe y no se puede poner el login\n");

		    }else{		

			printf("Name: %s\n", pw->pw_gecos); //No es lo mismo el nombre de usuario asociado a un login que el propio login
			printf("Login: %s\n", pw->pw_name);
			printf("Password: %s\n", pw->pw_passwd);
			printf("UID: %d\n", pw->pw_uid);
			printf("Home: %s\n", pw->pw_dir);
			printf("Name of principal group: %d\n", pw->pw_gid);

			// Obtenemos la estructura de información del grupo a través del número de grupo al que pertenece el usuario
			gr = getgrgid(pw->pw_gid);

			printf("Name of principal group: %s\n", gr->gr_name);
			printf("Password of principal group: %s\n", gr->gr_passwd);
			printf("GUID of principal group: %i\n", gr->gr_gid);

			}

		}

	}

	return 0;
}