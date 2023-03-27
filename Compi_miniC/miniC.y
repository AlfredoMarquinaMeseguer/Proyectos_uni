
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

%token EMPIEZA LEER ESCRIBIR A_PAREN C_PAREN SEMICOLON COMA ASIG_OP MAS_OP MENOS_OP A_LLAVE C_LLAVE VAR CONST SI SINO MIENTRAS POR_OP DIV_OP
%token<entero> NUM
%token<cadena> ID CADENA
%left MAS_OP MENOS_OP
%left POR_OP DIV_OP
%left UMENOS
%%

program 	: EMPIEZA ID A_PAREN C_PAREN A_LLAVE declarations statement_list C_LLAVE
		;

declarations 	: declarations VAR identifier_list SEMICOLON
		| declarations CONST identifier_list SEMICOLON
		| 
		;
		
identifier_list : asig
		| identifier_list COMA asig
		;
		
asig 		: ID
		| ID ASIG_OP expression
		;
	
statement_list 	: statement_list statement
		| 
		;
		
statement 	: ID ASIG_OP expression SEMICOLON
		| A_LLAVE statement_list C_LLAVE
		| SI A_PAREN expression C_PAREN statement SINO statement
		| SI A_PAREN expression C_PAREN statement
		| MIENTRAS A_PAREN expression C_PAREN statement
		| ESCRIBIR print_list SEMICOLON
		| LEER read_list SEMICOLON
		;
	
print_list 	: print_item
		| print_list COMA print_item
		;

print_item 	: expression
		| CADENA
		;
		
read_list 	: ID
		| read_list COMA ID
		;
		
expression 	: expression MAS_OP expression
		| expression MENOS_OP expression
		| expression POR_OP expression
		| expression DIV_OP expression
		| MENOS_OP expression %prec UMENOS
		| A_PAREN expression C_PAREN
		| ID
		| NUM
		;

%%

void yyerror()
{
printf("Expr. %d: Se ha producido un error en esta expresion\n",cont++);
}

