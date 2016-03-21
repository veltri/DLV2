/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "src/input/aspcore2.y" /* yacc.c:339  */

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


#line 92 "src/input/aspcore2_parser.hpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif


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
    ANNOTATION_ATOM_INDEXED_ATOM = 272,
    ANNOTATION_ATOM_INDEXED_ARGUMENTS = 273,
    ANNOTATION_RULE_PARTIAL_ORDER = 274,
    ANNOTATION_PARTIAL_ORDER_BEFORE = 275,
    ANNOTATION_PARTIAL_ORDER_AFTER = 276,
    ANNOTATION_GLOBAL_ORDERING = 277,
    ANNOTATION_GLOBAL_ATOM_INDEXED = 278,
    ANNOTATION_GLOBAL_PARTIAL_ORDER = 279,
    ERROR = 280,
    NEWLINE = 281,
    DOT = 282,
    DDOT = 283,
    SEMICOLON = 284,
    COLON = 285,
    CONS = 286,
    QUERY_MARK = 287,
    PLUS = 288,
    TIMES = 289,
    SLASH = 290,
    ANON_VAR = 291,
    PARAM_OPEN = 292,
    PARAM_CLOSE = 293,
    SQUARE_OPEN = 294,
    SQUARE_CLOSE = 295,
    CURLY_OPEN = 296,
    CURLY_CLOSE = 297,
    EQUAL = 298,
    UNEQUAL = 299,
    LESS = 300,
    GREATER = 301,
    LESS_OR_EQ = 302,
    GREATER_OR_EQ = 303,
    DASH = 304,
    COMMA = 305,
    NAF = 306,
    AT = 307,
    WCONS = 308,
    VEL = 309,
    EXISTS = 310
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
#define ANNOTATION_ATOM_INDEXED_ATOM 272
#define ANNOTATION_ATOM_INDEXED_ARGUMENTS 273
#define ANNOTATION_RULE_PARTIAL_ORDER 274
#define ANNOTATION_PARTIAL_ORDER_BEFORE 275
#define ANNOTATION_PARTIAL_ORDER_AFTER 276
#define ANNOTATION_GLOBAL_ORDERING 277
#define ANNOTATION_GLOBAL_ATOM_INDEXED 278
#define ANNOTATION_GLOBAL_PARTIAL_ORDER 279
#define ERROR 280
#define NEWLINE 281
#define DOT 282
#define DDOT 283
#define SEMICOLON 284
#define COLON 285
#define CONS 286
#define QUERY_MARK 287
#define PLUS 288
#define TIMES 289
#define SLASH 290
#define ANON_VAR 291
#define PARAM_OPEN 292
#define PARAM_CLOSE 293
#define SQUARE_OPEN 294
#define SQUARE_CLOSE 295
#define CURLY_OPEN 296
#define CURLY_CLOSE 297
#define EQUAL 298
#define UNEQUAL 299
#define LESS 300
#define GREATER 301
#define LESS_OR_EQ 302
#define GREATER_OR_EQ 303
#define DASH 304
#define COMMA 305
#define NAF 306
#define AT 307
#define WCONS 308
#define VEL 309
#define EXISTS 310

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 29 "src/input/aspcore2.y" /* yacc.c:355  */

    char* string;
    char single_char;
    int integer;

#line 245 "src/input/aspcore2_parser.hpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (DLV2::InputDirector& director);



/* Copy the second part of user declarations.  */

