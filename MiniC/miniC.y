
%{
#include "listaSimbolos.h"
#include <stdio.h>
#include "listaCodigo.h"

Lista lista;
int contCadenas = 0;
Tipo tipo;
void yyerror();
extern int yylex();
extern int yylineno;
extern int numErroresLex;
int numErroresSem = 0;
int numErroresSint = 0;
int cont = 1;
%}

%code requires{
#include "listaCodigo.h"
}

%union{
char *lexema;
ListaC codigo;
}

%type <codigo> expression statement statement_list print_item print_list read_list declarations identifier_list asig

%token EMPIEZA LEER ESCRIBIR A_PAREN C_PAREN SEMICOLON COMA ASIG_OP MAS_OP MENOS_OP A_LLAVE C_LLAVE VAR CONST SI SINO MIENTRAS POR_OP DIV_OP REAL HACER
%token<lexema> STRING ID NUM
%left MAS_OP MENOS_OP
%left POR_OP DIV_OP
%precedence UMENOS

%define parse.error verbose

%expect 1 /* conflicto desplazamiento/reduccion */

%%

program 	:  {lista=creaLS(); iniReg();} EMPIEZA ID A_PAREN C_PAREN A_LLAVE declarations statement_list C_LLAVE {
					if (numErroresLex + numErroresSint + numErroresSem == 0) { // Generamos el código
						imprimirTablaS(lista);
						concatenaLC($7, $8);
						liberaLC($8);
						imprimirListaC($7);
					}
					else {
						printf("----------------------\n");
						printf("Errores lexicos: %d\n",numErroresLex);
						printf("Errores sintacticos: %d\n",numErroresSint);
						printf("Errores semanticos: %d\n",numErroresSem);
					}
					/* Liberar memoria de tabla de símbolos y lista de código */
					liberaLS(lista);
					liberaLC($7); }
		;

declarations 	: declarations VAR {tipo = VARIABLE;} identifier_list SEMICOLON {
					$$=$1;
                    concatenaLC($$,$4);
                    liberaLC($4); }
		| declarations CONST {tipo = CONSTANTE;} identifier_list SEMICOLON {
			$$=$1;
			concatenaLC($$,$4);
			liberaLC($4); }
		|  %empty {$$ = creaLC();}
		;
		
identifier_list : asig { $$ = $1; }
		| identifier_list COMA asig {
			$$=$1;
			concatenaLC($$,$3);
			liberaLC($3); }
		;
		
asig 		: ID {if (!perteneceTablaS(lista, $1)) anyadeEntrada(lista, $1, tipo, 0);
 			else { printf("Variable %s ya declarada \n",$1); numErroresSem++;}
 			$$=creaLC();}
		| ID ASIG_OP expression { if (!perteneceTablaS(lista, $1)) anyadeEntrada(lista, $1, tipo, 0);
 						else { printf("Variable %s ya declarada \n",$1); numErroresSem++;}
 						$$=$3;

						Operacion aux;
						aux.op="sw";
						aux.res=recuperaResLC($3);
						aux.arg1=concatena("_",$1);
						aux.arg2=NULL;

						//Insertamos codigo
						insertaLC($$,finalLC($$),aux);
						liberarReg(aux.res);}
		;
	
statement_list 	: statement_list statement {
					$$=$1;
                    concatenaLC($$,$2);
                    liberaLC($2); }
				| %empty{
                    $$=creaLC(); }
				;
		
