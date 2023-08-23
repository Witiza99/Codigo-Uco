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
letra   [a-zA-ZÁÉÍÓÚÑñ]

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
operador            {menor_que|mayor_igual_que|mayor_que|mayor_igual_que|distinto|igual}

com_linea           {\#[.]*$\n}

negacion_logica     ".no."{operador}
conjuncion_logica   {operador|negacion_logica}".y."{operador|negacion_logica}
disyuncion_logica   {operador|negacion_logica}".o."{operador|negacion_logica}

fin_sentencia       {\;}
paretesis_I         {\(}
paretesis_D         {\)}

simbolo             {operador|negacion_logica|conjuncion_logica|disyuncion_logica}
no_simbolo          {[^{numero}]&&[^identificador]&&[^simbolo]}


/*cadena    "'"([^']|"\\\'")*"'"*/

%x ESTADO_CADENA Q1 Q2 Q3 Q4

/***** Zona de las reglas *****/
%%

{espacios}   { /* no se hace nada */ ; }

si                        {printf("\n Palabra reservada: %s --> token %d\n", yytext,si);}
SI                        {printf("\n Palabra reservada: %s --> token %d\n", yytext,si);}

entonces                  {printf("\n Palabra reservada: %s --> token %d\n", yytext,entonces);}
ENTONCES                  {printf("\n Palabra reservada: %s --> token %d\n", yytext,entonces);}

si_no                     {printf("\n Palabra reservada: %s --> token %d\n", yytext,si_no);}
SI_NO                     {printf("\n Palabra reservada: %s --> token %d\n", yytext,si_no);}

inicio                    {printf("\n Palabra reservada: %s --> token %d\n", yytext,inicio);}
INICIO                    {printf("\n Palabra reservada: %s --> token %d\n", yytext,inicio);}

fin                       {printf("\n Palabra reservada: %s --> token %d\n", yytext,fin);}
FIN                       {printf("\n Palabra reservada: %s --> token %d\n", yytext,fin);}

leer                      {printf("\n Palabra reservada: %s --> token %d\n", yytext,leer);}
LEER                      {printf("\n Palabra reservada: %s --> token %d\n", yytext,leer);}

escribir                  {printf("\n Palabra reservada: %s --> token %d\n", yytext,escribir);}
ESCRIBIR                  {printf("\n Palabra reservada: %s --> token %d\n", yytext,escribir);}

fin_si                    {printf("\n Palabra reservada: %s --> token %d\n", yytext,fin_si);}
FIN_SI                    {printf("\n Palabra reservada: %s --> token %d\n", yytext,fin_si);}

mientras                  {printf("\n Palabra reservada: %s --> token %d\n", yytext,mientras);}
MIENTRAS                  {printf("\n Palabra reservada: %s --> token %d\n", yytext,mientras);}

hacer                     {printf("\n Palabra reservada: %s --> token %d\n", yytext,hacer);}
HACER                     {printf("\n Palabra reservada: %s --> token %d\n", yytext,hacer);}

fin_mientras              {printf("\n Palabra reservada: %s --> token %d\n", yytext,fin_mientras);}
FIN_MIENTRAS              {printf("\n Palabra reservada: %s --> token %d\n", yytext,fin_mientras);}

repetir                   {printf("\n Palabra reservada: %s --> token %d\n", yytext,repetir);}
REPETIR                   {printf("\n Palabra reservada: %s --> token %d\n", yytext,repetir);}

hasta_que                 {printf("\n Palabra reservada: %s --> token %d\n", yytext,hasta_que);}
HASTA_QUE                 {printf("\n Palabra reservada: %s --> token %d\n", yytext,hasta_que);}

para                      {printf("\n Palabra reservada: %s --> token %d\n", yytext,para);}
PARA                      {printf("\n Palabra reservada: %s --> token %d\n", yytext,para);}

desde                     {printf("\n Palabra reservada: %s --> token %d\n", yytext,desde);}
DESDE                     {printf("\n Palabra reservada: %s --> token %d\n", yytext,desde);}

paso                      {printf("\n Palabra reservada: %s --> token %d\n", yytext,paso);}
PASO                      {printf("\n Palabra reservada: %s --> token %d\n", yytext,paso);}

fin_para                  {printf("\n Palabra reservada: %s --> token %d\n", yytext,fin_para);}
FIN_PARA                  {printf("\n Palabra reservada: %s --> token %d\n", yytext,fin_para);}

hasta                     {printf("\n Palabra reservada: %s --> token %d\n", yytext,hasta);}
HASTA                     {printf("\n Palabra reservada: %s --> token %d\n", yytext,hasta);}

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

menor_que                 {printf("\n Operador relacional de numeros y cadenas: %s --> token %d\n",yytext,MENOR_QUE);}

menor_igual_que           {printf("\n Operador relacional de numeros y cadenas: %s --> token %d\n",yytext,MENOR_IGUAL_QUE);}

mayor_que                 {printf("\n Operador relacional de numeros y cadenas: %s --> token %d\n",yytext,MAYOR_QUE);}

mayor_igual_que           {printf("\n Operador relacional de numeros y cadenas: %s --> token %d\n",yytext,MAYOR_IGUAL_QUE);}

igual                     {printf("\n Operador relacional de numeros y cadenas: %s --> token %d\n",yytext,IGUAL);}

distinto                  {printf("\n Operador relacional de numeros y cadenas: %s --> token %d\n",yytext,DISTINTO);}

negacion_logica           {printf("\n Operador logico: %s --> token %d\n",yytext,NEG_LOGICA);}

conjuncion_logica         {printf("\n Operador logico: %s --> token %d\n",yytext,CONJ_LOGICA);}

disyuncion_logica         {printf("\n Operador logico: %s --> token %d\n",yytext,DISY_LOGICA);}


"\("     BEGIN(Q1); /* change to Q1 */

<Q1>"*"   BEGIN(Q2); /* change to Q2 */

<Q2>[^*/]   ;        /* stay in Q2 */
<Q2>"*"   BEGIN(Q3); /* change to Q3 */
<Q2>"("   BEGIN(Q4); /* change to Q4 */


<Q3>"*"   ;        /* stay in Q3 */
<Q3>[^*/] BEGIN(Q2); /* change to Q2 */
<Q3>")"   { 
        printf("\n Comentario: %s --> token %d\n",yytext,COMENTARIO);

        BEGIN(INITIAL); /* change to INITIAL: default state */
      }

<Q4>[^*]  BEGIN(Q2); /* change to Q2 */
<Q4>"*"   { 
        printf("\nError: comentario anidado\n");

        BEGIN(INITIAL); /* change to INITIAL: default state */
      }
com_linea                  {printf("\n Comentario: %s --> token %d\n",yytext,COMENTARIO);}


fin_sentencia              {printf("\n Componentes lexicos: %s --> token %d\n",yytext,FIN_SENT);}
paretesis_I                {printf("\n Componentes lexicos: %s --> token %d\n",yytext,PARENTESIS_IZQ);}
paretesis_D                {printf("\n Componentes lexicos: %s --> token %d\n",yytext,PARENTESIS_DER);}


no_simbolo                 {
                            if(yyleng==1){
                              printf("\n Utilizacion de simbolos no permitidos: %s --> simbolo no permitido\n",yytext);
                            }else{
                              printf("\n Utilizacion de simbolos no permitidos: %s --> simbolos no permitidos\n",yytext);
                            }
                          ;}

no_numero                   {printf("\n Error numerico: %s --> numero mal escrito\n",yytext);}

no_identificador            {printf("\n Error en identificador: %s --> identificador mal escrito\n",yytext);}

.                           {printf("\n Error en identificador: %s --> identificador mal escrito\n",yytext);}

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