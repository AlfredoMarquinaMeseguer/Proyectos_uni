
%{
#include "listaSimbolos.h"
#include "listaCodigo.h"

Lista tablaSimb;
int contCadenas = 0;
Tipo tipo;
void yyerror();
extern int yylex();
int cont =1;
%}

%code requires {
	#include "listaCodigo.h"
}

%union{
char *lexema;
ListaC codigo;
}

%type <codigo> expression 

%token EMPIEZA LEER ESCRIBIR A_PAREN C_PAREN SEMICOLON COMA ASIG_OP MAS_OP MENOS_OP A_LLAVE C_LLAVE VAR CONST SI SINO MIENTRAS POR_OP DIV_OP REAL
%token<lexema> CADENA ID NUM
%left MAS_OP MENOS_OP
%left POR_OP DIV_OP
%left UMENOS
%%

program 	:  {tablaSimb=creaLS();} EMPIEZA ID A_PAREN C_PAREN A_LLAVE declarations statement_list C_LLAVE
		{imprimirTablaS(); liberaTS();} ;

declarations 	: declarations VAR {tipo = VARIABLE;} identifier_list SEMICOLON
		| declarations CONST {tipo = CONSTANTE;} identifier_list SEMICOLON
		| {$$=creaLC();}
		;
		
identifier_list : asig
		| identifier_list COMA asig
		;
		
asig 		: ID {if !(perteneceTablaS($1)) añadeEntrada($1,tipo)
 			else printf(“Variable %s ya declarada \n”,$1);}
		| ID ASIG_OP expression { if !(perteneceTablaS($1)) añadeEntrada($1,tipo)
 						else printf(“Variable %s ya declarada \n”,$1);}
		;
	
statement_list 	: statement_list statement
		| 
		;
		
statement 	: ID ASIG_OP expression SEMICOLON { imprimirCodigo($3); }
							{if !(perteneceTablaS($1))
 							printf(“Variable %s no declarada \n”,$1);
 						  else if (esConstante($1))
 							printf(“Asignación a constante\n”);}
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
		| CADENA {añadeEntrada($1,CADENA);contCadenas++;}
		;
		
read_list 	: ID {if !(perteneceTablaS($1)) printf(“Variable %s no declarada \n”,$1);
 		     else if esConstante($1) printf(“Asignación a constante\n”);}
		| read_list COMA ID {if !(perteneceTablaS($3)) printf(“Variable %s no declarada \n”,$3);
				    else if esConstante($3) printf(“Asignación a constante\n”);}
		;
		
expression 	: expression MAS_OP expression
		| expression MENOS_OP expression
		| expression POR_OP expression
		| expression DIV_OP expression
		| MENOS_OP expression %prec UMENOS
		| A_PAREN expression C_PAREN
		| ID {if !(perteneceTablaS($1)) printf(“Variable %s no declarada \n”,$1);}
		| NUM
		;

%%

void yyerror()
{
	printf("Expr. %d: Se ha producido un error en esta expresion\n",cont++);
}

void imprimirCodigo(ListaC codigo) {
 PosicionListaC p = inicioLC(codigo);
 while (p != finalLC(codigo)) {
 	Operacion oper = recuperaLC(codigo,p);
 	printf("%s",oper.op);
 	if (oper.res) printf(" %s",oper.res);
 	if (oper.arg1) printf(",%s",oper.arg1);
 	if (oper.arg2) printf(",%s",oper.arg2);
 	printf("\n");
 	p = siguienteLC(codigos,p);
 }
}

