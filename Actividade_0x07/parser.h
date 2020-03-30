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
    DOT = 264,
    COMMA = 265,
    COLON = 266,
    NOT_EQUALS = 267,
    EQUALS = 268,
    LESS = 269,
    GREATER = 270,
    LESS_EQUAL = 271,
    GREATER_EQUAL = 272,
    OR = 273,
    AND = 274,
    NOT = 275,
    T_INT = 276,
    T_FLOAT = 277,
    T_STR = 278,
    T_BOOL = 279,
    T_VOID = 280,
    DEFINE = 281,
    IF = 282,
    THEN = 283,
    ELSE = 284,
    WHILE = 285,
    DO = 286,
    RETURN = 287,
    BREAK = 288,
    NEXT = 289,
    ASSIGN = 290,
    ADD = 291,
    SUB = 292,
    DIV = 293,
    MUL = 294,
    MOD = 295,
    POW = 296,
    NEG = 297,
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
#define DOT 264
#define COMMA 265
#define COLON 266
#define NOT_EQUALS 267
#define EQUALS 268
#define LESS 269
#define GREATER 270
#define LESS_EQUAL 271
#define GREATER_EQUAL 272
#define OR 273
#define AND 274
#define NOT 275
#define T_INT 276
#define T_FLOAT 277
#define T_STR 278
#define T_BOOL 279
#define T_VOID 280
#define DEFINE 281
#define IF 282
#define THEN 283
#define ELSE 284
#define WHILE 285
#define DO 286
#define RETURN 287
#define BREAK 288
#define NEXT 289
#define ASSIGN 290
#define ADD 291
#define SUB 292
#define DIV 293
#define MUL 294
#define MOD 295
#define POW 296
#define NEG 297
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
