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
    t_exp exp;
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
%type <exp>   exp

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

exp:     	    lit                          {$$ = t_exp_new_lit($1);}
        |	    ID                           {$$ = t_exp_new_id($1);}
        |	    exp LSBRACE INTLIT RSBRACE   {$$ = t_exp_new_array($1,$3);}
        |	    exp ADD exp                  {$$ = t_exp_new_binop($1, $3);}
        |	    exp SUB exp                  {$$ = t_exp_new_binop($1, $3);}
        |	    exp MUL exp                  {$$ = t_exp_new_binop($1, $3);}
        |	    exp DIV exp                  {$$ = t_exp_new_binop($1, $3);}
        |	    exp POW exp                  {$$ = t_exp_new_binop($1, $3);}
        |	    exp MOD exp                  {$$ = t_exp_new_binop($1, $3);}
        |	    exp GT exp                   {$$ = t_exp_new_binop($1, $3);}
        |	    exp LT exp                   {$$ = t_exp_new_binop($1, $3);}
        |	    exp GEQ exp                  {$$ = t_exp_new_binop($1, $3);}
        |	    exp LEQ exp                  {$$ = t_exp_new_binop($1, $3);}
        |	    exp EQ exp                   {$$ = t_exp_new_binop($1, $3);}
        |	    exp NEQ exp                  {$$ = t_exp_new_binop($1, $3);}
        |	    exp AND exp                  {$$ = t_exp_new_binop($1, $3);}
        |	    exp OR exp                   {$$ = t_exp_new_binop($1, $3);}
        |	    NOT exp                      {$$ = t_exp_new_unop($2);}
        |	    SUB exp  %prec NEG           {$$ = t_exp_new_unop($2);}
        |	    LPAR exp RPAR                {$$ = $2;}
        |	    ID LPAR RPAR                 {$$ = t_exp_new_function($1,NULL);}
        |	    ID LPAR args RPAR            {$$ = t_exp_new_function($1,$3);}
        |	    exp ASSIGN exp               {$$ = t_exp_new_assign($1, $3);}
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
