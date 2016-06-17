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
#include <iostream>

bool queryFound=false;


#line 95 "src/input/aspcore2_parser.hpp" /* yacc.c:339  */

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
#line 32 "src/input/aspcore2.y" /* yacc.c:355  */

    char* string;
    char single_char;
    int integer;

#line 248 "src/input/aspcore2_parser.hpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (DLV2::InputDirector& director);



/* Copy the second part of user declarations.  */

#line 263 "src/input/aspcore2_parser.hpp" /* yacc.c:358  */

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
#define YYFINAL  94
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   601

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  88
/* YYNRULES -- Number of rules.  */
#define YYNRULES  191
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  372

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
       0,    76,    76,    78,    80,    81,    82,    83,    87,    91,
      92,    93,    94,    98,   102,   106,   110,   114,   118,   128,
     132,   140,   147,   152,   160,   165,   169,   179,   183,   187,
     191,   198,   202,   209,   210,   211,   212,   216,   223,   230,
     231,   235,   239,   246,   253,   257,   264,   268,   275,   279,
     283,   290,   291,   295,   302,   308,   309,   313,   318,   323,
     331,   332,   336,   337,   341,   348,   352,   359,   360,   361,
     366,   367,   371,   372,   376,   380,   385,   392,   400,   405,
     410,   417,   418,   424,   425,   433,   434,   440,   441,   445,
     450,   455,   460,   468,   473,   480,   485,   493,   494,   495,
     499,   506,   516,   523,   530,   537,   538,   542,   549,   553,
     554,   558,   565,   569,   576,   583,   584,   588,   589,   590,
     591,   592,   596,   600,   607,   611,   618,   622,   623,   628,
     635,   640,   645,   650,   658,   659,   663,   664,   665,   669,
     670,   674,   675,   676,   680,   684,   688,   695,   702,   707,
     712,   716,   723,   727,   734,   738,   745,   749,   756,   760,
     764,   768,   772,   779,   783,   787,   791,   795,   802,   806,
     810,   814,   818,   825,   829,   833,   837,   841,   848,   849,
     853,   854,   858,   859,   863,   864,   868,   874,   880,   882,
     887,   889
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
  "compareop", "binop", "arithop1", "arithop2", "term_", "term__", "term",
  "expr", "factor", "basic_term", "ground_term", "variable_term", "vars",
  "identifier", "directives", "query", "lower_guard_compare_aggregate",
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

#define YYPACT_NINF -301

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-301)))

