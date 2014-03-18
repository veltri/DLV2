/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
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



/* Line 268 of yacc.c  */
#line 98 "src/aspcore2_parser.hpp"

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
     ERROR = 262,
     NEWLINE = 263,
     DOT = 264,
     SEMICOLON = 265,
     COLON = 266,
     CONS = 267,
     QUERY_MARK = 268,
     PLUS = 269,
     TIMES = 270,
     SLASH = 271,
     ANON_VAR = 272,
     PARAM_OPEN = 273,
     PARAM_CLOSE = 274,
     SQUARE_OPEN = 275,
     SQUARE_CLOSE = 276,
     CURLY_OPEN = 277,
     CURLY_CLOSE = 278,
     EQUAL = 279,
     UNEQUAL = 280,
     LESS = 281,
     GREATER = 282,
     LESS_OR_EQ = 283,
     GREATER_OR_EQ = 284,
     DASH = 285,
     COMMA = 286,
     NAF = 287,
     AT = 288,
     WCONS = 289,
     VEL = 290,
     AGGR_COUNT = 291,
     AGGR_MAX = 292,
     AGGR_MIN = 293,
     AGGR_SUM = 294
   };
#endif
/* Tokens.  */
#define SYMBOLIC_CONSTANT 258
#define NUMBER 259
#define VARIABLE 260
#define STRING 261
#define ERROR 262
#define NEWLINE 263
#define DOT 264
#define SEMICOLON 265
#define COLON 266
#define CONS 267
#define QUERY_MARK 268
#define PLUS 269
#define TIMES 270
#define SLASH 271
#define ANON_VAR 272
#define PARAM_OPEN 273
#define PARAM_CLOSE 274
#define SQUARE_OPEN 275
#define SQUARE_CLOSE 276
#define CURLY_OPEN 277
#define CURLY_CLOSE 278
#define EQUAL 279
#define UNEQUAL 280
#define LESS 281
#define GREATER 282
#define LESS_OR_EQ 283
#define GREATER_OR_EQ 284
#define DASH 285
#define COMMA 286
#define NAF 287
#define AT 288
#define WCONS 289
#define VEL 290
#define AGGR_COUNT 291
#define AGGR_MAX 292
#define AGGR_MIN 293
#define AGGR_SUM 294




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 27 "src/aspcore2.y"

    char* string;
    int integer;



