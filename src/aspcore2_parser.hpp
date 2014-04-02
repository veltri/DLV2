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

/* Line 293 of yacc.c  */
#line 27 "src/aspcore2.y"

    char* string;
    char single_char;
    int integer;



/* Line 293 of yacc.c  */
#line 222 "src/aspcore2_parser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 234 "src/aspcore2_parser.hpp"

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
#define YYFINAL  62
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   346

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  121
/* YYNRULES -- Number of states.  */
#define YYNSTATES  192

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

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
      35,    36,    37,    38,    39,    40
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
     205,   207,   209,   214,   218,   221,   223,   227,   229,   231,
     233,   235,   237,   240,   242,   244,   246,   250,   252,   254,
     256,   259,   262,   265,   268,   271,   274,   277,   279,   281,
     284,   287,   290,   293,   296,   299,   301,   303,   305,   308,
     311,   313,   315,   317,   319,   324,   328,   330,   334,   336,
     338,   340
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,    35,    -1,    -1,    44,    -1,    44,    78,
      -1,     1,    -1,    44,    45,    -1,    45,    -1,    46,    15,
      -1,    46,    18,    15,    -1,    46,    18,    47,    15,    -1,
      18,    47,    15,    -1,    34,    47,    15,    48,    -1,    50,
      -1,    52,    -1,    51,    -1,    26,    72,    27,    -1,    26,
      72,    49,    27,    -1,    33,    72,    -1,    33,    72,    31,
      65,    -1,    31,    65,    -1,    63,    -1,    50,    42,    63,
      -1,    62,    -1,    50,    42,    62,    -1,    61,    -1,    51,
      31,    61,    -1,    53,    28,    55,    29,    54,    -1,    53,
      28,    55,    29,    -1,    28,    55,    29,    -1,    28,    55,
      29,    54,    -1,    72,    69,    -1,    69,    72,    -1,    55,
      16,    56,    -1,    56,    -1,    57,    -1,    57,    17,    58,
      -1,    64,    -1,    60,    -1,    58,    31,    60,    -1,    60,
      -1,    59,    31,    60,    -1,    63,    -1,    32,    63,    -1,
      67,    -1,    60,    -1,    90,    -1,    32,    90,    -1,    36,
      76,    64,    -1,    64,    -1,    30,    64,    -1,    77,    -1,
      77,    24,    65,    25,    -1,    77,    24,    25,    -1,    72,
      -1,    65,    31,    72,    -1,    73,    -1,    66,    31,    73,
      -1,    72,    69,    72,    -1,     7,    -1,     8,    -1,    68,
      -1,    91,    -1,    92,    -1,    20,    -1,    30,    -1,    21,
      -1,    22,    -1,    77,    -1,     4,    -1,    23,    -1,    77,
      24,    65,    25,    -1,    24,    72,    25,    -1,    30,    72,
      -1,    71,    -1,    72,    70,    71,    -1,    74,    -1,    75,
      -1,     3,    -1,     6,    -1,     4,    -1,    30,     4,    -1,
       5,    -1,    23,    -1,     5,    -1,    76,    31,     5,    -1,
       3,    -1,     6,    -1,     5,    -1,    64,    19,    -1,    72,
      68,    -1,    68,    72,    -1,    79,    93,    -1,    93,    80,
      -1,    72,    91,    -1,    82,    93,    -1,    83,    -1,    86,
      -1,    72,    92,    -1,    85,    93,    -1,    91,    72,    -1,
      92,    72,    -1,    93,    87,    -1,    93,    88,    -1,    84,
      -1,    89,    -1,    81,    -1,    83,    87,    -1,    86,    88,
      -1,     9,    -1,    11,    -1,    10,    -1,    12,    -1,    96,
      28,    94,    29,    -1,    94,    16,    95,    -1,    95,    -1,
      66,    17,    59,    -1,    37,    -1,    38,    -1,    39,    -1,
      40,    -1
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
     316,   317,   321,   322,   323,   327,   328,   329,   330,   334,
     339,   344,   352,   357,   361,   368,   369,   375,   376,   380,
     385,   390,   395,   403,   408,   419,   424,   432,   433,   434,
     438,   445,   453,   461,   462,   466,   474,   478,   479,   483,
     491,   495,   503,   511,   512,   516,   517,   518,   519,   520,
     524,   525,   529,   530,   534,   538,   539,   544,   551,   559,
     567,   575
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SYMBOLIC_CONSTANT", "NUMBER",
  "VARIABLE", "STRING", "EQUAL", "UNEQUAL", "LESS", "GREATER",
  "LESS_OR_EQ", "GREATER_OR_EQ", "ERROR", "NEWLINE", "DOT", "SEMICOLON",
  "COLON", "CONS", "QUERY_MARK", "PLUS", "TIMES", "SLASH", "ANON_VAR",
  "PARAM_OPEN", "PARAM_CLOSE", "SQUARE_OPEN", "SQUARE_CLOSE", "CURLY_OPEN",
  "CURLY_CLOSE", "DASH", "COMMA", "NAF", "AT", "WCONS", "VEL", "EXISTS",
  "AGGR_COUNT", "AGGR_MAX", "AGGR_MIN", "AGGR_SUM", "$accept",
  "HEAD_SEPARATOR", "program", "rules", "rule", "head", "body",
  "weight_at_levels", "levels_and_terms", "disjunction", "conjunction",
  "choice_atom", "lower_guard", "upper_guard", "choice_elements",
  "choice_element", "choice_element_atom", "choice_elements_literals",
  "naf_literals", "naf_literal", "naf_literal_aggregate",
  "existential_atom", "classic_literal", "atom", "terms", "basic_terms",
  "builtin_atom", "compareop", "binop", "arithop", "term_", "term",
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
     295
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    43,    43,    43,    43,    44,    44,    45,
      45,    45,    45,    45,    46,    46,    47,    48,    48,    49,
      49,    49,    50,    50,    50,    50,    51,    51,    52,    52,
      52,    52,    53,    54,    55,    55,    56,    56,    57,    58,
      58,    59,    59,    60,    60,    60,    61,    61,    61,    62,
      63,    63,    64,    64,    64,    65,    65,    66,    66,    67,
      68,    68,    69,    69,    69,    70,    70,    70,    70,    71,
      71,    71,    71,    71,    71,    72,    72,    73,    73,    74,
      74,    74,    74,    75,    75,    76,    76,    77,    77,    77,
      78,    79,    80,    81,    81,    82,    83,    84,    84,    85,
      86,    87,    88,    89,    89,    90,    90,    90,    90,    90,
      91,    91,    92,    92,    93,    94,    94,    95,    96,    96,
      96,    96
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     3,     2,     1,     3,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     3,     1,     1,     1,
       2,     2,     2,     2,     2,     2,     2,     1,     1,     2,
       2,     2,     2,     2,     2,     1,     1,     1,     2,     2,
       1,     1,     1,     1,     4,     3,     1,     3,     1,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     6,    87,    70,    89,    88,     0,    71,     0,     0,
       0,     0,     0,     0,     4,     8,     0,    14,    15,     0,
      24,    22,    50,    75,     0,    69,     0,   118,   119,   120,
     121,     0,    16,    46,    26,    43,    45,     0,     0,   107,
       0,    97,   105,     0,    98,   106,    47,     0,     0,     0,
       0,    69,     0,    35,    36,    38,    52,    51,    74,     0,
      85,     0,     1,     7,    50,     5,     9,     0,     2,     0,
       0,    60,    61,   110,   112,   111,   113,    65,    67,    68,
      66,    62,    32,     0,    63,    64,     0,    44,     0,    48,
      12,     0,    62,     0,    63,    64,    93,    96,   108,     0,
     100,   109,     0,     0,    94,   103,   104,     0,    73,     0,
       0,    30,     0,     0,     0,     0,    49,    90,    10,     0,
       0,    25,    23,     0,    76,    54,     0,    55,    91,    95,
      99,    27,    59,   101,   102,    92,    79,    81,    83,    80,
      84,     0,     0,    57,    77,    78,     0,   116,     0,    34,
      31,     0,     0,    37,    39,     0,     0,     0,    13,    86,
      11,    29,    72,     0,    82,     0,     0,     0,   114,    72,
      33,     0,    53,     0,    28,    56,   117,    41,    58,   115,
      40,    17,     0,     0,     0,     0,    21,    19,    18,    42,
       0,    20
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    69,    13,    14,    15,    16,    31,   158,   184,    17,
      32,    18,    19,   150,    52,    53,    54,   153,   176,    33,
      34,    20,    35,    22,   126,   142,    36,    81,    93,    83,
      23,   127,   143,   144,   145,    61,    51,    65,    38,   104,
      39,    40,    41,    42,    43,    44,    98,   101,    45,    46,
      84,    85,    47,   146,   147,    48
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -91
static const yytype_int16 yypact[] =
{
     213,   -91,   -91,   -91,   -91,   -91,   163,   -91,   289,   101,
     289,   163,    47,    53,   247,   -91,    46,    22,   -91,    34,
     -91,   -91,   -91,   -91,   313,   211,   185,   -91,   -91,   -91,
     -91,    70,    55,   -91,   -91,   -91,   -91,   313,   136,   -91,
     136,   107,   -91,   136,   128,   -91,   -91,   290,    85,   289,
      58,    98,    -4,   -91,   109,   -91,   108,   -91,    13,   116,
     -91,    41,   -91,   -91,   122,   -91,   -91,   105,   -91,    33,
     101,   -91,   -91,   -91,   -91,   -91,   -91,   -91,   -91,   -91,
     -91,   -91,   -91,   289,   -91,   -91,   285,   -91,   313,   -91,
     -91,   163,   142,   289,   217,   229,   -91,   -91,   -91,   289,
     -91,   -91,   289,   289,   -91,   -91,   -91,    91,   -91,   289,
     101,   290,   255,   285,   123,   149,   -91,   -91,   -91,   143,
     101,   -91,   -91,    26,   -91,   -91,    12,   126,   -91,   -91,
     -91,   -91,   126,   126,   126,   126,   -91,   -91,   -91,   -91,
     -91,   156,    23,   -91,   -91,   -91,    29,   -91,    35,   -91,
     -91,   289,    45,   130,   -91,   313,    59,   289,   -91,   -91,
     -91,   290,   311,   289,   -91,   255,    91,    91,   -91,   -91,
     126,   255,   -91,   103,   -91,   126,   131,   -91,   -91,   -91,
     -91,   -91,   289,   289,   137,   255,   139,   176,   -91,   -91,
     289,   139
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -91,   -91,   -91,   -91,   170,   -91,    -8,   -91,   -91,   -91,
     -91,   -91,   -91,    16,   124,    89,   -91,   -91,   -91,   -84,
     113,   141,     1,    -5,   -90,   -91,   -91,    -6,   -22,   -91,
     129,     0,    39,   -91,   -91,   -91,     7,   -91,   -91,   -91,
     -91,   -91,   -91,   -91,   -91,   -91,   164,   173,   -91,   195,
     -17,   -15,   112,   -91,    61,   -91
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -100
static const yytype_int16 yytable[] =
{
      24,    21,    82,    59,    55,    57,    37,    25,    50,    64,
      58,    37,   110,    25,    24,    21,    56,    25,    25,   148,
      94,    25,    95,   156,    99,   111,    88,    87,   154,   102,
      99,    92,   102,    25,    78,    79,     2,   162,     4,     5,
     165,   103,   110,   163,     2,   167,     4,     5,     2,    58,
       4,     5,    60,    62,   166,   161,   116,    68,   168,   119,
     169,    66,    70,   120,    67,    55,   163,    37,    56,    12,
     122,   129,   115,   130,    25,   120,    56,    56,    77,    78,
      79,   177,   128,   108,   172,    90,    91,   180,    80,   151,
     163,    37,   186,   132,   136,   137,   138,   139,    25,   133,
     191,   189,   134,   135,     2,    55,     4,     5,     2,     3,
       4,     5,   155,   107,   140,    57,    73,    56,    75,    25,
     118,   141,   109,    77,    78,    79,   112,    56,     7,     8,
     181,   114,   113,    80,   182,    10,   183,    26,    74,   151,
      76,   117,    27,    28,    29,    30,    77,    78,    79,   157,
      96,   170,    97,    87,   159,   100,    80,   173,   160,    56,
     164,   171,   185,   175,   188,   155,     2,     3,     4,     5,
     163,   155,    25,    27,    28,    29,    30,   174,    25,   -91,
     -91,   -91,   -91,   187,    63,   155,     7,     8,     2,     3,
       4,     5,    25,    10,   123,    26,    77,    78,    79,   149,
      27,    28,    29,    30,   131,   178,    80,   190,     7,     8,
     121,   105,   124,    -3,     1,    10,     2,     3,     4,     5,
     106,    89,    27,    28,    29,    30,   -52,   -52,   179,   -52,
     -52,     6,     0,     0,     0,    86,     7,     8,     0,     0,
     -52,     9,   -52,    10,     0,     0,   -52,    11,     0,    12,
       2,     3,     4,     5,   -95,   -95,   -95,   -95,     2,     3,
       4,     5,     0,     0,     0,     6,   -99,   -99,   -99,   -99,
       7,     8,     0,     0,     0,     9,     0,    10,     7,     8,
       0,    11,     0,    12,     0,    10,     0,   152,     2,     3,
       4,     5,     2,     3,     4,     5,     0,    71,    72,    73,
      74,    75,    76,     0,     0,     0,     0,     0,     7,     8,
     125,     0,     7,     8,     0,    49,     0,     0,     0,    49,
      71,    72,    73,    74,    75,    76,   -53,   -53,     0,   -53,
     -53,     0,     0,    77,    78,    79,     0,     0,     0,     0,
     -53,     0,   -53,    80,     0,     0,   -53
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-91))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,     0,    24,    11,     9,    10,     6,     0,     8,    14,
      10,    11,    16,     6,    14,    14,     9,    10,    11,   109,
      37,    14,    37,   113,    41,    29,    26,    26,   112,    44,
      47,    37,    47,    26,    21,    22,     3,    25,     5,     6,
      17,    47,    16,    31,     3,    16,     5,     6,     3,    49,
       5,     6,     5,     0,    31,    29,    61,    35,    29,    67,
      25,    15,    28,    30,    18,    70,    31,    67,    61,    36,
      69,    88,    31,    88,    67,    30,    69,    70,    20,    21,
      22,   165,    88,    25,    25,    15,    31,   171,    30,   111,
      31,    91,   182,    93,     3,     4,     5,     6,    91,    99,
     190,   185,   102,   103,     3,   110,     5,     6,     3,     4,
       5,     6,   112,    28,    23,   120,     9,   110,    11,   112,
      15,    30,    24,    20,    21,    22,    17,   120,    23,    24,
      27,    15,    24,    30,    31,    30,    33,    32,    10,   161,
      12,    19,    37,    38,    39,    40,    20,    21,    22,    26,
      38,   151,    40,   152,     5,    43,    30,   157,    15,   152,
       4,    31,    31,   163,    27,   165,     3,     4,     5,     6,
      31,   171,   165,    37,    38,    39,    40,   161,   171,    37,
      38,    39,    40,   183,    14,   185,    23,    24,     3,     4,
       5,     6,   185,    30,    70,    32,    20,    21,    22,   110,
      37,    38,    39,    40,    91,   166,    30,    31,    23,    24,
      69,    47,    83,     0,     1,    30,     3,     4,     5,     6,
      47,    26,    37,    38,    39,    40,    15,    16,   167,    18,
      19,    18,    -1,    -1,    -1,    24,    23,    24,    -1,    -1,
      29,    28,    31,    30,    -1,    -1,    35,    34,    -1,    36,
       3,     4,     5,     6,    37,    38,    39,    40,     3,     4,
       5,     6,    -1,    -1,    -1,    18,    37,    38,    39,    40,
      23,    24,    -1,    -1,    -1,    28,    -1,    30,    23,    24,
      -1,    34,    -1,    36,    -1,    30,    -1,    32,     3,     4,
       5,     6,     3,     4,     5,     6,    -1,     7,     8,     9,
      10,    11,    12,    -1,    -1,    -1,    -1,    -1,    23,    24,
      25,    -1,    23,    24,    -1,    30,    -1,    -1,    -1,    30,
       7,     8,     9,    10,    11,    12,    15,    16,    -1,    18,
      19,    -1,    -1,    20,    21,    22,    -1,    -1,    -1,    -1,
      29,    -1,    31,    30,    -1,    -1,    35
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,    18,    23,    24,    28,
      30,    34,    36,    43,    44,    45,    46,    50,    52,    53,
      62,    63,    64,    71,    72,    77,    32,    37,    38,    39,
      40,    47,    51,    60,    61,    63,    67,    72,    79,    81,
      82,    83,    84,    85,    86,    89,    90,    93,    96,    30,
      72,    77,    55,    56,    57,    64,    77,    64,    72,    47,
       5,    76,     0,    45,    64,    78,    15,    18,    35,    42,
      28,     7,     8,     9,    10,    11,    12,    20,    21,    22,
      30,    68,    69,    70,    91,    92,    24,    63,    72,    90,
      15,    31,    68,    69,    91,    92,    93,    93,    87,    91,
      93,    88,    92,    68,    80,    87,    88,    28,    25,    24,
      16,    29,    17,    24,    15,    31,    64,    19,    15,    47,
      30,    62,    63,    55,    71,    25,    65,    72,    68,    91,
      92,    61,    72,    72,    72,    72,     3,     4,     5,     6,
      23,    30,    66,    73,    74,    75,    94,    95,    65,    56,
      54,    69,    32,    58,    60,    72,    65,    26,    48,     5,
      15,    29,    25,    31,     4,    17,    31,    16,    29,    25,
      72,    31,    25,    72,    54,    72,    59,    60,    73,    95,
      60,    27,    31,    33,    49,    31,    65,    72,    27,    60,
      31,    65
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

  case 9:

/* Line 1806 of yacc.c  */
#line 78 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onRule(); 
        }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 82 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onRule(); 
        }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 86 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onRule(); 
        }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 90 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onConstraint(); 
        }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 94 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onWeakConstraint(); 
        }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 102 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onChoiceAtom();
        }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 113 "src/aspcore2.y"
    {
            // There is only the weight. No level and terms.
            InputDirector::getInstance().getBuilder()->onWeightAtLevels(1,0,0); 
        }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 118 "src/aspcore2.y"
    {
            // There are also a level and/or some terms.
            // The finalization has been postponed to "level_and_terms".
        }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 126 "src/aspcore2.y"
    {
            // There is no terms following the level.
            InputDirector::getInstance().getBuilder()->onWeightAtLevels(1,1,0); 
        }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 131 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onWeightAtLevels(1,1,(yyvsp[(4) - (4)].integer)); 
        }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 135 "src/aspcore2.y"
    { 
            // The level is omitted.
            // Thus, the first term, recognized as the
            // weight, should be a term of this list.
            InputDirector::getInstance().getBuilder()->onWeightAtLevels(0,0,(yyvsp[(2) - (2)].integer)+1); 
        }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 145 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onHeadAtom(); 
        }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 149 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onHeadAtom(); 
        }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 153 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onHeadAtom(); 
        }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 157 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onHeadAtom(); 
        }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 164 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onBodyLiteral(); 
        }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 168 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onBodyLiteral(); 
        }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 182 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onChoiceLowerGuard((yyvsp[(2) - (2)].string)); 
            delete (yyvsp[(2) - (2)].string);
        }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 190 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onChoiceUpperGuard((yyvsp[(1) - (2)].string)); 
            delete (yyvsp[(1) - (2)].string);
        }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 203 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onChoiceElement(); 
        }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 207 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onChoiceElement(); 
        }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 214 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onChoiceElementAtom(); 
        }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 221 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onChoiceElementLiteral(); 
        }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 225 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onChoiceElementLiteral();
        }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 232 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateNafLiteral();
        }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 236 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateNafLiteral();
        }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 243 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onNafLiteral();
        }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 247 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onNafLiteral(true);
        }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 251 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onNafLiteral();
        }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 259 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregate();
        }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 263 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregate(true);
        }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 270 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onExistentialAtom(); 
        }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 275 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->onAtom(); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 276 "src/aspcore2.y"
    { InputDirector::getInstance().getBuilder()->onAtom(true); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 281 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onPredicateName((yyvsp[(1) - (1)].string)); 
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 286 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onPredicateName((yyvsp[(1) - (4)].string)); 
            delete (yyvsp[(1) - (4)].string);
        }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 291 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onPredicateName((yyvsp[(1) - (3)].string)); 
            delete (yyvsp[(1) - (3)].string);
        }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 298 "src/aspcore2.y"
    { (yyval.integer) = 1; }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 299 "src/aspcore2.y"
    { (yyval.integer) = (yyvsp[(1) - (3)].integer) + 1; }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 309 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onBuiltinAtom((yyvsp[(2) - (3)].string));  
            delete (yyvsp[(2) - (3)].string);
        }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 316 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 317 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 321 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 322 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 323 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 327 "src/aspcore2.y"
    { (yyval.single_char) = '+'; }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 328 "src/aspcore2.y"
    { (yyval.single_char) = '-'; }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 329 "src/aspcore2.y"
    { (yyval.single_char) = '*'; }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 330 "src/aspcore2.y"
    { (yyval.single_char) = '/'; }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 335 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onTerm((yyvsp[(1) - (1)].string)); 
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 340 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onTerm((yyvsp[(1) - (1)].string)); 
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 345 "src/aspcore2.y"
    { 
            char* anonVar = new char[2];
            strcpy(anonVar,"_");
            anonVar[1] = '\0';
            InputDirector::getInstance().getBuilder()->onTerm(anonVar); 
            delete anonVar;
        }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 353 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onFunction((yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].integer)); 
            delete (yyvsp[(1) - (4)].string);
        }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 358 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onTermParams(); 
        }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 362 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onTermDash(); 
        }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 368 "src/aspcore2.y"
    {}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 370 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onArithmeticOperation((yyvsp[(2) - (3)].single_char)); 
        }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 375 "src/aspcore2.y"
    {}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 376 "src/aspcore2.y"
    {}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 381 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateGroundTerm((yyvsp[(1) - (1)].string));
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 386 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateGroundTerm((yyvsp[(1) - (1)].string));
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 391 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateGroundTerm((yyvsp[(1) - (1)].string));
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 396 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateGroundTerm((yyvsp[(2) - (2)].string),true);
            delete (yyvsp[(2) - (2)].string);
        }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 404 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onAggregateVariableTerm((yyvsp[(1) - (1)].string));
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 409 "src/aspcore2.y"
    {
            char* av = new char[2];
            strcpy(av,"_");
            av[1] = '\0';
            InputDirector::getInstance().getBuilder()->onAggregateVariableTerm(av);
            delete av;
        }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 420 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onExistentialVariable((yyvsp[(1) - (1)].string)); 
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 425 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onExistentialVariable((yyvsp[(3) - (3)].string));
            delete (yyvsp[(3) - (3)].string);
        }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 432 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 433 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 434 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 439 "src/aspcore2.y"
    { 
            InputDirector::getInstance().getBuilder()->onAtom(); 
        }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 446 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateLowerGuard((yyvsp[(2) - (2)].string));
            delete (yyvsp[(2) - (2)].string);
        }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 454 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateUpperGuard((yyvsp[(1) - (2)].string));
            delete (yyvsp[(1) - (2)].string);
        }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 467 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateLowerGuard((yyvsp[(2) - (2)].string));
            delete (yyvsp[(2) - (2)].string);
        }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 484 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateLowerGuard((yyvsp[(2) - (2)].string));
            delete (yyvsp[(2) - (2)].string);
        }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 496 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateUpperGuard((yyvsp[(1) - (2)].string));
            delete (yyvsp[(1) - (2)].string);
        }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 504 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateUpperGuard((yyvsp[(1) - (2)].string));
            delete (yyvsp[(1) - (2)].string);
        }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 524 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 525 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 529 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 530 "src/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 545 "src/aspcore2.y"
    {
            InputDirector::getInstance().getBuilder()->onAggregateElement();
        }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 552 "src/aspcore2.y"
    {
            char* f = new char[6];
            strcpy(f,"count");
            f[5] = '\0';
            InputDirector::getInstance().getBuilder()->onAggregateFunction(f);
            delete f;
        }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 560 "src/aspcore2.y"
    {
            char* f = new char[4];
            strcpy(f,"max");
            f[5] = '\0';
            InputDirector::getInstance().getBuilder()->onAggregateFunction(f);
            delete f;
        }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 568 "src/aspcore2.y"
    {
            char* f = new char[4];
            strcpy(f,"min");
            f[5] = '\0';
            InputDirector::getInstance().getBuilder()->onAggregateFunction(f);
            delete f;
        }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 576 "src/aspcore2.y"
    {
            char* f = new char[4];
            strcpy(f,"sum");
            f[5] = '\0';
            InputDirector::getInstance().getBuilder()->onAggregateFunction(f);
            delete f;
        }
    break;



/* Line 1806 of yacc.c  */
#line 2483 "src/aspcore2_parser.hpp"
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