#define YYTABLE_NINF -112

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     350,  -301,  -301,     8,  -301,  -301,    25,    38,    43,  -301,
      66,    71,  -301,   194,  -301,   124,    92,   124,   194,   119,
     156,  -301,   420,  -301,   153,   122,  -301,   167,  -301,  -301,
     180,  -301,  -301,   283,    -1,   115,   486,   391,  -301,   420,
     231,   411,   151,  -301,  -301,  -301,  -301,   155,   192,  -301,
    -301,   223,  -301,   233,   242,   258,   266,  -301,  -301,  -301,
    -301,   552,   249,   234,  -301,  -301,  -301,  -301,  -301,   283,
     225,  -301,   225,   112,  -301,   225,   142,  -301,  -301,   283,
     248,   124,   257,   267,    15,  -301,   273,  -301,   269,  -301,
    -301,   280,  -301,    62,  -301,  -301,   411,  -301,   288,  -301,
      50,    92,  -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,
    -301,  -301,  -301,  -301,  -301,   149,  -301,  -301,   149,   339,
     303,  -301,  -301,  -301,  -301,  -301,   221,   260,  -301,   271,
     274,   293,   295,  -301,   283,  -301,  -301,   194,   253,   124,
     259,   323,  -301,  -301,  -301,   124,  -301,  -301,   124,   124,
    -301,  -301,  -301,   190,  -301,   124,    92,   283,    85,   339,
     277,   307,  -301,  -301,  -301,   296,    92,  -301,  -301,    30,
    -301,   115,  -301,  -301,  -301,    63,  -301,  -301,   297,   309,
     315,   316,   356,   140,   357,   160,  -301,  -301,  -301,  -301,
    -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,   358,
      -4,  -301,  -301,  -301,    34,  -301,    88,  -301,  -301,   124,
     212,   314,  -301,   283,    94,   124,  -301,  -301,  -301,   283,
     522,   124,   324,   326,   327,   329,  -301,   333,   212,  -301,
     328,  -301,   341,   212,  -301,   330,  -301,    85,   190,   190,
    -301,  -301,  -301,    85,  -301,    83,  -301,  -301,   473,   483,
     493,   542,   355,  -301,   365,   362,  -301,   366,   335,  -301,
    -301,  -301,  -301,  -301,   124,   124,   352,   552,  -301,  -301,
    -301,   340,   351,   552,  -301,  -301,  -301,   359,   360,   552,
    -301,  -301,  -301,   361,   364,   552,  -301,  -301,  -301,   363,
     370,  -301,   375,  -301,   376,    85,   371,   379,  -301,  -301,
    -301,   473,   380,  -301,  -301,   483,   381,  -301,  -301,   493,
     384,  -301,  -301,   542,   385,   367,   396,  -301,   124,  -301,
     399,  -301,   418,  -301,   422,  -301,   421,   397,   441,   371,
     406,   407,   410,   412,  -301,     1,  -301,    52,   413,   417,
     424,   426,   425,   455,   430,   458,   483,   473,   542,   493,
     373,  -301,   443,  -301,   429,   432,   438,   439,  -301,  -301,
     434,   452,   453,   462,   474,   479,   480,   481,  -301,  -301,
    -301,  -301
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,    97,    79,    99,    98,     0,     0,     0,   186,
       0,     0,   187,     0,    74,     0,     0,     0,     0,     0,
       0,     4,     8,    10,     0,    19,    20,     0,    29,    27,
      55,    81,    85,     0,    82,    83,    78,     0,    18,     0,
     134,     0,   139,   141,   136,   142,   137,     0,     0,   143,
     138,     0,   100,     0,     0,     0,     0,   130,   131,   132,
     133,     0,     0,    21,    51,    31,    48,    55,    50,     0,
       0,   119,     0,   109,   117,     0,   110,   118,    52,     0,
       0,     0,     0,    78,     0,    40,    41,    43,    57,    56,
      77,     0,    95,     0,     1,     9,     0,    13,     0,     2,
       0,     0,   102,    65,    66,   122,   124,   123,   125,    67,
      37,    68,    69,    70,    71,     0,    72,    73,     0,     0,
       0,     5,     6,   135,    11,   140,     0,     0,    76,     0,
       0,     0,     0,    49,     0,    53,    16,     0,    67,     0,
      68,    69,   105,   108,   120,     0,   112,   121,     0,     0,
     106,   115,   116,     0,    80,     0,     0,    35,     0,     0,
       0,     0,    54,    12,    14,     0,     0,    30,    28,     0,
      79,    84,    78,    86,    59,     0,    60,   101,     0,     0,
       0,     0,     0,     0,     0,     0,   103,   107,   111,    32,
      64,   113,   114,   104,    89,    91,    93,    90,    94,     0,
       0,    62,    87,    88,     0,   128,     0,    39,    36,     0,
       0,    42,    44,     0,     0,     0,    17,    96,    15,    34,
      58,     0,     0,     0,     0,     0,   146,     0,     0,   152,
       0,   147,     0,     0,   156,     0,    92,     0,     0,     0,
     126,    75,    38,     0,    58,     0,    33,    61,     0,     0,
       0,     0,     0,   153,     0,     0,   157,     0,   129,    46,
      63,   127,    45,    22,     0,     0,     0,     0,   158,   160,
     161,   178,     0,     0,   168,   170,   171,   182,     0,     0,
     163,   165,   166,   180,     0,     0,   173,   175,   176,   184,
       0,   144,     0,   145,     0,     0,    26,    24,    23,   159,
     162,     0,     0,   169,   172,     0,     0,   164,   167,     0,
       0,   174,   177,     0,     0,     0,     0,    47,     0,   179,
       0,   183,     0,   181,     0,   185,     0,     0,     0,    25,
       0,     0,     0,     0,   150,     0,   154,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   151,     0,   155,     0,     0,     0,     0,   148,   149,
       0,     0,     0,     0,     0,     0,     0,     0,   188,   189,
     190,   191
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -301,  -301,  -301,   238,  -301,   -17,  -301,   -15,  -301,  -301,
    -301,  -301,  -301,  -301,   292,   415,   369,  -301,  -301,  -301,
    -156,   377,   427,     0,    13,  -144,  -301,  -231,   -65,   -32,
    -301,  -301,  -301,   394,    23,  -301,   416,   299,  -301,  -301,
    -301,    -8,  -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,
    -301,  -301,   442,   447,  -301,   -27,   -63,   -48,   144,  -301,
     294,  -301,   495,  -301,     5,  -301,  -301,  -301,  -301,  -301,
    -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,
    -289,  -300,  -280,  -271,  -301,  -301,  -301,  -301
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   100,    20,    21,    22,    23,    24,    62,   216,   266,
      25,    63,    26,    27,   208,    84,    85,    86,   211,   258,
      64,    65,    28,    66,    67,   175,   200,    68,   109,   139,
     115,   118,    31,    32,    69,    34,    35,   201,   202,   203,
      93,    36,    37,    38,    70,   150,    71,    72,    73,    74,
      75,    76,   144,   147,    77,    78,   111,   112,    79,   204,
     205,    80,    39,    40,    41,    42,    43,    44,   227,   232,
      45,    46,   335,   230,   337,   235,   271,   283,   277,   289,
     272,   284,   278,   290,    47,    48,    49,    50
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,   110,   212,    91,   138,    95,   140,    83,    88,   323,
     145,   206,   319,    30,   149,   214,   145,   269,   275,   281,
     287,   141,    29,    33,   124,   321,   237,    96,   148,    87,
      89,   148,   113,    52,   135,    30,    51,    29,    82,    29,
      90,    29,   325,   342,   156,    33,   238,   125,   114,   357,
      30,   343,    30,     2,    30,     4,     5,   157,   355,   156,
      33,   133,    33,   239,    33,     2,   354,     4,     5,   186,
     269,   187,   219,    83,   275,    53,   240,   356,   281,   163,
      54,   259,   287,   165,   134,    88,   188,   262,     2,     3,
       4,     5,    88,    88,   344,     2,    29,     4,     5,   166,
     168,   220,   345,    55,    90,    19,   162,   172,    56,    30,
     172,    83,   161,   221,    87,   275,   269,   287,   281,    33,
     296,    14,    15,   263,    92,   209,   241,     2,     3,     4,
       5,    83,   244,   264,    17,   265,   210,    83,   221,   317,
      83,    83,   176,     2,   221,     4,     5,    83,    88,   116,
     117,    83,     2,   170,     4,     5,    94,   105,    88,   107,
      14,    15,   190,     2,     7,     4,     5,     8,   191,    87,
       9,   192,   193,    81,   329,    88,    99,    88,   176,    89,
      97,   213,   176,   229,    98,   234,    15,   209,   106,   166,
     108,   228,   126,   194,   195,   196,   197,     2,     3,     4,
       5,    83,    88,    57,    58,    59,    60,    83,   101,   166,
     133,   233,   102,    83,   142,     2,   143,     4,     5,   146,
      88,   270,   276,   282,   288,    88,   198,   128,   253,   127,
      14,    15,   242,   256,    57,    58,    59,    60,   245,   199,
     300,   178,   179,    17,   247,    61,   304,   129,   268,   274,
     280,   286,   308,    10,    11,    12,    83,    83,   312,   130,
     213,   166,  -103,  -103,  -103,  -103,   213,   299,  -107,  -107,
    -107,  -107,   131,   303,   270,   121,   136,   122,   276,   307,
     180,   181,   282,   132,   137,   311,   288,   176,   297,   153,
     134,     2,     3,     4,     5,   154,   134,    57,    58,    59,
      60,   268,   134,   158,   155,   274,   159,   160,   134,   280,
      83,   177,   217,   286,   182,   164,   215,   183,   213,   276,
     270,   288,   282,   218,    14,    15,   103,   104,   105,   106,
     107,   108,  -111,  -111,  -111,  -111,   184,    17,   185,    61,
     222,   176,     2,     3,     4,     5,   274,   268,   286,   280,
      -3,     1,   223,     2,     3,     4,     5,     6,   224,   225,
     226,   231,   236,     7,   243,   248,     8,   249,   250,     9,
     251,   252,    10,    11,    12,    14,    15,   174,   254,   255,
     257,    13,   291,   292,   294,   295,    14,    15,    81,   293,
     301,    16,   298,   302,     2,     3,     4,     5,   120,    17,
     358,   334,   306,    18,     7,    19,   310,     8,   327,   305,
       9,   309,   314,   313,     2,     3,     4,     5,   315,   316,
     330,   221,    13,     2,     3,     4,     5,    14,    15,   318,
     320,   322,    16,     7,   324,   326,     8,   328,   331,     9,
      17,   333,    13,   332,    18,   336,    19,    14,    15,   338,
     339,    13,    16,   340,   346,   341,    14,    15,   347,   351,
      17,    16,   353,   350,    18,   348,    19,   349,   352,    17,
     359,   360,   364,    18,   361,    19,     2,     3,     4,     5,
     362,   363,    57,    58,    59,    60,     2,     3,     4,     5,
     365,   366,    57,    58,    59,    60,     2,     3,     4,     5,
     367,   368,    57,    58,    59,    60,   369,   370,   371,    14,
      15,   246,   173,   -57,   189,   -57,   169,   -57,   -57,    14,
      15,   151,    17,   119,   267,   207,   152,   167,   -57,    14,
      15,   171,    17,   261,   273,   123,   -57,   260,     0,     0,
     -57,     0,    17,     0,   279,     2,     3,     4,     5,     0,
       0,    57,    58,    59,    60,     2,     3,     4,     5,     0,
       0,    57,    58,    59,    60,   -75,   -75,   -75,   -75,   -75,
     -75,     0,     0,     0,     0,     0,     0,     0,    14,    15,
       0,     0,     0,     0,     0,     0,     0,     0,    14,    15,
       0,    17,     0,   285,     0,     0,     0,     0,     0,     0,
       0,    17
};

