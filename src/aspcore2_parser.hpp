/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "src/aspcore2.y"

//////////////////////////////////////////////////////////////////////////////
// aspcore2.y

//////////////////////////////////////////////////////////////////////////////
/*
This file is part of the ASPCOMP2013 ASP-Core-2 validator (validator in the following)

    The validator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The validator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the validator.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "input/InputDirector.h"



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 27 "src/aspcore2.y"
{
    char* string;
    char single_char;
    int integer;
}
/* Line 193 of yacc.c.  */
#line 210 "src/aspcore2_parser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 223 "src/aspcore2_parser.hpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  64
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   335

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  123
/* YYNRULES -- Number of states.  */
#define YYNSTATES  195

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    16,    18,
      21,    25,    30,    34,    39,    41,    43,    45,    49,    54,
      57,    62,    65,    67,    71,    73,    77,    79,    83,    89,
      94,    98,   103,   106,   109,   113,   115,   117,   121,   123,
     125,   129,   131,   135,   137,   140,   142,   144,   146,   149,
     153,   155,   158,   160,   165,   169,   171,   175,   177,   181,
     185,   187,   189,   191,   193,   195,   197,   199,   201,   203,
     204,   207,   209,   212,   214,   219,   223,   226,   228,   232,
     234,   236,   238,   240,   242,   245,   247,   249,   251,   255,
     257,   259,   261,   264,   267,   270,   273,   276,   279,   282,
     284,   286,   289,   292,   295,   298,   301,   304,   306,   308,
     310,   313,   316,   318,   320,   322,   324,   329,   333,   335,
     339,   341,   343,   345
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      44,     0,    -1,    36,    -1,    -1,    45,    -1,    45,    80,
      -1,     1,    -1,    45,    46,    -1,    46,    -1,    47,    15,
      -1,    47,    19,    15,    -1,    47,    19,    48,    15,    -1,
      19,    48,    15,    -1,    35,    48,    15,    49,    -1,    51,
      -1,    53,    -1,    52,    -1,    27,    74,    28,    -1,    27,
      74,    50,    28,    -1,    34,    74,    -1,    34,    74,    32,
      66,    -1,    32,    66,    -1,    64,    -1,    51,    43,    64,
      -1,    63,    -1,    51,    43,    63,    -1,    62,    -1,    52,
      32,    62,    -1,    54,    29,    56,    30,    55,    -1,    54,
      29,    56,    30,    -1,    29,    56,    30,    -1,    29,    56,
      30,    55,    -1,    74,    70,    -1,    70,    74,    -1,    56,
      17,    57,    -1,    57,    -1,    58,    -1,    58,    18,    59,
      -1,    65,    -1,    61,    -1,    59,    32,    61,    -1,    61,
      -1,    60,    32,    61,    -1,    64,    -1,    33,    64,    -1,
      68,    -1,    61,    -1,    92,    -1,    33,    92,    -1,    37,
      78,    65,    -1,    65,    -1,    31,    65,    -1,    79,    -1,
      79,    25,    66,    26,    -1,    79,    25,    26,    -1,    74,
      -1,    66,    32,    74,    -1,    75,    -1,    67,    32,    75,
      -1,    74,    70,    74,    -1,     7,    -1,     8,    -1,    69,
      -1,    93,    -1,    94,    -1,    21,    -1,    31,    -1,    22,
      -1,    23,    -1,    -1,    16,     4,    -1,    79,    -1,     4,
      72,    -1,    24,    -1,    79,    25,    66,    26,    -1,    25,
      74,    26,    -1,    31,    74,    -1,    73,    -1,    74,    71,
      73,    -1,    76,    -1,    77,    -1,     3,    -1,     6,    -1,
       4,    -1,    31,     4,    -1,     5,    -1,    24,    -1,     5,
      -1,    78,    32,     5,    -1,     3,    -1,     6,    -1,     5,
      -1,    65,    20,    -1,    74,    69,    -1,    69,    74,    -1,
      81,    95,    -1,    95,    82,    -1,    74,    93,    -1,    84,
      95,    -1,    85,    -1,    88,    -1,    74,    94,    -1,    87,
      95,    -1,    93,    74,    -1,    94,    74,    -1,    95,    89,
      -1,    95,    90,    -1,    86,    -1,    91,    -1,    83,    -1,
      85,    89,    -1,    88,    90,    -1,     9,    -1,    11,    -1,
      10,    -1,    12,    -1,    98,    29,    96,    30,    -1,    96,
      17,    97,    -1,    97,    -1,    67,    18,    60,    -1,    38,
      -1,    39,    -1,    40,    -1,    41,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    62,    62,    64,    66,    67,    68,    72,    73,    77,
      81,    85,    89,    93,   100,   101,   108,   112,   117,   125,
     130,   134,   144,   148,   152,   156,   163,   167,   174,   175,
     176,   177,   181,   189,   197,   198,   202,   206,   213,   220,
     224,   231,   235,   242,   246,   250,   257,   258,   262,   269,
     275,   276,   280,   285,   290,   298,   299,   303,   304,   308,
     316,   317,   321,   322,   323,   327,   328,   329,   330,   333,
     336,   340,   345,   350,   358,   363,   367,   374,   375,   381,
     382,   386,   391,   396,   401,   409,   414,   425,   430,   438,
     439,   440,   444,   451,   459,   467,   468,   472,   480,   484,
     485,   489,   497,   501,   509,   517,   518,   522,   523,   524,
     525,   526,   530,   531,   535,   536,   540,   544,   545,   550,
     557,   565,   573,   581
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SYMBOLIC_CONSTANT", "NUMBER",
  "VARIABLE", "STRING", "EQUAL", "UNEQUAL", "LESS", "GREATER",
  "LESS_OR_EQ", "GREATER_OR_EQ", "ERROR", "NEWLINE", "DOT", "DDOT",
  "SEMICOLON", "COLON", "CONS", "QUERY_MARK", "PLUS", "TIMES", "SLASH",
  "ANON_VAR", "PARAM_OPEN", "PARAM_CLOSE", "SQUARE_OPEN", "SQUARE_CLOSE",
  "CURLY_OPEN", "CURLY_CLOSE", "DASH", "COMMA", "NAF", "AT", "WCONS",
  "VEL", "EXISTS", "AGGR_COUNT", "AGGR_MAX", "AGGR_MIN", "AGGR_SUM",
  "$accept", "HEAD_SEPARATOR", "program", "rules", "rule", "head", "body",
  "weight_at_levels", "levels_and_terms", "disjunction", "conjunction",
  "choice_atom", "lower_guard", "upper_guard", "choice_elements",
  "choice_element", "choice_element_atom", "choice_elements_literals",
  "naf_literals", "naf_literal", "naf_literal_aggregate",
  "existential_atom", "classic_literal", "atom", "terms", "basic_terms",
  "builtin_atom", "compareop", "binop", "arithop", "ddt", "term_", "term",
  "basic_term", "ground_term", "variable_term", "vars", "identifier",
  "query", "lower_guard_compare_aggregate",
  "upper_guard_compare_aggregate", "compare_aggregate",
  "lower_guard_leftward_left_aggregate", "leftward_left_aggregate",
  "left_aggregate", "lower_guard_rightward_left_aggregate",
  "rightward_left_aggregate", "upper_guard_leftward_right_aggregate",
  "upper_guard_rightward_right_aggregate", "right_aggregate",
  "aggregate_atom", "leftwardop", "rightwardop", "aggregate",
  "aggregate_elements", "aggregate_element", "aggregate_function", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    44,    44,    44,    45,    45,    46,
      46,    46,    46,    46,    47,    47,    48,    49,    49,    50,
      50,    50,    51,    51,    51,    51,    52,    52,    53,    53,
      53,    53,    54,    55,    56,    56,    57,    57,    58,    59,
      59,    60,    60,    61,    61,    61,    62,    62,    62,    63,
      64,    64,    65,    65,    65,    66,    66,    67,    67,    68,
      69,    69,    70,    70,    70,    71,    71,    71,    71,    72,
      72,    73,    73,    73,    73,    73,    73,    74,    74,    75,
      75,    76,    76,    76,    76,    77,    77,    78,    78,    79,
      79,    79,    80,    81,    82,    83,    83,    84,    85,    86,
      86,    87,    88,    89,    90,    91,    91,    92,    92,    92,
      92,    92,    93,    93,    94,    94,    95,    96,    96,    97,
      98,    98,    98,    98
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     2,     1,     2,
       3,     4,     3,     4,     1,     1,     1,     3,     4,     2,
       4,     2,     1,     3,     1,     3,     1,     3,     5,     4,
       3,     4,     2,     2,     3,     1,     1,     3,     1,     1,
       3,     1,     3,     1,     2,     1,     1,     1,     2,     3,
       1,     2,     1,     4,     3,     1,     3,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       2,     1,     2,     1,     4,     3,     2,     1,     3,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     3,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     2,     1,
       1,     2,     2,     2,     2,     2,     2,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     4,     3,     1,     3,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     6,    89,    69,    91,    90,     0,    73,     0,     0,
       0,     0,     0,     0,     4,     8,     0,    14,    15,     0,
      24,    22,    50,    77,     0,    71,     0,    72,     0,   120,
     121,   122,   123,     0,    16,    46,    26,    43,    45,     0,
       0,   109,     0,    99,   107,     0,   100,   108,    47,     0,
       0,     0,     0,    71,     0,    35,    36,    38,    52,    51,
      76,     0,    87,     0,     1,     7,    50,     5,     9,     0,
       2,     0,     0,    60,    61,   112,   114,   113,   115,    65,
      67,    68,    66,    62,    32,     0,    63,    64,     0,    70,
      44,     0,    48,    12,     0,    62,     0,    63,    64,    95,
      98,   110,     0,   102,   111,     0,     0,    96,   105,   106,
       0,    75,     0,     0,    30,     0,     0,     0,     0,    49,
      92,    10,     0,     0,    25,    23,     0,    78,    54,     0,
      55,    93,    97,   101,    27,    59,   103,   104,    94,    81,
      83,    85,    82,    86,     0,     0,    57,    79,    80,     0,
     118,     0,    34,    31,     0,     0,    37,    39,     0,     0,
       0,    13,    88,    11,    29,    74,     0,    84,     0,     0,
       0,   116,    74,    33,     0,    53,     0,    28,    56,   119,
      41,    58,   117,    40,    17,     0,     0,     0,     0,    21,
      19,    18,    42,     0,    20
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    71,    13,    14,    15,    16,    33,   161,   187,    17,
      34,    18,    19,   153,    54,    55,    56,   156,   179,    35,
      36,    20,    37,    22,   129,   145,    38,    83,    96,    85,
      27,    23,   130,   146,   147,   148,    63,    53,    67,    40,
     107,    41,    42,    43,    44,    45,    46,   101,   104,    47,
      48,    86,    87,    49,   149,   150,    50
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -104
static const yytype_int16 yypact[] =
{
     208,  -104,  -104,     3,  -104,  -104,   166,  -104,   260,   104,
     260,   166,    19,    25,   217,  -104,    31,     9,  -104,    34,
    -104,  -104,  -104,  -104,   267,   277,    44,  -104,    49,  -104,
    -104,  -104,  -104,    66,    84,  -104,  -104,  -104,  -104,   267,
     138,  -104,   138,    57,  -104,   138,    81,  -104,  -104,   261,
      88,   260,   296,   101,    14,  -104,   132,  -104,   126,  -104,
     113,   137,  -104,    54,  -104,  -104,   135,  -104,  -104,   108,
    -104,    94,   104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,   260,  -104,  -104,   256,  -104,
    -104,   267,  -104,  -104,   166,   285,   260,   290,   294,  -104,
    -104,  -104,   260,  -104,  -104,   260,   260,  -104,  -104,  -104,
     179,  -104,   260,   104,   261,   225,   256,   130,   153,  -104,
    -104,  -104,   144,   104,  -104,  -104,    26,  -104,  -104,    15,
     122,  -104,  -104,  -104,  -104,   122,   122,   122,   122,  -104,
    -104,  -104,  -104,  -104,   157,     2,  -104,  -104,  -104,    32,
    -104,    51,  -104,  -104,   260,    33,   131,  -104,   267,    72,
     260,  -104,  -104,  -104,   261,   284,   260,  -104,   225,   179,
     179,  -104,  -104,   122,   225,  -104,   106,  -104,   122,   133,
    -104,  -104,  -104,  -104,  -104,   260,   260,   136,   225,   141,
     194,  -104,  -104,   260,   141
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -104,  -104,  -104,  -104,   173,  -104,    -8,  -104,  -104,  -104,
    -104,  -104,  -104,    16,    95,    76,  -104,  -104,  -104,  -103,
      98,   123,     1,    -5,   -90,  -104,  -104,    -7,   -22,  -104,
    -104,   111,     0,    24,  -104,  -104,  -104,     7,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,   149,   151,  -104,
     174,   -16,    -9,    79,  -104,    48,  -104
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -102
static const yytype_int16 yytable[] =
{
      24,    21,    84,    61,    57,    59,    39,    25,    52,    66,
      60,    39,   157,    25,    24,    21,    58,    25,    25,    26,
     168,    25,   151,    97,    62,    64,   159,   102,    91,    90,
      98,   113,    95,   102,   169,    25,     2,   105,     4,     5,
     105,   165,   106,   113,   114,    70,    68,   166,    89,   170,
      69,    60,     2,     3,     4,     5,   164,     2,   119,     4,
       5,   122,   171,    72,   123,   180,    75,    57,    77,    39,
      58,   183,   125,     7,     8,   132,    25,   172,    58,    58,
      10,    93,   133,   166,   131,   192,   118,    29,    30,    31,
      32,    76,   154,    78,    39,   189,   135,     2,   175,     4,
       5,    25,   136,   194,   166,   137,   138,     2,    57,     4,
       5,     2,     3,     4,     5,   158,    94,   110,    59,    99,
      58,   100,    25,   121,   103,   123,   112,    79,    80,    81,
      58,    12,     7,     8,   184,    80,    81,    82,   185,    10,
     186,    28,   154,    79,    80,    81,    29,    30,    31,    32,
     115,   116,   117,    82,   173,   120,    90,   160,   162,   163,
     176,   167,    58,   174,   191,   188,   178,   126,   158,     2,
       3,     4,     5,   166,   158,    25,    29,    30,    31,    32,
     177,    25,   139,   140,   141,   142,   190,    65,   158,   152,
       7,     8,   134,   181,   124,    25,   127,    10,   108,    28,
     109,     0,    92,   143,    29,    30,    31,    32,    -3,     1,
     144,     2,     3,     4,     5,    79,    80,    81,   182,     0,
       2,     3,     4,     5,     0,    82,   193,     6,     2,     3,
       4,     5,     7,     8,     0,     0,     6,     9,     0,    10,
       0,     7,     8,    11,     0,    12,     9,     0,    10,     7,
       8,     0,    11,     0,    12,     0,    10,     0,   155,     2,
       3,     4,     5,     2,     3,     4,     5,     0,    73,    74,
      75,    76,    77,    78,    73,    74,    75,    76,    77,    78,
       7,     8,   128,     0,     7,     8,     0,    51,    79,    80,
      81,    51,   -52,     0,   -52,     0,   -52,   -52,    82,   -53,
       0,   -53,    88,   -53,   -53,     0,     0,   -52,     0,   -52,
       0,     0,     0,   -52,   -53,     0,   -53,    79,    80,    81,
     -53,     0,   111,   -93,   -93,   -93,   -93,    82,   -97,   -97,
     -97,   -97,  -101,  -101,  -101,  -101
};

static const yytype_int16 yycheck[] =
{
       0,     0,    24,    11,     9,    10,     6,     0,     8,    14,
      10,    11,   115,     6,    14,    14,     9,    10,    11,    16,
      18,    14,   112,    39,     5,     0,   116,    43,    28,    28,
      39,    17,    39,    49,    32,    28,     3,    46,     5,     6,
      49,    26,    49,    17,    30,    36,    15,    32,     4,    17,
      19,    51,     3,     4,     5,     6,    30,     3,    63,     5,
       6,    69,    30,    29,    31,   168,     9,    72,    11,    69,
      63,   174,    71,    24,    25,    91,    69,    26,    71,    72,
      31,    15,    91,    32,    91,   188,    32,    38,    39,    40,
      41,    10,   114,    12,    94,   185,    96,     3,    26,     5,
       6,    94,   102,   193,    32,   105,   106,     3,   113,     5,
       6,     3,     4,     5,     6,   115,    32,    29,   123,    40,
     113,    42,   115,    15,    45,    31,    25,    21,    22,    23,
     123,    37,    24,    25,    28,    22,    23,    31,    32,    31,
      34,    33,   164,    21,    22,    23,    38,    39,    40,    41,
      18,    25,    15,    31,   154,    20,   155,    27,     5,    15,
     160,     4,   155,    32,    28,    32,   166,    72,   168,     3,
       4,     5,     6,    32,   174,   168,    38,    39,    40,    41,
     164,   174,     3,     4,     5,     6,   186,    14,   188,   113,
      24,    25,    94,   169,    71,   188,    85,    31,    49,    33,
      49,    -1,    28,    24,    38,    39,    40,    41,     0,     1,
      31,     3,     4,     5,     6,    21,    22,    23,   170,    -1,
       3,     4,     5,     6,    -1,    31,    32,    19,     3,     4,
       5,     6,    24,    25,    -1,    -1,    19,    29,    -1,    31,
      -1,    24,    25,    35,    -1,    37,    29,    -1,    31,    24,
      25,    -1,    35,    -1,    37,    -1,    31,    -1,    33,     3,
       4,     5,     6,     3,     4,     5,     6,    -1,     7,     8,
       9,    10,    11,    12,     7,     8,     9,    10,    11,    12,
      24,    25,    26,    -1,    24,    25,    -1,    31,    21,    22,
      23,    31,    15,    -1,    17,    -1,    19,    20,    31,    15,
      -1,    17,    25,    19,    20,    -1,    -1,    30,    -1,    32,
      -1,    -1,    -1,    36,    30,    -1,    32,    21,    22,    23,
      36,    -1,    26,    38,    39,    40,    41,    31,    38,    39,
      40,    41,    38,    39,    40,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,    19,    24,    25,    29,
      31,    35,    37,    44,    45,    46,    47,    51,    53,    54,
      63,    64,    65,    73,    74,    79,    16,    72,    33,    38,
      39,    40,    41,    48,    52,    61,    62,    64,    68,    74,
      81,    83,    84,    85,    86,    87,    88,    91,    92,    95,
      98,    31,    74,    79,    56,    57,    58,    65,    79,    65,
      74,    48,     5,    78,     0,    46,    65,    80,    15,    19,
      36,    43,    29,     7,     8,     9,    10,    11,    12,    21,
      22,    23,    31,    69,    70,    71,    93,    94,    25,     4,
      64,    74,    92,    15,    32,    69,    70,    93,    94,    95,
      95,    89,    93,    95,    90,    94,    69,    82,    89,    90,
      29,    26,    25,    17,    30,    18,    25,    15,    32,    65,
      20,    15,    48,    31,    63,    64,    56,    73,    26,    66,
      74,    69,    93,    94,    62,    74,    74,    74,    74,     3,
       4,     5,     6,    24,    31,    67,    75,    76,    77,    96,
      97,    66,    57,    55,    70,    33,    59,    61,    74,    66,
      27,    49,     5,    15,    30,    26,    32,     4,    18,    32,
      17,    30,    26,    74,    32,    26,    74,    55,    74,    60,
      61,    75,    97,    61,    28,    32,    34,    50,    32,    66,
      74,    28,    61,    32,    66
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 5:
#line 67 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->onQuery(); }
    break;

  case 6:
#line 68 "src/aspcore2.y"
    { yyerror("Generic error"); }
    break;

  case 9:
#line 78 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onRule(); 
        }
    break;

  case 10:
#line 82 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onRule(); 
        }
    break;

  case 11:
#line 86 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onRule(); 
        }
    break;

  case 12:
#line 90 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onConstraint(); 
        }
    break;

  case 13:
#line 94 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onWeakConstraint(); 
        }
    break;

  case 15:
#line 102 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onChoiceAtom();
        }
    break;

  case 17:
#line 113 "src/aspcore2.y"
    {
            // There is only the weight. No level and terms.
            InputDirector::getInstance().getBuilder()->onWeightAtLevels(1,0,0); 
        }
    break;

  case 18:
#line 118 "src/aspcore2.y"
    {
            // There are also a level and/or some terms.
            // The finalization has been postponed to "level_and_terms".
        }
    break;

  case 19:
#line 126 "src/aspcore2.y"
    {
            // There is no terms following the level.
            InputDirector::getInstance().getBuilder()->onWeightAtLevels(1,1,0); 
        }
    break;

  case 20:
#line 131 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onWeightAtLevels(1,1,(yyvsp[(4) - (4)].integer)); 
        }
    break;

  case 21:
#line 135 "src/aspcore2.y"
    { 
            // The level is omitted.
            // Thus, the first term, recognized as the
            // weight, should be a term of this list.
            InputDirector::getInstance().getBuilder()->onWeightAtLevels(0,0,(yyvsp[(2) - (2)].integer)+1); 
        }
    break;

  case 22:
#line 145 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onHeadAtom(); 
        }
    break;

  case 23:
#line 149 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onHeadAtom(); 
        }
    break;

  case 24:
#line 153 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onHeadAtom(); 
        }
    break;

  case 25:
#line 157 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onHeadAtom(); 
        }
    break;

  case 26:
#line 164 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onBodyLiteral(); 
        }
    break;

  case 27:
#line 168 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onBodyLiteral(); 
        }
    break;

  case 32:
#line 182 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onChoiceLowerGuard((yyvsp[(2) - (2)].string)); 
            delete (yyvsp[(2) - (2)].string);
        }
    break;

  case 33:
#line 190 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onChoiceUpperGuard((yyvsp[(1) - (2)].string)); 
            delete (yyvsp[(1) - (2)].string);
        }
    break;

  case 36:
#line 203 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onChoiceElement(); 
        }
    break;

  case 37:
#line 207 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onChoiceElement(); 
        }
    break;

  case 38:
#line 214 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onChoiceElementAtom(); 
        }
    break;

  case 39:
#line 221 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onChoiceElementLiteral(); 
        }
    break;

  case 40:
#line 225 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onChoiceElementLiteral();
        }
    break;

  case 41:
#line 232 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateNafLiteral();
        }
    break;

  case 42:
