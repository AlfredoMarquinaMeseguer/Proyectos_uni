%{
#include "miniC.tab.h"
#include "listaCodigo.h"

int numErroresLex = 0;
%}
digito              [0-9]
letra               [a-zA-Z]
entero              {digito}+
panico              [^A-Za-z0-9();,=+\-{}_$"]

%option yylineno
%x COMENTARIO  
%x ERROR
%%
	/*reglas en regex		acción realizada, normalmente codigo que devuelven*/
	/* Blancos */
[ \n\t\r]+                                      ;
	/* Comentario: 1 línea */
"//"(.*)[\n]                                    ;
	/* Comentario: multilinea */
"/*"                                            BEGIN COMENTARIO;
	/* "/∗"([ˆ∗]|[∗]+[ˆ∗/])∗[∗]+"/" comentario multilinea */
	/* <<EOF>> para comentarios no cerrados */
<COMENTARIO>[*]+[/]                             BEGIN 0;
<COMENTARIO>[^*]*								;
<COMENTARIO>[*]+[^/*]*							;
void                                            return EMPIEZA;
var                                             return VAR;
const                                           return CONST;
if                                              return SI;
else                                            return SINO;
do                                           return HACER;
while                                           return MIENTRAS;
read                                            return LEER;
print                                           return ESCRIBIR;
(_|\$|{letra})({letra}|{digito}|_|\$) 			{if (yyleng < 32){yylval.lexema = strdup(yytext); return ID;}else{yymore(); BEGIN ERROR;}}
	/* {yylval.lexema = strdup(yytext); return ID;}*/
{entero}                                          {yylval.lexema = strdup(yytext);return NUM;}
	/* atoll, comprobar si es mayor que 2^31*/
\"([^\"\n]|\\.)*\"                              {yylval.lexema = strdup(yytext);return STRING;}
\"([^\"\n]|\\.)*
   /* {entero}[.]{entero}                             return REAL; */
"("                                             return A_PAREN;		
")"                                             return C_PAREN;
";"                                             return SEMICOLON;
","                                             return COMA;
"="                                             return ASIG_OP; 
"+"                                             return MAS_OP;
"-"                                             return MENOS_OP;
"*"                                             return MULT_OP;
"/"                                             return DIV_OP;
"{"                                             return A_LLAVE;
"}"                                             return C_LLAVE;
	// Se puede eliminar los banderines de ERROR
{panico}+	                                	{printf("Reconocido error en linea %d: %s.\n",yylineno, yytext); numErroresLex++;}
	/*<ERROR>{panico} 								{yymore();printf("Error Reconocido %s\n",yytext);}*/
	/*<ERROR>.                                      {yyless(yyleng-1);printf("Reconocido error en linea %d: %s.\n",yylineno, yytext); numErroresLex++; BEGIN 0;}
	.                                               {yymore(); BEGIN ERROR;}
			
%%