static const yytype_int16 yycheck[] =
{
       0,    33,   158,    18,    69,    22,    69,    15,    16,   309,
      73,   155,   301,     0,    79,   159,    79,   248,   249,   250,
     251,    69,    22,     0,    41,   305,    30,    22,    76,    16,
      17,    79,    33,     8,    61,    22,    28,    37,    15,    39,
      17,    41,   313,    42,    29,    22,    50,    42,    49,   349,
      37,    50,    39,     3,    41,     5,     6,    42,   347,    29,
      37,    61,    39,    29,    41,     3,   346,     5,     6,   134,
     301,   134,    42,    81,   305,    37,    42,   348,   309,    96,
      37,   237,   313,    98,    61,    93,   134,   243,     3,     4,
       5,     6,   100,   101,    42,     3,    96,     5,     6,    49,
     100,    38,    50,    37,    81,    55,    93,   115,    37,    96,
     118,   119,    50,    50,   101,   346,   347,   348,   349,    96,
     264,    36,    37,    40,     5,   157,    38,     3,     4,     5,
       6,   139,    38,    50,    49,    52,    51,   145,    50,   295,
     148,   149,   119,     3,    50,     5,     6,   155,   156,    34,
      35,   159,     3,     4,     5,     6,     0,    45,   166,    47,
      36,    37,   139,     3,    13,     5,     6,    16,   145,   156,
      19,   148,   149,    49,   318,   183,    54,   185,   155,   166,
      27,   158,   159,   183,    31,   185,    37,   219,    46,    49,
      48,    51,    37,     3,     4,     5,     6,     3,     4,     5,
       6,   209,   210,     9,    10,    11,    12,   215,    41,    49,
     210,    51,    32,   221,    70,     3,    72,     5,     6,    75,
     228,   248,   249,   250,   251,   233,    36,     4,   228,    37,
      36,    37,   209,   233,     9,    10,    11,    12,   215,    49,
     267,    20,    21,    49,   221,    51,   273,    14,   248,   249,
     250,   251,   279,    22,    23,    24,   264,   265,   285,    17,
     237,    49,     9,    10,    11,    12,   243,   267,     9,    10,
      11,    12,    14,   273,   301,    37,    27,    39,   305,   279,
      20,    21,   309,    17,    50,   285,   313,   264,   265,    41,
     267,     3,     4,     5,     6,    38,   273,     9,    10,    11,
      12,   301,   279,    30,    37,   305,    37,    27,   285,   309,
     318,     8,     5,   313,    43,    27,    39,    43,   295,   346,
     347,   348,   349,    27,    36,    37,    43,    44,    45,    46,
      47,    48,     9,    10,    11,    12,    43,    49,    43,    51,
      43,   318,     3,     4,     5,     6,   346,   347,   348,   349,
       0,     1,    43,     3,     4,     5,     6,     7,    43,    43,
       4,     4,     4,    13,    50,    41,    16,    41,    41,    19,
      41,    38,    22,    23,    24,    36,    37,    38,    50,    38,
      50,    31,    27,    18,    18,    50,    36,    37,    49,    27,
      50,    41,    40,    42,     3,     4,     5,     6,     7,    49,
      27,     4,    42,    53,    13,    55,    42,    16,    41,    50,
      19,    50,    42,    50,     3,     4,     5,     6,    43,    43,
      21,    50,    31,     3,     4,     5,     6,    36,    37,    50,
      50,    50,    41,    13,    50,    50,    16,    41,    20,    19,
      49,    20,    31,    21,    53,     4,    55,    36,    37,    43,
      43,    31,    41,    43,    41,    43,    36,    37,    41,     4,
      49,    41,     4,    38,    53,    41,    55,    41,    38,    49,
      27,    42,    38,    53,    42,    55,     3,     4,     5,     6,
      42,    42,     9,    10,    11,    12,     3,     4,     5,     6,
      38,    38,     9,    10,    11,    12,     3,     4,     5,     6,
      38,    27,     9,    10,    11,    12,    27,    27,    27,    36,
      37,   219,   118,    27,   137,    29,   101,    31,    32,    36,
      37,    79,    49,    37,    51,   156,    79,   100,    42,    36,
      37,   115,    49,   239,    51,    40,    50,   238,    -1,    -1,
      54,    -1,    49,    -1,    51,     3,     4,     5,     6,    -1,
      -1,     9,    10,    11,    12,     3,     4,     5,     6,    -1,
      -1,     9,    10,    11,    12,    43,    44,    45,    46,    47,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,
      -1,    49,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    49
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,    13,    16,    19,
      22,    23,    24,    31,    36,    37,    41,    49,    53,    55,
      58,    59,    60,    61,    62,    66,    68,    69,    78,    79,
      80,    88,    89,    90,    91,    92,    97,    98,    99,   118,
     119,   120,   121,   122,   123,   126,   127,   140,   141,   142,
     143,    28,     8,    37,    37,    37,    37,     9,    10,    11,
      12,    51,    63,    67,    76,    77,    79,    80,    83,    90,
     100,   102,   103,   104,   105,   106,   107,   110,   111,   114,
     117,    49,    90,    97,    71,    72,    73,    80,    97,    80,
      90,    63,     5,    96,     0,    61,   120,    27,    31,    54,
      57,    41,    32,    43,    44,    45,    46,    47,    48,    84,
      85,   112,   113,    33,    49,    86,    34,    35,    87,    37,
       7,    59,    59,   118,    61,   120,    37,    37,     4,    14,
      17,    14,    17,    79,    90,   111,    27,    50,    84,    85,
     112,   113,   114,   114,   108,   112,   114,   109,   113,    84,
     101,   108,   109,    41,    38,    37,    29,    42,    30,    37,
      27,    50,    80,    61,    27,    63,    49,    78,    79,    71,
       4,    92,    97,    89,    38,    81,    90,     8,    20,    21,
      20,    21,    43,    43,    43,    43,    84,   112,   113,    77,
      90,    90,    90,    90,     3,     4,     5,     6,    36,    49,
      82,    93,    94,    95,   115,   116,    81,    72,    70,    85,
      51,    74,    76,    90,    81,    39,    64,     5,    27,    42,
      38,    50,    43,    43,    43,    43,     4,   124,    51,    79,
     129,     4,   125,    51,    79,   131,     4,    30,    50,    29,
      42,    38,    90,    50,    38,    90,    70,    90,    41,    41,
      41,    41,    38,    79,    50,    38,    79,    50,    75,    76,
      93,   116,    76,    40,    50,    52,    65,    51,    79,    83,
     111,   132,   136,    51,    79,    83,   111,   134,   138,    51,
      79,    83,   111,   133,   137,    51,    79,    83,   111,   135,
     139,    27,    18,    27,    18,    50,    81,    90,    40,    79,
     111,    50,    42,    79,   111,    50,    42,    79,   111,    50,
      42,    79,   111,    50,    42,    43,    43,    76,    50,   136,
      50,   138,    50,   137,    50,   139,    50,    41,    41,    81,
      21,    20,    21,    20,     4,   128,     4,   130,    43,    43,
      43,    43,    42,    50,    42,    50,    41,    41,    41,    41,
      38,     4,    38,     4,   138,   136,   139,   137,    27,    27,
      42,    42,    42,    42,    38,    38,    38,    38,    27,    27,
      27,    27
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    58,    58,    58,    58,    58,    59,    60,
      60,    60,    60,    61,    61,    61,    61,    61,    61,    62,
      62,    63,    64,    64,    65,    65,    65,    66,    66,    66,
      66,    67,    67,    68,    68,    68,    68,    69,    70,    71,
      71,    72,    72,    73,    74,    74,    75,    75,    76,    76,
      76,    77,    77,    77,    78,    79,    79,    80,    80,    80,
      81,    81,    82,    82,    83,    84,    84,    85,    85,    85,
      86,    86,    87,    87,    88,    88,    88,    88,    89,    89,
      89,    90,    90,    91,    91,    92,    92,    93,    93,    94,
      94,    94,    94,    95,    95,    96,    96,    97,    97,    97,
      98,    98,    99,   100,   101,   102,   102,   103,   104,   105,
     105,   106,   107,   108,   109,   110,   110,   111,   111,   111,
     111,   111,   112,   112,   113,   113,   114,   115,   115,   116,
     117,   117,   117,   117,   118,   118,   119,   119,   119,   120,
     120,   121,   121,   121,   122,   123,   124,   125,   126,   127,
     128,   128,   129,   129,   130,   130,   131,   131,   132,   132,
     132,   132,   132,   133,   133,   133,   133,   133,   134,   134,
     134,   134,   134,   135,   135,   135,   135,   135,   136,   136,
     137,   137,   138,   138,   139,   139,   140,   141,   142,   142,
     143,   143
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     2,     1,     1,     2,
       1,     2,     3,     2,     3,     4,     3,     4,     1,     1,
       1,     1,     3,     4,     2,     4,     2,     1,     3,     1,
       3,     1,     3,     5,     4,     3,     4,     2,     2,     3,
       1,     1,     3,     1,     1,     3,     1,     3,     1,     2,
       1,     1,     1,     2,     3,     1,     2,     1,     4,     3,
       1,     3,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     2,     1,     1,
       3,     1,     1,     1,     3,     1,     3,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     3,     1,     1,     1,
       2,     3,     2,     2,     2,     2,     2,     2,     2,     1,
       1,     2,     2,     2,     2,     2,     2,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     4,     3,     1,     3,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       2,     1,     1,     1,     7,     7,     1,     1,    13,    13,
       1,     3,     1,     2,     1,     3,     1,     2,     1,     2,
       1,     1,     2,     1,     2,     1,     1,     2,     1,     2,
       1,     1,     2,     1,     2,     1,     1,     2,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     1,    15,    15,
      15,    15
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
#line 83 "src/input/aspcore2.y" /* yacc.c:1646  */
    { yyerror(director,"Generic error"); }
#line 1686 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 13:
#line 99 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onRule(); 
        }
