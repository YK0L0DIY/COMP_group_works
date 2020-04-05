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
    t_decl decl;
    t_argdefs argdefs;
    t_argdef argdef;
    t_args args;
    t_ids ids;
    t_stms stms;
    t_stm stm;
    t_type type;
    t_lit lit;
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

%type	<decls>		program
%type 	<decls>		decls
%type 	<decl>		decl
%type	<argdefs>	argdefs
%type	<argdef>	argdef
%type	<args>		args
%type	<ids>		ids
%type	<stms>		stms
%type	<stm>		stm
%type	<type>		type
%type 	<lit>   	lit
%type 	<exp>   	exp

%%

program:  /*    empty */								{$$ = NULL;}
        |	    decls								{$$ = $1};
                ;

decls:   	    decl         							{$$ = t_decls_new($1, NULL);}
        |	    decl decls    							{$$ = t_decls_new($1, $2);}
                ;

decl:    	    ids COLON type SEMI  					        {$$ = t_decl_new_init($1,$3);}
        |	    ids COLON type ASSIGN exp SEMI 					{$$ = t_decl_new_assign($1,$3,$5);}
        |	    ID LPAR RPAR COLON type LCBRACE stms RCBRACE SEMI 			{$$ = t_decl_new_func($1,NULL,$6,$8);}
        |	    ID LPAR argdefs RPAR COLON type LCBRACE stms RCBRACE SEMI  		{$$ = t_decl_new_func($1,$3,$6,$8);}
        |	    DEFINE ID type SEMI							{$$ = t_decl_new_define($2,$3);}
                ;

argdefs: 	    argdef								{$$ = t_argdefs t_argdefs_new($1, NULL);}
        |	    argdef COMMA argdefs						{$$ = t_argdefs t_argdefs_new($1, $3);}
                ;

argdef:  	    ID COLON type							{$$ = t_argdef_new($1, $3);}
                ;

args:		    exp									{$$ = t_args_new($1, NULL);}
        |	    exp COMMA args							{$$ = t_args_new($1, $3);}
                ;

ids:     	    ID									{$$ = t_ids_new($1, NULL);}
        |	    ID COMMA ids							{$$ = t_ids_new($1, $3);}
                ;

stms:    	    stm									{$$ = t_stms t_stms_new($1, NULL);}
        |	    stm stms								{$$ = t_stms t_stms_new($1, $2);}
                ;

stm:     	    decl								{$$ = t_stm t_stm_new_decl($1);}
        |	    exp SEMI								{$$ = t_stm t_stm_new_exp($1);}
        |	    RETURN exp SEMI							{$$ = t_stm t_stm_new_return($2);}
        |	    IF exp THEN LCBRACE stms RCBRACE SEMI				{$$ = t_stm t_stm_new_if_else($2,$5,NULL);}
        |	    IF exp THEN LCBRACE stms RCBRACE ELSE LCBRACE stms RCBRACE SEMI	{$$ = t_stm t_stm_new_if_else($2,$5,$9);}
        |	    WHILE exp DO LCBRACE stms RCBRACE SEMI				{$$ = t_stm t_stm_new_while($2,$5);}
        |           NEXT								{$$ = t_stm t_stm_new_next();}
                ;

type:    	    T_INT 			 					{$$ = t_type_new_type(0,$1);}
        |	    T_FLOAT		 	 					{$$ = t_type_new_type(1,$1);}
        |	    T_STRING			 					{$$ = t_type_new_type(2,$1);}
        |	    T_BOOL			 					{$$ = t_type_new_type(3,$1);}
        |	    T_VOID			 					{$$ = t_type_new_type(4,$1);}
        |	    ID				 					{$$ = t_type_new_id($1);}
        |	    type LSBRACE INTLIT RSBRACE  					{$$ = t_type_new_arry($1,$3);}
                ;

lit:     	    INTLIT                       					{$$ = t_lit_new_intlit($1);}
        |	    FLOATLIT                    					{$$ = t_lit_new_floatlit($1);}
        |	    STRLIT                       					{$$ = t_lit_new_strlit($1);}
        |	    BOOLLIT                      					{$$ = t_lit_new_boollit($1);}
                ;

exp:     	    lit                          					{$$ = t_exp_new_lit($1);}
        |	    ID                          					{$$ = t_exp_new_id($1);}
        |	    exp LSBRACE INTLIT RSBRACE   					{$$ = t_exp_new_array($1,$3);}
        |	    exp ADD exp                  					{$$ = t_exp_new_binop($1, $3);}
        |	    exp SUB exp                  					{$$ = t_exp_new_binop($1, $3);}
        |	    exp MUL exp                  					{$$ = t_exp_new_binop($1, $3);}
        |	    exp DIV exp                  					{$$ = t_exp_new_binop($1, $3);}
        |	    exp POW exp                  					{$$ = t_exp_new_binop($1, $3);}
        |	    exp MOD exp                  					{$$ = t_exp_new_binop($1, $3);}
        |	    exp GT exp                   					{$$ = t_exp_new_binop($1, $3);}
        |	    exp LT exp                   					{$$ = t_exp_new_binop($1, $3);}
        |	    exp GEQ exp                  					{$$ = t_exp_new_binop($1, $3);}
        |	    exp LEQ exp                 					{$$ = t_exp_new_binop($1, $3);}
        |	    exp EQ exp                  					{$$ = t_exp_new_binop($1, $3);}
        |	    exp NEQ exp                  					{$$ = t_exp_new_binop($1, $3);}
        |	    exp AND exp                 					{$$ = t_exp_new_binop($1, $3);}
        |	    exp OR exp                  					{$$ = t_exp_new_binop($1, $3);}
        |	    NOT exp                     					{$$ = t_exp_new_unop($2);}
        |	    SUB exp  %prec NEG           					{$$ = t_exp_new_unop($2);}
        |	    LPAR exp RPAR                					{$$ = $2;}
        |	    ID LPAR RPAR                 					{$$ = t_exp_new_function($1,NULL);}
        |	    ID LPAR args RPAR            					{$$ = t_exp_new_function($1,$3);}
        |	    exp ASSIGN exp               					{$$ = t_exp_new_assign($1, $3);}
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