/* Line 293 of yacc.c  */
#line 219 "src/aspcore2_parser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 231 "src/aspcore2_parser.hpp"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  53
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   327

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNRULES -- Number of states.  */
#define YYNSTATES  175

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    16,    18,
      21,    25,    30,    34,    39,    41,    43,    45,    49,    54,
      57,    62,    65,    67,    71,    73,    77,    85,    91,    95,
     101,   105,   107,   109,   113,   115,   119,   121,   124,   126,
     128,   130,   133,   135,   138,   140,   145,   149,   151,   155,
     157,   161,   165,   167,   169,   171,   173,   175,   177,   179,
     181,   183,   185,   187,   189,   194,   198,   201,   203,   207,
     209,   211,   213,   215,   217,   220,   222,   224,   226,   228,
     230,   233,   237,   241,   245,   247,   249,   253,   257,   261,
     263,   265,   267,   271,   275,   277,   279,   281,   283,   288,
     292,   294,   298,   300,   302,   304
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      42,     0,    -1,    35,    -1,    -1,    43,    -1,    43,    71,
      -1,     1,    -1,    43,    44,    -1,    44,    -1,    45,     9,
      -1,    45,    12,     9,    -1,    45,    12,    46,     9,    -1,
      12,    46,     9,    -1,    34,    46,     9,    47,    -1,    49,
      -1,    51,    -1,    50,    -1,    20,    66,    21,    -1,    20,
      66,    48,    21,    -1,    33,    66,    -1,    33,    66,    31,
      59,    -1,    31,    59,    -1,    57,    -1,    49,    41,    57,
      -1,    56,    -1,    50,    31,    56,    -1,    66,    63,    22,
      52,    23,    63,    66,    -1,    66,    63,    22,    52,    23,
      -1,    22,    52,    23,    -1,    22,    52,    23,    63,    66,
      -1,    52,    10,    53,    -1,    53,    -1,    58,    -1,    58,
      11,    54,    -1,    55,    -1,    54,    31,    55,    -1,    57,
      -1,    32,    57,    -1,    61,    -1,    55,    -1,    77,    -1,
      32,    77,    -1,    58,    -1,    30,    58,    -1,    70,    -1,
      70,    18,    59,    19,    -1,    70,    18,    19,    -1,    66,
      -1,    59,    31,    66,    -1,    67,    -1,    60,    31,    67,
      -1,    66,    63,    66,    -1,    24,    -1,    25,    -1,    62,
      -1,    78,    -1,    79,    -1,    14,    -1,    30,    -1,    15,
      -1,    16,    -1,    70,    -1,     4,    -1,    17,    -1,    70,
      18,    59,    19,    -1,    18,    66,    19,    -1,    30,    66,
      -1,    65,    -1,    66,    64,    65,    -1,    68,    -1,    69,
      -1,     3,    -1,     6,    -1,     4,    -1,    30,     4,    -1,
       5,    -1,    17,    -1,     3,    -1,     6,    -1,     5,    -1,
      58,    13,    -1,    66,    62,    80,    -1,    80,    62,    66,
      -1,    66,    78,    80,    -1,    73,    -1,    75,    -1,    66,
      79,    80,    -1,    80,    78,    66,    -1,    80,    79,    66,
      -1,    74,    -1,    76,    -1,    72,    -1,    73,    78,    66,
      -1,    75,    79,    66,    -1,    26,    -1,    28,    -1,    27,
      -1,    29,    -1,    83,    22,    81,    23,    -1,    81,    10,
      82,    -1,    82,    -1,    60,    11,    54,    -1,    36,    -1,
      37,    -1,    38,    -1,    39,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    62,    62,    64,    66,    67,    68,    72,    73,    77,
      78,    79,    80,    81,    85,    86,    90,    93,    94,    97,
      98,    99,   103,   104,   108,   109,   112,   113,   114,   115,
     118,   119,   122,   123,   127,   128,   132,   133,   134,   138,
     139,   140,   144,   145,   149,   150,   151,   155,   156,   159,
     160,   165,   168,   169,   172,   173,   174,   177,   178,   179,
     180,   184,   189,   194,   199,   204,   208,   216,   217,   220,
     221,   225,   226,   227,   228,   232,   233,   237,   238,   239,
     242,   245,   246,   249,   251,   252,   255,   258,   259,   262,
     263,   264,   265,   266,   269,   270,   273,   274,   277,   280,
     281,   285,   288,   289,   290,   291
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SYMBOLIC_CONSTANT", "NUMBER",
  "VARIABLE", "STRING", "ERROR", "NEWLINE", "DOT", "SEMICOLON", "COLON",
  "CONS", "QUERY_MARK", "PLUS", "TIMES", "SLASH", "ANON_VAR", "PARAM_OPEN",
  "PARAM_CLOSE", "SQUARE_OPEN", "SQUARE_CLOSE", "CURLY_OPEN",
  "CURLY_CLOSE", "EQUAL", "UNEQUAL", "LESS", "GREATER", "LESS_OR_EQ",
  "GREATER_OR_EQ", "DASH", "COMMA", "NAF", "AT", "WCONS", "VEL",
  "AGGR_COUNT", "AGGR_MAX", "AGGR_MIN", "AGGR_SUM", "$accept",
  "HEAD_SEPARATOR", "program", "rules", "rule", "head", "body",
  "weight_at_levels", "levels_and_terms", "disjunction", "conjunction",
  "choice_atom", "choice_elements", "choice_element", "naf_literals",
  "naf_literal", "naf_literal_aggregate", "classic_literal", "atom",
  "terms", "basic_terms", "builtin_atom", "compareop", "binop", "arithop",
  "term_", "term", "basic_term", "ground_term", "variable_term",
  "identifier", "query", "compare_aggregate", "leftward_left_aggregate",
  "left_aggregate", "rightward_left_aggregate", "right_aggregate",
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    42,    42,    42,    43,    43,    44,
      44,    44,    44,    44,    45,    45,    46,    47,    47,    48,
      48,    48,    49,    49,    50,    50,    51,    51,    51,    51,
      52,    52,    53,    53,    54,    54,    55,    55,    55,    56,
      56,    56,    57,    57,    58,    58,    58,    59,    59,    60,
      60,    61,    62,    62,    63,    63,    63,    64,    64,    64,
      64,    65,    65,    65,    65,    65,    65,    66,    66,    67,
      67,    68,    68,    68,    68,    69,    69,    70,    70,    70,
      71,    72,    72,    73,    74,    74,    75,    76,    76,    77,
      77,    77,    77,    77,    78,    78,    79,    79,    80,    81,
      81,    82,    83,    83,    83,    83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     2,     1,     2,
       3,     4,     3,     4,     1,     1,     1,     3,     4,     2,
       4,     2,     1,     3,     1,     3,     7,     5,     3,     5,
       3,     1,     1,     3,     1,     3,     1,     2,     1,     1,
       1,     2,     1,     2,     1,     4,     3,     1,     3,     1,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     2,     1,     3,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       2,     3,     3,     3,     1,     1,     3,     3,     3,     1,
       1,     1,     3,     3,     1,     1,     1,     1,     4,     3,
       1,     3,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     6,    77,    62,    79,    78,     0,    63,     0,     0,
       0,     0,     0,     4,     8,     0,    14,    15,    22,    42,
      67,     0,    61,     0,   102,   103,   104,   105,     0,    16,
      39,    24,    36,    38,     0,    91,    84,    89,    85,    90,
      40,     0,     0,     0,     0,    61,     0,    31,    32,    44,
      43,    66,     0,     1,     7,    42,     5,     9,     0,     2,
       0,    57,    59,    60,    52,    53,    94,    96,    95,    97,
      58,    54,     0,     0,    55,    56,     0,    37,     0,    41,
      12,     0,    54,     0,    55,    56,     0,     0,     0,     0,
       0,     0,    65,     0,     0,    28,     0,     0,     0,    80,
      10,     0,     0,    23,     0,    68,    46,     0,    47,     0,
       0,     0,    25,    81,    51,    83,    86,    92,    93,    82,
      87,    88,    71,    73,    75,    72,    76,     0,     0,    49,
      69,    70,     0,   100,     0,    30,     0,     0,    33,    34,
       0,     0,     0,    13,    11,     0,    64,     0,    74,     0,
       0,     0,    98,    64,    29,     0,    45,     0,    27,    48,
     101,    50,    99,    35,    17,     0,     0,     0,     0,    21,
      19,    18,    26,     0,    20
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    60,    12,    13,    14,    15,    28,   143,   167,    16,
      29,    17,    46,    47,   138,    30,    31,    32,    19,   107,
     128,    33,    71,    83,    73,    20,   108,   129,   130,   131,
      45,    56,    35,    36,    37,    38,    39,    40,    74,    75,
      41,   132,   133,    42
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -93
static const yytype_int16 yypact[] =
{
     217,   -93,   -93,   -93,   -93,   -93,   171,   -93,   254,   121,
     254,   171,     5,    99,   -93,    66,   -26,   -93,   -93,   -93,
     -93,   291,   256,   194,   -93,   -93,   -93,   -93,    28,    42,
     -93,   -93,   -93,   -93,   291,   -93,    27,   -93,    80,   -93,
     -93,   298,    14,   254,   116,    26,    -3,   -93,    48,    75,
     -93,    83,    86,   -93,   -93,    71,   -93,   -93,   155,   -93,
      12,   -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,
     -93,   -93,    79,   254,   -93,   -93,   237,   -93,   291,   -93,
     -93,   171,   177,   254,   177,   177,   254,   254,   254,   254,
     254,   258,   -93,   254,   121,   298,    62,   237,    93,   -93,
     -93,    97,   121,   -93,   121,   -93,   -93,    31,    55,   177,
     177,   177,   -93,   -93,    55,   -93,   -93,    55,    55,    55,
      55,    55,   -93,   -93,   -93,   -93,   -93,   110,    10,   -93,
     -93,   -93,    23,   -93,    33,   -93,   254,    12,    88,   -93,
     291,    41,   254,   -93,   -93,    25,   273,   254,   -93,    62,
     258,   258,   -93,   -93,    55,    62,   -93,   279,   298,    55,
      88,   -93,   -93,   -93,   -93,   254,   254,   101,   254,   103,
     222,   -93,    55,   254,   103
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -93,   -93,   -93,   -93,   115,   -93,    -9,   -93,   -93,   -93,
     -93,   -93,    35,    43,    -8,   -92,    63,     1,    21,   -65,
     -93,   -93,   -22,   -18,   -93,    70,     0,    -5,   -93,   -93,
      16,   -93,   -93,   -93,   -93,   -93,   -93,   125,     4,    13,
      72,   -93,    -1,   -93
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -46
static const yytype_int16 yytable[] =
{
      21,    18,    52,    72,   139,    53,    34,    94,    44,    59,
      51,    34,    82,    21,    18,     2,    22,     4,     5,    88,
      95,   149,    22,    78,    77,    49,    22,    22,   134,    22,
      48,    50,   141,   151,    55,    94,    91,    80,    84,    22,
      86,   150,   102,    51,    93,    89,   152,    85,   158,   101,
     146,    87,   153,    66,    90,    68,   109,   139,    34,    96,
     156,   103,   147,   163,   147,     2,     3,     4,     5,    61,
      62,    63,   147,    81,    22,    57,    49,   136,    58,     7,
       8,    34,   110,   114,    99,    70,   117,   118,   119,   120,
     121,   111,    10,    97,   137,    98,   140,    22,    62,    63,
     169,   104,     2,     3,     4,     5,   144,    67,   174,    69,
      49,     6,    22,   142,   148,    48,     7,     8,    49,   155,
      49,     9,   171,    50,     2,    48,     4,     5,    54,    10,
      61,    62,    63,    11,   147,    92,   154,   135,    77,   145,
     168,   160,   157,   105,   112,   161,    70,   159,    79,   140,
     162,     0,     0,    49,   113,   140,   115,   116,     2,     3,
       4,     5,     0,     0,   100,    22,   170,     0,   172,     0,
       0,    22,     7,     8,     2,     3,     4,     5,     0,     0,
       0,   113,   115,   116,     0,    10,     0,    23,     7,     8,
       0,    24,    25,    26,    27,     0,     0,     2,     3,     4,
       5,    10,     0,    23,     0,     0,     0,    24,    25,    26,
      27,     7,     8,    24,    25,    26,    27,    -3,     1,     0,
       2,     3,     4,     5,    10,     0,     0,     0,     0,     6,
      24,    25,    26,    27,     7,     8,    61,    62,    63,     9,
       2,     3,     4,     5,     0,     0,     0,    10,     0,     0,
       0,    11,    70,   173,     7,     8,   106,     2,     3,     4,
       5,   122,   123,   124,   125,   -44,   -44,    43,   -44,   -44,
       0,     7,     8,     0,    76,   126,     0,     0,     0,   -44,
       0,     0,   -45,   -45,    43,   -45,   -45,   -44,   127,     0,
       0,   -44,     0,    61,    62,    63,   -45,     0,     0,     0,
     164,     0,     0,     0,   -45,    61,    62,    63,   -45,    70,
     165,     0,   166,     0,     0,    64,    65,    66,    67,    68,
      69,    70,    64,    65,    66,    67,    68,    69
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-93))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,     0,    11,    21,    96,     0,     6,    10,     8,    35,
      10,    11,    34,    13,    13,     3,     0,     5,     6,    41,
      23,    11,     6,    23,    23,     9,    10,    11,    93,    13,
       9,    10,    97,    10,    13,    10,    22,     9,    34,    23,
      36,    31,    30,    43,    18,    41,    23,    34,    23,    58,
      19,    38,    19,    26,    41,    28,    78,   149,    58,    11,
      19,    60,    31,   155,    31,     3,     4,     5,     6,    14,
      15,    16,    31,    31,    58,     9,    60,    95,    12,    17,
      18,    81,    78,    83,    13,    30,    86,    87,    88,    89,
      90,    78,    30,    18,    32,     9,    96,    81,    15,    16,
     165,    22,     3,     4,     5,     6,     9,    27,   173,    29,
      94,    12,    96,    20,     4,    94,    17,    18,   102,    31,
     104,    22,    21,   102,     3,   104,     5,     6,    13,    30,
      14,    15,    16,    34,    31,    19,   136,    94,   137,   104,
     158,   149,   142,    73,    81,   150,    30,   147,    23,   149,
     151,    -1,    -1,   137,    82,   155,    84,    85,     3,     4,
       5,     6,    -1,    -1,     9,   149,   166,    -1,   168,    -1,
      -1,   155,    17,    18,     3,     4,     5,     6,    -1,    -1,
      -1,   109,   110,   111,    -1,    30,    -1,    32,    17,    18,
      -1,    36,    37,    38,    39,    -1,    -1,     3,     4,     5,
       6,    30,    -1,    32,    -1,    -1,    -1,    36,    37,    38,
      39,    17,    18,    36,    37,    38,    39,     0,     1,    -1,
       3,     4,     5,     6,    30,    -1,    -1,    -1,    -1,    12,
      36,    37,    38,    39,    17,    18,    14,    15,    16,    22,
       3,     4,     5,     6,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    34,    30,    31,    17,    18,    19,     3,     4,     5,
       6,     3,     4,     5,     6,     9,    10,    30,    12,    13,
      -1,    17,    18,    -1,    18,    17,    -1,    -1,    -1,    23,
      -1,    -1,     9,    10,    30,    12,    13,    31,    30,    -1,
      -1,    35,    -1,    14,    15,    16,    23,    -1,    -1,    -1,
      21,    -1,    -1,    -1,    31,    14,    15,    16,    35,    30,
      31,    -1,    33,    -1,    -1,    24,    25,    26,    27,    28,
      29,    30,    24,    25,    26,    27,    28,    29
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,    12,    17,    18,    22,
      30,    34,    42,    43,    44,    45,    49,    51,    57,    58,
      65,    66,    70,    32,    36,    37,    38,    39,    46,    50,
      55,    56,    57,    61,    66,    72,    73,    74,    75,    76,
      77,    80,    83,    30,    66,    70,    52,    53,    58,    70,
      58,    66,    46,     0,    44,    58,    71,     9,    12,    35,
      41,    14,    15,    16,    24,    25,    26,    27,    28,    29,
      30,    62,    63,    64,    78,    79,    18,    57,    66,    77,
       9,    31,    62,    63,    78,    79,    78,    79,    62,    78,
      79,    22,    19,    18,    10,    23,    11,    18,     9,    13,
       9,    46,    30,    57,    22,    65,    19,    59,    66,    62,
      78,    79,    56,    80,    66,    80,    80,    66,    66,    66,
      66,    66,     3,     4,     5,     6,    17,    30,    60,    67,
      68,    69,    81,    82,    59,    53,    63,    32,    54,    55,
      66,    59,    20,    47,     9,    52,    19,    31,     4,    11,
      31,    10,    23,    19,    66,    31,    19,    66,    23,    66,
      54,    67,    82,    55,    21,    31,    33,    48,    63,    59,
      66,    21,    66,    31,    59
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

