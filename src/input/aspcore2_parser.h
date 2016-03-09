/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_SRC_INPUT_ASPCORE2_PARSER_H_INCLUDED
# define YY_YY_SRC_INPUT_ASPCORE2_PARSER_H_INCLUDED
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
    SYMBOLIC_CONSTANT = 258,
    NUMBER = 259,
    VARIABLE = 260,
    STRING = 261,
    DIRECTIVE_NAME = 262,
    DIRECTIVE_VALUE = 263,
    AGGR_COUNT = 264,
    AGGR_MAX = 265,
    AGGR_MIN = 266,
    AGGR_SUM = 267,
    ANNOTATION_RULE_ORDERING = 268,
    ANNOTATION_ORDERING_VALUE = 269,
    NUMBER_ANNOTATION = 270,
    ANNOTATION_RULE_ATOM_INDEXED = 271,
    ANNOTATION_ATOM_INDEXED = 272,
    ANNOTATION_ATOM_INDEXED_ARGUMENTS = 273,
    PARAM_OPEN_ANNOTATION = 274,
    PARAM_CLOSE_ANNOTATION = 275,
    DOT_ANNOTATION = 276,
    EQUAL_ANNOTATION = 277,
    COMMA_ANNOTATION = 278,
    ERROR = 279,
    NEWLINE = 280,
    DOT = 281,
    DDOT = 282,
    SEMICOLON = 283,
    COLON = 284,
    CONS = 285,
    QUERY_MARK = 286,
    PLUS = 287,
    TIMES = 288,
    SLASH = 289,
    ANON_VAR = 290,
    PARAM_OPEN = 291,
    PARAM_CLOSE = 292,
    SQUARE_OPEN = 293,
    SQUARE_CLOSE = 294,
    CURLY_OPEN = 295,
    CURLY_CLOSE = 296,
    EQUAL = 297,
    UNEQUAL = 298,
    LESS = 299,
    GREATER = 300,
    LESS_OR_EQ = 301,
    GREATER_OR_EQ = 302,
    DASH = 303,
    COMMA = 304,
    NAF = 305,
    AT = 306,
    WCONS = 307,
    VEL = 308,
    EXISTS = 309
  };
#endif
/* Tokens.  */
#define SYMBOLIC_CONSTANT 258
#define NUMBER 259
#define VARIABLE 260
#define STRING 261
#define DIRECTIVE_NAME 262
#define DIRECTIVE_VALUE 263
#define AGGR_COUNT 264
#define AGGR_MAX 265
#define AGGR_MIN 266
#define AGGR_SUM 267
#define ANNOTATION_RULE_ORDERING 268
#define ANNOTATION_ORDERING_VALUE 269
#define NUMBER_ANNOTATION 270
#define ANNOTATION_RULE_ATOM_INDEXED 271
#define ANNOTATION_ATOM_INDEXED 272
#define ANNOTATION_ATOM_INDEXED_ARGUMENTS 273
#define PARAM_OPEN_ANNOTATION 274
#define PARAM_CLOSE_ANNOTATION 275
#define DOT_ANNOTATION 276
#define EQUAL_ANNOTATION 277
#define COMMA_ANNOTATION 278
#define ERROR 279
#define NEWLINE 280
#define DOT 281
#define DDOT 282
#define SEMICOLON 283
#define COLON 284
#define CONS 285
#define QUERY_MARK 286
#define PLUS 287
#define TIMES 288
#define SLASH 289
#define ANON_VAR 290
#define PARAM_OPEN 291
#define PARAM_CLOSE 292
#define SQUARE_OPEN 293
#define SQUARE_CLOSE 294
#define CURLY_OPEN 295
#define CURLY_CLOSE 296
#define EQUAL 297
#define UNEQUAL 298
#define LESS 299
#define GREATER 300
#define LESS_OR_EQ 301
#define GREATER_OR_EQ 302
#define DASH 303
#define COMMA 304
#define NAF 305
#define AT 306
#define WCONS 307
#define VEL 308
#define EXISTS 309

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 29 "src/input/aspcore2.y" /* yacc.c:1909  */

    char* string;
    char single_char;
    int integer;

#line 168 "src/input/aspcore2_parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (DLV2::InputDirector& director);

#endif /* !YY_YY_SRC_INPUT_ASPCORE2_PARSER_H_INCLUDED  */
