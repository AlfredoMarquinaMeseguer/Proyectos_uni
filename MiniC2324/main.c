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