#line 260 "src/input/aspcore2_parser.hpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  89
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   641

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  84
/* YYNRULES -- Number of rules.  */
#define YYNRULES  187
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  365

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   310

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    71,    71,    73,    75,    76,    77,    78,    82,    83,
      87,    88,    89,    90,    94,    98,   102,   106,   110,   117,
     121,   129,   136,   141,   149,   154,   158,   168,   172,   176,
     180,   187,   191,   198,   199,   200,   201,   205,   212,   219,
     220,   224,   228,   235,   242,   246,   253,   257,   264,   268,
     272,   279,   280,   284,   291,   297,   298,   302,   307,   312,
     320,   321,   325,   326,   330,   337,   341,   348,   349,   350,
     354,   355,   356,   357,   361,   366,   371,   375,   380,   387,
     391,   398,   399,   405,   406,   410,   415,   420,   425,   433,
     438,   445,   450,   458,   459,   460,   464,   471,   481,   488,
     495,   502,   503,   507,   514,   518,   519,   523,   530,   534,
     541,   548,   549,   553,   554,   555,   556,   557,   561,   565,
     572,   576,   583,   587,   588,   593,   600,   605,   610,   615,
     623,   624,   628,   629,   630,   634,   635,   639,   640,   641,
     645,   649,   653,   660,   667,   672,   677,   681,   690,   694,
     701,   705,   714,   718,   725,   729,   733,   737,   741,   748,
     752,   756,   760,   764,   771,   775,   779,   783,   787,   794,
     798,   802,   806,   810,   817,   818,   822,   823,   827,   828,
     832,   833,   837,   843,   849,   851,   856,   858
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SYMBOLIC_CONSTANT", "NUMBER",
  "VARIABLE", "STRING", "DIRECTIVE_NAME", "DIRECTIVE_VALUE", "AGGR_COUNT",
  "AGGR_MAX", "AGGR_MIN", "AGGR_SUM", "ANNOTATION_RULE_ORDERING",
  "ANNOTATION_ORDERING_VALUE", "NUMBER_ANNOTATION",
  "ANNOTATION_RULE_ATOM_INDEXED", "ANNOTATION_ATOM_INDEXED_ATOM",
  "ANNOTATION_ATOM_INDEXED_ARGUMENTS", "ANNOTATION_RULE_PARTIAL_ORDER",
  "ANNOTATION_PARTIAL_ORDER_BEFORE", "ANNOTATION_PARTIAL_ORDER_AFTER",
  "ANNOTATION_GLOBAL_ORDERING", "ANNOTATION_GLOBAL_ATOM_INDEXED",
  "ANNOTATION_GLOBAL_PARTIAL_ORDER", "ERROR", "NEWLINE", "DOT", "DDOT",
  "SEMICOLON", "COLON", "CONS", "QUERY_MARK", "PLUS", "TIMES", "SLASH",
  "ANON_VAR", "PARAM_OPEN", "PARAM_CLOSE", "SQUARE_OPEN", "SQUARE_CLOSE",
  "CURLY_OPEN", "CURLY_CLOSE", "EQUAL", "UNEQUAL", "LESS", "GREATER",
  "LESS_OR_EQ", "GREATER_OR_EQ", "DASH", "COMMA", "NAF", "AT", "WCONS",
  "VEL", "EXISTS", "$accept", "HEAD_SEPARATOR", "program", "real_program",
  "rules", "rule", "head", "body", "weight_at_levels", "levels_and_terms",
  "disjunction", "conjunction", "choice_atom", "lower_guard",
  "upper_guard", "choice_elements", "choice_element",
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
  "aggregate_elements", "aggregate_element", "aggregate_function",
  "annotations_global", "annotation_global", "annotations_rule",
  "annotation_rule", "annotation_rule_ordering",
  "annotation_global_ordering", "rule_ordering_type",
  "global_ordering_type", "annotation_rule_atom_indexed",
  "annotation_global_atom_indexed", "rule_indexing_arguments",
  "rule_naf_literal_annotation", "global_indexing_arguments",
  "global_naf_literal_annotation", "rule_atom_annotation_before",
  "global_atom_annotation_before", "rule_atom_annotation_after",
  "global_atom_annotation_after", "rule_atoms_annotation_before",
  "global_atoms_annotation_before", "rule_atoms_annotation_after",
  "global_atoms_annotation_after", "annotation_rule_partial_order_begin",
  "annotation_global_partial_order_begin", "annotation_rule_partial_order",
  "annotation_global_partial_order", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310
};
# endif

#define YYPACT_NINF -290

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-290)))

