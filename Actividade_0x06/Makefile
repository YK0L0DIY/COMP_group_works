CC = gcc
CFLAGS = -g
OUTFILE = calc
LIBS = -lm


all: parser.c lexer.c calctypes.o latex.o
	$(CC) $(CFLAGS) parser.c lexer.c calctypes.o latex.o -o $(OUTFILE) $(LIBS)

parser.c: calc.y
	bison -y -d calc.y -o parser.c

lexer.c: calc.lex
	flex -o lexer.c calc.lex

calctypes.o: calctypes.h calctypes.c
	gcc $(CFLAGS) -c calctypes.c

latex.o: latex.h latex.c
	gcc $(CFLAGS) -c latex.c

clean: 
	rm -rf parser.c lexer.c parser.h
	rm -f *~
	rm -f *.o
	rm -f calc
