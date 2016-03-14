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
#define YYFINAL  90
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   672

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  83
/* YYNRULES -- Number of rules.  */
#define YYNRULES  185
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  362

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
      87,    88,    89,    93,    97,   101,   105,   109,   116,   120,
     128,   135,   140,   148,   153,   157,   167,   171,   175,   179,
     186,   190,   197,   198,   199,   200,   204,   211,   218,   219,
     223,   227,   234,   241,   245,   252,   256,   263,   267,   271,
     278,   279,   283,   290,   296,   297,   301,   306,   311,   319,
     320,   324,   325,   329,   336,   340,   347,   348,   349,   353,
     354,   355,   356,   360,   365,   370,   374,   379,   386,   390,
     397,   398,   404,   405,   409,   414,   419,   424,   432,   437,
     444,   449,   457,   458,   459,   463,   470,   480,   487,   494,
     501,   502,   506,   513,   517,   518,   522,   529,   533,   540,
     547,   548,   552,   553,   554,   555,   556,   560,   564,   571,
     575,   582,   586,   587,   592,   599,   604,   609,   614,   622,
     623,   627,   628,   629,   633,   634,   638,   639,   640,   644,
     648,   652,   659,   666,   671,   676,   680,   689,   693,   700,
     704,   713,   717,   724,   728,   732,   736,   740,   747,   751,
     755,   759,   763,   770,   774,   778,   782,   786,   793,   797,
     801,   805,   809,   816,   817,   821,   822,   826,   827,   831,
     832,   836,   842,   844,   849,   851
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
  "annotation_rule_partial_order", "annotation_global_partial_order", YY_NULLPTR
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

#define YYPACT_NINF -295

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-295)))

