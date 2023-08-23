/***** Zona de las declaraciones o definiciones *****/
%{
  /*
      Descripción: el analizador léxico que reconocelos componentes léxicos de un programa escrito en pseudocódigo.
  */

  #include "ej3.h"   /* declaracion de los componentes lexicos o tokens */

%}

/* Definiciones regulares */

digito    [0-9]
espacio   [ \t\n]
espacios  {espacio}+
letra     [a-zA-ZáéíóúÁÉÍÓÚÑñ]

com_linea           #(.)*$

identificador       {letra}(({letra}+|{digito}+|\_){letra}|{digito})?
no_identificador    {{digito}(({letra}+|{digito}+|\_){letra}|{digito})?|{letra}({letra}+|{digito}+|\_)?{\_}|{letra}(({letra}+|{digito}+|[\_]{2,10000}){letra}|{digito})?}
numero              {digito}+(\.{digito}+)?(E[+\-]?{digito}+)?
no_numero           {digito}+(\.{digito}{0})?(E[+\-]?{digito}{0})?

menor_que           ({numero}|{identificador})"<"({numero}|{identificador})
menor_igual_que     ({numero}|{identificador})"<="({numero}|{identificador})
mayor_que           ({numero}|{identificador})">"({numero}|{identificador})  
mayor_igual_que     ({numero}|{identificador})">="({numero}|{identificador})
igual               ({numero}|{identificador})"=="({numero}|{identificador})
distinto            ({numero}|{identificador})"<>"({numero}|{identificador})
operador            {menor_que}|{mayor_igual_que}|{mayor_que}|{mayor_igual_que}|{distinto|igual}

negacion_logica     ".no."

fin_sentencia       \;
parentesis_I         \(
parentesis_D         \)

%x ESTADO_CADENA Q1 Q2 Q3 Q4 Q5

/***** Zona de las reglas *****/
%%

{espacios}   { /* no se hace nada */ ; }

"\("                      BEGIN(Q1);

<Q1>"*"                   BEGIN(Q2);
<Q1>[^*)]                 BEGIN(INITIAL);

<Q2>[^*\(]                ;
<Q2>"*"                   BEGIN(Q3);
<Q2>"\("                  BEGIN(Q4);


<Q3>"*"                   BEGIN(Q5); 
<Q3>[^*]                  ;

<Q4>[^*]                  BEGIN(Q2);
<Q4>"*"   { 
                          printf("\nError: comentario anidado\n");

                          BEGIN(INITIAL);
      }

<Q5>"\)"   { 
                          printf("\n Comentario: %s --> token %d\n",yytext,COMENTARIO);

                          BEGIN(INITIAL);
      }
<Q5>[^\)]                 BEGIN(Q2);

{com_linea}                 {printf("\n Comentario: %s --> token %d\n",yytext,COMENTARIO);}

(?i:si)                        {printf("\n Palabra reservada: %s --> token %d\n", yytext,si);}

{identificador}           {printf("\n Identificador: %s --> token %d\n", yytext, id);}

{numero}                  {printf("\n Numero: %s --> token %d\n", yytext, num);}

"'"                       {
                           /* Se activa el reconocimiento de la cadena */
                            BEGIN ESTADO_CADENA; 
                          }
<ESTADO_CADENA>"'"        { /* Fin de la cadena: se vuelve al estado por defecto */
                            BEGIN 0; 
                            yytext[yyleng-1]='\0';
                            printf("\t Cadena: %s  --> token %d\n",yytext, cad);
                          }      
<ESTADO_CADENA>"\\\'"     {yymore();}
<ESTADO_CADENA>.          {yymore();}

":="                      {printf("\n Operador de asignacion: %s --> token %d\n",yytext,asig);}

"+"                       {printf("\n Operador aritmetico: %s --> token %d\n",yytext,sum);}

"-"                       {printf("\n Operador aritmetico: %s --> token %d\n",yytext,res);}

"*"                       {printf("\n Operador aritmetico: %s --> token %d\n",yytext,prod);}

"/"                       {printf("\n Operador aritmetico: %s --> token %d\n",yytext,div);}

"__mod"                   {printf("\n Operador aritmetico: %s --> token %d\n",yytext,mod);}

"**"                      {printf("\n Operador aritmetico: %s --> token %d\n",yytext,pot);}

"||"                      {printf("\n Operador alfanumerico: %s --> token %d\n",yytext,concat);}

{menor_que}                 {printf("\n Operador relacional de numeros y cadenas: %s --> token %d\n",yytext,MENOR_QUE);}



%%

/***** Zona de funciones auxiliares *****/

extern FILE *yyin;
int  main(int argc, char *argv[]){
 switch(argc)
  {
   case 1:  
            printf("ej3.exe <entrada.txt> \n");
            break;
   case 2:  yyin=fopen(argv[1],"r");
            if(!yyin) {
               printf("El fichero %s no existe o no puede ser abierto.\n", argv[1]);
               exit(-1);
            }
            yylex();
            break;
  }
  return 0;
}