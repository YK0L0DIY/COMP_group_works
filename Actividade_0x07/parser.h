/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    STR = 260,
    ID = 261,
    BOOL = 262,
    SEMICOLON = 263,
    QUOTE = 264,
    DOT = 265,
    COMMA = 266,
    COLON = 267,
    NOT_EQUALS = 268,
    EQUALS = 269,
    LESS = 270,
    GREATER = 271,
    LESS_EQUAL = 272,
    GREATER_EQUAL = 273,
    OR = 274,
    AND = 275,
    NOT = 276,
    T_INT = 277,
    T_FLOAT = 278,
    T_STR = 279,
    T_BOOL = 280,
    T_VOID = 281,
    DEFINE = 282,
    IF = 283,
    THEN = 284,
    ELSE = 285,
    WHILE = 286,
    DO = 287,
    RETURN = 288,
    BREAK = 289,
    NEXT = 290,
    ASSIGN = 291,
    ADD = 292,
    SUB = 293,
    DIV = 294,
    MUL = 295,
    MOD = 296,
    POW = 297,
    LPAR = 298,
    RPAR = 299,
    LBRACK = 300,
    RBRACK = 301,
    LBRACE = 302,
    RBRACE = 303
  };
#endif
/* Tokens.  */
#define INT 258
#define FLOAT 259
#define STR 260
#define ID 261
#define BOOL 262
#define SEMICOLON 263
#define QUOTE 264
#define DOT 265
#define COMMA 266
#define COLON 267
#define NOT_EQUALS 268
#define EQUALS 269
#define LESS 270
#define GREATER 271
#define LESS_EQUAL 272
#define GREATER_EQUAL 273
#define OR 274
#define AND 275
#define NOT 276
#define T_INT 277
#define T_FLOAT 278
#define T_STR 279
#define T_BOOL 280
#define T_VOID 281
#define DEFINE 282
#define IF 283
#define THEN 284
#define ELSE 285
#define WHILE 286
#define DO 287
#define RETURN 288
#define BREAK 289
#define NEXT 290
#define ASSIGN 291
#define ADD 292
#define SUB 293
#define DIV 294
#define MUL 295
#define MOD 296
#define POW 297
#define LPAR 298
#define RPAR 299
#define LBRACK 300
#define RBRACK 301
#define LBRACE 302
#define RBRACE 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 9 "ya.y" /* yacc.c:1909  */

    int ival;
    double fval;
    char *sval;
    char *id;

#line 157 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