#define YYTABLE_NINF -107

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     362,  -295,  -295,    -5,  -295,  -295,    36,    17,    28,  -295,
      77,    94,     9,   495,  -295,   204,    68,   204,   495,    75,
      98,  -295,   282,  -295,    81,    89,  -295,   105,  -295,  -295,
    -295,  -295,   504,   428,   403,   432,   111,   282,   134,  -295,
    -295,  -295,  -295,   124,  -295,  -295,   179,  -295,   172,   170,
     175,   187,   162,   191,  -295,  -295,  -295,  -295,   623,   186,
     165,  -295,  -295,  -295,  -295,   504,   211,  -295,   211,   117,
    -295,   211,   120,  -295,  -295,   153,   176,   204,    92,   188,
      24,  -295,   196,  -295,   192,  -295,    72,   203,  -295,    26,
    -295,  -295,   200,  -295,  -295,   485,  -295,    44,    68,  -295,
    -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,
    -295,   204,  -295,  -295,   231,   230,  -295,  -295,  -295,  -295,
    -295,   136,  -295,   201,   212,   214,   217,   220,   222,  -295,
     504,  -295,  -295,   495,   280,   204,   337,   348,  -295,  -295,
    -295,   204,  -295,  -295,   204,   204,  -295,  -295,  -295,   246,
    -295,   204,    68,   153,    64,   231,   224,   261,  -295,  -295,
    -295,   243,    68,  -295,  -295,    43,  -295,  -295,    13,   145,
    -295,   228,   229,   272,    54,   277,   116,   505,   253,  -295,
    -295,  -295,  -295,   145,   145,   145,   145,  -295,  -295,  -295,
    -295,  -295,   292,   -14,  -295,  -295,  -295,    60,  -295,    66,
    -295,  -295,   204,    37,   250,  -295,   504,    90,   204,  -295,
    -295,  -295,   153,   399,   204,   262,   263,  -295,   264,    37,
    -295,   256,  -295,   270,    37,  -295,   265,   623,  -295,  -295,
    -295,   266,   278,   554,  -295,    64,   246,   246,  -295,  -295,
     145,    64,  -295,   293,  -295,   145,   564,   574,   285,  -295,
     296,   294,  -295,   304,  -295,  -295,   505,   275,   623,  -295,
    -295,  -295,   284,   290,   286,  -295,  -295,  -295,  -295,  -295,
     204,   204,   301,   623,  -295,  -295,  -295,   300,   309,   623,
    -295,  -295,  -295,   305,   312,  -295,   318,  -295,   321,  -295,
     350,  -295,  -295,   554,   322,    64,   323,    61,  -295,  -295,
    -295,   564,   324,  -295,  -295,   574,   326,   330,   336,   339,
    -295,   358,  -295,   204,  -295,   366,  -295,   363,   384,   388,
     353,   352,   323,   354,   357,   346,   359,   355,   360,   554,
     371,   372,   373,   400,   380,   416,   383,   381,   505,   574,
     564,  -295,   397,  -295,   398,   389,   387,   390,   391,  -295,
    -295,   415,   405,   408,   409,  -295,   423,   427,   434,  -295,
    -295,  -295
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,    92,    74,    94,    93,     0,     0,     0,   181,
       0,     0,     0,     0,    75,     0,     0,     0,     0,     0,
       0,     4,     8,    11,     0,    18,    19,     0,    28,    26,
      54,    80,     0,    73,     0,     0,   129,     0,   134,   136,
     131,   137,   132,     0,   138,   133,     0,    95,     0,     0,
       0,     0,     0,     0,   125,   126,   127,   128,     0,     0,
      20,    50,    30,    47,    49,     0,     0,   114,     0,   104,
     112,     0,   105,   113,    51,     0,     0,     0,     0,    73,
       0,    39,    40,    42,    56,    55,    79,     0,    90,     0,
       1,    10,    54,     9,    13,     0,     2,     0,     0,    69,
      71,    72,    64,    65,   117,   119,   118,   120,    70,    66,
      36,     0,    67,    68,     0,     0,     5,     6,   130,    12,
     135,     0,    77,     0,     0,     0,     0,     0,     0,    48,
       0,    52,    16,     0,    66,     0,    67,    68,   100,   103,
     115,     0,   107,   116,     0,     0,   101,   110,   111,     0,
      78,     0,     0,    34,     0,     0,     0,     0,    53,    97,
      14,     0,     0,    29,    27,     0,    81,    58,     0,    59,
      96,     0,     0,     0,     0,     0,     0,     0,     0,    98,
     102,   106,    31,    63,   108,   109,    99,    84,    86,    88,
      85,    89,     0,     0,    61,    82,    83,     0,   123,     0,
      38,    35,     0,     0,    41,    43,     0,     0,     0,    17,
      91,    15,    33,    76,     0,     0,     0,   141,     0,     0,
     147,     0,   142,     0,     0,   151,     0,     0,   168,   170,
     171,   179,     0,     0,    87,     0,     0,     0,   121,    76,
      37,     0,    57,     0,    32,    60,     0,     0,     0,   148,
       0,     0,   152,     0,   169,   172,     0,     0,     0,   158,
     160,   161,   175,     0,   124,    45,    62,   122,    44,    21,
       0,     0,     0,     0,   153,   155,   156,   173,     0,     0,
     163,   165,   166,   177,     0,   139,     0,   140,     0,   180,
       0,   159,   162,     0,     0,     0,    25,    23,    22,   154,
     157,     0,     0,   164,   167,     0,     0,     0,     0,     0,
     176,     0,    46,     0,   174,     0,   178,     0,     0,     0,
       0,     0,    24,     0,     0,   145,     0,   149,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   146,     0,   150,     0,     0,     0,     0,     0,   143,
     144,     0,     0,     0,     0,   185,     0,     0,     0,   184,
     182,   183
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -295,  -295,  -295,   138,  -295,    11,  -295,    -3,  -295,  -295,
    -295,  -295,  -295,  -295,   252,   364,   314,  -295,  -295,  -295,
    -151,   334,   374,     0,   -10,  -150,  -295,  -169,   -47,   -30,
    -295,   361,     4,   238,  -295,  -295,  -295,    40,  -295,  -295,
    -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,   401,   402,
    -295,    51,   -55,   -48,   122,  -295,   242,  -295,   439,  -295,
     442,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,
    -295,  -295,  -295,  -295,  -295,  -295,  -288,  -268,  -294,  -247,
    -295,  -295,  -295
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    97,    20,    21,    22,    23,    24,    59,   209,   272,
      25,    60,    26,    27,   201,    80,    81,    82,   204,   264,
      61,    62,    28,    63,    30,   168,   193,    64,   109,   135,
     111,    31,    65,   194,   195,   196,    89,    33,    34,    93,
      66,   146,    67,    68,    69,    70,    71,    72,   140,   143,
      73,    74,   112,   113,    75,   197,   198,    76,    35,    36,
      37,    38,    39,    40,   218,   223,    41,    42,   326,   221,
     328,   226,   277,   262,   283,   231,   278,   263,   284,   232,
      43,    44,    45
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,   199,   110,   205,    32,   207,    83,    85,   229,   289,
     136,   316,    92,   314,   141,    87,   235,   137,   134,    78,
     141,    86,    29,    46,   144,   310,    32,   144,   145,     2,
      52,     4,     5,    91,    29,    29,   236,    29,    32,    32,
       2,    32,     4,     5,    47,   347,    53,     2,   119,     4,
       5,   213,   348,   152,    48,    79,    84,     2,   129,     4,
       5,   337,   130,   214,   260,    49,   153,     2,     3,     4,
       5,     2,   152,     4,     5,   180,   157,   275,   281,   158,
      88,    86,   181,   179,   265,   212,   162,   229,    83,   237,
     268,   346,   161,   162,    99,   100,   101,   164,    90,    19,
      14,    15,   238,   162,   239,   219,   100,   101,    94,   131,
     108,   313,    95,    17,    50,   203,   214,    79,   169,     2,
     296,     4,     5,   202,   260,    99,   100,   101,   242,    84,
     150,    51,   275,    10,    11,    12,   281,    84,    84,   183,
     214,   108,    83,    96,   312,   184,    98,     7,   185,   186,
       8,    79,    85,     9,    79,   169,   171,   172,   206,   169,
     260,   121,   104,   322,   106,   162,   105,   224,   107,   229,
     281,   275,   116,   117,   220,    79,   225,   228,    99,   100,
     101,    79,   202,   122,    79,    79,   123,   124,   138,   125,
     139,    79,    84,   142,   108,    79,   102,   103,   104,   105,
     106,   107,    84,   129,   126,   127,   240,     2,     3,     4,
       5,   128,   243,   132,    84,   133,    84,   149,   245,   249,
      54,    55,    56,    57,   252,   151,   154,   254,   230,   155,
     156,   130,   159,   259,     2,     3,     4,     5,   170,   206,
      14,    15,    79,    84,   173,   206,   274,   280,    79,   187,
     188,   189,   190,    77,    79,   174,   228,   175,   291,    84,
     176,   177,   130,   208,    84,   178,   210,    14,    15,   167,
     211,   215,   216,   299,   169,   297,   217,   130,   255,   303,
      77,   222,   191,   130,   261,     2,     3,     4,     5,   -98,
     -98,   -98,   -98,   259,   233,   192,   234,   276,   282,   206,
     241,   274,   248,   246,   247,   280,   250,   230,   251,   292,
      79,    79,   285,    13,   286,   253,   256,   169,    14,    15,
     257,   287,   288,    16,   300,   290,    99,   100,   101,   259,
     304,    17,   294,   269,   293,    18,   295,    19,   228,   280,
     274,   298,   108,   270,   261,   271,  -102,  -102,  -102,  -102,
     301,   302,   276,    79,   306,   305,   282,  -106,  -106,  -106,
    -106,   307,    -3,     1,   308,     2,     3,     4,     5,     6,
     309,   318,   311,   214,   315,     7,   317,   319,     8,   321,
     261,     9,   320,   324,    10,    11,    12,   323,   325,   230,
     282,   276,   327,    13,   329,   330,   333,   331,    14,    15,
     332,   334,   336,    16,   341,   335,     2,     3,     4,     5,
     115,    17,   338,   339,   340,    18,     7,    19,   342,     8,
     343,   344,     9,   345,   349,   350,   -57,   351,   -57,   352,
     -57,   -57,   353,   354,    13,     2,     3,     4,     5,    14,
      15,   -57,   355,   356,    16,     7,   357,   358,     8,   -57,
     359,     9,    17,   -57,   360,   -56,    18,   -56,    19,   -56,
     -56,   361,   165,    13,   244,   114,   200,   182,    14,    15,
     -56,   163,   166,    16,   266,   118,   147,   148,   -56,   267,
     120,    17,   -56,     0,     0,    18,     0,    19,     2,     3,
       4,     5,     0,     0,    54,    55,    56,    57,     2,     3,
       4,     5,     0,     0,    54,    55,    56,    57,     2,     3,
       4,     5,   160,     0,    54,    55,    56,    57,     0,     0,
       0,    14,    15,     0,     0,     0,     0,     0,     0,     0,
       0,    14,    15,     0,    17,     0,    58,    99,   100,   101,
       0,    14,    15,     0,    17,     0,    58,   102,   103,   104,
     105,   106,   107,   108,    17,     0,   227,     2,     3,     4,
       5,     0,     0,    54,    55,    56,    57,     2,     3,     4,
       5,     0,     0,    54,    55,    56,    57,     2,     3,     4,
       5,     0,     0,    54,    55,    56,    57,     0,     0,     0,
      14,    15,     0,     0,     0,     0,     0,     0,     0,     0,
      14,    15,     0,    17,     0,   258,     0,     0,     0,     0,
      14,    15,     0,    17,     0,   273,     0,     0,     0,     0,
       0,     0,     0,    17,     0,   279,     2,     3,     4,     5,
       0,     0,    54,    55,    56,    57,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    14,
      15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    17
};