statement 	: ID ASIG_OP expression SEMICOLON  /*{ imprimirCodigo($3); }*/ 
							{if (!perteneceTablaS(lista, $1)) {
 							printf("Variable %s no declarada \n",$1); numErroresSem++;}
							else if (esConstante(lista, $1)) {
 							printf("Asignación a constante\n"); numErroresSem++;}
								$$=$3;
								Operacion aux;
								aux.op="sw";
								aux.res=recuperaResLC($3);
								aux.arg1=concatena("_",$1);
								aux.arg2=NULL;

								//Insertamos codigo
								insertaLC($$,finalLC($$),aux);
								liberarReg(aux.res);}
								
		| A_LLAVE statement_list C_LLAVE { $$ = $2; }
		| SI A_PAREN expression C_PAREN statement SINO statement { 
			$$=$3;
			//Etiqueta 1
			char * etiq1=nuevaEtiqueta();
			Operacion aux;
			aux.op="beqz";
			aux.res=recuperaResLC($3);
			aux.arg1=etiq1;
			aux.arg2=NULL;

			//Insertamos codigo
			insertaLC($$,finalLC($$),aux);

			//Añadir codigo statement
			concatenaLC($$,$5);

			//liberamos temporal
			liberarReg(aux.res);
			liberaLC($5);

			char * etiq2=nuevaEtiqueta();
			aux.op="b";
			aux.res=etiq2;
			aux.arg1=NULL;
			aux.arg2=NULL;

			//Insertamos codigo
			insertaLC($$,finalLC($$),aux);

			//añadir etiqueta 1
			aux.op="etiq";
			aux.res=etiq1;
			aux.arg1=NULL;
			aux.arg2=NULL;

			//Insertamos codigo
			insertaLC($$,finalLC($$),aux);

			//Añadimos codigo statement 2
			concatenaLC($$,$7);

			liberaLC($7);

			//Añadir etiqueta 2
			aux.op="etiq";
			aux.res=etiq2;
			aux.arg1=NULL;
			aux.arg2=NULL;

			//Insertamos codigo
			insertaLC($$,finalLC($$),aux); }
		| SI A_PAREN expression C_PAREN statement {
			$$=$3;
			char * etiq=nuevaEtiqueta();

			Operacion aux;
			aux.op="beqz";
			aux.res=recuperaResLC($3);
			aux.arg1=etiq;
			aux.arg2=NULL;

			//Insertamos codigo
			insertaLC($$,finalLC($$),aux);

			liberarReg(aux.res);
			//Añadir statement
			concatenaLC($$,$5);

			//Añadir etiqueta
			aux.op="etiq";
			aux.res=etiq;
			aux.arg1=NULL;
			aux.arg2=NULL;

			//Insertar codigo
			insertaLC($$,finalLC($$),aux); }
		| MIENTRAS A_PAREN expression C_PAREN statement {
			// etiqueta1:
			// beqz expression  -> salto etiqueta2
			// 
			//	statement
			//
			//	salto etiqueta1
			// etiqueta2:
			char * etiq1=nuevaEtiqueta();
			char * etiq2=nuevaEtiqueta();

			$$=creaLC();

			//Añadir etiqueta 1
			Operacion aux;
			aux.op="etiq";
			aux.res=etiq1;
			aux.arg1=NULL;
			aux.arg2=NULL;

			insertaLC($$,finalLC($$),aux);

			concatenaLC($$,$3);

			aux.op="beqz";
			aux.res=recuperaResLC($3);
			aux.arg1=etiq2;
			aux.arg2=NULL;

			//Liberar lc
			liberaLC($3);

			//Insertar codigo
			insertaLC($$,finalLC($$),aux);

			liberarReg(aux.res);

			//Añadir statement
			concatenaLC($$,$5);

			//Liberar codigo
			liberaLC($5);

			//Añadir salto a etiqueta 1
			aux.op="b";
			aux.res=etiq1;
			aux.arg1=NULL;
			aux.arg2=NULL;

			//Insertar codigo
			insertaLC($$,finalLC($$),aux);

			//Añadir etiqueta 2
			aux.op = "etiq";
			aux.res = etiq2;
			aux.arg1=NULL;
			aux.arg2=NULL;
			insertaLC($$,finalLC($$),aux); }
		| HACER statement MIENTRAS A_PAREN expression C_PAREN SEMICOLON {
            $$=creaLC();
			char * etiq = nuevaEtiqueta();

			Operacion aux;

			insertaLC($$,finalLC($$),aux);


			//Añadir etiqueta
			aux.op = "etiq";
			aux.res = etiq;
			aux.arg1=NULL;
			aux.arg2=NULL;
			insertaLC($$,finalLC($$),aux);
			
			// Añadimos statement
			concatenaLC($$,$2);

			// Añadimos expression
			concatenaLC($$,$5);

			// Añadimos bnez
			aux.op="bnez";
			aux.res=recuperaResLC($5);
			aux.arg1=etiq;
			aux.arg2=NULL;
			insertaLC($$,finalLC($$),aux);
            liberaLC($2);
			liberaLC($5);
			liberarReg(aux.res);
		}		
		| ESCRIBIR print_list SEMICOLON { $$ = $2; }
		| LEER read_list SEMICOLON { $$ = $2; }
		| error SEMICOLON { $$ = creaLC(); }
		;
	
print_list 	: print_item { $$ = $1; }
		| print_list COMA print_item {
			$$=$1;
			concatenaLC($$,$3);
			liberaLC($3); }
		;

print_item 	: expression {
				$$=$1;
				Operacion aux;
				aux.op="li";
				aux.res="$v0";
				aux.arg1="1";
				aux.arg2=NULL;

				//Insertamos codigo
				insertaLC($$,finalLC($$),aux);
				aux.op="move";
				aux.res="$a0";
				aux.arg1=recuperaResLC($1);
				aux.arg2=NULL;

				//Insertamos codigo
				insertaLC($$,finalLC($$),aux);

				liberarReg(aux.arg1);

				aux.op="syscall";
				aux.res=NULL;
				aux.arg1=NULL;
				aux.arg2=NULL;
				//Insertamos el codigo en la lista
				insertaLC($$,finalLC($$),aux); }
		| STRING { 
					contCadenas++; 
					anyadeEntrada(lista, $1, CADENA, contCadenas);

					$$=creaLC();

                    Operacion aux;
                    aux.op="li";
                    aux.res="$v0";
                    aux.arg1="4";
                    aux.arg2=NULL;

                    //Insertar codigo
                    insertaLC($$,finalLC($$),aux);

                    aux.op="la";
                    aux.res="$a0";

                    //Para hacer cadena que indica cadenas hay que hacer $str (4) + 000(3) + 0(1)=\0
                    char * cadena = (char *) malloc(4+3+1);
                    sprintf(cadena, "$str%d", contCadenas);
                    aux.arg1 = cadena;
                    aux.arg2 = NULL;
                    //Insertamos el codigo en la lista
                    insertaLC($$,finalLC($$),aux);
                    //syscall
                    aux.op="syscall";
                    aux.res=NULL;
                    aux.arg1=NULL;
                    aux.arg2=NULL;
                    //Insertamos el codigo en la lista
                    insertaLC($$,finalLC($$),aux);}
		;
		