#line 1694 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 14:
#line 103 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onRule(); 
        }
#line 1702 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 15:
#line 107 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onRule(); 
        }
#line 1710 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 16:
#line 111 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onConstraint(); 
        }
#line 1718 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 17:
#line 115 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onWeakConstraint(); 
        }
#line 1726 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 18:
#line 119 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
			if(!queryFound) 
				{ queryFound=true; director.getBuilder()->onQuery(); } 
			else 
				{ yyerror(director,"A query has been already found"); }
		}
#line 1737 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 19:
#line 129 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onHead();
        }
#line 1745 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 20:
#line 133 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceAtom();
            director.getBuilder()->onHead();
        }
#line 1754 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 21:
#line 141 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onBody();
        }
#line 1762 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 22:
#line 148 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            // There is only the weight. No level and terms.
            director.getBuilder()->onWeightAtLevels(1,0,0); 
        }
#line 1771 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 23:
#line 153 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            // There are also a level and/or some terms.
            // The finalization has been postponed to "level_and_terms".
        }
#line 1780 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 24:
#line 161 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            // There is no terms following the level.
            director.getBuilder()->onWeightAtLevels(1,1,0); 
        }
#line 1789 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 25:
#line 166 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onWeightAtLevels(1,1,(yyvsp[0].integer)); 
        }
