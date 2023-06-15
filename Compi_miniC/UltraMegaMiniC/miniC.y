
%{
#include "listaSimbolos.h"
#include <stdio.h>
#include "listaCodigo.h"

Lista tablaSimb;
int contCadenas = 0;
Tipo tipo;
void yyerror();
extern int yylex();
int cont =1;
%}

%code requires{
#include "listaCodigo.h"
}

%union{
char *lexema;
ListaC codigo;
}

%type <codigo> expression /*declarations identifier_list asig
statement_list statement print_list print_item read_list */

%token EMPIEZA LEER ESCRIBIR A_PAREN C_PAREN SEMICOLON COMA ASIG_OP MAS_OP MENOS_OP A_LLAVE C_LLAVE VAR CONST SI SINO MIENTRAS POR_OP DIV_OP REAL
%token<lexema> STRING ID NUM
%left MAS_OP MENOS_OP
%left POR_OP DIV_OP
%precedence UMENOS

%expect 1 /* conflicto desplazamiento/reduccion del if-else */
%%

program 	:  {tablaSimb=creaLS();} EMPIEZA ID A_PAREN C_PAREN A_LLAVE declarations statement_list C_LLAVE
		{imprimirTablaS(tablaSimb); liberaLS(tablaSimb);}
		;

declarations 	: declarations VAR {tipo = VARIABLE;} identifier_list SEMICOLON
		| declarations CONST {tipo = CONSTANTE;} identifier_list SEMICOLON
		/*|  {$$=creaLC();}*/
		;
		
identifier_list : asig
		| identifier_list COMA asig
		;
		
asig 	: ID {if (!perteneceTablaS(tablaSimb, $1)) anyadeEntrada(tablaSimb, $1, tipo);
 			else printf("Variable %s ya declarada \n",$1);}
		| ID ASIG_OP expression { if (!perteneceTablaS(tablaSimb, $1)) anyadeEntrada(tablaSimb, $1, tipo);
 						else printf("Variable %s ya declarada \n",$1);}
		;
	
statement_list 	: statement_list statement
		| 
		;
		
statement 	: ID ASIG_OP expression SEMICOLON /* { imprimirCodigo($3); } */
							{if (!perteneceTablaS(tablaSimb, $1))
 							printf("Variable %s no declarada \n",$1);
 						  else if (esConstante(tablaSimb, $1))
 							printf("Asignación a constante\n");}
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
		| STRING {anyadeEntrada(tablaSimb, $1, CADENA);contCadenas++;}
		;
		
read_list 	: ID {if (!perteneceTablaS(tablaSimb, $1)) printf("Variable %s no declarada \n",$1);
 		     else if (esConstante(tablaSimb, $1)) printf("Asignación a constante\n");}
		| read_list COMA ID {if (!perteneceTablaS(tablaSimb, $3)) printf("Variable %s no declarada \n",$3);
				    else if (esConstante(tablaSimb, $3)) printf("Asignación a constante\n");}
		;
		
expression 	: expression MAS_OP expression { $$ = $1; concatenaLC($$,$3);
 						Operacion oper; oper.op = "add"; oper.res = recuperaResLC($1);
 						oper.arg1 = recuperaResLC($1); oper.arg2 = recuperaResLC($3);
 						insertaLC($$,finalLC($$),oper); liberaLC($3);
 						liberarReg(oper.arg2); }
		| expression MENOS_OP expression { $$ = $1; concatenaLC($$,$3);
 						Operacion oper; oper.op = "sub"; oper.res = recuperaResLC($1);
 						oper.arg1 = recuperaResLC($1); oper.arg2 = recuperaResLC($3);
 						insertaLC($$,finalLC($$),oper); liberaLC($3);
 						liberarReg(oper.arg2); }
		| expression POR_OP expression { $$ = $1; concatenaLC($$,$3);
 						Operacion oper; oper.op = "mul"; oper.res = recuperaResLC($1);
 						oper.arg1 = recuperaResLC($1); oper.arg2 = recuperaResLC($3);
 						insertaLC($$,finalLC($$),oper); liberaLC($3);
 						liberarReg(oper.arg2); }
		| expression DIV_OP expression { $$ = $1; concatenaLC($$,$3);
 						Operacion oper; oper.op = "div"; oper.res = recuperaResLC($1);
 						oper.arg1 = recuperaResLC($1); oper.arg2 = recuperaResLC($3);
 						insertaLC($$,finalLC($$),oper); liberaLC($3);
 						liberarReg(oper.arg2); }
		| MENOS_OP expression %prec UMENOS
		| A_PAREN expression C_PAREN
		| ID {if (!perteneceTablaS(tablaSimb, $1)) printf("Variable %s no declarada \n",$1);
			$$ = creaLC();
 			Operacion oper;
 			oper.op = "lw";
 			oper.res = obtenerReg();
 			oper.arg1 = concatena("_",$1);
 			oper.arg2 = NULL;
 			insertaLC($$,finalLC($$),oper);
 			guardaResLC($$,oper.res); }

		| NUM  { $$ = creaLC();
 			Operacion oper;
 			oper.op = "li";
 			oper.res = obtenerReg();
 			oper.arg1 = $1;
 			oper.arg2 = NULL;
 			insertaLC($$,finalLC($$),oper);
 			guardaResLC($$,oper.res);  }
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
 	p = siguienteLC(codigo,p);
 }
}

