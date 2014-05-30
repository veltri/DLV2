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
#line 1 "src/input/aspcore2.y"

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

#include "InputDirector.h"



/* Line 268 of yacc.c  */
#line 98 "src/input/aspcore2_parser.hpp"

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

/* Line 293 of yacc.c  */
#line 29 "src/input/aspcore2.y"

    char* string;
    char single_char;
    int integer;



/* Line 293 of yacc.c  */
#line 228 "src/input/aspcore2_parser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 240 "src/input/aspcore2_parser.hpp"

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
#define YYFINAL  67
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   372

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  126
/* YYNRULES -- Number of states.  */
#define YYNSTATES  201

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    15,    18,
      21,    23,    26,    30,    35,    39,    44,    46,    48,    50,
      54,    59,    62,    67,    70,    72,    76,    78,    82,    84,
      88,    94,    99,   103,   108,   111,   114,   118,   120,   122,
     126,   128,   130,   134,   136,   140,   142,   145,   147,   149,
     151,   154,   158,   160,   163,   165,   170,   174,   176,   180,
     182,   186,   190,   192,   194,   196,   198,   200,   202,   204,
     206,   208,   210,   212,   214,   219,   223,   227,   230,   232,
     236,   238,   240,   242,   244,   246,   249,   251,   253,   255,
     259,   261,   263,   265,   268,   272,   275,   278,   281,   284,
     287,   290,   293,   295,   297,   300,   303,   306,   309,   312,
     315,   317,   319,   321,   324,   327,   329,   331,   333,   335,
     340,   344,   346,   350,   352,   354,   356
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      46,     0,    -1,    42,    -1,    -1,    47,    -1,    82,    47,
      -1,     1,    -1,    48,    -1,    48,    83,    -1,    48,    49,
      -1,    49,    -1,    50,    22,    -1,    50,    26,    22,    -1,
      50,    26,    51,    22,    -1,    26,    51,    22,    -1,    41,
      51,    22,    52,    -1,    54,    -1,    56,    -1,    55,    -1,
      33,    76,    34,    -1,    33,    76,    53,    34,    -1,    40,
      76,    -1,    40,    76,    38,    69,    -1,    38,    69,    -1,
      67,    -1,    54,    45,    67,    -1,    66,    -1,    54,    45,
      66,    -1,    65,    -1,    55,    38,    65,    -1,    57,    35,
      59,    36,    58,    -1,    57,    35,    59,    36,    -1,    35,
      59,    36,    -1,    35,    59,    36,    58,    -1,    76,    73,
      -1,    73,    76,    -1,    59,    24,    60,    -1,    60,    -1,
      61,    -1,    61,    25,    62,    -1,    68,    -1,    64,    -1,
      62,    38,    64,    -1,    64,    -1,    63,    38,    64,    -1,
      67,    -1,    39,    67,    -1,    71,    -1,    64,    -1,    95,
      -1,    39,    95,    -1,    43,    80,    68,    -1,    68,    -1,
      37,    68,    -1,    81,    -1,    81,    31,    69,    32,    -1,
      81,    31,    32,    -1,    76,    -1,    69,    38,    76,    -1,
      77,    -1,    70,    38,    77,    -1,    76,    73,    76,    -1,
       9,    -1,    10,    -1,    72,    -1,    96,    -1,    97,    -1,
      28,    -1,    37,    -1,    29,    -1,    30,    -1,    81,    -1,
       4,    -1,    19,    -1,    81,    31,    69,    32,    -1,     4,
      23,     4,    -1,    31,    76,    32,    -1,    37,    76,    -1,
      75,    -1,    76,    74,    75,    -1,    78,    -1,    79,    -1,
       3,    -1,     6,    -1,     4,    -1,    37,     4,    -1,     5,
      -1,    19,    -1,     5,    -1,    80,    38,     5,    -1,     3,
      -1,     6,    -1,     5,    -1,     7,     8,    -1,    82,     7,
       8,    -1,    68,    27,    -1,    76,    72,    -1,    72,    76,
      -1,    84,    98,    -1,    98,    85,    -1,    76,    96,    -1,
      87,    98,    -1,    88,    -1,    91,    -1,    76,    97,    -1,
      90,    98,    -1,    96,    76,    -1,    97,    76,    -1,    98,
      92,    -1,    98,    93,    -1,    89,    -1,    94,    -1,    86,
      -1,    88,    92,    -1,    91,    93,    -1,    11,    -1,    13,
      -1,    12,    -1,    14,    -1,   101,    35,    99,    36,    -1,
      99,    24,   100,    -1,   100,    -1,    70,    25,    63,    -1,
      15,    -1,    16,    -1,    17,    -1,    18,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    63,    63,    65,    67,    68,    69,    73,    74,    78,
      79,    83,    87,    91,    95,    99,   106,   110,   118,   125,
     130,   138,   143,   147,   157,   161,   165,   169,   176,   180,
     187,   188,   189,   190,   194,   202,   210,   211,   215,   219,
     226,   233,   237,   244,   248,   255,   259,   263,   270,   271,
     275,   282,   288,   289,   293,   298,   303,   311,   312,   316,
     317,   321,   329,   330,   334,   335,   336,   340,   341,   342,
     343,   347,   352,   357,   362,   367,   373,   377,   384,   385,
     391,   392,   396,   401,   406,   411,   419,   424,   432,   437,
     445,   446,   447,   451,   458,   468,   475,   483,   491,   492,
     496,   504,   508,   509,   513,   521,   525,   533,   541,   542,
     546,   547,   548,   549,   550,   554,   555,   559,   560,   564,
     568,   569,   574,   581,   586,   591,   596
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SYMBOLIC_CONSTANT", "NUMBER",
  "VARIABLE", "STRING", "DIRECTIVE_NAME", "DIRECTIVE_VALUE", "EQUAL",
  "UNEQUAL", "LESS", "GREATER", "LESS_OR_EQ", "GREATER_OR_EQ",
  "AGGR_COUNT", "AGGR_MAX", "AGGR_MIN", "AGGR_SUM", "ANON_VAR", "ERROR",
  "NEWLINE", "DOT", "DDOT", "SEMICOLON", "COLON", "CONS", "QUERY_MARK",
  "PLUS", "TIMES", "SLASH", "PARAM_OPEN", "PARAM_CLOSE", "SQUARE_OPEN",
  "SQUARE_CLOSE", "CURLY_OPEN", "CURLY_CLOSE", "DASH", "COMMA", "NAF",
  "AT", "WCONS", "VEL", "EXISTS", "$accept", "HEAD_SEPARATOR", "program",
  "real_program", "rules", "rule", "head", "body", "weight_at_levels",
  "levels_and_terms", "disjunction", "conjunction", "choice_atom",
  "lower_guard", "upper_guard", "choice_elements", "choice_element",
  "choice_element_atom", "choice_elements_literals", "naf_literals",
  "naf_literal", "naf_literal_aggregate", "existential_atom",
  "classic_literal", "atom", "terms", "basic_terms", "builtin_atom",
  "compareop", "binop", "arithop", "term_", "term", "basic_term",
  "ground_term", "variable_term", "vars", "identifier", "directives",
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
     295,   296,   297,   298
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    46,    46,    46,    46,    47,    47,    48,
      48,    49,    49,    49,    49,    49,    50,    50,    51,    52,
      52,    53,    53,    53,    54,    54,    54,    54,    55,    55,
      56,    56,    56,    56,    57,    58,    59,    59,    60,    60,
      61,    62,    62,    63,    63,    64,    64,    64,    65,    65,
      65,    66,    67,    67,    68,    68,    68,    69,    69,    70,
      70,    71,    72,    72,    73,    73,    73,    74,    74,    74,
      74,    75,    75,    75,    75,    75,    75,    75,    76,    76,
      77,    77,    78,    78,    78,    78,    79,    79,    80,    80,
      81,    81,    81,    82,    82,    83,    84,    85,    86,    86,
      87,    88,    89,    89,    90,    91,    92,    93,    94,    94,
      95,    95,    95,    95,    95,    96,    96,    97,    97,    98,
      99,    99,   100,   101,   101,   101,   101
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     2,     2,
       1,     2,     3,     4,     3,     4,     1,     1,     1,     3,
       4,     2,     4,     2,     1,     3,     1,     3,     1,     3,
       5,     4,     3,     4,     2,     2,     3,     1,     1,     3,
       1,     1,     3,     1,     3,     1,     2,     1,     1,     1,
       2,     3,     1,     2,     1,     4,     3,     1,     3,     1,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     3,     2,     1,     3,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     3,
       1,     1,     1,     2,     3,     2,     2,     2,     2,     2,
       2,     2,     1,     1,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     2,     2,     1,     1,     1,     1,     4,
       3,     1,     3,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     6,    90,    72,    92,    91,     0,    73,     0,     0,
       0,     0,     0,     0,     0,     4,     7,    10,     0,    16,
      17,     0,    26,    24,    52,    78,     0,    71,     0,     0,
      93,   123,   124,   125,   126,     0,     0,    18,    48,    28,
      45,    47,     0,     0,   112,     0,   102,   110,     0,   103,
     111,    49,     0,     0,     0,     0,    71,     0,    37,    38,
      40,    54,    53,    77,     0,    88,     0,     1,     9,    52,
       8,    11,     0,     2,     0,     0,    62,    63,   115,   117,
     116,   118,    67,    69,    70,    68,    64,    34,     0,    65,
      66,     0,     0,     5,    75,    46,     0,    50,    14,     0,
      64,     0,    65,    66,    98,   101,   113,     0,   105,   114,
       0,     0,    99,   108,   109,     0,    76,     0,     0,    32,
       0,     0,     0,     0,    51,    95,    12,     0,     0,    27,
      25,     0,    79,    56,     0,    57,    94,    96,   100,   104,
      29,    61,   106,   107,    97,    82,    84,    86,    83,    87,
       0,     0,    59,    80,    81,     0,   121,     0,    36,    33,
       0,     0,    39,    41,     0,     0,     0,    15,    89,    13,
      31,    74,     0,    85,     0,     0,     0,   119,    74,    35,
       0,    55,     0,    30,    58,   122,    43,    60,   120,    42,
      19,     0,     0,     0,     0,    23,    21,    20,    44,     0,
      22
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    74,    14,    15,    16,    17,    18,    36,   167,   193,
      19,    37,    20,    21,   159,    57,    58,    59,   162,   185,
      38,    39,    22,    40,    24,   134,   151,    41,    86,   101,
      88,    25,   135,   152,   153,   154,    66,    56,    28,    70,
      43,   112,    44,    45,    46,    47,    48,    49,   106,   109,
      50,    51,    89,    90,    52,   155,   156,    53
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -118
static const yytype_int16 yypact[] =
{
     144,  -118,  -118,    18,  -118,  -118,    16,  -118,   281,   203,
     183,   203,   281,    60,    66,  -118,   211,  -118,     8,    39,
    -118,    38,  -118,  -118,  -118,  -118,   296,   310,   192,    96,
    -118,  -118,  -118,  -118,  -118,   298,    81,    70,  -118,  -118,
    -118,  -118,   296,   185,  -118,   185,   116,  -118,   185,    84,
    -118,  -118,   267,    69,   203,   124,    86,    24,  -118,    91,
    -118,   101,  -118,   -23,    90,  -118,    41,  -118,  -118,   110,
    -118,  -118,   252,  -118,    46,   183,  -118,  -118,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,   203,  -118,
    -118,   136,   125,  -118,  -118,  -118,   296,  -118,  -118,   281,
     346,   203,   350,   354,  -118,  -118,  -118,   203,  -118,  -118,
     203,   203,  -118,  -118,  -118,   256,  -118,   203,   183,   267,
      87,   136,   126,   152,  -118,  -118,  -118,   142,   183,  -118,
    -118,    26,  -118,  -118,    -7,   106,  -118,  -118,  -118,  -118,
    -118,   106,   106,   106,   106,  -118,  -118,  -118,  -118,  -118,
     154,    15,  -118,  -118,  -118,    31,  -118,    42,  -118,  -118,
     203,    65,   127,  -118,   296,    56,   203,  -118,  -118,  -118,
     267,   318,   203,  -118,    87,   256,   256,  -118,  -118,   106,
      87,  -118,    85,  -118,   106,   131,  -118,  -118,  -118,  -118,
    -118,   203,   203,   143,    87,   138,   235,  -118,  -118,   203,
     138
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -118,  -118,  -118,   150,  -118,   166,  -118,    -8,  -118,  -118,
    -118,  -118,  -118,  -118,    21,   108,    75,  -118,  -118,  -118,
    -117,   111,   139,     1,     3,   -94,  -118,  -118,   -37,   -24,
    -118,   117,     0,    37,  -118,  -118,  -118,    10,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,   167,   168,
    -118,   186,    -9,   -10,    13,  -118,    48,  -118
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -105
static const yytype_int16 yytable[] =
{
      26,    23,    87,   163,    64,   100,    83,    84,    42,    55,
      27,    63,    42,    60,    62,   111,    26,    23,    27,    69,
      61,    27,    27,   157,    30,   171,    27,   165,    26,    23,
      71,   172,   103,   102,    72,    96,    95,   107,    27,   110,
     174,    29,   110,   107,     2,    27,     4,     5,   118,     2,
     118,     4,     5,   175,    63,   176,   104,   186,   105,   137,
     119,   108,   170,   189,   127,    65,    67,   177,     2,   124,
       4,     5,    42,    75,   178,   130,    61,   198,    60,   123,
     172,    73,    27,   128,    61,    61,   139,   138,   181,    13,
       2,     3,     4,     5,   172,   160,    79,   195,    81,    42,
      94,   141,   128,    98,   115,   200,     7,   142,    99,    27,
     143,   144,   122,    82,    83,    84,   120,   117,     9,   190,
     164,    60,    85,   191,    11,   192,   161,    78,    61,    80,
      27,    62,   121,   136,    82,    83,    84,   125,    61,     2,
       3,     4,     5,    85,    -3,     1,   160,     2,     3,     4,
       5,     6,    82,    83,    84,     7,   116,   168,   173,   166,
     179,    85,    95,     7,   169,   180,   182,     9,   133,   194,
       8,    61,   184,    54,   164,     9,   172,   197,    93,    10,
     164,    11,    68,   131,    27,    12,     2,    13,     4,     5,
      27,   183,   196,   158,   164,     2,     3,     4,     5,    92,
      31,    32,    33,    34,    27,   132,     2,     3,     4,     5,
     140,     7,   187,   129,     2,     3,     4,     5,     8,   113,
     114,    97,     7,     9,   188,     0,     0,    10,     0,    11,
       7,     0,     0,    12,     9,    13,     0,     8,     0,     0,
      54,     0,     9,     0,     0,     0,    10,     0,    11,     0,
       0,     0,    12,     0,    13,     2,     3,     4,     5,   145,
     146,   147,   148,    82,    83,    84,     0,    31,    32,    33,
      34,     7,    85,   199,   126,   149,    76,    77,    78,    79,
      80,    81,     0,     9,     2,     3,     4,     5,     0,    11,
       0,    35,     0,   150,     0,     0,    31,    32,    33,    34,
       7,     2,     3,     4,     5,    76,    77,    78,    79,    80,
      81,     0,     9,    31,    32,    33,    34,     7,    11,     0,
      35,     0,     0,     0,    82,    83,    84,     0,     0,     9,
       0,     0,   -54,    85,   -54,    11,   -54,   -54,     0,     0,
     -55,    91,   -55,     0,   -55,   -55,   -54,     0,   -54,     0,
       0,     0,   -54,     0,   -55,     0,   -55,     0,     0,     0,
     -55,   -96,   -96,   -96,   -96,  -100,  -100,  -100,  -100,  -104,
    -104,  -104,  -104
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-118))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,     0,    26,   120,    12,    42,    29,    30,     8,     9,
       0,    11,    12,    10,    11,    52,    16,    16,     8,    16,
      10,    11,    12,   117,     8,    32,    16,   121,    28,    28,
      22,    38,    42,    42,    26,    35,    35,    46,    28,    49,
      25,    23,    52,    52,     3,    35,     5,     6,    24,     3,
      24,     5,     6,    38,    54,    24,    43,   174,    45,    96,
      36,    48,    36,   180,    72,     5,     0,    36,     3,    66,
       5,     6,    72,    35,    32,    74,    66,   194,    75,    38,
      38,    42,    72,    37,    74,    75,    96,    96,    32,    43,
       3,     4,     5,     6,    38,   119,    12,   191,    14,    99,
       4,   101,    37,    22,    35,   199,    19,   107,    38,    99,
     110,   111,    22,    28,    29,    30,    25,    31,    31,    34,
     120,   118,    37,    38,    37,    40,    39,    11,   118,    13,
     120,   128,    31,     8,    28,    29,    30,    27,   128,     3,
       4,     5,     6,    37,     0,     1,   170,     3,     4,     5,
       6,     7,    28,    29,    30,    19,    32,     5,     4,    33,
     160,    37,   161,    19,    22,    38,   166,    31,    32,    38,
      26,   161,   172,    37,   174,    31,    38,    34,    28,    35,
     180,    37,    16,    75,   174,    41,     3,    43,     5,     6,
     180,   170,   192,   118,   194,     3,     4,     5,     6,     7,
      15,    16,    17,    18,   194,    88,     3,     4,     5,     6,
      99,    19,   175,    74,     3,     4,     5,     6,    26,    52,
      52,    35,    19,    31,   176,    -1,    -1,    35,    -1,    37,
      19,    -1,    -1,    41,    31,    43,    -1,    26,    -1,    -1,
      37,    -1,    31,    -1,    -1,    -1,    35,    -1,    37,    -1,
      -1,    -1,    41,    -1,    43,     3,     4,     5,     6,     3,
       4,     5,     6,    28,    29,    30,    -1,    15,    16,    17,
      18,    19,    37,    38,    22,    19,     9,    10,    11,    12,
      13,    14,    -1,    31,     3,     4,     5,     6,    -1,    37,
      -1,    39,    -1,    37,    -1,    -1,    15,    16,    17,    18,
      19,     3,     4,     5,     6,     9,    10,    11,    12,    13,
      14,    -1,    31,    15,    16,    17,    18,    19,    37,    -1,
      39,    -1,    -1,    -1,    28,    29,    30,    -1,    -1,    31,
      -1,    -1,    22,    37,    24,    37,    26,    27,    -1,    -1,
      22,    31,    24,    -1,    26,    27,    36,    -1,    38,    -1,
      -1,    -1,    42,    -1,    36,    -1,    38,    -1,    -1,    -1,
      42,    15,    16,    17,    18,    15,    16,    17,    18,    15,
      16,    17,    18
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,    19,    26,    31,
      35,    37,    41,    43,    46,    47,    48,    49,    50,    54,
      56,    57,    66,    67,    68,    75,    76,    81,    82,    23,
       8,    15,    16,    17,    18,    39,    51,    55,    64,    65,
      67,    71,    76,    84,    86,    87,    88,    89,    90,    91,
      94,    95,    98,   101,    37,    76,    81,    59,    60,    61,
      68,    81,    68,    76,    51,     5,    80,     0,    49,    68,
      83,    22,    26,    42,    45,    35,     9,    10,    11,    12,
      13,    14,    28,    29,    30,    37,    72,    73,    74,    96,
      97,    31,     7,    47,     4,    67,    76,    95,    22,    38,
      72,    73,    96,    97,    98,    98,    92,    96,    98,    93,
      97,    72,    85,    92,    93,    35,    32,    31,    24,    36,
      25,    31,    22,    38,    68,    27,    22,    51,    37,    66,
      67,    59,    75,    32,    69,    76,     8,    72,    96,    97,
      65,    76,    76,    76,    76,     3,     4,     5,     6,    19,
      37,    70,    77,    78,    79,    99,   100,    69,    60,    58,
      73,    39,    62,    64,    76,    69,    33,    52,     5,    22,
      36,    32,    38,     4,    25,    38,    24,    36,    32,    76,
      38,    32,    76,    58,    76,    63,    64,    77,   100,    64,
      34,    38,    40,    53,    38,    69,    76,    34,    64,    38,
      69
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
      yyerror (director, YY_("syntax error: cannot back up")); \
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
# define YYLEX yylex (director)
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
		  Type, Value, director); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, DLV2::InputDirector& director)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, director)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    DLV2::InputDirector& director;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (director);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, DLV2::InputDirector& director)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, director)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    DLV2::InputDirector& director;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, director);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, DLV2::InputDirector& director)
