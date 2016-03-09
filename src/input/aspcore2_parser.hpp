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
#line 29 "src/input/aspcore2.y" /* yacc.c:355  */

    char* string;
    char single_char;
    int integer;

#line 243 "src/input/aspcore2_parser.hpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (DLV2::InputDirector& director);



/* Copy the second part of user declarations.  */

#line 258 "src/input/aspcore2_parser.hpp" /* yacc.c:358  */

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
#define YYFINAL  74
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   381

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  132
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  224

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    70,    70,    72,    74,    75,    76,    80,    81,    85,
      86,    87,    91,    95,    99,   103,   107,   114,   118,   126,
     133,   138,   146,   151,   155,   165,   169,   173,   177,   184,
     188,   195,   196,   197,   198,   202,   209,   216,   217,   221,
     225,   232,   239,   243,   250,   254,   261,   265,   269,   276,
     277,   281,   288,   294,   295,   299,   304,   309,   317,   318,
     322,   323,   327,   334,   338,   345,   346,   347,   351,   352,
     353,   354,   358,   363,   368,   372,   377,   384,   388,   395,
     396,   402,   403,   407,   412,   417,   422,   430,   435,   442,
     447,   455,   456,   457,   461,   468,   478,   485,   492,   499,
     500,   504,   511,   515,   516,   520,   527,   531,   538,   545,
     546,   550,   551,   552,   553,   554,   558,   562,   569,   573,
     580,   584,   585,   590,   597,   602,   607,   612,   620,   621,
     625,   629,   636
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
  "ANNOTATION_RULE_ATOM_INDEXED", "ANNOTATION_ATOM_INDEXED",
  "ANNOTATION_ATOM_INDEXED_ARGUMENTS", "PARAM_OPEN_ANNOTATION",
  "PARAM_CLOSE_ANNOTATION", "DOT_ANNOTATION", "EQUAL_ANNOTATION",
  "COMMA_ANNOTATION", "ERROR", "NEWLINE", "DOT", "DDOT", "SEMICOLON",
  "COLON", "CONS", "QUERY_MARK", "PLUS", "TIMES", "SLASH", "ANON_VAR",
  "PARAM_OPEN", "PARAM_CLOSE", "SQUARE_OPEN", "SQUARE_CLOSE", "CURLY_OPEN",
  "CURLY_CLOSE", "EQUAL", "UNEQUAL", "LESS", "GREATER", "LESS_OR_EQ",
  "GREATER_OR_EQ", "DASH", "COMMA", "NAF", "AT", "WCONS", "VEL", "EXISTS",
  "$accept", "HEAD_SEPARATOR", "program", "real_program", "rules", "rule",
  "head", "body", "weight_at_levels", "levels_and_terms", "disjunction",
  "conjunction", "choice_atom", "lower_guard", "upper_guard",
  "choice_elements", "choice_element", "choice_element_atom",
  "choice_elements_literals", "naf_literals", "naf_literal",
  "naf_literal_aggregate", "existential_atom", "classic_literal", "atom",
  "terms", "basic_terms", "builtin_atom", "compareop", "binop", "arithop",
  "term_", "term", "basic_term", "ground_term", "variable_term", "vars",
  "identifier", "directives", "query", "lower_guard_compare_aggregate",
  "upper_guard_compare_aggregate", "compare_aggregate",
  "lower_guard_leftward_left_aggregate", "leftward_left_aggregate",
  "left_aggregate", "lower_guard_rightward_left_aggregate",
  "rightward_left_aggregate", "upper_guard_leftward_right_aggregate",
  "upper_guard_rightward_right_aggregate", "right_aggregate",
  "aggregate_atom", "leftwardop", "rightwardop", "aggregate",
  "aggregate_elements", "aggregate_element", "aggregate_function",
  "annotation", "annotation_rule_ordering", "ordering_type",
  "annotation_rule_atom_indexed", YY_NULLPTR
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
     305,   306,   307,   308,   309
};
# endif

#define YYPACT_NINF -147

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-147)))

