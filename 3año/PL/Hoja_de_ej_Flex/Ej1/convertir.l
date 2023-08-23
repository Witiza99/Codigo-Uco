/***** Zona de las declaraciones o definiciones *****/
%{
  /*
      Descripción: el analizador léxico genera nuevo fichero donde los enteros pasan a float
  */
%}

/***** Zona de las reglas *****/
%%
[0-9]+([.][0-9]+)?   {fprintf(yyout,"%.1f", atof(yytext));}
.|\n                {fprintf(yyout,"%s", yytext);}
%%

/***** Zona de funciones auxiliares *****/

extern FILE *yyin, *yyout;
int  main(int argc, char *argv[])
{
 int contador=0;
 switch(argc)
  {
   case 1:  
            printf("convertir.exe <entrada.txt> <salida.txt> \n");
            contador++;
            break;
   case 2:  yyin=fopen(argv[1],"r");
            if(!yyin) {
               printf("El fichero %s no existe o no puede ser abierto.\n", argv[1]);
               contador++;
            }
            yyout=fopen("salida.txt","w"); 
            break;
   case 3:  yyin=fopen(argv[1],"r");
            if(!yyin) {
               printf("El fichero %s no existe o no puede ser abierto.\n", argv[1]);
               contador++;
            }
            yyout=fopen(argv[2],"w");
            break;
  }
  if(contador==0){
    yylex();
  }

  return 0;
}
