/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SYMBOLIC_CONSTANT = 258,
     NUMBER = 259,
     VARIABLE = 260,
     STRING = 261,
     DIRECTIVE_NAME = 262,
     DIRECTIVE_VALUE = 263,
     EQUAL = 264,
     UNEQUAL = 265,
     LESS = 266,
     GREATER = 267,
     LESS_OR_EQ = 268,
     GREATER_OR_EQ = 269,
     AGGR_COUNT = 270,
     AGGR_MAX = 271,
     AGGR_MIN = 272,
     AGGR_SUM = 273,
     ANON_VAR = 274,
     ERROR = 275,
     NEWLINE = 276,
     DOT = 277,
     DDOT = 278,
     SEMICOLON = 279,
     COLON = 280,
     CONS = 281,
     QUERY_MARK = 282,
     PLUS = 283,
     TIMES = 284,
     SLASH = 285,
     PARAM_OPEN = 286,
     PARAM_CLOSE = 287,
     SQUARE_OPEN = 288,
     SQUARE_CLOSE = 289,
     CURLY_OPEN = 290,
     CURLY_CLOSE = 291,
     DASH = 292,
     COMMA = 293,
     NAF = 294,
     AT = 295,
     WCONS = 296,
     VEL = 297,
     EXISTS = 298
   };
#endif
/* Tokens.  */
#define SYMBOLIC_CONSTANT 258
#define NUMBER 259
#define VARIABLE 260
#define STRING 261
#define DIRECTIVE_NAME 262
#define DIRECTIVE_VALUE 263
#define EQUAL 264
#define UNEQUAL 265
#define LESS 266
#define GREATER 267
#define LESS_OR_EQ 268
#define GREATER_OR_EQ 269
#define AGGR_COUNT 270
#define AGGR_MAX 271
#define AGGR_MIN 272
#define AGGR_SUM 273
#define ANON_VAR 274
#define ERROR 275
#define NEWLINE 276
#define DOT 277
#define DDOT 278
#define SEMICOLON 279
#define COLON 280
#define CONS 281
#define QUERY_MARK 282
#define PLUS 283
#define TIMES 284
#define SLASH 285
#define PARAM_OPEN 286
#define PARAM_CLOSE 287
#define SQUARE_OPEN 288
#define SQUARE_CLOSE 289
#define CURLY_OPEN 290
#define CURLY_CLOSE 291
#define DASH 292
#define COMMA 293
#define NAF 294
#define AT 295
#define WCONS 296
#define VEL 297
#define EXISTS 298




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 29 "src/input/aspcore2.y"

    char* string;
    char single_char;
    int integer;



/* Line 2068 of yacc.c  */
#line 144 "src/input/aspcore2_parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


