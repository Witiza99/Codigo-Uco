/*

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
"/" 		BEGIN(Q1); /* change to Q1 */

<Q1>"*" 	BEGIN(Q2); /* change to Q2 */

<Q2>[^*/] 	; 		   /* stay in Q2 */
<Q2>"*" 	BEGIN(Q3); /* change to Q3 */
<Q2>"/" 	BEGIN(Q4); /* change to Q4 */


<Q3>"*" 	; 		   /* stay in Q3 */
<Q3>[^*/]	BEGIN(Q2); /* change to Q2 */
<Q3>"/"		{ 
				printf("\nComentario reconocido\n");

				BEGIN(INITIAL); /* change to INITIAL: default state */
			}

<Q4>[^*] 	BEGIN(Q2); /* change to Q2 */
<Q4>"*" 	{ 
				printf("\nError: comentario anidado\n");

				BEGIN(INITIAL); /* change to INITIAL: default state */
			}

(.|n)	ECHO;
%% 

