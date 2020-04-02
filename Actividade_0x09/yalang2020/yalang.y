%{

#include <stdio.h>
#include "ya.h"

extern int yylineno;
extern FILE *yyin;
extern char *yytext;

int yylex (void);
void yyerror (char const *);

%}

%union {
    int    ival;
    double dval;
    char   *str;

    t_decls decls;
}

/* Bison declarations.  */
%token	<ival>          INTLIT BOOLLIT
%token	<dval>          FLOATLIT
%token	<str>           STRLIT ID

%token                  COLON

%token			DEFINE RETURN STRUCT WHILE IF THEN ELSE DO NEXT BREAK

%token			T_INT T_FLOAT T_STRING T_BOOL T_VOID /* atomic types */

%left			SEMI    /* semicolon */

%right			ASSIGN

%left			COMMA

%left			OR
%left			AND
%left			NOT

%nonassoc		EQ NEQ GT GEQ LT LEQ

%left			SUB ADD
%left			MUL DIV MOD
%right			POW
%left			NEG     /* negation--unary minus */

%nonassoc		LCBRACE RCBRACE
%nonassoc		LSBRACE RSBRACE
%nonassoc		LPAR RPAR

%type <decls>   decls

%%

program:  /*    empty */
        |	    decls
                ;

decls:   	    decl          {$$ = t_decls_new($1, NULL);}
        |	    decl decls    {$$ = t_decls_new($1, $2);}
                ;

decl:    	    ids COLON type SEMI
        |	    ids COLON type ASSIGN exp SEMI
        |	    ID LPAR RPAR COLON type LCBRACE stms RCBRACE SEMI
        |	    ID LPAR argdefs RPAR COLON type LCBRACE stms RCBRACE SEMI
        |	    DEFINE ID type SEMI
                ;

argdefs: 	    argdef
        |	    argdef COMMA argdefs
                ;

argdef:  	    ID COLON type
                ;

args:		    exp
        |	    exp COMMA args
                ;

ids:     	    ID
        |	    ID COMMA ids
                ;

stms:    	    stm
        |	    stm stms
                ;

stm:     	    decl
        |	    exp SEMI
        |	    RETURN exp SEMI
        |	    IF exp THEN LCBRACE stms RCBRACE SEMI
        |	    IF exp THEN LCBRACE stms RCBRACE ELSE LCBRACE stms RCBRACE SEMI
        |	    WHILE exp DO LCBRACE stms RCBRACE SEMI
        |       NEXT
                ;

type:    	    T_INT
        |	    T_FLOAT
        |	    T_STRING
        |	    T_BOOL
        |	    T_VOID
        |	    ID
        |	    type LSBRACE INTLIT RSBRACE
                ;

lit:     	    INTLIT
        |	    FLOATLIT
        |	    STRLIT
        |	    BOOLLIT
                ;

exp:     	    lit
        |	    ID
        |	    exp LSBRACE INTLIT RSBRACE
        |	    exp ADD exp
        |	    exp SUB exp
        |	    exp MUL exp
        |	    exp DIV exp
        |	    exp POW exp
        |	    exp MOD exp
        |	    exp GT exp
        |	    exp LT exp
        |	    exp GEQ exp
        |	    exp LEQ exp
        |	    exp EQ exp
        |	    exp NEQ exp
        |	    exp AND exp
        |	    exp OR exp
        |	    NOT exp
        |	    SUB exp  %prec NEG
        |	    LPAR exp RPAR
        |	    ID LPAR RPAR
        |	    ID LPAR args RPAR
        |	    exp ASSIGN exp
                ;
%%


void yyerror (char const *s)
/* Called by yyparse on error.  */
{
    fprintf (stderr, "Syntax error at line %d at or near \"%s\"\n", yylineno, yytext);
}

int main( int argc, char **argv )
{
    ++argv, --argc;

    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;

    return yyparse();
}

/*
int main (void)
{
    return yyparse();
}
*/