#define YYTABLE_NINF -108

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     343,  -290,  -290,    14,  -290,  -290,    17,    29,    35,  -290,
      44,    69,  -290,   464,  -290,   412,   155,   412,   464,   111,
     127,  -290,   372,  -290,     1,    76,  -290,   103,  -290,  -290,
    -290,  -290,   572,   397,   233,   372,   130,   401,   169,  -290,
    -290,  -290,  -290,   125,   147,  -290,  -290,   194,  -290,   190,
     189,   193,   195,  -290,  -290,  -290,  -290,   592,   186,   164,
    -290,  -290,  -290,  -290,   572,   223,  -290,   223,   124,  -290,
     223,   144,  -290,  -290,   449,   176,   412,   100,   179,     4,
    -290,   192,  -290,   182,  -290,    13,   221,  -290,    18,  -290,
    -290,   188,  -290,   401,  -290,   454,  -290,    50,   155,  -290,
    -290,  -290,  -290,  -290,  -290,  -290,  -290,  -290,  -290,  -290,
    -290,   412,  -290,  -290,   332,   242,  -290,  -290,  -290,  -290,
    -290,    31,   174,  -290,   213,   215,   218,   219,  -290,   572,
    -290,  -290,   464,   301,   412,   307,   313,  -290,  -290,  -290,
     412,  -290,  -290,   412,   412,  -290,  -290,  -290,   514,  -290,
     412,   155,   449,   119,   332,   224,   262,  -290,  -290,  -290,
    -290,   241,   155,  -290,  -290,    40,  -290,  -290,    60,   131,
    -290,   228,   232,   234,   237,   272,   123,   279,   140,  -290,
    -290,  -290,  -290,   131,   131,   131,   131,  -290,  -290,  -290,
    -290,  -290,   280,   -10,  -290,  -290,  -290,    41,  -290,    82,
    -290,  -290,   412,    58,   240,  -290,   572,   129,   412,  -290,
    -290,  -290,   449,   535,   412,   246,   250,   251,   254,  -290,
     258,    58,  -290,   247,  -290,   261,    58,  -290,   255,  -290,
     119,   514,   514,  -290,  -290,   131,   119,  -290,   175,  -290,
     131,   474,   523,   533,   543,   277,  -290,   289,   287,  -290,
     302,   282,  -290,  -290,  -290,  -290,  -290,   412,   412,   290,
     592,  -290,  -290,  -290,   283,   292,   592,  -290,  -290,  -290,
     295,   309,   592,  -290,  -290,  -290,   303,   310,   592,  -290,
    -290,  -290,   305,   315,  -290,   317,  -290,   318,   119,   308,
      68,  -290,  -290,  -290,   474,   314,  -290,  -290,   523,   321,
    -290,  -290,   533,   322,  -290,  -290,   543,   323,   341,   342,
    -290,   412,  -290,   365,  -290,   367,  -290,   368,  -290,   370,
     359,   389,   308,   351,   352,   354,   356,   350,   360,   361,
     377,   369,   371,   373,   379,   418,   363,   419,   392,   523,
     474,   543,   533,  -290,   404,  -290,   406,   393,   394,   398,
     399,  -290,  -290,   405,   407,   408,   414,   417,   426,   428,
     435,  -290,  -290,  -290,  -290
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,    93,    75,    95,    94,     0,     0,     0,   182,
       0,     0,   183,     0,    76,     0,     0,     0,     0,     0,
       0,     4,     8,    11,     0,    19,    20,     0,    29,    27,
      55,    81,     0,    74,     0,     0,   130,     0,   135,   137,
     132,   138,   133,     0,     0,   139,   134,     0,    96,     0,
       0,     0,     0,   126,   127,   128,   129,     0,     0,    21,
      51,    31,    48,    50,     0,     0,   115,     0,   105,   113,
       0,   106,   114,    52,     0,     0,     0,     0,    74,     0,
      40,    41,    43,    57,    56,    80,     0,    91,     0,     1,
      10,    55,     9,     0,    14,     0,     2,     0,     0,    70,
      72,    73,    65,    66,   118,   120,   119,   121,    71,    67,
      37,     0,    68,    69,     0,     0,     5,     6,   131,    12,
     136,     0,     0,    78,     0,     0,     0,     0,    49,     0,
      53,    17,     0,    67,     0,    68,    69,   101,   104,   116,
       0,   108,   117,     0,     0,   102,   111,   112,     0,    79,
       0,     0,    35,     0,     0,     0,     0,    54,    98,    13,
      15,     0,     0,    30,    28,     0,    82,    59,     0,    60,
      97,     0,     0,     0,     0,     0,     0,     0,     0,    99,
     103,   107,    32,    64,   109,   110,   100,    85,    87,    89,
      86,    90,     0,     0,    62,    83,    84,     0,   124,     0,
      39,    36,     0,     0,    42,    44,     0,     0,     0,    18,
      92,    16,    34,    77,     0,     0,     0,     0,     0,   142,
       0,     0,   148,     0,   143,     0,     0,   152,     0,    88,
       0,     0,     0,   122,    77,    38,     0,    58,     0,    33,
      61,     0,     0,     0,     0,     0,   149,     0,     0,   153,
       0,   125,    46,    63,   123,    45,    22,     0,     0,     0,
       0,   154,   156,   157,   174,     0,     0,   164,   166,   167,
     178,     0,     0,   159,   161,   162,   176,     0,     0,   169,
     171,   172,   180,     0,   140,     0,   141,     0,     0,    26,
      24,    23,   155,   158,     0,     0,   165,   168,     0,     0,
     160,   163,     0,     0,   170,   173,     0,     0,     0,     0,
      47,     0,   175,     0,   179,     0,   177,     0,   181,     0,
       0,     0,    25,     0,     0,     0,     0,   146,     0,   150,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   147,     0,   151,     0,     0,     0,     0,
       0,   144,   145,     0,     0,     0,     0,     0,     0,     0,
       0,   184,   185,   186,   187
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -290,  -290,  -290,   167,  -290,   -19,  -290,    -7,  -290,  -290,
    -290,  -290,  -290,  -290,   259,   374,   331,  -290,  -290,  -290,
    -146,   355,   391,     0,   -12,  -148,  -290,  -227,   -25,   -31,
    -290,   378,    43,   267,  -290,  -290,  -290,    -3,  -290,  -290,
    -290,  -290,  -290,  -290,  -290,  -290,  -290,  -290,   425,   430,
    -290,   -13,   -38,   -33,    22,  -290,   270,  -290,   470,  -290,
       7,  -290,  -290,  -290,  -290,  -290,  -290,  -290,  -290,  -290,
    -290,  -290,  -290,  -290,  -290,  -290,  -286,  -283,  -289,  -279,
    -290,  -290,  -290,  -290
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    97,    20,    21,    22,    23,    24,    58,   209,   259,
      25,    59,    26,    27,   201,    79,    80,    81,   204,   251,
      60,    61,    28,    62,    30,   168,   193,    63,   109,   134,
     111,    31,    64,   194,   195,   196,    88,    33,    34,    92,
      65,   145,    66,    67,    68,    69,    70,    71,   139,   142,
      72,    73,   112,   113,    74,   197,   198,    75,    35,    36,
      37,    38,    39,    40,   220,   225,    41,    42,   328,   223,
     330,   228,   264,   276,   270,   282,   265,   277,   271,   283,
      43,    44,    45,    46
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,   110,   199,    90,    82,    84,   207,   205,   312,   314,
      91,    86,    78,    83,   262,   268,   274,   280,   119,   316,
     230,     2,    29,     4,     5,    48,   135,   318,    94,    93,
     140,   136,    95,   151,    29,    29,   140,    29,   143,   133,
     231,   143,    47,    32,   130,   120,   152,   100,   101,   144,
     347,   171,   172,     2,   348,     4,     5,   128,    77,   350,
      85,     2,   349,     4,     5,    32,    49,   262,   156,   151,
     232,   268,    50,    78,   159,   274,   157,    32,    32,   280,
      32,    51,   212,   233,   252,    83,    82,   137,   161,   138,
     255,   180,   141,    29,    83,    83,   181,   164,   213,   162,
     129,    99,   100,   101,   179,    19,    52,   162,    78,   289,
     214,    78,   268,   262,   280,   274,    87,   108,   311,    85,
     234,   202,     2,     3,     4,     5,     2,    89,     4,     5,
      96,    78,   214,    99,   100,   101,    32,    78,   149,    82,
      78,    78,   310,     2,    98,     4,     5,    78,    83,   108,
      84,    78,    10,    11,    12,    14,    15,   169,     2,    83,
       4,     5,   121,   322,    99,   100,   101,   237,    17,   104,
     203,   106,   162,    83,   221,    83,   222,   183,   227,   214,
     108,   202,     7,   184,   122,     8,   185,   186,     9,   162,
     105,   226,   107,   169,   173,   174,   206,   169,   123,    78,
      83,   116,   117,   128,   124,    78,   125,   126,    99,   100,
     101,    78,   127,   131,   132,   256,   150,   148,    83,   154,
     158,   246,   153,    83,   108,   257,   249,   258,   263,   269,
     275,   281,    53,    54,    55,    56,     2,     3,     4,     5,
     115,   261,   267,   273,   279,   235,     7,   293,   155,     8,
     170,   238,     9,   297,    78,    78,   175,   240,   176,   301,
     292,   177,   178,   208,    13,   305,   296,   210,   211,    14,
      15,   215,   300,   206,    16,   216,   219,   217,   304,   206,
     218,   263,    17,   224,   229,   269,    18,   241,    19,   275,
     236,   242,   243,   281,   261,   244,   245,   247,   267,   248,
     169,   290,   273,   129,   284,   250,   279,   285,    78,   129,
     -99,   -99,   -99,   -99,   286,   129,  -103,  -103,  -103,  -103,
     287,   129,  -107,  -107,  -107,  -107,   269,   263,   281,   275,
     291,   206,   288,   294,   295,     2,     3,     4,     5,   267,
     261,   279,   273,    -3,     1,   298,     2,     3,     4,     5,
       6,   299,   303,   302,   169,   306,     7,   307,   214,     8,
     308,   309,     9,   327,   313,    10,    11,    12,    14,    15,
     167,   315,   317,   319,    13,     2,     3,     4,     5,    14,
      15,    76,   320,   321,    16,     7,   323,   324,     8,   325,
     326,     9,    17,   329,   331,   332,    18,   333,    19,   334,
     335,   344,   336,    13,     2,     3,     4,     5,    14,    15,
     339,   337,   340,    16,   341,     2,     3,     4,     5,   338,
     342,    17,   343,   345,   -57,    18,   -57,    19,   -57,   -57,
     346,   351,    13,   352,   114,   353,   354,    14,    15,   -57,
     355,   356,    16,   357,   361,   358,   359,   -57,    14,    15,
      17,   -57,   360,   362,    18,   363,    19,     2,     3,     4,
       5,    76,   364,    53,    54,    55,    56,     2,     3,     4,
       5,   239,   165,    53,    54,    55,    56,     2,     3,     4,
       5,   160,   200,    53,    54,    55,    56,   182,   163,   166,
      14,    15,   102,   103,   104,   105,   106,   107,   253,   146,
      14,    15,   254,    17,   147,    57,   118,     0,     0,     0,
      14,    15,     0,    17,     0,    57,     0,   187,   188,   189,
     190,     0,     0,    17,     0,   260,     2,     3,     4,     5,
       0,     0,    53,    54,    55,    56,     2,     3,     4,     5,
       0,     0,    53,    54,    55,    56,     2,     3,     4,     5,
     191,     0,    53,    54,    55,    56,     0,     0,     0,    14,
      15,     0,   -58,   192,   -58,     0,   -58,   -58,     0,    14,
      15,     0,    17,     0,   266,     0,     0,   -58,     0,    14,
      15,     0,    17,     0,   272,   -58,     0,     0,     0,   -58,
       0,     0,    17,     0,   278,     2,     3,     4,     5,     0,
       0,    53,    54,    55,    56,    99,   100,   101,     0,     0,
       0,     0,     0,     0,     0,   102,   103,   104,   105,   106,
     107,   108,     0,     0,     0,     0,     0,     0,    14,    15,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17
};

