miniC: lex.yy.c miniC.tab.c main.c listaSimbolos.c listaCodigo.c
	gcc lex.yy.c miniC.tab.c main.c listaSimbolos.c listaCodigo.c -lfl -o miniC
miniC.l miniC.h: miniC.y
	bison -d -v miniC.y
lex.yy.c: calc.l
	flex calc.l
limpia:
	rm lex.yy.c miniC.tab.C main.c listaSimbolos.c listaCodigo.c miniC
run: 
	./miniC p
