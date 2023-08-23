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
/* {letra|(\_)}(({letra}*|{digito}*|(\_){2,10000}){letra}|{digito|(\_)})? */
identificador       {letra}({letra}+|{digito}+|(\_{letra})+|(\_{numero})+)*
no_identificador    ({letra}|\_)({letra}+|{digito}+|(\_)+)+({letra}|{digito}|\_)  
numero              {digito}+(\.{digito}+)?(E[+\-]?{digito}+)?
no_numero           {digito}+(\.)(E[+\-]?{digito}+)?|{digito}+(\.{digito}+)?(E[+\-]?)|{digito}+(\.)(E[+\-]?)


/*
si uso estas formas no funciona por que las reglas de numero e identificador cogen la palabra antes y nunca entran aqui
igual               {numero}|{identificador}(==){numero}|{identificador}
distinto            ({numero}|{identificador})(<>)({numero}|{identificador})
menor_que           {numero}|{identificador}"<"(numero}|{identificador}
menor_igual_que     {numero}|{identificador}"<="{numero}|{identificador}
mayor_que           {numero}|{identificador}">"(numero}|{identificador}  
mayor_igual_que     {numero}|{identificador}">="{numero}|{identificador}
*/

igual               (==)
distinto            (<>)
menor_que           (<)
menor_igual_que     (<=)
mayor_que           (>)
mayor_igual_que     (>=)

/*
me ocurre lo mismo que en el caso anterior
operador            {menor_que}|{mayor_igual_que}|{mayor_que}|{mayor_igual_que}|{distinto|igual}

negacion_logica     ".no."{operador}
conjuncion_logica   {operador|negacion_logica}".y."{operador|negacion_logica}
disyuncion_logica   {operador|negacion_logica}".o."{operador|negacion_logica}
*/

negacion_logica     (\.no\.)
conjuncion_logica   (\.y\.)
disyuncion_logica   (\.o\.)

fin_sentencia       (\;)
/*paretesis_I       (\() */
paretesis_D         (\))

simbolo             {operador|negacion_logica|conjuncion_logica|disyuncion_logica}
no_simbolo          [^{simbolo}]


/*cadena    "'"([^']|"\\\'")*"'"*/

%x ESTADO_CADENA Q1 Q2 Q4 Q5 Q6 Q7

/***** Zona de las reglas *****/
%%

{espacios}   { /* no se hace nada */ ; }


"\("                      {
                            yymore();
                            BEGIN(Q1);
                          }
<Q1>"*"                   {
                            yymore();
                            BEGIN(Q2);
                          }
<Q1>[^*)]                 {
                            yyless(yyleng-1);
                            printf("\n Componentes lexicos: %s --> token %d\n",yytext,PARENTESIS_IZQ);   
                            BEGIN(INITIAL);
                          }
<Q2>[^*\(]                  yymore();
<Q2>"*"                   {
                            yymore();
                            BEGIN(Q5);
                          }
<Q2>"\("                  {
                            yymore();
                            BEGIN(Q4);
                          }
<Q4>[^*]                  {
                            yymore();
                            BEGIN(Q2);
                          }
<Q4>"*"                   { 
                          printf("\n Error: comentario anidado:%s\n", yytext);
                          BEGIN(Q6);
                          }
<Q5>"\)"                  { 
                          printf("\n Comentario: %s --> token %d\n",yytext,COMENTARIO);
                          BEGIN(INITIAL);
                          }
<Q5>[^\)]                 {
                            yymore();
                            BEGIN(Q2);
                          }
<Q6>"*\)"                 BEGIN(Q7);
<Q6>[^*\)]                ;

<Q7>"*\)"                 BEGIN(INITIAL);
<Q7>[^*\)]                ;


{com_linea}               {printf("\n Comentario: %s --> token %d\n",yytext,COMENTARIO);}

