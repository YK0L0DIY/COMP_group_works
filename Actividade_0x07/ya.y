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

%token SEMICOLON QUOTE
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
        |   ID LPAR args RPAR COLON type LBRACE statms RBRACE SEMICOLON
        |   ID LPAR args RPAR COLON T_VOID LBRACE statms RBRACE SEMICOLON

        //Define
        |   DEFINE ID type SEMICOLON
        ;

statms:
            statm
        |   statm statms
        ;

statm:
            decl
        |   IF bool_exp THEN LBRACE statms RBRACE SEMICOLON
        |   IF bool_exp THEN LBRACE statms RBRACE ELSE LBRACE statms RBRACE SEMICOLON
        |   WHILE bool_exp DO LBRACE statms RBRACE SEMICOLON
        |   BREAK SEMICOLON
        |   RETURN exp SEMICOLON
        ;

bool_exp:
            BOOL
        |   bool_exp AND bool_exp
        |   bool_exp OR bool_exp
        |   NOT bool_exp
        |   bool_exp NOT_EQUALS bool_exp
        |   bool_exp GREATER bool_exp
        |   bool_exp GREATER_EQUAL bool_exp
        |   bool_exp LESS bool_exp
        |   bool_exp LESS_EQUAL bool_exp
        ;

args:
            ID COLON type
        |   ID COLON type COMMA args
        ;

ids:
          ID
        | ID COMMA ids
        ;

exp:
            INT
        |   FLOAT
        |   STR
        |   bool_exp
        |   exp ADD exp
        |   exp SUB exp
        |   exp MUL exp
        |   exp DIV exp
        |   LPAR exp RPAR
        ;

type:
            T_INT
        |   T_FLOAT
        |   T_STR
        |   T_BOOL
        ;

%%

void yyerror (char const *s){
    fprintf (stderr, "%s\n", s);
}

int main (void){
    return yyparse();
}