static const yytype_int16 yycheck[] =
{
       0,   151,    32,   154,     0,   155,    16,    17,   177,   256,
      65,   305,    22,   301,    69,    18,    30,    65,    65,    15,
      75,    17,    22,    28,    72,   293,    22,    75,    75,     3,
      21,     5,     6,    22,    34,    35,    50,    37,    34,    35,
       3,    37,     5,     6,     8,   339,    37,     3,    37,     5,
       6,    38,   340,    29,    37,    15,    16,     3,    58,     5,
       6,   329,    58,    50,   233,    37,    42,     3,     4,     5,
       6,     3,    29,     5,     6,   130,    50,   246,   247,    89,
       5,    77,   130,   130,   235,    42,    49,   256,    98,    29,
     241,   338,    95,    49,    33,    34,    35,    97,     0,    55,
      36,    37,    42,    49,    38,    51,    34,    35,    27,    58,
      49,    50,    31,    49,    37,    51,    50,    77,   114,     3,
     270,     5,     6,   153,   293,    33,    34,    35,    38,    89,
      38,    37,   301,    22,    23,    24,   305,    97,    98,   135,
      50,    49,   152,    54,   295,   141,    41,    13,   144,   145,
      16,   111,   162,    19,   114,   151,    20,    21,   154,   155,
     329,    37,    45,   313,    47,    49,    46,    51,    48,   338,
     339,   340,    34,    35,   174,   135,   176,   177,    33,    34,
      35,   141,   212,     4,   144,   145,    14,    17,    66,    14,
      68,   151,   152,    71,    49,   155,    43,    44,    45,    46,
      47,    48,   162,   203,    17,    43,   202,     3,     4,     5,
       6,    20,   208,    27,   174,    50,   176,    41,   214,   219,
       9,    10,    11,    12,   224,    37,    30,   227,   177,    37,
      27,   227,    32,   233,     3,     4,     5,     6,     8,   235,
      36,    37,   202,   203,    43,   241,   246,   247,   208,     3,
       4,     5,     6,    49,   214,    43,   256,    43,   258,   219,
      43,    41,   258,    39,   224,    43,     5,    36,    37,    38,
      27,    43,    43,   273,   270,   271,     4,   273,   227,   279,
      49,     4,    36,   279,   233,     3,     4,     5,     6,     9,
      10,    11,    12,   293,    41,    49,     4,   246,   247,   295,
      50,   301,    38,    41,    41,   305,    50,   256,    38,   258,
     270,   271,    27,    31,    18,    50,    50,   313,    36,    37,
      42,    27,    18,    41,   273,    50,    33,    34,    35,   329,
     279,    49,    42,    40,    50,    53,    50,    55,   338,   339,
     340,    40,    49,    50,   293,    52,     9,    10,    11,    12,
      50,    42,   301,   313,    42,    50,   305,     9,    10,    11,
      12,    43,     0,     1,    43,     3,     4,     5,     6,     7,
      20,    41,    50,    50,    50,    13,    50,    41,    16,    21,
     329,    19,    43,    20,    22,    23,    24,    21,     4,   338,
     339,   340,     4,    31,    41,    43,    50,    43,    36,    37,
      43,    42,    42,    41,     4,    50,     3,     4,     5,     6,
       7,    49,    41,    41,    41,    53,    13,    55,    38,    16,
       4,    38,    19,    42,    27,    27,    27,    38,    29,    42,
      31,    32,    42,    42,    31,     3,     4,     5,     6,    36,
      37,    42,    27,    38,    41,    13,    38,    38,    16,    50,
      27,    19,    49,    54,    27,    27,    53,    29,    55,    31,
      32,    27,    98,    31,   212,    37,   152,   133,    36,    37,
      42,    97,   111,    41,   236,    36,    75,    75,    50,   237,
      38,    49,    54,    -1,    -1,    53,    -1,    55,     3,     4,
       5,     6,    -1,    -1,     9,    10,    11,    12,     3,     4,
       5,     6,    -1,    -1,     9,    10,    11,    12,     3,     4,
       5,     6,    27,    -1,     9,    10,    11,    12,    -1,    -1,
      -1,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    37,    -1,    49,    -1,    51,    33,    34,    35,
      -1,    36,    37,    -1,    49,    -1,    51,    43,    44,    45,
      46,    47,    48,    49,    49,    -1,    51,     3,     4,     5,
       6,    -1,    -1,     9,    10,    11,    12,     3,     4,     5,
       6,    -1,    -1,     9,    10,    11,    12,     3,     4,     5,
       6,    -1,    -1,     9,    10,    11,    12,    -1,    -1,    -1,
      36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    37,    -1,    49,    -1,    51,    -1,    -1,    -1,    -1,
      36,    37,    -1,    49,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    51,     3,     4,     5,     6,
      -1,    -1,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    49
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,    13,    16,    19,
      22,    23,    24,    31,    36,    37,    41,    49,    53,    55,
      58,    59,    60,    61,    62,    66,    68,    69,    78,    79,
      80,    87,    88,    93,    94,   114,   115,   116,   117,   118,
     119,   122,   123,   136,   137,   138,    28,     8,    37,    37,
      37,    37,    21,    37,     9,    10,    11,    12,    51,    63,
      67,    76,    77,    79,    83,    88,    96,    98,    99,   100,
     101,   102,   103,   106,   107,   110,   113,    49,    88,    93,
      71,    72,    73,    80,    93,    80,    88,    63,     5,    92,
       0,    61,    80,    95,    27,    31,    54,    57,    41,    33,
      34,    35,    43,    44,    45,    46,    47,    48,    49,    84,
      85,    86,   108,   109,    37,     7,    59,    59,   114,    61,
     116,    37,     4,    14,    17,    14,    17,    43,    20,    79,
      88,   107,    27,    50,    84,    85,   108,   109,   110,   110,
     104,   108,   110,   105,   109,    84,    97,   104,   105,    41,
      38,    37,    29,    42,    30,    37,    27,    50,    80,    32,
      27,    63,    49,    78,    79,    71,    87,    38,    81,    88,
       8,    20,    21,    43,    43,    43,    43,    41,    43,    84,
     108,   109,    77,    88,    88,    88,    88,     3,     4,     5,
       6,    36,    49,    82,    89,    90,    91,   111,   112,    81,
      72,    70,    85,    51,    74,    76,    88,    81,    39,    64,
       5,    27,    42,    38,    50,    43,    43,     4,   120,    51,
      79,   125,     4,   121,    51,    79,   127,    51,    79,    83,
     107,   131,   135,    41,     4,    30,    50,    29,    42,    38,
      88,    50,    38,    88,    70,    88,    41,    41,    38,    79,
      50,    38,    79,    50,    79,   107,    50,    42,    51,    79,
      83,   107,   129,   133,    75,    76,    89,   112,    76,    40,
      50,    52,    65,    51,    79,    83,   107,   128,   132,    51,
      79,    83,   107,   130,   134,    27,    18,    27,    18,   135,
      50,    79,   107,    50,    42,    50,    81,    88,    40,    79,
     107,    50,    42,    79,   107,    50,    42,    43,    43,    20,
     133,    50,    76,    50,   132,    50,   134,    50,    41,    41,
      43,    21,    81,    21,    20,     4,   124,     4,   126,    41,
      43,    43,    43,    50,    42,    50,    42,   133,    41,    41,
      41,     4,    38,     4,    38,    42,   135,   134,   132,    27,
      27,    38,    42,    42,    42,    27,    38,    38,    38,    27,
      27,    27
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    58,    58,    58,    58,    58,    59,    59,
      60,    60,    60,    61,    61,    61,    61,    61,    62,    62,
      63,    64,    64,    65,    65,    65,    66,    66,    66,    66,
      67,    67,    68,    68,    68,    68,    69,    70,    71,    71,
      72,    72,    73,    74,    74,    75,    75,    76,    76,    76,
      77,    77,    77,    78,    79,    79,    80,    80,    80,    81,
      81,    82,    82,    83,    84,    84,    85,    85,    85,    86,
      86,    86,    86,    87,    87,    87,    87,    87,    87,    87,
      88,    88,    89,    89,    90,    90,    90,    90,    91,    91,
      92,    92,    93,    93,    93,    94,    94,    95,    96,    97,
      98,    98,    99,   100,   101,   101,   102,   103,   104,   105,
     106,   106,   107,   107,   107,   107,   107,   108,   108,   109,
     109,   110,   111,   111,   112,   113,   113,   113,   113,   114,
     114,   115,   115,   115,   116,   116,   117,   117,   117,   118,
     119,   120,   121,   122,   123,   124,   124,   125,   125,   126,
     126,   127,   127,   128,   128,   128,   128,   128,   129,   129,
     129,   129,   129,   130,   130,   130,   130,   130,   131,   131,
     131,   131,   131,   132,   132,   133,   133,   134,   134,   135,
     135,   136,   137,   137,   138,   138
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     2,     1,     1,     2,
       2,     1,     2,     2,     3,     4,     3,     4,     1,     1,
       1,     3,     4,     2,     4,     2,     1,     3,     1,     3,
       1,     3,     5,     4,     3,     4,     2,     2,     3,     1,
       1,     3,     1,     1,     3,     1,     3,     1,     2,     1,
       1,     1,     2,     3,     1,     2,     1,     4,     3,     1,
       3,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     3,     3,     2,
       1,     3,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     3,     1,     1,     1,     2,     3,     2,     2,     2,
       2,     2,     2,     2,     1,     1,     2,     2,     2,     2,
       2,     2,     1,     1,     1,     2,     2,     1,     1,     1,
       1,     4,     3,     1,     3,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     2,     1,     1,     1,     7,
       7,     1,     1,    13,    13,     1,     3,     1,     2,     1,
       3,     1,     2,     1,     2,     1,     1,     2,     1,     2,
       1,     1,     2,     1,     2,     1,     1,     2,     1,     2,
       1,     1,     2,     1,     3,     1,     3,     1,     3,     1,
       3,     1,    15,    15,    15,    14
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
#line 1690 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 9:
#line 83 "src/input/aspcore2.y" /* yacc.c:1646  */
    { director.getBuilder()->onQuery(); }
#line 1696 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 13:
#line 94 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onRule(); 
        }