(?i:si)                   {printf("\n Palabra reservada: %s --> token %d\n", yytext,si);}
(?i:entonces)             {printf("\n Palabra reservada: %s --> token %d\n", yytext,entonces);}
(?i:si_no)                {printf("\n Palabra reservada: %s --> token %d\n", yytext,si_no);}
(?i:inicio)               {printf("\n Palabra reservada: %s --> token %d\n", yytext,inicio);}
(?i:fin)                  {printf("\n Palabra reservada: %s --> token %d\n", yytext,fin);}
(?i:leer)                 {printf("\n Palabra reservada: %s --> token %d\n", yytext,leer);}
(?i:escribir)             {printf("\n Palabra reservada: %s --> token %d\n", yytext,escribir);}
(?i:fin_si)               {printf("\n Palabra reservada: %s --> token %d\n", yytext,fin_si);}
(?i:mientras)             {printf("\n Palabra reservada: %s --> token %d\n", yytext,mientras);}
(?i:hacer)                {printf("\n Palabra reservada: %s --> token %d\n", yytext,hacer);}
(?i:fin_mientras)         {printf("\n Palabra reservada: %s --> token %d\n", yytext,fin_mientras);}
(?i:repetir)              {printf("\n Palabra reservada: %s --> token %d\n", yytext,repetir);}
(?i:hasta_que)            {printf("\n Palabra reservada: %s --> token %d\n", yytext,hasta_que);}
(?i:para)                 {printf("\n Palabra reservada: %s --> token %d\n", yytext,para);}
(?i:desde)                {printf("\n Palabra reservada: %s --> token %d\n", yytext,desde);}
(?i:paso)                 {printf("\n Palabra reservada: %s --> token %d\n", yytext,paso);}
(?i:fin_para)             {printf("\n Palabra reservada: %s --> token %d\n", yytext,fin_para);}
(?i:hasta)                {printf("\n Palabra reservada: %s --> token %d\n", yytext,hasta);}

{identificador}           {printf("\n Identificador: %s --> token %d\n", yytext, id);}

{numero}                  {printf("\n Numero: %s --> token %d\n", yytext, num);}

"'"                       {
                           /* Se activa el reconocimiento de la cadena */
                            BEGIN ESTADO_CADENA; 
                          }
<ESTADO_CADENA>"'"        { /* Fin de la cadena: se vuelve al estado por defecto */
                            BEGIN 0; 
                            yytext[yyleng-1]='\0';
                            printf("\n Cadena: %s  --> token %d\n",yytext, cad);
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


{igual}                   {printf("\n Operador relacional de numeros y cadenas: %s --> token %d\n",yytext,IGUALH);}

{distinto}                {printf("\n Operador relacional de numeros y cadenas: %s --> token %d\n",yytext,DISTINTOH);}

{menor_que}               {printf("\n Operador relacional de numeros y cadenas: %s --> token %d\n",yytext,MENOR_QUE);}

{menor_igual_que}         {printf("\n Operador relacional de numeros y cadenas: %s --> token %d\n",yytext,MENOR_IGUAL_QUE);}

{mayor_que}               {printf("\n Operador relacional de numeros y cadenas: %s --> token %d\n",yytext,MAYOR_QUE);}

{mayor_igual_que}         {printf("\n Operador relacional de numeros y cadenas: %s --> token %d\n",yytext,MAYOR_IGUAL_QUE);}

{fin_sentencia}           {printf("\n Componentes lexicos: %s --> token %d\n",yytext,FIN_SENT);}
{paretesis_D}             {printf("\n Componentes lexicos: %s --> token %d\n",yytext,PARENTESIS_DER);}


{negacion_logica}         {printf("\n Operador logico: %s --> token %d\n",yytext,NEG_LOGICA);}

{conjuncion_logica}       {printf("\n Operador logico: %s --> token %d\n",yytext,CONJ_LOGICA);}

{disyuncion_logica}       {printf("\n Operador logico: %s --> token %d\n",yytext,DISY_LOGICA);}


{no_identificador}        {printf("\n Error en identificador: %s --> identificador mal escrito\n",yytext);}
{no_numero}               {printf("\n Error numerico: %s --> numero mal escrito\n",yytext);}
{no_simbolo}              {
                            if(yyleng==1){
                              printf("\n Utilizacion de simbolos no permitidos: %s --> simbolo no permitido\n",yytext);
                            }else{
                              printf("\n Utilizacion de simbolos no permitidos: %s --> simbolos no permitidos\n",yytext);
                            }
                          }

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