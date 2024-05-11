%{
#include <limits.h>
#include "listaCodigo.h"
#include "miniC.tab.h"

int numErroresLex = 0;
%}
digito              [0-9]
letra               [a-zA-Z]
entero              {digito}+
panico              [^A-Za-z0-9();,=+/*\-{}_"]

%option yylineno
%x COMENTARIO  
%x ERROR
%%
	/*reglas en regex                       acción realizada, normalmente codigo que devuelven*/
[ \n\t\r]+                                      ;
"//"(.*)[\n]                                    ;
"/*"                                            BEGIN COMENTARIO;
<COMENTARIO>[*]+[/]                             BEGIN 0;
<COMENTARIO><<EOF>>                             BEGIN 0;
<COMENTARIO>[^*]*                               ;
<COMENTARIO>[*]+[^/*]*                          ;
        	/* "/∗"([ˆ∗]|[∗]+[ˆ∗/])∗[∗]+"/" comentario multilinea */
void                                            return EMPIEZA;
var                                             return VAR;
const                                           return CONST;
if                                              return SI;
else                                            return SINO;
do                                              return HACER;
while                                           return MIENTRAS;
read                                            return LEER;
print                                           return ESCRIBIR;
(_|{letra})({letra}|{digito}|_)*                {if (yyleng < 32){yylval.lexema = strdup(yytext);}else{yymore(); BEGIN ERROR;}return ID;}
{entero}                                        {if (atoll(yytext) < INT_MAX){yylval.lexema = strdup(yytext);}else{yymore(); BEGIN ERROR;}return NUM;}
\"([^\"\n]|\\.)*(\"|\n)                         {yylval.lexema = strdup(yytext);return STRING;}
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

{panico}+                                       {printf("Reconocido error en linea %d: %s.\n",yylineno, yytext); numErroresLex++;}
<ERROR>{panico}+                                {yymore();}
<ERROR>.                                        {yyless(yyleng-1);printf("Reconocido error en linea %d: %s.\n",yylineno, yytext); numErroresLex++; BEGIN 0;}
%%