#line 1704 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 14:
#line 98 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onRule(); 
        }
#line 1712 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 15:
#line 102 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onRule(); 
        }
#line 1720 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 16:
#line 106 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onConstraint(); 
        }
#line 1728 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 17:
#line 110 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onWeakConstraint(); 
        }
#line 1736 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 18:
#line 117 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onHead();
        }
#line 1744 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 19:
#line 121 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceAtom();
            director.getBuilder()->onHead();
        }
#line 1753 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 20:
#line 129 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onBody();
        }
#line 1761 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 21:
#line 136 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            // There is only the weight. No level and terms.
            director.getBuilder()->onWeightAtLevels(1,0,0); 
        }
#line 1770 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 22:
#line 141 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            // There are also a level and/or some terms.
            // The finalization has been postponed to "level_and_terms".
        }
#line 1779 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 23:
#line 149 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            // There is no terms following the level.
            director.getBuilder()->onWeightAtLevels(1,1,0); 
        }
#line 1788 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 24:
#line 154 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onWeightAtLevels(1,1,(yyvsp[0].integer)); 
        }
#line 1796 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 25:
#line 158 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            // The level is omitted.
            // Thus, the first term, recognized as the
            // weight, should be a term of this list.
            director.getBuilder()->onWeightAtLevels(0,0,(yyvsp[0].integer)+1); 
        }
