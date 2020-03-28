%option noyywrap
%option yylineno

%{
    #include <stdlib.h>
    #include <string.h>
    #include "parser.h"

    int line = 0;
    int column = 0;

    #define INC_RET(c, r)   column += c; return r
    #define INC_COL(c)      column += c
    #define INC_LINE()        line++; column = 0
%}

INT     [0-9]+
FLOAT   [0-9]+\.[0-9]+
STRING  \"[^\"]*\"
ID      [a-zA-Z_][a-zA-Z_0-9]*
SPC     [\t ]*

%%

";"         { INC_RET(1, SEMICOLON); }
"."         { INC_RET(1, DOT); }
","         { INC_RET(1, COMMA); }
":"         { INC_RET(1, COLON); }
"="         { INC_RET(1, ASSIGN); }

"("         { INC_RET(1, LPAR); }
")"         { INC_RET(1, RPAR); }
"["         { INC_RET(1, LBRACK); }
"]"         { INC_RET(1, RBRACK); }
"{"         { INC_RET(1, LBRACE); }
"}"         { INC_RET(1, RBRACE); }

"+"         { INC_RET(1, ADD); }
"-"         { INC_RET(1, SUB); }
"/"         { INC_RET(1, DIV); }
"*"         { INC_RET(1, MUL); }
"^"         { INC_RET(1, POW); }
"mod"       { INC_RET(3, MOD); }

"=="        { INC_RET(2, EQUALS); }
"<"         { INC_RET(1, LESS); }
">"         { INC_RET(1, GREATER); }
"<="        { INC_RET(2, LESS_EQUAL); }
">="        { INC_RET(2, GREATER_EQUAL); }
"!="        { INC_RET(2, NOT_EQUALS); }

"or"        { INC_RET(2, OR); }
"and"       { INC_RET(3, AND); }
"not"       { INC_RET(3, NOT); }

"int"       { INC_RET(3, T_INT); }
"float"     { INC_RET(5, T_FLOAT); }
"string"    { INC_RET(6, T_STR); }
"bool"      { INC_RET(4, T_BOOL); }
"void"      { INC_RET(4, T_VOID); }

"define"    { INC_RET(6, DEFINE); }

"if"        { INC_RET(2, IF); }
"then"      { INC_RET(4, THEN); }
"else"      { INC_RET(4, ELSE); }

"while"     { INC_RET(5, WHILE); }
"do"        { INC_RET(2, DO); }

"return"    { INC_RET(6, RETURN); }
"break"     { INC_RET(5, BREAK); }
"next"      { INC_RET(4, NEXT); }

"true"      { yylval.ival = 1;  INC_RET(4, BOOL); }
"false"     { yylval.ival = 0;  INC_RET(5, BOOL); }


{INT}       { yylval.ival = atoi(yytext); return INT; }
{FLOAT}     { yylval.fval = atof(yytext); return FLOAT; }
{ID}        { yylval.id = strdup(yytext); return ID; }
{STRING}    { yylval.sval = strdup(yytext); return STR; }
{SPC}       { INC_COL(strlen(yytext)); }

\n          {INC_LINE();}
.           {/*¯\_(ツ)_/¯*/}
