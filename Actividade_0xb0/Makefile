CC = gcc
CFLAGS = -g
OUTFILE = yac
LIBS = -lm

OFILES = t_exp.o


all: parser.o lexer.o ya.o ST.o hash.o list.o semantic_analyser.o
	$(CC) $(CFLAGS) parser.o lexer.o ya.o ST.o hash.o list.o semantic_analyser.o -o $(OUTFILE) $(LIBS)

parser.c: yalang.y
	bison -y -d $< -o $@ -r all

lexer.c: yalang.lex
	flex -o $@ $<

%.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $<

clean: 
	rm -rf parser.c lexer.c parser.h
	rm -f *~
	rm -f *.o
	rm -f *.output
	rm -f $(OUTFILE)

clean-all clean_all: clean
	rm -f $(OUTFILE)
