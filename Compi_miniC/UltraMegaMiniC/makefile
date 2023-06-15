miniC: lex.yy.c miniC.tab.c main.c listaSimbolos.c listaCodigo.c
	gcc -g lex.yy.c miniC.tab.c main.c listaSimbolos.c listaCodigo.c -lfl -o miniC
miniC.tab.h miniC.tab.c: miniC.y
	bison -d -v miniC.y
lex.yy.c: miniC.l miniC.tab.h
	flex miniC.l
limpia:
	rm -f lex.yy.c miniC.tab.* miniC.output miniC
run: 	miniC p
	./miniC p
