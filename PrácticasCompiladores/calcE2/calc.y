
%{
#include <stdio.h>
void yyerror();
extern int yylex();
int contador = 0;
%}
%union{
 int numero;
 char * cad;
}


%token PARI PARD FIN ASIG MAS MENOS POR DIV MOD
%token <numero> NUM
%token <cad> ID
%left MAS MENOS
%left DIV POR MOD
%left UMENOS

%type <numero> expresion entrada
%%

entrada : 	{$$=1;}
	| entrada {printf("Expr. %d: ",$1);}linea {$$=$1+1;};

linea : expresion FIN {printf("%d\n", $1);} 
	| ID ASIG expresion FIN {printf("La variable %s toma el valor %d\n",$1,$3);}
    | error FIN {}
	;

expresion : expresion MAS expresion {$$ = $1 + $3; }
          | expresion MENOS expresion {$$ = $1 - $3;}
          | expresion POR expresion {$$ = $1 * $3;}
          | expresion DIV expresion {$$ = $1 / $3;}
          | expresion MOD expresion {$$ = $1 % $3;}
          | PARI expresion PARD {$$ = $2;}
	      | MENOS expresion %prec UMENOS{$$=-$2;} 
          | NUM 
          ;

%%

void yyerror()
{
        printf("Se ha producido un error en esta expresion\n");
}

