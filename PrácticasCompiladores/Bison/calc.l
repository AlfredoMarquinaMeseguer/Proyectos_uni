%{
#include "calc.tab.h"
%}
%option yylineno
%%

[ \n\t\r]+                                      ;
"*"                 return POR;
"+"                 return MAS;
"-"                 return RESTA;
"/"                 return DIVISION;
"("                 return APAR;
")"                 return CPAR;
[0-9]+              {yylval=atoi(yytext);return NUM;}
";"                 return FIN;
.                   printf("Error lexico con tokes %s en linea %d", yytext, yylineno);

%%