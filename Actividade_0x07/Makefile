CC = gcc
CFLAGS = -g
OUTFILE = ya
LIBS = -lm
BISON_FILE = ya.y
LEX_FILE = ya.lex


all: parser.c lexer.c
	$(CC) $(CFLAGS) parser.c lexer.c -o $(OUTFILE) $(LIBS)

parser.c: $(BISON_FILE)
	bison -y -d $(BISON_FILE) -o parser.c

lexer.c: $(LEX_FILE)
	flex -o lexer.c $(LEX_FILE)

clean:
	rm -rf parser.c parser.h lexer.c
	rm -f *~
	rm -f $(OUTFILE)