static const yytype_int16 yycheck[] =
{
       0,    32,   150,    22,    16,    17,   154,   153,   294,   298,
      22,    18,    15,    16,   241,   242,   243,   244,    37,   302,
      30,     3,    22,     5,     6,     8,    64,   306,    27,    22,
      68,    64,    31,    29,    34,    35,    74,    37,    71,    64,
      50,    74,    28,     0,    57,    38,    42,    34,    35,    74,
     339,    20,    21,     3,   340,     5,     6,    57,    15,   342,
      17,     3,   341,     5,     6,    22,    37,   294,    50,    29,
      29,   298,    37,    76,    93,   302,    88,    34,    35,   306,
      37,    37,    42,    42,   230,    88,    98,    65,    95,    67,
     236,   129,    70,    93,    97,    98,   129,    97,    38,    49,
      57,    33,    34,    35,   129,    55,    37,    49,   111,   257,
      50,   114,   339,   340,   341,   342,     5,    49,    50,    76,
      38,   152,     3,     4,     5,     6,     3,     0,     5,     6,
      54,   134,    50,    33,    34,    35,    93,   140,    38,   151,
     143,   144,   288,     3,    41,     5,     6,   150,   151,    49,
     162,   154,    22,    23,    24,    36,    37,   114,     3,   162,
       5,     6,    37,   311,    33,    34,    35,    38,    49,    45,
      51,    47,    49,   176,    51,   178,   176,   134,   178,    50,
      49,   212,    13,   140,    37,    16,   143,   144,    19,    49,
      46,    51,    48,   150,    20,    21,   153,   154,     4,   202,
     203,    34,    35,   203,    14,   208,    17,    14,    33,    34,
      35,   214,    17,    27,    50,    40,    37,    41,   221,    37,
      32,   221,    30,   226,    49,    50,   226,    52,   241,   242,
     243,   244,     9,    10,    11,    12,     3,     4,     5,     6,
       7,   241,   242,   243,   244,   202,    13,   260,    27,    16,
       8,   208,    19,   266,   257,   258,    43,   214,    43,   272,
     260,    43,    43,    39,    31,   278,   266,     5,    27,    36,
      37,    43,   272,   230,    41,    43,     4,    43,   278,   236,
      43,   294,    49,     4,     4,   298,    53,    41,    55,   302,
      50,    41,    41,   306,   294,    41,    38,    50,   298,    38,
     257,   258,   302,   260,    27,    50,   306,    18,   311,   266,
       9,    10,    11,    12,    27,   272,     9,    10,    11,    12,
      18,   278,     9,    10,    11,    12,   339,   340,   341,   342,
      40,   288,    50,    50,    42,     3,     4,     5,     6,   339,
     340,   341,   342,     0,     1,    50,     3,     4,     5,     6,
       7,    42,    42,    50,   311,    50,    13,    42,    50,    16,
      43,    43,    19,     4,    50,    22,    23,    24,    36,    37,
      38,    50,    50,    50,    31,     3,     4,     5,     6,    36,
      37,    49,    41,    41,    41,    13,    21,    20,    16,    21,
      20,    19,    49,     4,    43,    43,    53,    43,    55,    43,
      50,    38,    42,    31,     3,     4,     5,     6,    36,    37,
      41,    50,    41,    41,    41,     3,     4,     5,     6,    42,
      41,    49,     4,     4,    27,    53,    29,    55,    31,    32,
      38,    27,    31,    27,    37,    42,    42,    36,    37,    42,
      42,    42,    41,    38,    27,    38,    38,    50,    36,    37,
      49,    54,    38,    27,    53,    27,    55,     3,     4,     5,
       6,    49,    27,     9,    10,    11,    12,     3,     4,     5,
       6,   212,    98,     9,    10,    11,    12,     3,     4,     5,
       6,    27,   151,     9,    10,    11,    12,   132,    97,   111,
      36,    37,    43,    44,    45,    46,    47,    48,   231,    74,
      36,    37,   232,    49,    74,    51,    36,    -1,    -1,    -1,
      36,    37,    -1,    49,    -1,    51,    -1,     3,     4,     5,
       6,    -1,    -1,    49,    -1,    51,     3,     4,     5,     6,
      -1,    -1,     9,    10,    11,    12,     3,     4,     5,     6,
      -1,    -1,     9,    10,    11,    12,     3,     4,     5,     6,
      36,    -1,     9,    10,    11,    12,    -1,    -1,    -1,    36,
      37,    -1,    27,    49,    29,    -1,    31,    32,    -1,    36,
      37,    -1,    49,    -1,    51,    -1,    -1,    42,    -1,    36,
      37,    -1,    49,    -1,    51,    50,    -1,    -1,    -1,    54,
      -1,    -1,    49,    -1,    51,     3,     4,     5,     6,    -1,
      -1,     9,    10,    11,    12,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,    47,
      48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    49
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,    13,    16,    19,
      22,    23,    24,    31,    36,    37,    41,    49,    53,    55,
      58,    59,    60,    61,    62,    66,    68,    69,    78,    79,
      80,    87,    88,    93,    94,   114,   115,   116,   117,   118,
     119,   122,   123,   136,   137,   138,   139,    28,     8,    37,
      37,    37,    37,     9,    10,    11,    12,    51,    63,    67,
      76,    77,    79,    83,    88,    96,    98,    99,   100,   101,
     102,   103,   106,   107,   110,   113,    49,    88,    93,    71,
      72,    73,    80,    93,    80,    88,    63,     5,    92,     0,
      61,    80,    95,   116,    27,    31,    54,    57,    41,    33,
      34,    35,    43,    44,    45,    46,    47,    48,    49,    84,
      85,    86,   108,   109,    37,     7,    59,    59,   114,    61,
     116,    37,    37,     4,    14,    17,    14,    17,    79,    88,
     107,    27,    50,    84,    85,   108,   109,   110,   110,   104,
     108,   110,   105,   109,    84,    97,   104,   105,    41,    38,
      37,    29,    42,    30,    37,    27,    50,    80,    32,    61,
      27,    63,    49,    78,    79,    71,    87,    38,    81,    88,
       8,    20,    21,    20,    21,    43,    43,    43,    43,    84,
     108,   109,    77,    88,    88,    88,    88,     3,     4,     5,
       6,    36,    49,    82,    89,    90,    91,   111,   112,    81,
      72,    70,    85,    51,    74,    76,    88,    81,    39,    64,
       5,    27,    42,    38,    50,    43,    43,    43,    43,     4,
     120,    51,    79,   125,     4,   121,    51,    79,   127,     4,
      30,    50,    29,    42,    38,    88,    50,    38,    88,    70,
      88,    41,    41,    41,    41,    38,    79,    50,    38,    79,
      50,    75,    76,    89,   112,    76,    40,    50,    52,    65,
      51,    79,    83,   107,   128,   132,    51,    79,    83,   107,
     130,   134,    51,    79,    83,   107,   129,   133,    51,    79,
      83,   107,   131,   135,    27,    18,    27,    18,    50,    81,
      88,    40,    79,   107,    50,    42,    79,   107,    50,    42,
      79,   107,    50,    42,    79,   107,    50,    42,    43,    43,
      76,    50,   132,    50,   134,    50,   133,    50,   135,    50,
      41,    41,    81,    21,    20,    21,    20,     4,   124,     4,
     126,    43,    43,    43,    43,    50,    42,    50,    42,    41,
      41,    41,    41,     4,    38,     4,    38,   134,   132,   135,
     133,    27,    27,    42,    42,    42,    42,    38,    38,    38,
      38,    27,    27,    27,    27
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    58,    58,    58,    58,    58,    59,    59,
      60,    60,    60,    60,    61,    61,    61,    61,    61,    62,
      62,    63,    64,    64,    65,    65,    65,    66,    66,    66,
      66,    67,    67,    68,    68,    68,    68,    69,    70,    71,
      71,    72,    72,    73,    74,    74,    75,    75,    76,    76,
      76,    77,    77,    77,    78,    79,    79,    80,    80,    80,
      81,    81,    82,    82,    83,    84,    84,    85,    85,    85,
      86,    86,    86,    86,    87,    87,    87,    87,    87,    87,
      87,    88,    88,    89,    89,    90,    90,    90,    90,    91,
      91,    92,    92,    93,    93,    93,    94,    94,    95,    96,
      97,    98,    98,    99,   100,   101,   101,   102,   103,   104,
     105,   106,   106,   107,   107,   107,   107,   107,   108,   108,
     109,   109,   110,   111,   111,   112,   113,   113,   113,   113,
     114,   114,   115,   115,   115,   116,   116,   117,   117,   117,
     118,   119,   120,   121,   122,   123,   124,   124,   125,   125,
     126,   126,   127,   127,   128,   128,   128,   128,   128,   129,
     129,   129,   129,   129,   130,   130,   130,   130,   130,   131,
     131,   131,   131,   131,   132,   132,   133,   133,   134,   134,
     135,   135,   136,   137,   138,   138,   139,   139
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     2,     1,     1,     2,
       2,     1,     2,     3,     2,     3,     4,     3,     4,     1,
       1,     1,     3,     4,     2,     4,     2,     1,     3,     1,
       3,     1,     3,     5,     4,     3,     4,     2,     2,     3,
       1,     1,     3,     1,     1,     3,     1,     3,     1,     2,
       1,     1,     1,     2,     3,     1,     2,     1,     4,     3,
       1,     3,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     3,     3,
       2,     1,     3,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     3,     1,     1,     1,     2,     3,     2,     2,
       2,     2,     2,     2,     2,     1,     1,     2,     2,     2,
       2,     2,     2,     1,     1,     1,     2,     2,     1,     1,
       1,     1,     4,     3,     1,     3,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     2,     1,     1,     1,
       7,     7,     1,     1,    13,    13,     1,     3,     1,     2,
       1,     3,     1,     2,     1,     2,     1,     1,     2,     1,
       2,     1,     1,     2,     1,     2,     1,     1,     2,     1,
       2,     1,     1,     2,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     1,    15,    15,    15,    15
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (director, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, director); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, DLV2::InputDirector& director)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (director);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, DLV2::InputDirector& director)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, director);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, DLV2::InputDirector& director)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , director);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, director); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, DLV2::InputDirector& director)
{
  YYUSE (yyvaluep);
  YYUSE (director);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (DLV2::InputDirector& director)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
      yychar = yylex (director);
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 7:
#line 78 "src/input/aspcore2.y" /* yacc.c:1646  */
    { yyerror(director,"Generic error"); }
#line 1685 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 9:
#line 83 "src/input/aspcore2.y" /* yacc.c:1646  */
    { director.getBuilder()->onQuery(); }
#line 1691 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 14:
#line 95 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onRule(); 
        }
