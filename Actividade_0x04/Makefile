
calc: lexer.c parser.c
	gcc -o mycalc lexer.c parser.c

lexer.c: calc.l
	flex -o lexer.c calc.l

parser.c: calc.y
	bison -y -d -o parser.c calc.y
