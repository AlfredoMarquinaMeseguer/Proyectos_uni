%{
#include "lexico1.h"
void error_lexico();
%}
digito              [0-9]
letra               [a-zA-Z]
entero              {digito}+
%option yylineno
%x COMENTARIO
%%
	/*reglas en regex		acción realizada, normalmente codigo que devuelven*/					
[ \n\t]+                            ;
"//"(.*)[\n]                        ;
"/*"				{yymore(); BEGIN COMENTARIO;}
<COMENTARIO>"*"+"/"		{printf("Reconocido comentario en linea %d: %s \n",yylineno, yytext); BEGIN 0;}
<COMENTARIO>[^*]*		yymore();
<COMENTARIO>[*]+[^*/]*		yymore();
main                               return BEGINN;
end                                return END;
input                               return READ;
print                               return WRITE;
(_|\$|{letra})({letra}|{digito}|_|\$)*        return ID;
{entero}                            return INTLITERAL;
"("                                 return L_PAREN;		
")"                                 return R_PAREN;
";"                                 return SEMICOLON;
","                                 return COMMA;
"="                                return ASSIGNOP;
"+"                                 return PLUSOP;
"-"                                 return MINUSOP;
		/*{entero}[.]{entero}                 return REALLIT;*/
"{"				    return I_LLAVE;
"}"				    return F_LLAVE;
.                                   error_lexico();
%%

void error_lexico()
{
  printf("\nERROR, símbolo no reconocido %s\n",yytext);
}

void main() {
    int i;
    while (i=yylex())
        printf("%d %s\n",i,yytext);
    printf("FIN DE ANALISIS LEXICO\n");
}
