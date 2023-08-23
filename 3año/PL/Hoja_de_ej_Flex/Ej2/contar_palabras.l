/***** Zona de las declaraciones o definiciones *****/
%{
  /*
      Descripción: el analizador léxico cuenta cuantas palabras hay y cuantas veces se repite la misma palabra
  */
  /*  Variables globales */
  int aux = 0;
  int rep_pal = 0;
  int cont = 0;
  char *palabra2=NULL;

  void buscar_palabra(char *palabra);
%}

/***** Zona de las reglas *****/
%%
[a-z|A-Z|Á|É|Í|Ó|Ú|á|é|í|ó|ú|ñ]+   {
  if(cont == 0){
      aux++;
    }else{
      buscar_palabra(yytext);
    }
  }
.|\n                          {;}
%%

/***** Zona de funciones auxiliares *****/

extern FILE *yyin;
int  main(int argc, char *argv[]){
palabra2 = argv[2];
 switch(argc)
  {
   case 1:  
            printf("contar_palabras.exe <entrada.txt> <palabra> \n");
            break;
   case 2:  yyin=fopen(argv[1],"r");
            if(!yyin) {
               printf("El fichero %s no existe o no puede ser abierto.\n", argv[1]);
               exit(-1);
            }
            cont = 0;
            yylex();
            if(aux==0){
              printf("No hay palabras en el fichero %s\n", argv[1]);
            }else if(aux==1){
              printf("%s contiene %d palabra.\n", argv[1], aux);
            }else{
              printf("%s contiene %d palabras.\n", argv[1], aux);
            }
            break;
   case 3:  yyin=fopen(argv[1],"r");
            if(!yyin) {
               printf("El fichero %s no existe o no puede ser abierto.\n", argv[1]);
               exit(-1);
            } 
            cont = 1;
            yylex();
            if(rep_pal==0){
              printf("La palabra <%s> no aparece en el fichero %s.\n", argv[2], argv[1]);
            }else if(rep_pal==1){
              printf("La palabra <%s> aparece %d vez en el fichero %s.\n", argv[2], rep_pal, argv[1]);
            }else{
              printf("La palabra <%s> aparece %d veces en el fichero %s.\n", argv[2], rep_pal, argv[1]);
            }          
            break;
  }
  return 0;
}

void buscar_palabra(char *palabra){
    if(strcmp(palabra2, palabra) == 0){
      rep_pal++;
    }
}