#line 1797 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 26:
#line 170 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            // The level is omitted.
            // Thus, the first term, recognized as the
            // weight, should be a term of this list.
            director.getBuilder()->onWeightAtLevels(0,0,(yyvsp[0].integer)+1); 
        }
#line 1808 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 27:
#line 180 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onHeadAtom(); 
        }
#line 1816 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 28:
#line 184 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onHeadAtom(); 
        }
#line 1824 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 29:
#line 188 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onHeadAtom(); 
        }
#line 1832 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 30:
#line 192 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onHeadAtom(); 
        }
#line 1840 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 31:
#line 199 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onBodyLiteral(); 
        }
#line 1848 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 32:
#line 203 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onBodyLiteral(); 
        }
#line 1856 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 37:
#line 217 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onChoiceLowerGuard();
        }
#line 1864 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 38:
#line 224 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onChoiceUpperGuard();
        }
#line 1872 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 41:
#line 236 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceElement(); 
        }
#line 1880 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 42:
#line 240 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceElement(); 
        }
#line 1888 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 43:
#line 247 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceElementAtom(); 
        }
#line 1896 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 44:
#line 254 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onChoiceElementLiteral(); 
        }
#line 1904 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 45:
#line 258 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceElementLiteral();
        }
#line 1912 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 46:
#line 265 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateNafLiteral();
        }