#define YYTABLE_NINF -106

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     199,  -147,  -147,   -19,  -147,  -147,    24,    16,    19,   276,
    -147,   314,   137,   314,   276,    38,    58,  -147,   214,  -147,
      42,    21,  -147,    43,  -147,  -147,  -147,  -147,   333,   118,
     121,   214,  -147,  -147,   111,  -147,   102,   105,  -147,  -147,
    -147,  -147,   324,    93,    74,  -147,  -147,  -147,  -147,   333,
     221,  -147,   221,   114,  -147,   221,   123,  -147,  -147,   179,
      89,   314,   153,    96,   -18,  -147,   107,  -147,   103,  -147,
      62,   126,  -147,    50,  -147,  -147,   116,  -147,  -147,   266,
    -147,    46,   137,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,   314,  -147,  -147,   303,   145,
    -147,  -147,  -147,   144,   152,  -147,   333,  -147,  -147,   276,
     231,   314,   284,   288,  -147,  -147,  -147,   314,  -147,  -147,
     314,   314,  -147,  -147,  -147,   159,  -147,   314,   137,   179,
     255,   303,   139,   178,  -147,  -147,  -147,   162,   137,  -147,
    -147,    18,  -147,  -147,    64,    33,  -147,   176,   176,  -147,
    -147,  -147,  -147,    33,    33,    33,    33,  -147,  -147,  -147,
    -147,  -147,   189,   -22,  -147,  -147,  -147,    49,  -147,    69,
    -147,  -147,   314,    57,   161,  -147,   333,   101,   314,  -147,
    -147,  -147,   179,   315,   314,  -147,   188,   191,  -147,   255,
     159,   159,  -147,  -147,    33,   255,  -147,    59,  -147,    33,
     190,   209,   187,  -147,  -147,  -147,  -147,  -147,   314,   314,
     198,  -147,   206,   255,   196,   148,  -147,   176,  -147,   314,
     218,   196,   225,  -147
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     6,    91,    73,    93,    92,     0,     0,     0,     0,
      74,     0,     0,     0,     0,     0,     0,     4,     7,    10,
       0,    17,    18,     0,    27,    25,    53,    79,     0,    72,
       0,     0,   128,   129,     0,    94,     0,     0,   124,   125,
     126,   127,     0,     0,    19,    49,    29,    46,    48,     0,
       0,   113,     0,   103,   111,     0,   104,   112,    50,     0,
       0,     0,     0,    72,     0,    38,    39,    41,    55,    54,
      78,     0,    89,     0,     1,     9,    53,     8,    12,     0,
       2,     0,     0,    68,    70,    71,    63,    64,   116,   118,
     117,   119,    69,    65,    35,     0,    66,    67,     0,     0,
       5,    11,    76,     0,     0,    47,     0,    51,    15,     0,
      65,     0,    66,    67,    99,   102,   114,     0,   106,   115,
       0,     0,   100,   109,   110,     0,    77,     0,     0,    33,
       0,     0,     0,     0,    52,    96,    13,     0,     0,    28,
      26,     0,    80,    57,     0,    58,    95,     0,     0,    97,
     101,   105,    30,    62,   107,   108,    98,    83,    85,    87,
      84,    88,     0,     0,    60,    81,    82,     0,   122,     0,
      37,    34,     0,     0,    40,    42,     0,     0,     0,    16,
      90,    14,    32,    75,     0,   131,     0,     0,    86,     0,
       0,     0,   120,    75,    36,     0,    56,     0,    31,    59,
       0,     0,   123,    44,    61,   121,    43,    20,     0,     0,
       0,   130,     0,     0,    24,    22,    21,     0,    45,     0,
       0,    23,     0,   132
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -147,  -147,  -147,   222,  -147,    10,  -147,   -10,  -147,  -147,
    -147,  -147,  -147,  -147,    66,   173,   128,  -147,  -147,  -147,
    -125,   154,   183,     6,     7,  -105,  -147,  -147,   -20,   -27,
    -147,   170,     0,    67,  -147,  -147,  -147,     3,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,   208,   215,
    -147,   241,    -9,    -2,    23,  -147,    82,  -147,  -147,  -147,
    -146,  -147
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    81,    16,    17,    18,    19,    20,    43,   179,   210,
      21,    44,    22,    23,   171,    64,    65,    66,   174,   202,
      45,    46,    24,    47,    26,   144,   163,    48,    93,   111,
      95,    27,   145,   164,   165,   166,    73,    63,    30,    77,
      50,   122,    51,    52,    53,    54,    55,    56,   116,   119,
      57,    58,    96,    97,    59,   167,   168,    60,    31,    32,
     186,    33
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,    94,   187,    29,    71,   175,    25,   189,    34,    49,
     128,    62,    29,    70,    49,    68,    29,    29,    28,    67,
      69,    29,   169,   129,    25,    76,   177,   190,    75,   110,
      28,    28,    35,    29,    29,    36,    25,    25,    37,   121,
     112,   101,   106,    72,   117,    29,   128,   113,   105,     2,
     117,     4,     5,     2,   120,     4,     5,   120,    74,   182,
       2,    70,     4,     5,   203,    83,    84,    85,    78,   137,
     206,   220,    79,   114,    80,   115,    68,   191,   118,    49,
     134,    92,    29,    82,    68,    68,   149,   140,   218,    67,
     192,    83,    84,    85,   138,    84,    85,   150,   207,   133,
      15,   183,   172,   214,   151,   138,   193,    92,   208,    49,
     209,   153,    29,   184,   221,   102,   103,   154,   184,   108,
     155,   156,   104,   109,     2,     3,     4,     5,    99,   125,
     176,    68,   127,    29,     7,    67,   130,     8,   196,   131,
       2,    68,     4,     5,   -55,    69,   -55,   135,   -55,   -55,
     184,     9,   132,   146,    98,   172,    10,    11,    88,   -55,
      90,    12,   157,   158,   159,   160,   147,   -55,    89,    13,
      91,   -55,   194,    14,   148,    15,    68,   178,   197,   105,
      83,    84,    85,   180,   199,    83,    84,    85,   181,   176,
     126,   185,    29,   188,   161,   176,    92,   219,    29,    -3,
       1,    92,     2,     3,     4,     5,     6,   162,   200,   215,
     195,   211,     7,   176,   201,     8,    29,     2,     3,     4,
       5,    86,    87,    88,    89,    90,    91,   212,   217,     9,
      38,    39,    40,    41,    10,    11,   213,   216,   222,    12,
     -97,   -97,   -97,   -97,     9,   184,   223,    13,   198,    10,
      11,    14,   100,    15,    12,   141,   170,   204,     2,     3,
       4,     5,    13,   152,   139,   142,    14,   123,    15,     2,
       3,     4,     5,   205,   124,    38,    39,    40,    41,     2,
       3,     4,     5,   107,     0,    38,    39,    40,    41,     0,
      10,    11,   136,  -101,  -101,  -101,  -101,  -105,  -105,  -105,
    -105,    10,    11,    13,     0,   173,     2,     3,     4,     5,
       0,    10,    11,     0,    13,     0,    42,     2,     3,     4,
       5,     0,     0,     0,    13,     0,    42,     2,     3,     4,
       5,     0,     0,    38,    39,    40,    41,     0,    10,    11,
     143,   -56,     0,   -56,     0,   -56,   -56,     0,     0,    10,
      11,    61,     0,     0,     0,     0,   -56,     0,     0,    10,
      11,     0,    61,     0,   -56,    83,    84,    85,   -56,     0,
       0,     0,    13,     0,     0,    86,    87,    88,    89,    90,
      91,    92
};

