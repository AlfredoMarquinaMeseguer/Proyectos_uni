#include <stdio.h>
#include <stdlib.h>
#include "miniC.h"

extern char *yytext;
extern int  yyleng;
extern int yyparse();
extern FILE *yyin;
extern int yylex();
FILE *fich;
int main(int argc,char* argv[])
{
    char *nombre;
    if (argc >= 2) nombre = argv[1];

    if ((fich=fopen(nombre,"r"))==NULL) {
        printf("***ERROR, no puedo abrir el fichero\n");
        exit(1);		}
    yyin=fich;
    yyparse();
    return 0;
}
/*
#include <stdio.h>
#include <stdlib.h>

//Dice si el analisis sintactico ha ido bien o no (true/false)
extern int yyparse();
extern int yylex();

extern FILE *yyin;

int main(int argc,char* argv[]){

    if(argc != 2){
        printf("Uso %s fichero\n",argv[0]);
        exit(1);
    }

    yyin = fopen(argv[1],"r");

    if(yyin == NULL){
        printf("No se puede abrir %s\n", argv[1]);
        exit(2);
    }

    yyparse();
}
*/
