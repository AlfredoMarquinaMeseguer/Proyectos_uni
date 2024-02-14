%s pl
%option yylineno
%%
\n                                  BEGIN pl;
<pl>compi                           {printf("Reconocido en %d\n", yylineno);BEGIN INITIAL;} // O ... BEGIN 0; ...
.                                   BEGIN 0;
%%
 