static const yytype_int16 yycheck[] =
{
       0,    28,   148,     0,    14,   130,     0,    29,    27,     9,
      28,    11,     9,    13,    14,    12,    13,    14,    18,    12,
      13,    18,   127,    41,    18,    18,   131,    49,    18,    49,
      30,    31,     8,    30,    31,    19,    30,    31,    19,    59,
      49,    31,    42,     5,    53,    42,    28,    49,    42,     3,
      59,     5,     6,     3,    56,     5,     6,    59,     0,    41,
       3,    61,     5,     6,   189,    32,    33,    34,    26,    79,
     195,   217,    30,    50,    53,    52,    73,    28,    55,    79,
      73,    48,    79,    40,    81,    82,   106,    81,   213,    82,
      41,    32,    33,    34,    48,    33,    34,   106,    39,    49,
      54,    37,   129,   208,   106,    48,    37,    48,    49,   109,
      51,   111,   109,    49,   219,     4,    14,   117,    49,    26,
     120,   121,    17,    49,     3,     4,     5,     6,     7,    40,
     130,   128,    36,   130,    13,   128,    29,    16,    37,    36,
       3,   138,     5,     6,    26,   138,    28,    31,    30,    31,
      49,    30,    26,     8,    36,   182,    35,    36,    44,    41,
      46,    40,     3,     4,     5,     6,    22,    49,    45,    48,
      47,    53,   172,    52,    22,    54,   173,    38,   178,   173,
      32,    33,    34,     5,   184,    32,    33,    34,    26,   189,
      37,    15,   189,     4,    35,   195,    48,    49,   195,     0,
       1,    48,     3,     4,     5,     6,     7,    48,    20,   209,
      49,    21,    13,   213,    23,    16,   213,     3,     4,     5,
       6,    42,    43,    44,    45,    46,    47,    18,    22,    30,
       9,    10,    11,    12,    35,    36,    49,    39,    20,    40,
       9,    10,    11,    12,    30,    49,    21,    48,   182,    35,
      36,    52,    30,    54,    40,    82,   128,   190,     3,     4,
       5,     6,    48,   109,    81,    95,    52,    59,    54,     3,
       4,     5,     6,   191,    59,     9,    10,    11,    12,     3,
       4,     5,     6,    42,    -1,     9,    10,    11,    12,    -1,
      35,    36,    26,     9,    10,    11,    12,     9,    10,    11,
      12,    35,    36,    48,    -1,    50,     3,     4,     5,     6,
      -1,    35,    36,    -1,    48,    -1,    50,     3,     4,     5,
       6,    -1,    -1,    -1,    48,    -1,    50,     3,     4,     5,
       6,    -1,    -1,     9,    10,    11,    12,    -1,    35,    36,
      37,    26,    -1,    28,    -1,    30,    31,    -1,    -1,    35,
      36,    48,    -1,    -1,    -1,    -1,    41,    -1,    -1,    35,
      36,    -1,    48,    -1,    49,    32,    33,    34,    53,    -1,
      -1,    -1,    48,    -1,    -1,    42,    43,    44,    45,    46,
      47,    48
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,    13,    16,    30,
      35,    36,    40,    48,    52,    54,    57,    58,    59,    60,
      61,    65,    67,    68,    77,    78,    79,    86,    87,    92,
      93,   113,   114,   116,    27,     8,    19,    19,     9,    10,
      11,    12,    50,    62,    66,    75,    76,    78,    82,    87,
      95,    97,    98,    99,   100,   101,   102,   105,   106,   109,
     112,    48,    87,    92,    70,    71,    72,    79,    92,    79,
      87,    62,     5,    91,     0,    60,    79,    94,    26,    30,
      53,    56,    40,    32,    33,    34,    42,    43,    44,    45,
      46,    47,    48,    83,    84,    85,   107,   108,    36,     7,
      58,    60,     4,    14,    17,    78,    87,   106,    26,    49,
      83,    84,   107,   108,   109,   109,   103,   107,   109,   104,
     108,    83,    96,   103,   104,    40,    37,    36,    28,    41,
      29,    36,    26,    49,    79,    31,    26,    62,    48,    77,
      78,    70,    86,    37,    80,    87,     8,    22,    22,    83,
     107,   108,    76,    87,    87,    87,    87,     3,     4,     5,
       6,    35,    48,    81,    88,    89,    90,   110,   111,    80,
      71,    69,    84,    50,    73,    75,    87,    80,    38,    63,
       5,    26,    41,    37,    49,    15,   115,   115,     4,    29,
      49,    28,    41,    37,    87,    49,    37,    87,    69,    87,
      20,    23,    74,    75,    88,   111,    75,    39,    49,    51,
      64,    21,    18,    49,    80,    87,    39,    22,    75,    49,
     115,    80,    20,    21
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    57,    57,    57,    57,    58,    58,    59,
      59,    59,    60,    60,    60,    60,    60,    61,    61,    62,
      63,    63,    64,    64,    64,    65,    65,    65,    65,    66,
      66,    67,    67,    67,    67,    68,    69,    70,    70,    71,
      71,    72,    73,    73,    74,    74,    75,    75,    75,    76,
      76,    76,    77,    78,    78,    79,    79,    79,    80,    80,
      81,    81,    82,    83,    83,    84,    84,    84,    85,    85,
      85,    85,    86,    86,    86,    86,    86,    86,    86,    87,
      87,    88,    88,    89,    89,    89,    89,    90,    90,    91,
      91,    92,    92,    92,    93,    93,    94,    95,    96,    97,
      97,    98,    99,   100,   100,   101,   102,   103,   104,   105,
     105,   106,   106,   106,   106,   106,   107,   107,   108,   108,
     109,   110,   110,   111,   112,   112,   112,   112,   113,   113,
     114,   115,   116
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     2,     2,
       1,     2,     2,     3,     4,     3,     4,     1,     1,     1,
       3,     4,     2,     4,     2,     1,     3,     1,     3,     1,
       3,     5,     4,     3,     4,     2,     2,     3,     1,     1,
       3,     1,     1,     3,     1,     3,     1,     2,     1,     1,
       1,     2,     3,     1,     2,     1,     4,     3,     1,     3,
       1,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     3,     2,     1,
       3,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       3,     1,     1,     1,     2,     3,     2,     2,     2,     2,
       2,     2,     2,     1,     1,     2,     2,     2,     2,     2,
       2,     1,     1,     1,     2,     2,     1,     1,     1,     1,
       4,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       7,     1,    11
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
        case 6:
#line 76 "src/input/aspcore2.y" /* yacc.c:1646  */
    { yyerror(director,"Generic error"); }
#line 1556 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 8:
#line 81 "src/input/aspcore2.y" /* yacc.c:1646  */
    { director.getBuilder()->onQuery(); }
#line 1562 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 12:
#line 92 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onRule(); 
        }
