%{
#include "lexico1.h"
%}
digito              [0-9]
letra               [a-zA-Z]
entero              {digito}+

%option yylineno

%%
[ \n\t\r]+                                    ;
"//"(.*)[\n]                                ;
main                                        return BEGINN;
    /*end                                         return END;*/
    /*read                                        return READ;*/
print                                       return WRITE;
("$"|_|{letra})({letra}|{digito}|_|"$")*      return ID;
{entero}                                    return INTLITERAL;
"("                                         return LPAREN;		
")"                                         return RPAREN;
"{"                                         return L_LLAVE;
"}"                                         return R_LLAVE;
";"                                         return SEMICOLON;
","                                         return COMMA;
"="                                         return ASSIGNOP;
"+"                                         return PLUSOP;
"-"                                         return MINUSOP;
{entero}[.]{entero}                         return REALLIT;
.                                           printf("Error en caracter %s en la linea %d\n",yytext, yylineno);
%%