%{
    #include <stdio.h>

    int yylex(void);
    void yyerror(char const*);

%}

%union {
    int ival;
    double fval;
    char *sval;
    char *id;
}

%token <ival>   INT
%token <fval>   FLOAT
%token <sval>   STR
%token <id>     ID
%token <ival>   BOOL

%token SEMICOLON
%token DOT COMMA COLON

%nonassoc NOT_EQUALS EQUALS
%nonassoc LESS GREATER LESS_EQUAL GREATER_EQUAL

%left OR
%left AND
%left NOT

%token T_INT
%token T_FLOAT
%token T_STR
%token T_BOOL
%token T_VOID

%token DEFINE
%token IF
%token THEN
%token ELSE
%token WHILE
%token DO
%token RETURN
%token BREAK
%token NEXT

%right ASSIGN

%left ADD SUB
%left DIV MUL
%left MOD

%right POW

%left NEG

%nonassoc LPAR RPAR
%nonassoc LBRACK RBRACK
%nonassoc LBRACE RBRACE

%%

program:
            /*¯\_(ツ)_/¯*/
        |   decls
        ;

decls:
            decl
        |   decl decls
        ;

decl:   //Variables
            ids COLON type SEMICOLON
        |   ids COLON type ASSIGN exp SEMICOLON

        //Functions
        |   ID LPAR RPAR COLON type LBRACE statms RBRACE SEMICOLON
        |   ID LPAR argdefs RPAR COLON type LBRACE statms RBRACE SEMICOLON

        //Define
        |   DEFINE ID type SEMICOLON
        ;

statms:
            statm
        |   statm statms
        ;

statm:
            decl
        |   exp SEMICOLON
        |   IF exp THEN LBRACE statms RBRACE SEMICOLON
        |   IF exp THEN LBRACE statms RBRACE ELSE LBRACE statms RBRACE SEMICOLON
        |   WHILE exp DO LBRACE statms RBRACE SEMICOLON
        |   BREAK SEMICOLON
        |   RETURN exp SEMICOLON
        |   NEXT
        ;

argdefs:
            ID COLON type
        |   ID COLON type COMMA argdefs
        ;

args:
            exp
        |   exp COMMA args
        ;

ids:
            ID
        |   ID COMMA ids
        ;

lit:
            INT
        |   FLOAT
        |   STR
        |   BOOL
        ;

exp:
            lit
        |   ID
        |   exp LBRACK INT RBRACK
        |   exp ADD exp
        |   exp SUB exp
        |   exp MUL exp
        |   exp DIV exp
        |   exp POW exp
        |   exp MOD exp

        //logical
        |   exp AND exp
        |   exp OR exp
        |   NOT exp
        |   exp EQUALS exp
        |   exp NOT_EQUALS exp
        |   exp GREATER exp
        |   exp GREATER_EQUAL exp
        |   exp LESS exp
        |   exp LESS_EQUAL exp

        |   LPAR exp RPAR
        |   SUB exp %prec NEG
        |   ID LPAR RPAR
        |   ID LPAR args RPAR
        |   exp ASSIGN exp
        ;

type:
            T_INT
        |   T_FLOAT
        |   T_STR
        |   T_BOOL
        |   T_VOID
        |   ID
        |   type LBRACK INT LBRACK
        ;

%%

void yyerror (char const *s){
    fprintf (stderr, "%s\n", s);
}

int main (void){
    return yyparse();
}