#line 1570 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 13:
#line 96 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onRule(); 
        }
#line 1578 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 14:
#line 100 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onRule(); 
        }
#line 1586 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 15:
#line 104 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onConstraint(); 
        }
#line 1594 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 16:
#line 108 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onWeakConstraint(); 
        }
#line 1602 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 17:
#line 115 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onHead();
        }
#line 1610 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 18:
#line 119 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceAtom();
            director.getBuilder()->onHead();
        }
#line 1619 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 19:
#line 127 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onBody();
        }
#line 1627 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 20:
#line 134 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            // There is only the weight. No level and terms.
            director.getBuilder()->onWeightAtLevels(1,0,0); 
        }
#line 1636 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 21:
#line 139 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            // There are also a level and/or some terms.
            // The finalization has been postponed to "level_and_terms".
        }
#line 1645 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 22:
#line 147 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            // There is no terms following the level.
            director.getBuilder()->onWeightAtLevels(1,1,0); 
        }
#line 1654 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 23:
#line 152 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onWeightAtLevels(1,1,(yyvsp[0].integer)); 
        }
#line 1662 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 24:
#line 156 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            // The level is omitted.
            // Thus, the first term, recognized as the
            // weight, should be a term of this list.
            director.getBuilder()->onWeightAtLevels(0,0,(yyvsp[0].integer)+1); 
        }