#line 1699 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 15:
#line 99 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onRule(); 
        }
#line 1707 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 16:
#line 103 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onRule(); 
        }
#line 1715 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 17:
#line 107 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onConstraint(); 
        }
#line 1723 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 18:
#line 111 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onWeakConstraint(); 
        }
#line 1731 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 19:
#line 118 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onHead();
        }
#line 1739 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 20:
#line 122 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceAtom();
            director.getBuilder()->onHead();
        }
#line 1748 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 21:
#line 130 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onBody();
        }
#line 1756 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 22:
#line 137 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            // There is only the weight. No level and terms.
            director.getBuilder()->onWeightAtLevels(1,0,0); 
        }
#line 1765 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 23:
#line 142 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            // There are also a level and/or some terms.
            // The finalization has been postponed to "level_and_terms".
        }
#line 1774 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 24:
#line 150 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            // There is no terms following the level.
            director.getBuilder()->onWeightAtLevels(1,1,0); 
        }
#line 1783 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 25:
#line 155 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onWeightAtLevels(1,1,(yyvsp[0].integer)); 
        }
#line 1791 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 26:
#line 159 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            // The level is omitted.
            // Thus, the first term, recognized as the
            // weight, should be a term of this list.
            director.getBuilder()->onWeightAtLevels(0,0,(yyvsp[0].integer)+1); 
        }