#line 236 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateNafLiteral();
        }
    break;

  case 43:
#line 243 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onNafLiteral();
        }
    break;

  case 44:
#line 247 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onNafLiteral(true);
        }
    break;

  case 45:
#line 251 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onNafLiteral();
        }
    break;

  case 47:
#line 259 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregate();
        }
    break;

  case 48:
#line 263 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregate(true);
        }
    break;

  case 49:
#line 270 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onExistentialAtom(); 
        }
    break;

  case 50:
#line 275 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->onAtom(); }
    break;

  case 51:
#line 276 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->onAtom(true); }
    break;

  case 52:
#line 281 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onPredicateName((yyvsp[(1) - (1)].string)); 
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 53:
#line 286 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onPredicateName((yyvsp[(1) - (4)].string)); 
            delete (yyvsp[(1) - (4)].string);
        }
    break;

  case 54:
#line 291 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onPredicateName((yyvsp[(1) - (3)].string)); 
            delete (yyvsp[(1) - (3)].string);
        }
    break;

  case 55:
#line 298 "src/aspcore2.y"
    { (yyval.integer) = 1; }
    break;

  case 56:
#line 299 "src/aspcore2.y"
    { (yyval.integer) = (yyvsp[(1) - (3)].integer) + 1; }
    break;

  case 59:
#line 309 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onBuiltinAtom((yyvsp[(2) - (3)].string));  
            delete (yyvsp[(2) - (3)].string);
        }
    break;

  case 60:
#line 316 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 61:
#line 317 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 62:
#line 321 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 63:
#line 322 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 64:
#line 323 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 65:
#line 327 "src/aspcore2.y"
    { (yyval.single_char) = '+'; }
    break;

  case 66:
#line 328 "src/aspcore2.y"
    { (yyval.single_char) = '-'; }
    break;

  case 67:
#line 329 "src/aspcore2.y"
    { (yyval.single_char) = '*'; }
    break;

  case 68:
#line 330 "src/aspcore2.y"
    { (yyval.single_char) = '/'; }
    break;

  case 71:
#line 341 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onTerm((yyvsp[(1) - (1)].string)); 
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 72:
#line 346 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onTerm((yyvsp[(1) - (2)].string)); 
            delete (yyvsp[(1) - (2)].string);
        }
    break;

  case 73:
#line 351 "src/aspcore2.y"
    { 
            char* anonVar = new char[2];
            strcpy(anonVar,"_");
            anonVar[1] = '\0';
            InputDirector::getInstance().getBuilder()->onTerm(anonVar); 
            delete anonVar;
        }
    break;

  case 74:
