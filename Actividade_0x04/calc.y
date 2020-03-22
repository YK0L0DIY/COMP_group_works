%{
#include <stdio.h>
#include <string.h>

int yylex(void);
void yyerror(char const*);
void SET_VAR(char *ID, double val);
double GET_VAR(char *ID);

struct element {
    int val;
    char *id;

} vars[300];

int vp = 0;

%}

%union {
    double val;
    char *id;
}

%token  <val>       INTLIT  FLOATLIT
%token  <id>        ID
%token              NL

%right      ASSIGN
%left       SUB ADD
%left       MUL DIV
%left       NEG
%token      LPAR RPAR

%type   <val>       line exp

%%

input:      /*empty*/
        |   line input;

line:       NL      {$$ = 0;}
        |   exp NL  {$$ = $1; printf("%.2lf\n", $$);}

exp:        ID ASSIGN exp       {$$ = $3; SET_VAR($1, $3);}
        |   ID                  {$$ = GET_VAR($1);}
        |   FLOATLIT            {$$ = $1;}
        |   INTLIT              {$$ = $1;}
        |   exp ADD exp         {$$ = $1 + $3;}
        |   exp SUB exp         {$$ = $1 - $3;}
        |   exp MUL exp         {$$ = $1 * $3;}
        |   exp DIV exp         {$$ = $1 / $3;}
        |   SUB exp %prec NEG   {$$ = (0 - $2);}
        |   LPAR exp RPAR       {$$ = $2;}

%%

void yyerror(char const *s) {
    fprintf(stderr, "%s\n", s);
}

int EXISTS(char *id) {

    for(int i = 0; i <= vp; i++)
        if((vars[i].id != NULL) && (strcmp(vars[i].id, id) == 0))
            return i;

    return -1;
}

void SET_VAR(char *id, double val) {

    int var_index = EXISTS(id);

    if(var_index != -1) {

        vars[var_index].val = val;

    } else {

        vars[vp].id = id;
        vars[vp++].val = val;
    }

}

double GET_VAR(char *id) {

    int var_index = EXISTS(id);

    if(var_index != -1)
        return vars[var_index].val;

    else
        return -1;

}

int main(void) {
    return yyparse();
}