#line 1807 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 26:
#line 168 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onHeadAtom(); 
        }
#line 1815 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 27:
#line 172 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onHeadAtom(); 
        }
#line 1823 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 28:
#line 176 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onHeadAtom(); 
        }
#line 1831 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 29:
#line 180 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onHeadAtom(); 
        }
#line 1839 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 30:
#line 187 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onBodyLiteral(); 
        }
#line 1847 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 31:
#line 191 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onBodyLiteral(); 
        }
#line 1855 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 36:
#line 205 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onChoiceLowerGuard();
        }
#line 1863 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 37:
#line 212 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onChoiceUpperGuard();
        }
#line 1871 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 40:
#line 224 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceElement(); 
        }
#line 1879 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 41:
#line 228 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceElement(); 
        }
#line 1887 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 42:
#line 235 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceElementAtom(); 
        }
#line 1895 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 43:
#line 242 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onChoiceElementLiteral(); 
        }
#line 1903 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 44:
#line 246 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onChoiceElementLiteral();
        }
#line 1911 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 45:
#line 253 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateNafLiteral();
        }
#line 1919 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 46:
#line 257 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateNafLiteral();
        }
#line 1927 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 47:
#line 264 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onNafLiteral();
        }
#line 1935 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 48:
#line 268 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onNafLiteral(true);
        }