#line 1920 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 47:
#line 269 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateNafLiteral();
        }
#line 1928 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 48:
#line 276 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onNafLiteral();
        }
#line 1936 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 49:
#line 280 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onNafLiteral(true);
        }
#line 1944 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 50:
#line 284 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onNafLiteral();
        }
#line 1952 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 52:
#line 292 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregate();
        }
#line 1960 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 53:
#line 296 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregate(true);
        }
#line 1968 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 54:
#line 303 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onExistentialAtom(); 
        }
#line 1976 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 55:
#line 308 "src/input/aspcore2.y" /* yacc.c:1646  */
    { director.getBuilder()->onAtom(); }
#line 1982 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 56:
#line 309 "src/input/aspcore2.y" /* yacc.c:1646  */
    { director.getBuilder()->onAtom(true); }
#line 1988 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 57:
#line 314 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onPredicateName((yyvsp[0].string)); 
            delete[] (yyvsp[0].string);
        }
#line 1997 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 58:
#line 319 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onPredicateName((yyvsp[-3].string)); 
            delete[] (yyvsp[-3].string);
        }
#line 2006 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 59:
#line 324 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onPredicateName((yyvsp[-2].string)); 
            delete[] (yyvsp[-2].string);
        }
#line 2015 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 60:
#line 331 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.integer) = 1; }
#line 2021 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 61:
#line 332 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[-2].integer) + 1; }
#line 2027 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 64:
#line 342 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onBuiltinAtom();
        }