#line 1802 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 27:
#line 169 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onHeadAtom(); 
        }
#line 1810 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 28:
#line 173 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onHeadAtom(); 
        }
#line 1818 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 29:
#line 177 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onHeadAtom(); 
        }
#line 1826 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 30:
#line 181 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onHeadAtom(); 
        }
#line 1834 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 31:
#line 188 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onBodyLiteral(); 
        }
#line 1842 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 32:
#line 192 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onBodyLiteral(); 
        }
#line 1850 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 37:
#line 206 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onChoiceLowerGuard();
        }
#line 1858 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 38:
#line 213 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onChoiceUpperGuard();
        }
#line 1866 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 41:
#line 225 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceElement(); 
        }
#line 1874 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 42:
#line 229 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceElement(); 
        }
#line 1882 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 43:
#line 236 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceElementAtom(); 
        }
#line 1890 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 44:
#line 243 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onChoiceElementLiteral(); 
        }
#line 1898 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 45:
#line 247 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceElementLiteral();
        }
#line 1906 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 46:
#line 254 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateNafLiteral();
        }
#line 1914 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 47:
#line 258 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateNafLiteral();
        }
#line 1922 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 48:
#line 265 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onNafLiteral();
        }
#line 1930 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 49:
#line 269 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onNafLiteral(true);
        }
