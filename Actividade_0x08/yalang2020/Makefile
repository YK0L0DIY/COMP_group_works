CC = clang
CFLAGS = -g
OUTFILE = ya!c
LIBS = -lm

OFILES = t_exp.o


all: parser.c lexer.c parser.h
	$(CC) $(CFLAGS) parser.c lexer.c -o $(OUTFILE) $(LIBS)

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

clean-all clean_all: clean
	rm -f $(OUTFILE)