#line 2035 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 65:
#line 349 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onEqualOperator();
        }
#line 2043 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 66:
#line 353 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onUnequalOperator(); 
        }
#line 2051 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 70:
#line 366 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.single_char) = '+'; }
#line 2057 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 71:
#line 367 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.single_char) = '-'; }
#line 2063 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 72:
#line 371 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.single_char) = '*'; }
#line 2069 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 73:
#line 372 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.single_char) = '/'; }
#line 2075 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 74:
#line 377 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onUnknownVariable(); 
        }
#line 2083 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 75:
#line 381 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onFunction((yyvsp[-3].string), (yyvsp[-1].integer)); 
            delete[] (yyvsp[-3].string);
        }
#line 2092 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 76:
#line 386 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getParserConstraint()->rangeFacts();
            director.getBuilder()->onTermRange((yyvsp[-2].string), (yyvsp[0].string));
            delete[] (yyvsp[-2].string);
            delete[] (yyvsp[0].string);
        }
#line 2103 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 77:
#line 393 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onTermDash(); 
        }
#line 2111 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 78:
#line 401 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onTerm((yyvsp[0].string)); 
            delete[] (yyvsp[0].string);
        }
#line 2120 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 79:
#line 406 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onTerm((yyvsp[0].string)); 
            delete[] (yyvsp[0].string);
        }
#line 2129 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 80:
#line 411 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onTermParams(); 
        }
#line 2137 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 81:
#line 417 "src/input/aspcore2.y" /* yacc.c:1646  */
    {}
#line 2143 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 84:
#line 426 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onArithmeticOperation((yyvsp[-1].single_char)); 
        }
#line 2151 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 85:
#line 433 "src/input/aspcore2.y" /* yacc.c:1646  */
    {}
#line 2157 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 86:
#line 435 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onArithmeticOperation((yyvsp[-1].single_char)); 
        }
#line 2165 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 87:
#line 440 "src/input/aspcore2.y" /* yacc.c:1646  */
    {}
#line 2171 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 88:
#line 441 "src/input/aspcore2.y" /* yacc.c:1646  */
    {}
#line 2177 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 89:
#line 446 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2186 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 90:
#line 451 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2195 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 91:
#line 456 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2204 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 92:
#line 461 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[0].string),true);
            delete[] (yyvsp[0].string);
        }
#line 2213 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 93:
#line 469 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAggregateVariableTerm((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2222 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 94:
#line 474 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateUnknownVariable();
        }
#line 2230 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 95:
#line 481 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onExistentialVariable((yyvsp[0].string)); 
            delete[] (yyvsp[0].string);
        }
#line 2239 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 96:
#line 486 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onExistentialVariable((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2248 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 97:
#line 493 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2254 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 98:
#line 494 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2260 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 99:
#line 495 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2266 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 100:
#line 500 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getParserConstraint()->directives();
            director.getBuilder()->onDirective((yyvsp[-1].string),(yyvsp[0].string));
            delete[] (yyvsp[-1].string);
            delete[] (yyvsp[0].string);
        }
#line 2277 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 101:
#line 507 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getParserConstraint()->directives();
            director.getBuilder()->onDirective((yyvsp[-1].string),(yyvsp[0].string));
            delete[] (yyvsp[-1].string);
            delete[] (yyvsp[0].string);
        }
#line 2288 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 102:
#line 517 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAtom(); 
        }