#line 1938 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 50:
#line 273 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onNafLiteral();
        }
#line 1946 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 52:
#line 281 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregate();
        }
#line 1954 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 53:
#line 285 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregate(true);
        }
#line 1962 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 54:
#line 292 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onExistentialAtom(); 
        }
#line 1970 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 55:
#line 297 "src/input/aspcore2.y" /* yacc.c:1646  */
    { director.getBuilder()->onAtom(); }
#line 1976 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 56:
#line 298 "src/input/aspcore2.y" /* yacc.c:1646  */
    { director.getBuilder()->onAtom(true); }
#line 1982 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 57:
#line 303 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onPredicateName((yyvsp[0].string)); 
            delete[] (yyvsp[0].string);
        }
#line 1991 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 58:
#line 308 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onPredicateName((yyvsp[-3].string)); 
            delete[] (yyvsp[-3].string);
        }
#line 2000 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 59:
#line 313 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onPredicateName((yyvsp[-2].string)); 
            delete[] (yyvsp[-2].string);
        }
#line 2009 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 60:
#line 320 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.integer) = 1; }
#line 2015 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 61:
#line 321 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[-2].integer) + 1; }
#line 2021 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 64:
#line 331 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onBuiltinAtom();
        }
#line 2029 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 65:
#line 338 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onEqualOperator();
        }
#line 2037 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 66:
#line 342 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onUnequalOperator(); 
        }
#line 2045 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 70:
#line 354 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.single_char) = '+'; }
#line 2051 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 71:
#line 355 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.single_char) = '-'; }
#line 2057 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 72:
#line 356 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.single_char) = '*'; }
#line 2063 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 73:
#line 357 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.single_char) = '/'; }
#line 2069 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 74:
#line 362 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onTerm((yyvsp[0].string)); 
            delete[] (yyvsp[0].string);
        }
#line 2078 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 75:
#line 367 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onTerm((yyvsp[0].string)); 
            delete[] (yyvsp[0].string);
        }
#line 2087 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 76:
#line 372 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onUnknownVariable(); 
        }
#line 2095 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 77:
#line 376 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onFunction((yyvsp[-3].string), (yyvsp[-1].integer)); 
            delete[] (yyvsp[-3].string);
        }
#line 2104 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 78:
#line 381 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getParserConstraint()->rangeFacts();
            director.getBuilder()->onTermRange((yyvsp[-2].string), (yyvsp[0].string));
            delete[] (yyvsp[-2].string);
            delete[] (yyvsp[0].string);
        }
#line 2115 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 79:
#line 388 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onTermParams(); 
        }
#line 2123 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 80:
#line 392 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onTermDash(); 
        }
#line 2131 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 81:
#line 398 "src/input/aspcore2.y" /* yacc.c:1646  */
    {}
#line 2137 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 82:
#line 400 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onArithmeticOperation((yyvsp[-1].single_char)); 
        }
#line 2145 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 83:
#line 405 "src/input/aspcore2.y" /* yacc.c:1646  */
    {}
#line 2151 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 84:
#line 406 "src/input/aspcore2.y" /* yacc.c:1646  */
    {}
#line 2157 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 85:
#line 411 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2166 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 86:
#line 416 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2175 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 87:
#line 421 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2184 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 88:
#line 426 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[0].string),true);
            delete[] (yyvsp[0].string);
        }
#line 2193 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 89:
#line 434 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAggregateVariableTerm((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2202 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 90:
#line 439 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateUnknownVariable();
        }
#line 2210 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 91:
#line 446 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onExistentialVariable((yyvsp[0].string)); 
            delete[] (yyvsp[0].string);
        }
#line 2219 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 92:
#line 451 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onExistentialVariable((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2228 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 93:
#line 458 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2234 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 94:
#line 459 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2240 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 95:
#line 460 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2246 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 96:
#line 465 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getParserConstraint()->directives();
            director.getBuilder()->onDirective((yyvsp[-1].string),(yyvsp[0].string));
            delete[] (yyvsp[-1].string);
            delete[] (yyvsp[0].string);
        }
