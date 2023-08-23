/***** Zona de las declaraciones o definiciones *****/
%{
  /*
      Descripción: el analizador léxico que permite varias funciones.
  */

  #include <string.h>

  /*  Variables globales */
  int aux=0;
  int rep_pal = 0;
  int cont = 0;
  char *palabra2=NULL;
  char *palabra3=NULL;
  char *palabra4=NULL;
  char *palabra5=NULL;
  char *palabra_Aux=NULL;

  void buscar_palabra(char *palabra);
  int verificar( char *cadena, char *subcadena );
%}

/*Expresiones regulares*/

espacio   [ \t\n]
digito    [0-9]
letra     [a-zA-ZáéíóúÁÉÍÓÚÑñ]



/***** Zona de las reglas *****/
%%

(\n)                                                                 {cont++;}

{letra}{letra}{digito}+{espacio}{digito}+{espacio}{digito}+          {buscar_palabra(yytext);}

(.)                                                                  {;}


%%

/***** Zona de funciones auxiliares *****/
extern FILE *yyin;
int  main(int argc, char *argv[]){
palabra2 = argv[2];
palabra3 = argv[3];
palabra4 = argv[4];
char *cad = NULL;
 switch(argc)
  {
  case 1:  
            printf("cuentas.exe <fichero.txt> <pais> <entidad bancaria> <oficina>\n");
            break;
  case 2: 
            yyin=fopen(argv[1],"r");
            if(!yyin) {
               printf("El fichero %s no existe o no puede ser abierto.\n", argv[1]);
               exit(-1);
            }
            aux=1;
            yylex();
            printf("Número total de cuentas: %d.\n", cont);
            break;
  case 3:  
            yyin=fopen(argv[1],"r");
            if(!yyin) {
               printf("El fichero %s no existe o no puede ser abierto.\n", argv[1]);
               exit(-1);
            } 
            palabra5=palabra2;
            yylex();
            printf("Numero total de cuentas en un pais(%s): %d\n", palabra2, rep_pal);
            break;
  case 4:  
            yyin=fopen(argv[1],"r");
            if(!yyin) {
               printf("El fichero %s no existe o no puede ser abierto.\n", argv[1]);
               exit(-1);
            }
            cad=(char *) malloc(2 + strlen(palabra2) + strlen(palabra3));
            strcpy(cad, palabra2);
            strcat(cad, " ");
            strcat(cad, palabra3);
            palabra5=cad;
            yylex();
            printf("Numero total de cuentas en un pais (%s) en una entidad bancaria (%s): %d\n", palabra2, palabra3, rep_pal);             
            break;
  case 5:  
            yyin=fopen(argv[1],"r");
            if(!yyin) {
               printf("El fichero %s no existe o no puede ser abierto.\n", argv[1]);
               exit(-1);
            }
            cad=(char *) malloc(3 + strlen(palabra2) + strlen(palabra3) + strlen(palabra4));
            strcpy(cad, palabra2);
            strcat(cad, " ");
            strcat(cad, palabra3);
            strcat(cad, " ");
            strcat(cad, palabra4);
            palabra5=cad;
            yylex();
            printf("Numero total de cuentas en un pais (%s) en una entidad bancaria (%s) en una oficina (%s): %d\n", palabra2, palabra3, palabra4,rep_pal);             
            break;
  }
  return 0;
}

void buscar_palabra(char *palabra){
  if(aux==0){
    palabra_Aux=(char *) malloc(strlen(palabra)-1);
    palabra_Aux[0]=palabra[0];
    palabra_Aux[1]=palabra[1];
    for(int i=4;i<(strlen(palabra));i++){
      palabra_Aux[i-2]=palabra[i];
    }
    if(verificar(palabra_Aux, palabra5) == 1){
      rep_pal++;
    }
  }  
} 

int verificar( char *cadena, char *subcadena )
{
   char *tmp = cadena;
   char *pdest;
 
   pdest = strstr( tmp, subcadena );
   if( pdest ) return 1;

   return 0;
}