#line 2296 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 103:
#line 524 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateLowerGuard();
        }
#line 2304 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 104:
#line 531 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateUpperGuard();
        }
#line 2312 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 107:
#line 543 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateLowerGuard();
        }
#line 2320 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 111:
#line 559 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateLowerGuard();
        }
#line 2328 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 113:
#line 570 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateUpperGuard();
        }
#line 2336 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 114:
#line 577 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateUpperGuard();
        }
#line 2344 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 122:
#line 597 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onLessOperator(); 
        }
#line 2352 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 123:
#line 601 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onLessOrEqualOperator(); 
        }
#line 2360 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 124:
#line 608 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onGreaterOperator();
        }
#line 2368 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 125:
#line 612 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onGreaterOrEqualOperator();
        }
#line 2376 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 129:
#line 629 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateElement();
        }
#line 2384 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 130:
#line 636 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateFunction((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2393 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 131:
#line 641 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateFunction((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2402 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 132:
#line 646 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateFunction((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2411 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 133:
#line 651 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateFunction((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2420 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 146:
#line 688 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationRuleOrdering((yyvsp[0].string));
        delete[] (yyvsp[0].string);
	}
#line 2429 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 147:
#line 695 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationGlobalOrdering((yyvsp[0].string));
        delete[] (yyvsp[0].string);
	}
#line 2438 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 150:
#line 712 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationRuleAtomIndexedArgument((yyvsp[0].string));
        delete[] (yyvsp[0].string);
	}
#line 2447 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 151:
#line 716 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationRuleAtomIndexedArgument((yyvsp[0].string));
        delete[] (yyvsp[0].string);
	}
#line 2456 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 152:
#line 724 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRuleAtomIndexedLiteral();
        }
#line 2464 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 153:
#line 728 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRuleAtomIndexedLiteral(true);
        }
#line 2472 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 154:
#line 734 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationGlobalAtomIndexedArgument((yyvsp[0].string));
        delete[] (yyvsp[0].string);
	}
#line 2481 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 155:
#line 738 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationGlobalAtomIndexedArgument((yyvsp[0].string));
        delete[] (yyvsp[0].string);
	}
#line 2490 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 156:
#line 746 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalAtomIndexedLiteral();
        }
#line 2498 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 157:
#line 750 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalAtomIndexedLiteral(true);
        }
#line 2506 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 158:
#line 757 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRulePartialOrderingBefore();
        }
#line 2514 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 159:
#line 761 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRulePartialOrderingBefore(true);
        }
#line 2522 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 160:
#line 765 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationRulePartialOrderingBefore();
        }
#line 2530 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 161:
#line 769 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
           director.getBuilder()->onAnnotationAggregateRulePartialOrderingBefore();
        }
#line 2538 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 162:
#line 773 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationAggregateRulePartialOrderingBefore(true);
        }
#line 2546 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 163:
#line 780 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalPartialOrderingBefore();
        }
#line 2554 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 164:
#line 784 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalPartialOrderingBefore(true);
        }
#line 2562 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 165:
#line 788 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationGlobalPartialOrderingBefore();
        }
#line 2570 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 166:
#line 792 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
           director.getBuilder()->onAnnotationAggregateGlobalPartialOrderingBefore();
        }
#line 2578 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 167:
#line 796 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationAggregateGlobalPartialOrderingBefore(true);
        }
#line 2586 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 168:
#line 803 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRulePartialOrderingAfter();
        }
#line 2594 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 169:
#line 807 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRulePartialOrderingAfter(true);
        }
#line 2602 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 170:
#line 811 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationRulePartialOrderingAfter();
        }
#line 2610 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 171:
#line 815 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
           director.getBuilder()->onAnnotationAggregateRulePartialOrderingAfter();
        }
#line 2618 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 172:
#line 819 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationAggregateRulePartialOrderingAfter(true);
        }
#line 2626 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 173:
#line 826 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalPartialOrderingAfter();
        }
#line 2634 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 174:
#line 830 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalPartialOrderingAfter(true);
        }
#line 2642 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 175:
#line 834 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationGlobalPartialOrderingAfter();
        }
#line 2650 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 176:
#line 838 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
           director.getBuilder()->onAnnotationAggregateGlobalPartialOrderingAfter();
        }
#line 2658 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 177:
#line 842 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationAggregateGlobalPartialOrderingAfter(true);
        }
#line 2666 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 186:
#line 869 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationPartialOrdering();
	}
#line 2674 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 187:
#line 875 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationPartialOrdering(true);
	}
#line 2682 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;


#line 2686 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
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