#line 2257 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 97:
#line 472 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getParserConstraint()->directives();
            director.getBuilder()->onDirective((yyvsp[-1].string),(yyvsp[0].string));
            delete[] (yyvsp[-1].string);
            delete[] (yyvsp[0].string);
        }
#line 2268 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 98:
#line 482 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAtom(); 
        }
#line 2276 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 99:
#line 489 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateLowerGuard();
        }
#line 2284 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 100:
#line 496 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateUpperGuard();
        }
#line 2292 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 103:
#line 508 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateLowerGuard();
        }
#line 2300 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 107:
#line 524 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateLowerGuard();
        }
#line 2308 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 109:
#line 535 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateUpperGuard();
        }
#line 2316 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 110:
#line 542 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateUpperGuard();
        }
#line 2324 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 118:
#line 562 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onLessOperator(); 
        }
#line 2332 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 119:
#line 566 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onLessOrEqualOperator(); 
        }
#line 2340 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 120:
#line 573 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onGreaterOperator();
        }
#line 2348 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 121:
#line 577 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onGreaterOrEqualOperator();
        }
#line 2356 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 125:
#line 594 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateElement();
        }
#line 2364 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 126:
#line 601 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateFunction((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2373 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 127:
#line 606 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateFunction((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2382 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 128:
#line 611 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateFunction((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2391 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 129:
#line 616 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateFunction((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2400 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 142:
#line 653 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationRuleOrdering((yyvsp[0].string));
        delete[] (yyvsp[0].string);
	}
#line 2409 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 143:
#line 660 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationGlobalOrdering((yyvsp[0].string));
        delete[] (yyvsp[0].string);
	}
#line 2418 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 146:
#line 677 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationRuleAtomIndexedArgument((yyvsp[0].string));
        delete[] (yyvsp[0].string);
	}
#line 2427 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 147:
#line 681 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationRuleAtomIndexedArgument((yyvsp[-2].string));
		director.getBuilder()->onAnnotationRuleAtomIndexedArgument((yyvsp[0].string));
        delete[] (yyvsp[-2].string);
        delete[] (yyvsp[0].string);
	}
#line 2438 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 148:
#line 691 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRuleAtomIndexedLiteral();
        }
#line 2446 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 149:
#line 695 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRuleAtomIndexedLiteral(true);
        }
#line 2454 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 150:
#line 701 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationGlobalAtomIndexedArgument((yyvsp[0].string));
        delete[] (yyvsp[0].string);
	}
#line 2463 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 151:
#line 705 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationGlobalAtomIndexedArgument((yyvsp[-2].string));
		director.getBuilder()->onAnnotationGlobalAtomIndexedArgument((yyvsp[0].string));
        delete[] (yyvsp[-2].string);
        delete[] (yyvsp[0].string);
	}
#line 2474 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 152:
#line 715 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalAtomIndexedLiteral();
        }
#line 2482 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 153:
#line 719 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalAtomIndexedLiteral(true);
        }
#line 2490 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 154:
#line 726 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRulePartialOrderingBefore();
        }
#line 2498 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 155:
#line 730 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRulePartialOrderingBefore(true);
        }
#line 2506 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 156:
#line 734 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationRulePartialOrderingBefore();
        }
#line 2514 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 157:
#line 738 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
           director.getBuilder()->onAnnotationAggregateRulePartialOrderingBefore();
        }
#line 2522 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 158:
#line 742 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationAggregateRulePartialOrderingBefore(true);
        }
#line 2530 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 159:
#line 749 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalPartialOrderingBefore();
        }
#line 2538 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 160:
#line 753 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalPartialOrderingBefore(true);
        }
#line 2546 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 161:
#line 757 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationGlobalPartialOrderingBefore();
        }
#line 2554 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 162:
#line 761 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
           director.getBuilder()->onAnnotationAggregateGlobalPartialOrderingBefore();
        }
#line 2562 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 163:
#line 765 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationAggregateGlobalPartialOrderingBefore(true);
        }
#line 2570 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 164:
#line 772 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRulePartialOrderingAfter();
        }
#line 2578 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 165:
#line 776 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRulePartialOrderingAfter(true);
        }
#line 2586 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 166:
#line 780 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationRulePartialOrderingAfter();
        }
#line 2594 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 167:
#line 784 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
           director.getBuilder()->onAnnotationAggregateRulePartialOrderingAfter();
        }
#line 2602 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 168:
#line 788 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationAggregateRulePartialOrderingAfter(true);
        }
#line 2610 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 169:
#line 795 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalPartialOrderingAfter();
        }
#line 2618 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 170:
#line 799 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalPartialOrderingAfter(true);
        }
#line 2626 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 171:
#line 803 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationGlobalPartialOrderingAfter();
        }
#line 2634 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 172:
#line 807 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
           director.getBuilder()->onAnnotationAggregateGlobalPartialOrderingAfter();
        }
#line 2642 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 173:
#line 811 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationAggregateGlobalPartialOrderingAfter(true);
        }
#line 2650 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 182:
#line 838 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationPartialOrdering();
	}
#line 2658 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 183:
#line 844 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationPartialOrdering(true);
	}
#line 2666 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;


#line 2670 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
