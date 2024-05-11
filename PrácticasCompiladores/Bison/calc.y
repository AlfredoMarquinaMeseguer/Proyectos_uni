%{
#include <stdio.h>

void main();
void yyerror();
extern int yylineno;
extern char *yytext;
extern int yylex();
%}

%token POR MAS APAR CPAR NUM FIN RESTA DIVISION;
%%
entrada :                              {} 
        | entrada linea                 {}
        ;
linea : E FIN  {printf("%d\n", $1);}
      ;
E : E MAS T          {$$=$1+$3;}
  | E RESTA T      {$$=$1-$3;}
  | T              {$$=$1;}
  ;
T : T POR F       {$$=$1*$3;}
  | T DIVISION F    {$$=$1/$3;}
  | F             {$$=$1;}
  ;
 
F : APAR E CPAR {$$=$2;}
  | NUM {$$=$1; }
  | RESTA F {$$=-$2;}
  ;
%%

void main() {yyparse();}

void yyerror() {
    
}