#else
static void
yy_reduce_print (yyvsp, yyrule, director)
    YYSTYPE *yyvsp;
    int yyrule;
    DLV2::InputDirector& director;
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
		       		       , director);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, director); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, DLV2::InputDirector& director)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, director)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    DLV2::InputDirector& director;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (director);

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
int yyparse (DLV2::InputDirector& director);
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
yyparse (DLV2::InputDirector& director)
#else
int
yyparse (director)
    DLV2::InputDirector& director;
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
        case 6:

/* Line 1806 of yacc.c  */
#line 69 "src/input/aspcore2.y"
    { yyerror(director,"Generic error"); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 74 "src/input/aspcore2.y"
    { director.getBuilder()->onQuery(); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 84 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onRule(); 
        }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 88 "src/input/aspcore2.y"
    {
            director.getBuilder()->onRule(); 
        }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 92 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onRule(); 
        }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 96 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onConstraint(); 
        }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 100 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onWeakConstraint(); 
        }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 107 "src/input/aspcore2.y"
    {
            director.getBuilder()->onHead();
        }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 111 "src/input/aspcore2.y"
    {
            director.getBuilder()->onChoiceAtom();
            director.getBuilder()->onHead();
        }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 119 "src/input/aspcore2.y"
    {
            director.getBuilder()->onBody();
        }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 126 "src/input/aspcore2.y"
    {
            // There is only the weight. No level and terms.
            director.getBuilder()->onWeightAtLevels(1,0,0); 
        }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 131 "src/input/aspcore2.y"
    {
            // There are also a level and/or some terms.
            // The finalization has been postponed to "level_and_terms".
        }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 139 "src/input/aspcore2.y"
    {
            // There is no terms following the level.
            director.getBuilder()->onWeightAtLevels(1,1,0); 
        }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 144 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onWeightAtLevels(1,1,(yyvsp[(4) - (4)].integer)); 
        }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 148 "src/input/aspcore2.y"
    { 
            // The level is omitted.
            // Thus, the first term, recognized as the
            // weight, should be a term of this list.
            director.getBuilder()->onWeightAtLevels(0,0,(yyvsp[(2) - (2)].integer)+1); 
        }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 158 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onHeadAtom(); 
        }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 162 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onHeadAtom(); 
        }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 166 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onHeadAtom(); 
        }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 170 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onHeadAtom(); 
        }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 177 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onBodyLiteral(); 
        }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 181 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onBodyLiteral(); 
        }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 195 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onChoiceLowerGuard((yyvsp[(2) - (2)].string)); 
            delete[] (yyvsp[(2) - (2)].string);
        }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 203 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onChoiceUpperGuard((yyvsp[(1) - (2)].string)); 
            delete[] (yyvsp[(1) - (2)].string);
        }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 216 "src/input/aspcore2.y"
    {
            director.getBuilder()->onChoiceElement(); 
        }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 220 "src/input/aspcore2.y"
    {
            director.getBuilder()->onChoiceElement(); 
        }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 227 "src/input/aspcore2.y"
    {
            director.getBuilder()->onChoiceElementAtom(); 
        }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 234 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onChoiceElementLiteral(); 
        }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 238 "src/input/aspcore2.y"
    {
            director.getBuilder()->onChoiceElementLiteral();
        }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 245 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateNafLiteral();
        }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 249 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateNafLiteral();
        }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 256 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onNafLiteral();
        }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 260 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onNafLiteral(true);
        }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 264 "src/input/aspcore2.y"
    {
            director.getBuilder()->onNafLiteral();
        }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 272 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregate();
        }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 276 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregate(true);
        }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 283 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onExistentialAtom(); 
        }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 288 "src/input/aspcore2.y"
    { director.getBuilder()->onAtom(); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 289 "src/input/aspcore2.y"
    { director.getBuilder()->onAtom(true); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 294 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onPredicateName((yyvsp[(1) - (1)].string)); 
            delete[] (yyvsp[(1) - (1)].string);
        }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 299 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onPredicateName((yyvsp[(1) - (4)].string)); 
            delete[] (yyvsp[(1) - (4)].string);
        }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 304 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onPredicateName((yyvsp[(1) - (3)].string)); 
            delete[] (yyvsp[(1) - (3)].string);
        }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 311 "src/input/aspcore2.y"
    { (yyval.integer) = 1; }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 312 "src/input/aspcore2.y"
    { (yyval.integer) = (yyvsp[(1) - (3)].integer) + 1; }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 322 "src/input/aspcore2.y"
    {
            director.getBuilder()->onBuiltinAtom((yyvsp[(2) - (3)].string));  
            delete[] (yyvsp[(2) - (3)].string);
        }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 329 "src/input/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 330 "src/input/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 334 "src/input/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 335 "src/input/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 336 "src/input/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 340 "src/input/aspcore2.y"
    { (yyval.single_char) = '+'; }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 341 "src/input/aspcore2.y"
    { (yyval.single_char) = '-'; }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 342 "src/input/aspcore2.y"
    { (yyval.single_char) = '*'; }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 343 "src/input/aspcore2.y"
    { (yyval.single_char) = '/'; }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 348 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onTerm((yyvsp[(1) - (1)].string)); 
            delete[] (yyvsp[(1) - (1)].string);
        }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 353 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onTerm((yyvsp[(1) - (1)].string)); 
            delete[] (yyvsp[(1) - (1)].string);
        }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 358 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onTerm((yyvsp[(1) - (1)].string)); 
            delete[] (yyvsp[(1) - (1)].string);
        }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 363 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onFunction((yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].integer)); 
            delete[] (yyvsp[(1) - (4)].string);
        }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 368 "src/input/aspcore2.y"
    {
            director.getBuilder()->onTermRange((yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string));
            delete[] (yyvsp[(1) - (3)].string);
            delete[] (yyvsp[(3) - (3)].string);
        }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 374 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onTermParams(); 
        }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 378 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onTermDash(); 
        }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 384 "src/input/aspcore2.y"
    {}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 386 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onArithmeticOperation((yyvsp[(2) - (3)].single_char)); 
        }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 391 "src/input/aspcore2.y"
    {}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 392 "src/input/aspcore2.y"
    {}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 397 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[(1) - (1)].string));
            delete[] (yyvsp[(1) - (1)].string);
        }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 402 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[(1) - (1)].string));
            delete[] (yyvsp[(1) - (1)].string);
        }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 407 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[(1) - (1)].string));
            delete[] (yyvsp[(1) - (1)].string);
        }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 412 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[(2) - (2)].string),true);
            delete[] (yyvsp[(2) - (2)].string);
        }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 420 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onAggregateVariableTerm((yyvsp[(1) - (1)].string));
            delete[] (yyvsp[(1) - (1)].string);
        }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 425 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateVariableTerm((yyvsp[(1) - (1)].string));
            delete[] (yyvsp[(1) - (1)].string);
        }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 433 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onExistentialVariable((yyvsp[(1) - (1)].string)); 
            delete[] (yyvsp[(1) - (1)].string);
        }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 438 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onExistentialVariable((yyvsp[(3) - (3)].string));
            delete[] (yyvsp[(3) - (3)].string);
        }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 445 "src/input/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 446 "src/input/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 447 "src/input/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 452 "src/input/aspcore2.y"
    {
            director.getParserConstraint()->directives();
            director.getBuilder()->onDirective((yyvsp[(1) - (2)].string),(yyvsp[(2) - (2)].string));
            delete[] (yyvsp[(1) - (2)].string);
            delete[] (yyvsp[(2) - (2)].string);
        }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 459 "src/input/aspcore2.y"
    {
            director.getParserConstraint()->directives();
            director.getBuilder()->onDirective((yyvsp[(2) - (3)].string),(yyvsp[(3) - (3)].string));
            delete[] (yyvsp[(2) - (3)].string);
            delete[] (yyvsp[(3) - (3)].string);
        }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 469 "src/input/aspcore2.y"
    { 
            director.getBuilder()->onAtom(); 
        }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 476 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateLowerGuard((yyvsp[(2) - (2)].string));
            delete[] (yyvsp[(2) - (2)].string);
        }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 484 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateUpperGuard((yyvsp[(1) - (2)].string));
            delete[] (yyvsp[(1) - (2)].string);
        }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 497 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateLowerGuard((yyvsp[(2) - (2)].string));
            delete[] (yyvsp[(2) - (2)].string);
        }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 514 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateLowerGuard((yyvsp[(2) - (2)].string));
            delete[] (yyvsp[(2) - (2)].string);
        }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 526 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateUpperGuard((yyvsp[(1) - (2)].string));
            delete[] (yyvsp[(1) - (2)].string);
        }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 534 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateUpperGuard((yyvsp[(1) - (2)].string));
            delete[] (yyvsp[(1) - (2)].string);
        }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 554 "src/input/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 555 "src/input/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 559 "src/input/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 560 "src/input/aspcore2.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 575 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateElement();
        }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 582 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateFunction((yyvsp[(1) - (1)].string));
            delete[] (yyvsp[(1) - (1)].string);
        }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 587 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateFunction((yyvsp[(1) - (1)].string));
            delete[] (yyvsp[(1) - (1)].string);
        }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 592 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateFunction((yyvsp[(1) - (1)].string));
            delete[] (yyvsp[(1) - (1)].string);
        }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 597 "src/input/aspcore2.y"
    {
            director.getBuilder()->onAggregateFunction((yyvsp[(1) - (1)].string));
            delete[] (yyvsp[(1) - (1)].string);
        }
    break;



/* Line 1806 of yacc.c  */
#line 2542 "src/input/aspcore2_parser.hpp"
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
      yyerror (director, YY_("syntax error"));
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
        yyerror (director, yymsgp);
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
		      yytoken, &yylval, director);
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
		  yystos[yystate], yyvsp, director);
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
  yyerror (director, YY_("memory exhausted"));
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
                  yytoken, &yylval, director);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, director);
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



