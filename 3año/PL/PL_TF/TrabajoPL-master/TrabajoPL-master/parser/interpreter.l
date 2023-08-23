/*!
  \file interpreter.l
  \brief Lexical or scanner file
*/
%{
#include <iostream>
#include <string.h>
/*********************/
/* NEW in example 4 */
/* atof */
#include <stdlib.h>
/*********************/

/* Macros for the screen */
#include "../includes/macros.hpp"

/*********************/
/*
  NEW in example 16
  AST class
  IMPORTANT: must be written before interpreter.tab.h
*/
#include "../ast/ast.hpp"
/*********************/

/*  interpreter.tab.h contains the numeric values of the tokens produced by the parser */
#include "interpreter.tab.h"

/********************/
/* NEW in example 3 */
#include "../error/error.hpp"
/********************/


/*********************************************/
/* NEW in example 7 */
/* Table of symbols */
#include "../table/table.hpp"

#include "../table/numericVariable.hpp"


extern lp::Table table; //!< External Table of Symbols
/*********************************************/

extern int lineNumber; //!< External line counter

int stringSize = 0;

char* string;

%}


/*! \name REGULAR DEFINITIONS  */

DIGIT  [0-9]

LETTER [a-zA-Z]

NUMBER1 {DIGIT}+(\.{DIGIT}+)?

NUMBER2 {DIGIT}(\.{DIGIT}+)?(E[+-]?{DIGIT}+)?

BADNUMBER {DIGIT}+(\.)(E[+-]?{DIGIT}+)?|{DIGIT}+(\.{DIGIT}+)?(E[+-]?)({DIGIT}+)?|{DIGIT}+(\.)(E[+-]?)

IDENTIFIER  {LETTER}({LETTER}+|{DIGIT}+|(\_{LETTER})+|(\_{DIGIT})+)*

BADIDENTIFIER ({LETTER}|\_|{DIGIT})({LETTER}+|{DIGIT}+|(\_)+)+({LETTER}|{DIGIT}|\_)?

COM_LINE           @(.)*$



/* NEW in example 3 */
/* STATE  */
%x ERROR ESTADO_CADENA Q1 Q2

/*! \name REGULAR EXPRESSIONS  */
%%

[ \t] 	{ ; }    /* skip white space and tabular */

\n      {
			/* Line counter */
           	lineNumber++;

			/* MODIFIED in example 3 */
			/* COMMENTED in example 5 */
        	/* return NEWLINE; */
        }



"'"                       {
                           /* Se activa el reconocimiento de la cadena */
                            BEGIN ESTADO_CADENA;
                          }
<ESTADO_CADENA>"'"        { /* Fin de la cadena: se vuelve al estado por defecto */
                            BEGIN 0;
                            yytext[yyleng-1]='\0';
                            yylval.string = yytext;
                            return STRING;
                          }
<ESTADO_CADENA>"\\\'"   {yymore();}
<ESTADO_CADENA>.        {yymore();}

"#"                      {
                            yymore();
                            BEGIN(Q1);
                          }
<Q1>[^#]                 {
                            yymore();
                          }

<Q1>"#"                  {
                          BEGIN 0;
                          }



";"		{
			/* NEW in example 5 */
			return SEMICOLON;
		}


","		{
			/* NEW in example 14 */
			return COMMA;
		}

{NUMBER1}|{NUMBER2}  {
					  /* MODIFIED in example 4 */
					  /* Conversion of type and sending of the numerical value to the parser */
					   yylval.number = atof(yytext);

                       return NUMBER;
                      }

{BADNUMBER}  {
                warning("Lexical error: bad number format", yytext);
              }

{IDENTIFIER}   		 {
						 /* NEW in example 7 */
						 std::string identifier(yytext);
             for (int i = 0; i < identifier.size(); i++) {
               identifier[i] = tolower(identifier[i]);
             }

						/*
                          strdup() function returns a pointer to a new string
                          which  is a duplicate of the string yytext
                        */
						  yylval.identifier =  strdup(identifier.c_str());


						/* If the identifier is not in the table of symbols then it is inserted */
						 if (table.lookupSymbol(identifier) == false)
							{
								/*
								 The identifier is inserted into the symbol table
								 as undefined Variable with value 0.0
								*/
								lp::NumericVariable *n = new lp::NumericVariable(identifier,VARIABLE,UNDEFINED,0.0);

								/* A pointer to the new NumericVariable is inserted into the table of symbols */
								table.installSymbol(n);

								return VARIABLE;
							}

						/* MODIFIED in example 11 */
						/*
							If the identifier is in the table of symbols then its token is returned
								The identifier can be a variable or a numeric constant
						*/
						else
							{
								lp::Symbol	*s = table.getSymbol(identifier);

/*
								std::cout << "lex: "<< s->getName()
										  << "token " << s->getToken()
  										  << std::endl;
*/

								/*  If the identifier is in the table then its token is returned  */
								return s->getToken();
							}
}



{BADIDENTIFIER} {
                  warning("Lexical error: bad identifier", yytext);
                }

{COM_LINE} { ; }


"-"		{ return MINUS;  } 			/* NEW in example 3 */
"+"		{ return PLUS;   } 			/* NEW in example 3 */

"*"	    { return MULTIPLICATION; } 	/* NEW in example 3 */
"/"     { return DIVISION; } 		/* NEW in example 3 */

"("     { return LPAREN; } 			/* NEW in example 3 */
")"	    { return RPAREN; } 			/* NEW in example 3 */


"**"	    { return POWER; }			/* NEW in example 5 */

"="	{ return EQUAL; }			/* NEW in example 15 */

":=" 	{ return ASSIGNMENT; }		/* NEW in example 7 */

"<>"	{ return NOT_EQUAL; }		/* NEW in example 15 */

">="	{ return GREATER_OR_EQUAL; }/* NEW in example 15 */

"<="	{ return LESS_OR_EQUAL; }	/* NEW in example 15 */

">"		{ return GREATER_THAN; }	/* NEW in example 15 */

"<"		{ return LESS_THAN; }		/* NEW in example 15 */

"||"  { return CONCAT; } /* NEW in final work */

<<EOF>> { /* The interpreter finishes when finds the end of file character */
		/*  PLACE(24,10);
	  	  std::cout <<  BICYAN;
	   	  std::cout <<  ">>>>>>> End of file <<<<<<<";
	 	  std::cout << std::endl;
	   	  std::cout << RESET;
		  PLACE(25,1);
		*/
	  	  return 0;
	}


.								{
									/* Any other character */
									/* MODIFIIED in example 3 */
									/* Change to error state */
									BEGIN(ERROR);

									/*
										The current value of yytext
										will be concatenated with the next character
									*/
									yymore();
								}

<ERROR>[^0-9+\-*/()\^% \t\n\;a-zA-Z=<>!&]	{ /* MODIFIED in examples 5, 7, 15 */
								  /* NEW in example 3 */
								  /*
									The current value of yytext
									will be concatenated with the next character
								  */
									yymore();
								}

<ERROR>(.|\n)                {
								/* NEW in example 3 */
								/* Rewind one position */
								yyless(yyleng-1);

								/* Display the error message */
								warning("Lexical error: unknown symbol", yytext);

								/* Restore the initial state */
   								BEGIN(INITIAL);
							}
%%
