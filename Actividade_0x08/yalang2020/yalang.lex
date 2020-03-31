%option noyywrap
%option yylineno

%{
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int line   = 0;
int column = 0;

#define INC_RET(x, y) column += x; return (y)
#define INC_COL(x)    column += x
#define INC_LINE      line++;      column = 0

void strappend(char **dest, char *new);

%}

INT      [0-9]+
FLOAT    [0-9]*\.[0-9]+
ID       [a-zA-Z][a-zA-Z_0-9]*
WHITESP  [\t ]+

%x string
			
%%

<string>[^\"\n]* { strappend(&yylval.str,yytext); INC_COL(strlen(yytext));}
<string>\n       { strappend(&yylval.str, "\n"); INC_LINE; }
<string>\"       { INC_COL(1); BEGIN(INITIAL); return STRLIT; }

\"               { INC_COL(1); yylval.str=strdup(""); BEGIN(string); }

{INT}            { yylval.ival=atof(yytext); INC_RET(strlen(yytext), INTLIT); }
{FLOAT}          { yylval.dval=atof(yytext); INC_RET(strlen(yytext), FLOATLIT); }

"+"              { INC_RET (1, ADD); }
"-"	             { INC_RET (1, SUB); }
"/"	             { INC_RET (1, DIV); }
"*"     	     { INC_RET (1, MUL); }
"^"              { INC_RET (1, POW); }
"mod"            { INC_RET (3, MOD); }

"=="             { INC_RET (2, EQ); }
"<"              { INC_RET (1, LT); }
">"	             { INC_RET (1, GT); }
"<="	         { INC_RET (2, LEQ); }
">="     	     { INC_RET (2, GEQ); }
"!="             { INC_RET (2, NEQ); }

"and"	         { INC_RET (3, AND); }
"or"     	     { INC_RET (2, OR); }
"not"            { INC_RET (3, NOT); }

"("     	     { INC_RET (1, LPAR); }
")"     	     { INC_RET (1, RPAR); }
"["              { INC_RET (1, LSBRACE); }
"]"              { INC_RET (1, RSBRACE); }
"{"              { INC_RET (1, LCBRACE); }
"}"              { INC_RET (1, RCBRACE); }

";"              { INC_RET (1, SEMI); }
":"              { INC_RET (1, COLON); }
"="              { INC_RET (1, ASSIGN); }
","              { INC_RET (1, COMMA); }

"return"         { INC_RET (6, RETURN); }
"while"          { INC_RET (5, WHILE); }
"break"          { INC_RET (5, BREAK); }
"next"           { INC_RET (4, NEXT); }
"if"             { INC_RET (2, IF); }
"then"           { INC_RET (4, THEN); }
"else"           { INC_RET (4, ELSE); }
"int"            { INC_RET (3, T_INT); }
"float"          { INC_RET (5, T_FLOAT); }
"string"         { INC_RET (6, T_STRING); }
"bool"           { INC_RET (4, T_BOOL); }
"void"           { INC_RET (4, T_VOID); }
"define"         { INC_RET (6, DEFINE); }
"do"             { INC_RET (2, DO); }
"struct"         { INC_RET (6, STRUCT); }
"true"           { yylval.ival = 1; INC_RET(4, BOOLLIT); }
"false"          { yylval.ival = 0; INC_RET(5, BOOLLIT); }

{ID}             { yylval.str = strdup(yytext); return(ID); }
\n      	     { INC_LINE; }
{WHITESP}        { INC_COL(strlen(yytext)); }
.       	     { printf("Lexical error: char %d at line %d\n", column, line);}

%%

void strappend(char **dest, char *new)
{
    int i;
    int len = strlen(*dest);
    int totlen = len + strlen(new) + 1;
    
    *dest = realloc(*dest, totlen);

    for (i=len; i < totlen; i++) {
      (*dest)[i] = new[i-len];
    }

    (*dest)[i] = 0;
}