#line 1673 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 25:
#line 166 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onHeadAtom(); 
        }
#line 1681 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 26:
#line 170 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onHeadAtom(); 
        }
#line 1689 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 27:
#line 174 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onHeadAtom(); 
        }
#line 1697 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 28:
#line 178 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onHeadAtom(); 
        }
#line 1705 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 29:
#line 185 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onBodyLiteral(); 
        }
#line 1713 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 30:
#line 189 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onBodyLiteral(); 
        }
#line 1721 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 35:
#line 203 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onChoiceLowerGuard();
        }
#line 1729 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 36:
#line 210 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onChoiceUpperGuard();
        }
#line 1737 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 39:
#line 222 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceElement(); 
        }
#line 1745 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 40:
#line 226 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceElement(); 
        }
#line 1753 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 41:
#line 233 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceElementAtom(); 
        }
#line 1761 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 42:
#line 240 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onChoiceElementLiteral(); 
        }
#line 1769 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 43:
#line 244 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceElementLiteral();
        }
#line 1777 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 44:
#line 251 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateNafLiteral();
        }
#line 1785 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 45:
#line 255 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateNafLiteral();
        }
#line 1793 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 46:
#line 262 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onNafLiteral();
        }
#line 1801 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 47:
#line 266 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onNafLiteral(true);
        }
#line 1809 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 48:
#line 270 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onNafLiteral();
        }
#line 1817 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 50:
#line 278 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregate();
        }
#line 1825 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 51:
#line 282 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregate(true);
        }
#line 1833 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 52:
#line 289 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onExistentialAtom(); 
        }
#line 1841 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 53:
#line 294 "src/input/aspcore2.y" /* yacc.c:1646  */
    { director.getBuilder()->onAtom(); }
#line 1847 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 54:
#line 295 "src/input/aspcore2.y" /* yacc.c:1646  */
    { director.getBuilder()->onAtom(true); }
#line 1853 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 55:
#line 300 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onPredicateName((yyvsp[0].string)); 
            delete[] (yyvsp[0].string);
        }
#line 1862 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 56:
#line 305 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onPredicateName((yyvsp[-3].string)); 
            delete[] (yyvsp[-3].string);
        }
#line 1871 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 57:
#line 310 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onPredicateName((yyvsp[-2].string)); 
            delete[] (yyvsp[-2].string);
        }
#line 1880 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 58:
#line 317 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.integer) = 1; }
#line 1886 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 59:
#line 318 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[-2].integer) + 1; }
#line 1892 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 62:
#line 328 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onBuiltinAtom();
        }