#line 1943 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 49:
#line 272 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onNafLiteral();
        }
#line 1951 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 51:
#line 280 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregate();
        }
#line 1959 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 52:
#line 284 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregate(true);
        }
#line 1967 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 53:
#line 291 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onExistentialAtom(); 
        }
#line 1975 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 54:
#line 296 "src/input/aspcore2.y" /* yacc.c:1646  */
    { director.getBuilder()->onAtom(); }
#line 1981 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 55:
#line 297 "src/input/aspcore2.y" /* yacc.c:1646  */
    { director.getBuilder()->onAtom(true); }
#line 1987 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 56:
#line 302 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onPredicateName((yyvsp[0].string)); 
            delete[] (yyvsp[0].string);
        }
#line 1996 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 57:
#line 307 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onPredicateName((yyvsp[-3].string)); 
            delete[] (yyvsp[-3].string);
        }
#line 2005 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 58:
#line 312 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onPredicateName((yyvsp[-2].string)); 
            delete[] (yyvsp[-2].string);
        }
#line 2014 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 59:
#line 319 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.integer) = 1; }
#line 2020 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 60:
#line 320 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[-2].integer) + 1; }
#line 2026 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 63:
#line 330 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onBuiltinAtom();
        }
#line 2034 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 64:
#line 337 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onEqualOperator();
        }
