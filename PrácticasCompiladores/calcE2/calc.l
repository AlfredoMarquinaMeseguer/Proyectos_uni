%{
#include "calc.tab.h"
void error();
%}
digito [0-9]
caracter  [a-zA-Z_]
%%
[ \t\n\r]+				  ;
{digito}+				{yylval.numero=atoi(yytext);return NUM;}
{caracter}({caracter}|{digito})* 	{yylval.cad=strdup(yytext);return ID;}
"+"					return MAS;
"-"					return MENOS;
"*"					return POR;
"/"					return DIV;
"("					return PARI;
")"					return PARD;
"="					return ASIG;
";"					return FIN;
"%"					return MOD;
.					{error();}
%%

void error()
{
printf("Error en el caracter %s\n",yytext);
}



