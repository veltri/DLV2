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
     EQUAL = 262,
     UNEQUAL = 263,
     LESS = 264,
     GREATER = 265,
     LESS_OR_EQ = 266,
     GREATER_OR_EQ = 267,
     ERROR = 268,
     NEWLINE = 269,
     DOT = 270,
     SEMICOLON = 271,
     COLON = 272,
     CONS = 273,
     QUERY_MARK = 274,
     PLUS = 275,
     TIMES = 276,
     SLASH = 277,
     ANON_VAR = 278,
     PARAM_OPEN = 279,
     PARAM_CLOSE = 280,
     SQUARE_OPEN = 281,
     SQUARE_CLOSE = 282,
     CURLY_OPEN = 283,
     CURLY_CLOSE = 284,
     DASH = 285,
     COMMA = 286,
     NAF = 287,
     AT = 288,
     WCONS = 289,
     VEL = 290,
     EXISTS = 291,
     AGGR_COUNT = 292,
     AGGR_MAX = 293,
     AGGR_MIN = 294,
     AGGR_SUM = 295
   };
#endif
/* Tokens.  */
#define SYMBOLIC_CONSTANT 258
#define NUMBER 259
#define VARIABLE 260
#define STRING 261
#define EQUAL 262
#define UNEQUAL 263
#define LESS 264
#define GREATER 265
#define LESS_OR_EQ 266
#define GREATER_OR_EQ 267
#define ERROR 268
#define NEWLINE 269
#define DOT 270
#define SEMICOLON 271
#define COLON 272
#define CONS 273
#define QUERY_MARK 274
#define PLUS 275
#define TIMES 276
#define SLASH 277
#define ANON_VAR 278
#define PARAM_OPEN 279
#define PARAM_CLOSE 280
#define SQUARE_OPEN 281
#define SQUARE_CLOSE 282
#define CURLY_OPEN 283
#define CURLY_CLOSE 284
#define DASH 285
#define COMMA 286
#define NAF 287
#define AT 288
#define WCONS 289
#define VEL 290
#define EXISTS 291
#define AGGR_COUNT 292
#define AGGR_MAX 293
#define AGGR_MIN 294
#define AGGR_SUM 295




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 27 "src/aspcore2.y"

    char* string;
    char single_char;
    int integer;



/* Line 2068 of yacc.c  */
#line 138 "src/aspcore2_parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