#line 2042 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 65:
#line 341 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onUnequalOperator(); 
        }
#line 2050 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 69:
#line 353 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.single_char) = '+'; }
#line 2056 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 70:
#line 354 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.single_char) = '-'; }
#line 2062 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 71:
#line 355 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.single_char) = '*'; }
#line 2068 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 72:
#line 356 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.single_char) = '/'; }
#line 2074 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 73:
#line 361 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onTerm((yyvsp[0].string)); 
            delete[] (yyvsp[0].string);
        }
#line 2083 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 74:
#line 366 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onTerm((yyvsp[0].string)); 
            delete[] (yyvsp[0].string);
        }
#line 2092 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 75:
#line 371 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onUnknownVariable(); 
        }
#line 2100 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 76:
#line 375 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onFunction((yyvsp[-3].string), (yyvsp[-1].integer)); 
            delete[] (yyvsp[-3].string);
        }
#line 2109 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 77:
#line 380 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getParserConstraint()->rangeFacts();
            director.getBuilder()->onTermRange((yyvsp[-2].string), (yyvsp[0].string));
            delete[] (yyvsp[-2].string);
            delete[] (yyvsp[0].string);
        }
#line 2120 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 78:
#line 387 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onTermParams(); 
        }
#line 2128 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 79:
#line 391 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onTermDash(); 
        }
#line 2136 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 80:
#line 397 "src/input/aspcore2.y" /* yacc.c:1646  */
    {}
#line 2142 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 81:
#line 399 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onArithmeticOperation((yyvsp[-1].single_char)); 
        }
#line 2150 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 82:
#line 404 "src/input/aspcore2.y" /* yacc.c:1646  */
    {}
#line 2156 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 83:
#line 405 "src/input/aspcore2.y" /* yacc.c:1646  */
    {}
#line 2162 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 84:
#line 410 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2171 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 85:
#line 415 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2180 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 86:
#line 420 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2189 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 87:
#line 425 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateGroundTerm((yyvsp[0].string),true);
            delete[] (yyvsp[0].string);
        }
#line 2198 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 88:
#line 433 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAggregateVariableTerm((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2207 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 89:
#line 438 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateUnknownVariable();
        }
#line 2215 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 90:
#line 445 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onExistentialVariable((yyvsp[0].string)); 
            delete[] (yyvsp[0].string);
        }
#line 2224 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 91:
#line 450 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onExistentialVariable((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2233 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 92:
#line 457 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2239 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 93:
#line 458 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2245 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 94:
#line 459 "src/input/aspcore2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2251 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 95:
#line 464 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getParserConstraint()->directives();
            director.getBuilder()->onDirective((yyvsp[-1].string),(yyvsp[0].string));
            delete[] (yyvsp[-1].string);
            delete[] (yyvsp[0].string);
        }
#line 2262 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 96:
#line 471 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getParserConstraint()->directives();
            director.getBuilder()->onDirective((yyvsp[-1].string),(yyvsp[0].string));
            delete[] (yyvsp[-1].string);
            delete[] (yyvsp[0].string);
        }
#line 2273 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 97:
#line 481 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAtom(); 
        }
#line 2281 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 98:
#line 488 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateLowerGuard();
        }
#line 2289 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 99:
#line 495 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateUpperGuard();
        }
#line 2297 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 102:
#line 507 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateLowerGuard();
        }
#line 2305 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 106:
#line 523 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateLowerGuard();
        }
#line 2313 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 108:
#line 534 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateUpperGuard();
        }
#line 2321 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 109:
#line 541 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateUpperGuard();
        }
#line 2329 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 117:
#line 561 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onLessOperator(); 
        }
#line 2337 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 118:
#line 565 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onLessOrEqualOperator(); 
        }
#line 2345 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 119:
#line 572 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onGreaterOperator();
        }
