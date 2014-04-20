/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     DDOT = 271,
     SEMICOLON = 272,
     COLON = 273,
     CONS = 274,
     QUERY_MARK = 275,
     PLUS = 276,
     TIMES = 277,
     SLASH = 278,
     ANON_VAR = 279,
     PARAM_OPEN = 280,
     PARAM_CLOSE = 281,
     SQUARE_OPEN = 282,
     SQUARE_CLOSE = 283,
     CURLY_OPEN = 284,
     CURLY_CLOSE = 285,
     DASH = 286,
     COMMA = 287,
     NAF = 288,
     AT = 289,
     WCONS = 290,
     VEL = 291,
     EXISTS = 292,
     AGGR_COUNT = 293,
     AGGR_MAX = 294,
     AGGR_MIN = 295,
     AGGR_SUM = 296
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
#define DDOT 271
#define SEMICOLON 272
#define COLON 273
#define CONS 274
#define QUERY_MARK 275
#define PLUS 276
#define TIMES 277
#define SLASH 278
#define ANON_VAR 279
#define PARAM_OPEN 280
#define PARAM_CLOSE 281
#define SQUARE_OPEN 282
#define SQUARE_CLOSE 283
#define CURLY_OPEN 284
#define CURLY_CLOSE 285
#define DASH 286
#define COMMA 287
#define NAF 288
#define AT 289
#define WCONS 290
#define VEL 291
#define EXISTS 292
#define AGGR_COUNT 293
#define AGGR_MAX 294
#define AGGR_MIN 295
#define AGGR_SUM 296




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 27 "src/aspcore2.y"
{
    char* string;
    char single_char;
    int integer;
}
/* Line 1529 of yacc.c.  */
#line 137 "src/aspcore2_parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

