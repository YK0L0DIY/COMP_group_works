%{
#include <stdlib.h> 
#include "calctypes.h"
#include "parser.h"

%}

INT  [0-9]+
ID   [a-zA-Z_][a-zA-Z_0-9]*
SPC  [\t ]*
			
%%

{INT}   {yylval.val = atof(yytext); return NUM;}
"+"	{ return ADD; }
"-"	{ return SUB; }
"/"	{ return DIV; }
"*"	{ return MUL; }
"("	{ return LPAR; }
")"	{ return RPAR; }
"="	{ return ASSIGN; }
"quit"	{ exit(0); }
\n	{ return NL; }
{ID}   {yylval.name = strdup(yytext); return ID;}
.	{/*ignorar (- ou dar erro?)*/}

%%

int yywrap()  {return 1;}