#line 2353 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 120:
#line 576 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onGreaterOrEqualOperator();
        }
#line 2361 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 124:
#line 593 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateElement();
        }
#line 2369 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 125:
#line 600 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateFunction((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2378 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 126:
#line 605 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateFunction((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2387 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 127:
#line 610 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateFunction((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2396 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 128:
#line 615 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAggregateFunction((yyvsp[0].string));
            delete[] (yyvsp[0].string);
        }
#line 2405 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 141:
#line 652 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationRuleOrdering((yyvsp[0].string));
        delete[] (yyvsp[0].string);
	}
#line 2414 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 142:
#line 659 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationGlobalOrdering((yyvsp[0].string));
        delete[] (yyvsp[0].string);
	}
#line 2423 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 145:
#line 676 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationRuleAtomIndexedArgument((yyvsp[0].string));
        delete[] (yyvsp[0].string);
	}
#line 2432 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 146:
#line 680 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationRuleAtomIndexedArgument((yyvsp[-2].string));
		director.getBuilder()->onAnnotationRuleAtomIndexedArgument((yyvsp[0].string));
        delete[] (yyvsp[-2].string);
        delete[] (yyvsp[0].string);
	}
#line 2443 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 147:
#line 690 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRuleAtomIndexedLiteral();
        }
#line 2451 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 148:
#line 694 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRuleAtomIndexedLiteral(true);
        }
#line 2459 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 149:
#line 700 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationGlobalAtomIndexedArgument((yyvsp[0].string));
        delete[] (yyvsp[0].string);
	}
#line 2468 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 150:
#line 704 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationGlobalAtomIndexedArgument((yyvsp[-2].string));
		director.getBuilder()->onAnnotationGlobalAtomIndexedArgument((yyvsp[0].string));
        delete[] (yyvsp[-2].string);
        delete[] (yyvsp[0].string);
	}
#line 2479 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 151:
#line 714 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalAtomIndexedLiteral();
        }
#line 2487 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 152:
#line 718 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalAtomIndexedLiteral(true);
        }
#line 2495 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 153:
#line 725 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRulePartialOrderingBefore();
        }
#line 2503 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 154:
#line 729 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRulePartialOrderingBefore(true);
        }
#line 2511 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 155:
#line 733 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationRulePartialOrderingBefore();
        }
#line 2519 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 156:
#line 737 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
           director.getBuilder()->onAnnotationAggregateRulePartialOrderingBefore();
        }
#line 2527 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 157:
#line 741 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationAggregateRulePartialOrderingBefore(true);
        }
#line 2535 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 158:
#line 748 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalPartialOrderingBefore();
        }
#line 2543 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 159:
#line 752 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalPartialOrderingBefore(true);
        }
#line 2551 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 160:
#line 756 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationGlobalPartialOrderingBefore();
        }
#line 2559 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 161:
#line 760 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
           director.getBuilder()->onAnnotationAggregateGlobalPartialOrderingBefore();
        }
#line 2567 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 162:
#line 764 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationAggregateGlobalPartialOrderingBefore(true);
        }
#line 2575 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 163:
#line 771 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRulePartialOrderingAfter();
        }
#line 2583 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 164:
#line 775 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationRulePartialOrderingAfter(true);
        }
#line 2591 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 165:
#line 779 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationRulePartialOrderingAfter();
        }
#line 2599 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 166:
#line 783 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
           director.getBuilder()->onAnnotationAggregateRulePartialOrderingAfter();
        }
#line 2607 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 167:
#line 787 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationAggregateRulePartialOrderingAfter(true);
        }
#line 2615 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 168:
#line 794 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalPartialOrderingAfter();
        }
#line 2623 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 169:
#line 798 "src/input/aspcore2.y" /* yacc.c:1646  */
    { 
            director.getBuilder()->onAnnotationGlobalPartialOrderingAfter(true);
        }
#line 2631 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 170:
#line 802 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationGlobalPartialOrderingAfter();
        }
#line 2639 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 171:
#line 806 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
           director.getBuilder()->onAnnotationAggregateGlobalPartialOrderingAfter();
        }
#line 2647 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 172:
#line 810 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
            director.getBuilder()->onAnnotationAggregateGlobalPartialOrderingAfter(true);
        }
#line 2655 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;

  case 181:
#line 837 "src/input/aspcore2.y" /* yacc.c:1646  */
    {
		director.getBuilder()->onAnnotationRulePartialOrdering();
	}
#line 2663 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
    break;


#line 2667 "src/input/aspcore2_parser.hpp" /* yacc.c:1646  */
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