#line 359 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onFunction((yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].integer)); 
            delete (yyvsp[(1) - (4)].string);
        }
    break;

  case 75:
#line 364 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onTermParams(); 
        }
    break;

  case 76:
#line 368 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onTermDash(); 
        }
    break;

  case 77:
#line 374 "src/aspcore2.y"
    {}
    break;

  case 78:
#line 376 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onArithmeticOperation((yyvsp[(2) - (3)].single_char)); 
        }
    break;

  case 79:
#line 381 "src/aspcore2.y"
    {}
    break;

  case 80:
#line 382 "src/aspcore2.y"
    {}
    break;

  case 81:
#line 387 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateGroundTerm((yyvsp[(1) - (1)].string));
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 82:
#line 392 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateGroundTerm((yyvsp[(1) - (1)].string));
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 83:
#line 397 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateGroundTerm((yyvsp[(1) - (1)].string));
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 84:
#line 402 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateGroundTerm((yyvsp[(2) - (2)].string),true);
            delete (yyvsp[(2) - (2)].string);
        }
    break;

  case 85:
#line 410 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onAggregateVariableTerm((yyvsp[(1) - (1)].string));
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 86:
#line 415 "src/aspcore2.y"
    {
            char* av = new char[2];
            strcpy(av,"_");
            av[1] = '\0';
            InputDirector::getInstance().getBuilder()->onAggregateVariableTerm(av);
            delete av;
        }
    break;

  case 87:
#line 426 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onExistentialVariable((yyvsp[(1) - (1)].string)); 
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 88:
#line 431 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onExistentialVariable((yyvsp[(3) - (3)].string));
            delete (yyvsp[(3) - (3)].string);
        }
    break;

  case 89:
#line 438 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 90:
#line 439 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 91:
#line 440 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 92:
#line 445 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onAtom(); 
        }
    break;

  case 93:
#line 452 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateLowerGuard((yyvsp[(2) - (2)].string));
            delete (yyvsp[(2) - (2)].string);
        }
    break;

  case 94:
#line 460 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateUpperGuard((yyvsp[(1) - (2)].string));
            delete (yyvsp[(1) - (2)].string);
        }
    break;

  case 97:
#line 473 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateLowerGuard((yyvsp[(2) - (2)].string));
            delete (yyvsp[(2) - (2)].string);
        }
    break;

  case 101:
#line 490 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateLowerGuard((yyvsp[(2) - (2)].string));
            delete (yyvsp[(2) - (2)].string);
        }
    break;

  case 103:
#line 502 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateUpperGuard((yyvsp[(1) - (2)].string));
            delete (yyvsp[(1) - (2)].string);
        }
    break;

  case 104:
#line 510 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateUpperGuard((yyvsp[(1) - (2)].string));
            delete (yyvsp[(1) - (2)].string);
        }
    break;

  case 112:
#line 530 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 113:
#line 531 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 114:
#line 535 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 115:
#line 536 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 119:
#line 551 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateElement();
        }
    break;

  case 120:
#line 558 "src/aspcore2.y"
    {
            char* f = new char[6];
            strcpy(f,"count");
            f[5] = '\0';
            InputDirector::getInstance().getBuilder()->onAggregateFunction(f);
            delete f;
        }
    break;

  case 121:
#line 566 "src/aspcore2.y"
    {
            char* f = new char[4];
            strcpy(f,"max");
            f[5] = '\0';
            InputDirector::getInstance().getBuilder()->onAggregateFunction(f);
            delete f;
        }
    break;

  case 122:
#line 574 "src/aspcore2.y"
    {
            char* f = new char[4];
            strcpy(f,"min");
            f[5] = '\0';
            InputDirector::getInstance().getBuilder()->onAggregateFunction(f);
            delete f;
        }
    break;

  case 123:
#line 582 "src/aspcore2.y"
    {
            char* f = new char[4];
            strcpy(f,"sum");
            f[5] = '\0';
            InputDirector::getInstance().getBuilder()->onAggregateFunction(f);
            delete f;
        }
    break;


/* Line 1267 of yacc.c.  */
#line 2264 "src/aspcore2_parser.hpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