/* Line 1806 of yacc.c  */
#line 67 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->onQuery(); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 68 "src/aspcore2.y"
    { yyerror("Generic error"); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 72 "src/aspcore2.y"
    {}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 73 "src/aspcore2.y"
    {}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 77 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->onRule(); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 78 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->onRule(); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 79 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->onRule(); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 80 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->onConstraint(); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 81 "src/aspcore2.y"
    {}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 85 "src/aspcore2.y"
    {}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 86 "src/aspcore2.y"
    {}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 90 "src/aspcore2.y"
    {}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 93 "src/aspcore2.y"
    {}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 94 "src/aspcore2.y"
    {}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 97 "src/aspcore2.y"
    {}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 98 "src/aspcore2.y"
    {}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 99 "src/aspcore2.y"
    {}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 103 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->addToHead(); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 104 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->addToHead(); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 108 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->addToBody(); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 109 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->addToBody(); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 112 "src/aspcore2.y"
    {}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 113 "src/aspcore2.y"
    {}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 114 "src/aspcore2.y"
    {}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 115 "src/aspcore2.y"
    {}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 118 "src/aspcore2.y"
    {}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 119 "src/aspcore2.y"
    {}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 122 "src/aspcore2.y"
    {}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 123 "src/aspcore2.y"
    {}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 127 "src/aspcore2.y"
    {}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 128 "src/aspcore2.y"
    {}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 132 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->onNafLiteral(); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 133 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->onNafLiteral(true); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 134 "src/aspcore2.y"
    {}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 138 "src/aspcore2.y"
    {}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 139 "src/aspcore2.y"
    {}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 140 "src/aspcore2.y"
    {}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 144 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->onAtom(); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 145 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->onAtom(true); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 149 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->predicateName((yyvsp[(1) - (1)].string)); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 150 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->predicateName((yyvsp[(1) - (4)].string)); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 151 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->predicateName((yyvsp[(1) - (3)].string)); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 155 "src/aspcore2.y"
    { (yyval.integer) = (yyvsp[(1) - (1)].integer); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 156 "src/aspcore2.y"
    { (yyval.integer) = (yyvsp[(1) - (3)].integer) + (yyvsp[(3) - (3)].integer); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 159 "src/aspcore2.y"
    {}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 160 "src/aspcore2.y"
    {}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 165 "src/aspcore2.y"
    {}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 168 "src/aspcore2.y"
    {}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 169 "src/aspcore2.y"
    {}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 172 "src/aspcore2.y"
    {}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 173 "src/aspcore2.y"
    {}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 174 "src/aspcore2.y"
    {}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 177 "src/aspcore2.y"
    {}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 178 "src/aspcore2.y"
    {}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 179 "src/aspcore2.y"
    {}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 180 "src/aspcore2.y"
    {}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 185 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onTerm((yyvsp[(1) - (1)].string)); 
            (yyval.integer) = 1; 
        }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 190 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onTerm((yyvsp[(1) - (1)].string)); 
            (yyval.integer) = 1; 
        }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 195 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onTerm("_"); 
            (yyval.integer) = 1; 
        }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 200 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onFunction((yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].integer)); 
            (yyval.integer) = 1; 
        }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 205 "src/aspcore2.y"
    { 
            (yyval.integer) = 1;
        }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 209 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onTermDash(); 
            (yyval.integer) = (yyvsp[(2) - (2)].integer);
        }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 216 "src/aspcore2.y"
    { (yyval.integer) = (yyvsp[(1) - (1)].integer); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 217 "src/aspcore2.y"
    { (yyval.integer) = 1; }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 220 "src/aspcore2.y"
    {}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 221 "src/aspcore2.y"
    {}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 232 "src/aspcore2.y"
    {}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 233 "src/aspcore2.y"
    {}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 237 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 238 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 239 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 242 "src/aspcore2.y"
    {}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 245 "src/aspcore2.y"
    {}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 246 "src/aspcore2.y"
    {}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 249 "src/aspcore2.y"
    {}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 252 "src/aspcore2.y"
    {}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 255 "src/aspcore2.y"
    {}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 258 "src/aspcore2.y"
    {}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 259 "src/aspcore2.y"
    {}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 262 "src/aspcore2.y"
    {}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 263 "src/aspcore2.y"
    {}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 264 "src/aspcore2.y"
    {}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 265 "src/aspcore2.y"
    {}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 266 "src/aspcore2.y"
    {}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 269 "src/aspcore2.y"
    {}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 270 "src/aspcore2.y"
    {}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 273 "src/aspcore2.y"
    {}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 274 "src/aspcore2.y"
    {}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 277 "src/aspcore2.y"
    {}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 280 "src/aspcore2.y"
    {}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 281 "src/aspcore2.y"
    {}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 285 "src/aspcore2.y"
    {}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 288 "src/aspcore2.y"
    {}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 289 "src/aspcore2.y"
    {}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 290 "src/aspcore2.y"
    {}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 291 "src/aspcore2.y"
    {}
    break;



/* Line 1806 of yacc.c  */
#line 2344 "src/aspcore2_parser.hpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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
      if (!yypact_value_is_default (yyn))
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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



