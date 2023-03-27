
%{
#include <stdio.h>
void yyerror();
extern int yylex();
int cont =1;
%}

%union{
int entero; 
char *cadena;
}
%type<entero> expresion entrada
%token PARI PARD FIN ASIG MAS MENOS POR DIV MOD
%token<entero> NUM
%token<cadena> ID
%left MAS MENOS
%left POR DIV MOD
%left UMENOS
%%

entrada : 	                     				{$$=1;}
	| entrada {printf("Expr. %d ", $1);} linea		     {$$=$1+1;} 
	;

linea : expresion FIN {printf("Expr. %d: %d\n",cont++,$1);} 
	| ID ASIG expresion FIN {printf("Expr. %d: La variable ID %s toma el valor %d\n",cont++,$1,$3);}
	| error FIN {}/*Esto puede dar conflictos si existe + de 1*/
	;

expresion : expresion MAS expresion {$$ = $1 + $3; }
          | expresion MENOS expresion {$$ = $1 - $3;}
          | expresion POR expresion {$$ = $1 * $3;}
       	  | expresion DIV expresion {$$ = $1 / $3;}
          | expresion MOD expresion {$$ = $1 % $3;}
          | PARI expresion PARD {$$ = $2;}
          | MENOS expresion %prec UMENOS {$$=-$2;} 
          | NUM ;

%%

void yyerror()
{
printf("Expr. %d: Se ha producido un error en esta expresion\n",cont++);
}