#line 1900 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 63:
#line 335 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onEqualOperator();
        }
#line 1908 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 64:
#line 339 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onUnequalOperator(); 
        }
#line 1916 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 68:
#line 351 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.single_char) = '+'; }
#line 1922 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 69:
#line 352 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.single_char) = '-'; }
#line 1928 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 70:
#line 353 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.single_char) = '*'; }
#line 1934 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 71:
#line 354 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.single_char) = '/'; }
#line 1940 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 72:
#line 359 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onTerm((yyvsp[0].string)); 
            delete[] (yyvsp[0].string);
        }
#line 1949 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 73:
#line 364 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onTerm((yyvsp[0].string)); 
            delete[] (yyvsp[0].string);
        }
#line 1958 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 74:
#line 369 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onUnknownVariable(); 
        }
#line 1966 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 75:
#line 373 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onFunction((yyvsp[-3].string), (yyvsp[-1].integer)); 
            delete[] (yyvsp[-3].string);
        }
#line 1975 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 76:
#line 378 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getParserConstraint()->rangeFacts();
            director.getBuilder()->onTermRange((yyvsp[-2].string), (yyvsp[0].string));
            delete[] (yyvsp[-2].string);
            delete[] (yyvsp[0].string);
        }
#line 1986 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 77:
#line 385 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onTermParams(); 
        }
#line 1994 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 78:
#line 389 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onTermDash(); 
        }
#line 2002 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 79:
#line 395 "src/input/aspcore2.y" /* yacc.c:1646  */
    {}
#line 2008 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 80:
#line 397 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onArithmeticOperation((yyvsp[-1].single_char)); 
        }
#line 2016 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 81:
#line 402 "src/input/aspcore2.y" /* yacc.c:1646  */
    {}
#line 2022 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 82:
#line 403 "src/input/aspcore2.y" /* yacc.c:1646  */
    {}
#line 2028 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 83:
#line 408 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2037 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 84:
#line 413 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2046 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 85:
#line 418 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2055 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 86:
#line 423 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[0].string),true);
            delete[] (yyvsp[0].string);
        }
#line 2064 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 87:
#line 431 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAggregateVariableTerm((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2073 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 88:
#line 436 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateUnknownVariable();
        }
#line 2081 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 89:
#line 443 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onExistentialVariable((yyvsp[0].string)); 
            delete[] (yyvsp[0].string);
        }
#line 2090 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 90:
#line 448 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onExistentialVariable((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2099 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 91:
#line 455 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2105 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 92:
#line 456 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2111 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 93:
#line 457 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2117 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 94:
#line 462 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getParserConstraint()->directives();
            director.getBuilder()->onDirective((yyvsp[-1].string),(yyvsp[0].string));
            delete[] (yyvsp[-1].string);
            delete[] (yyvsp[0].string);
        }
#line 2128 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 95:
#line 469 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getParserConstraint()->directives();
            director.getBuilder()->onDirective((yyvsp[-1].string),(yyvsp[0].string));
            delete[] (yyvsp[-1].string);
            delete[] (yyvsp[0].string);
        }
#line 2139 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 96:
#line 479 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAtom(); 
        }
#line 2147 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 97:
#line 486 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateLowerGuard();
        }
#line 2155 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 98:
#line 493 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateUpperGuard();
        }
#line 2163 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 101:
#line 505 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateLowerGuard();
        }
#line 2171 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 105:
#line 521 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateLowerGuard();
        }
#line 2179 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 107:
#line 532 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateUpperGuard();
        }
#line 2187 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 108:
#line 539 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateUpperGuard();
        }
#line 2195 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 116:
#line 559 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onLessOperator(); 
        }
#line 2203 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 117:
#line 563 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onLessOrEqualOperator(); 
        }
#line 2211 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 118:
#line 570 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onGreaterOperator();
        }
#line 2219 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 119:
#line 574 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onGreaterOrEqualOperator();
        }
#line 2227 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 123:
#line 591 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateElement();
        }
#line 2235 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 124:
#line 598 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateFunction((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2244 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 125:
#line 603 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateFunction((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2253 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 126:
#line 608 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateFunction((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2262 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 127:
#line 613 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateFunction((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2271 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 131:
#line 629 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationRuleOrdering((yyvsp[0].string));
        delete[] (yyvsp[0].string);
	}
#line 2280 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;


#line 2284 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
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