read_list 	: ID {if (!perteneceTablaS(lista, $1)) { printf("Variable %s no declarada \n",$1); numErroresSem++;}
 		     else if (esConstante(lista, $1)) { printf("Asignación a constante\n"); numErroresSem++;}
                    $$=creaLC();

                    Operacion aux;
                    aux.op="li";
                    aux.res="$v0";
                    aux.arg1="5";
                    aux.arg2=NULL;

                    //Insertar codigo
                    insertaLC($$,finalLC($$),aux);

                    aux.op="syscall";
                    aux.res=NULL;
                    aux.arg1=NULL;
                    aux.arg2=NULL;

                    //Insertar codigo
                    insertaLC($$,finalLC($$),aux);

                    aux.op="sw";
                    aux.res="$v0";
                    aux.arg1=concatena("_",$1);
                    aux.arg2=NULL;

                    //Insertar codigo
                    insertaLC($$,finalLC($$),aux); }
		| read_list COMA ID {if (!perteneceTablaS(lista, $3)) { printf("Variable %s no declarada \n",$3); numErroresSem++; }
				    else if (esConstante(lista, $3)) { printf("Asignación a constante\n"); numErroresSem++;}
						$$=$1;

						Operacion aux;
						aux.op="li";
						aux.res="$v0";
						aux.arg1="5";
						aux.arg2=NULL;

						//Insertar codigo
						insertaLC($$,finalLC($$),aux);

						aux.op="syscall";
						aux.res=NULL;
						aux.arg1=NULL;
						aux.arg2=NULL;

						//Insertar codigo
						insertaLC($$,finalLC($$),aux);

						aux.op="sw";
						aux.res="$v0";
						aux.arg1=concatena("_",$3);
						aux.arg2=NULL;

						//Insertar codigo
						insertaLC($$,finalLC($$),aux); }
		;
		
expression 	: expression MAS_OP expression {
							$$=$1;
							concatenaLC($$,$3);
							Operacion oper;
							oper.op = "add";
							oper.res = recuperaResLC($1);
							oper.arg1 = recuperaResLC($1);
							oper.arg2 = recuperaResLC($3);
							insertaLC($$,finalLC($$),oper);
							liberaLC($3);
							liberarReg(oper.arg2); }
		| expression MENOS_OP expression {
							$$ = $1;
							concatenaLC($$,$3);
							Operacion oper;
							oper.op = "sub";
							oper.res = recuperaResLC($1);
							oper.arg1 = recuperaResLC($1);
							oper.arg2 = recuperaResLC($3);
							insertaLC($$,finalLC($$),oper);
							liberaLC($3);
							liberarReg(oper.arg2); }
		| expression POR_OP expression {
							$$ = $1;
							concatenaLC($$,$3);
							Operacion oper;
							oper.op = "mul";
							oper.res = recuperaResLC($1);
							oper.arg1 = recuperaResLC($1);
							oper.arg2 = recuperaResLC($3);
							insertaLC($$,finalLC($$),oper);
							liberaLC($3);
							liberarReg(oper.arg2); }
		| expression DIV_OP expression {
							$$ = $1;
							concatenaLC($$,$3);
							Operacion oper;
							oper.op = "div";
							oper.res = recuperaResLC($1);
							oper.arg1 = recuperaResLC($1);
							oper.arg2 = recuperaResLC($3);
							insertaLC($$,finalLC($$),oper);
							liberaLC($3);
							liberarReg(oper.arg2); }
		| MENOS_OP expression %prec UMENOS {
							$$ = $2;
							Operacion oper;
							oper.op = "neg";
							oper.res = obtenerReg();
							oper.arg1 = recuperaResLC($2);
							oper.arg2 = NULL;
							insertaLC($$, finalLC($$), oper); }
		| A_PAREN expression C_PAREN {$$ = $2;}
		| ID {if (!perteneceTablaS(lista, $1)){ printf("Variable %s no declarada \n",$1);  numErroresSem++;}

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

void yyerror(const char *msg)
{
	numErroresSint++;
    printf("Error en linea %d: %s\n", yylineno, msg);
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
