calc: lex.yy.c calc.tab.c
	gcc -g lex.yy.c calc.tab.c -lfl -o calc

lex.yy.c: calc.l calc.tab.h
	flex calc.l

calc.tab.c calc.tab.h: calc.y
	bison -d calc.y

limpia:
	rm lex.yy.c calc.tab.c calc.tab.h calc