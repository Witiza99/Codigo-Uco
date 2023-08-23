/*
Autómata que reconoce cadenas delimitadas por comillas simples, pero no las muestra

Adaptado de 
A [f]lex tutorial (Powerpoint slides) 

http://www2.cs.arizona.edu/classes/cs453/fall14/DOCS/lex%20tutorial.ppt

En 
http://www2.cs.arizona.edu/classes/cs453/fall14/DOCS/index.html

*/

/***** Zona de las declaraciones o definiciones *****/
%{

%}

/* ESTADOS DE FLEX: estados del autómata */
%x Q1 Q2 Q3 Q4

%%
"'" 		BEGIN(Q1); /* change to Q1 */

<Q1>[^'\\] 	; 		   /* stay in Q1 */
<Q1>"\\" 	BEGIN(Q2); /* change to Q2 */
<Q1>"'" 	{ 
			    printf("\nCadena reconocida\n");

				BEGIN(INITIAL); /* change to INITIAL: default state */
			}

<Q2>[^\\] 	BEGIN(Q1); /* change to 1 */
<Q2>"/" 	; 		   /* stay in Q2 */


(.|n)		ECHO;
%% 

