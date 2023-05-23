%{
#include "miniC.h"
%}
digito              [0-9]
letra               [a-zA-Z]
entero              {digito}+

%option yylineno
%x COMENTARIO  
%x ERROR
%%
	/*reglas en regex		acción realizada, normalmente codigo que devuelven*/					
[ \n\t]+                            ;
"//"(.*)[\n]                        ;
"/*"				{yymore(); BEGIN COMENTARIO;}
<COMENTARIO>"*"+"/"		{printf("Reconocido comentario en linea %d: %s \n",yylineno, yytext); BEGIN 0;}
<COMENTARIO>[^*]*		yymore();
<COMENTARIO>[*]+[^*"//"(.*)[\n]                        ;/]*		yymore();
void                                		return EMPIEZA;
	/*end                                 		return END;*/
var                                             return VAR;
const                                           return CONST;
if						return SI;
else						return SINO;
while						return MIENTRAS;
read                               		return LEER;
print                               		return ESCRIBIR;
(_|\$|{letra})({letra}|{digito}|_|\$){0,15}     return ID; {yylval.lexema=strdup(yytext);}
entero			                        return NUM; {yylval.lexema=strdup(yytext);}
"([^\\\"]|\\.)*"				return CADENA; {yylval.lexema=strdup(yytext);}
{entero}[.]{entero}				return REAL
"("                     		        return A_PAREN;		
")"		                                return C_PAREN;
";"             		                return SEMICOLON;
","                             		return COMA;
"="		                                return ASIG_OP; 
"+"             		                return MAS_OP;
"-"                             		return MENOS_OP;
"*"                                             return POR_OP;
"/"		                                return DIV_OP;
"{"				                return A_LLAVE;
"}"						return C_LLAVE;
<ERROR>[^A-Za-z0-9();,=+-{}_$]	                {yymore();printf("Error Reconocido %s\n",yytext);}
<ERROR>.			                {yyless(yyleng-1);printf("Reconocido error en linea %d: %s.\n",yylineno, yytext); BEGIN 0;}
.                                               {yymore(); BEGIN ERROR;}
			
%%
