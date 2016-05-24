/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 4 "tokens.y"

#include <iostream>
#include <fstream>
#include "PrettyPrinter.h"
#include "SymbTableBuilder.h"
#include "TypeChecker.h"
#include "IRTranslator.h"
#include "IRCanonizator.h"
#include "IRTreePrettyPrinter.h"
#include "IRBlockDecompositor.h"
#include "AsmTreeMaker.h"
#include "RegisterDistribution.h"

extern "C" int yylex();
extern int yylineno;

int CLabel::nextUniqueId = 0;
int CTemp::nextUniqueId = 0;
int CFrame::wordSize = 4;
void yyerror( int*, const char* str );

/* Line 371 of yacc.c  */
#line 90 "tokens.tab.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "tokens.tab.hpp".  */
#ifndef YY_YY_TOKENS_TAB_HPP_INCLUDED
# define YY_YY_TOKENS_TAB_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
/* Line 387 of yacc.c  */
#line 29 "tokens.y"

	#include "classes.h"


/* Line 387 of yacc.c  */
#line 127 "tokens.tab.cpp"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     UMINUS = 258,
     CLASS = 259,
     PUBLIC = 260,
     STATIC = 261,
     VOID = 262,
     MAIN = 263,
     STRING = 264,
     EXTENDS = 265,
     RETURN = 266,
     INT = 267,
     BOOLEAN = 268,
     IF = 269,
     ELSE = 270,
     WHILE = 271,
     PRINT = 272,
     LENGTH = 273,
     TRUE = 274,
     FALSE = 275,
     THIS = 276,
     NEW = 277,
     INTEGER_LITERAL = 278,
     ID = 279
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 36 "tokens.y"

	int ival;
	char sval[255];
	IProgram* program;
	IMainClass* mainClass;
	IClassDecl* classDecl;
	IClassDeclList* classDecls;
	IExpList* expList;
	IFormalList* formalList;
	IStatement* statement;
	IMethodDecl* methodDecl;
	IMethodDeclList* methodDecls;
	IStatementList* statements;
	IExp* exp;
	IVarDecl* varDecl;
	IVarDeclList* varDecls;
	IType* type;
	CFormalListElement* formalListElement;


/* Line 387 of yacc.c  */
#line 187 "tokens.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (int* hasError);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_TOKENS_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 215 "tokens.tab.cpp"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   377

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNRULES -- Number of states.  */
#define YYNSTATES  171

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    12,     2,     2,     2,     2,    13,     2,
       9,    10,     5,     3,    40,     4,    11,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    39,
      14,    41,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     7,     2,     8,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,    15,    38,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     6,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    13,    31,    38,    44,
      50,    55,    64,    72,    80,    87,    89,    92,    94,    97,
     101,   115,   128,   141,   153,   155,   158,   159,   163,   166,
     168,   171,   175,   179,   181,   183,   185,   189,   192,   200,
     206,   212,   217,   225,   228,   232,   236,   240,   244,   248,
     252,   257,   261,   268,   270,   272,   274,   276,   278,   284,
     289,   292,   296,   297,   299,   302,   304,   307
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,    45,    -1,    45,    44,    -1,    46,    -1,
      44,    46,    -1,    16,    36,    37,    17,    18,    19,    20,
       9,    21,     7,     8,    36,    10,    37,    51,    38,    38,
      -1,    16,    36,    37,    47,    48,    38,    -1,    16,    36,
      37,    48,    38,    -1,    16,    36,    37,    47,    38,    -1,
      16,    36,    37,    38,    -1,    16,    36,    22,    36,    37,
      47,    48,    38,    -1,    16,    36,    22,    36,    37,    48,
      38,    -1,    16,    36,    22,    36,    37,    47,    38,    -1,
      16,    36,    22,    36,    37,    38,    -1,    49,    -1,    47,
      49,    -1,    50,    -1,    48,    50,    -1,    55,    36,    39,
      -1,    17,    55,    36,     9,    52,    10,    37,    47,    51,
      23,    57,    39,    38,    -1,    17,    55,    36,     9,    52,
      10,    37,    51,    23,    57,    39,    38,    -1,    17,    55,
      36,     9,    52,    10,    37,    47,    23,    57,    39,    38,
      -1,    17,    55,    36,     9,    52,    10,    37,    23,    57,
      39,    38,    -1,    56,    -1,    51,    56,    -1,    -1,    55,
      36,    53,    -1,    55,    36,    -1,    54,    -1,    53,    54,
      -1,    40,    55,    36,    -1,    24,     7,     8,    -1,    25,
      -1,    24,    -1,    36,    -1,    37,    51,    38,    -1,    37,
      38,    -1,    26,     9,    57,    10,    56,    27,    56,    -1,
      28,     9,    57,    10,    56,    -1,    29,     9,    57,    10,
      39,    -1,    36,    41,    57,    39,    -1,    36,     7,    57,
       8,    41,    57,    39,    -1,     4,    57,    -1,    57,     3,
      57,    -1,    57,    14,    57,    -1,    57,    13,    57,    -1,
      57,    15,    57,    -1,    57,     4,    57,    -1,    57,     5,
      57,    -1,    57,     7,    57,     8,    -1,    57,    11,    30,
      -1,    57,    11,    36,     9,    58,    10,    -1,    35,    -1,
      31,    -1,    32,    -1,    36,    -1,    33,    -1,    34,    24,
       7,    57,     8,    -1,    34,    36,     9,    10,    -1,    12,
      57,    -1,     9,    57,    10,    -1,    -1,    57,    -1,    57,
      59,    -1,    60,    -1,    59,    60,    -1,    40,    57,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   113,   113,   114,   115,   116,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   136,   137,   142,
     143,   154,   165,   176,   187,   188,   193,   194,   200,   201,
     202,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   245,   246,   251
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'+'", "'-'", "'*'", "UMINUS", "'['",
  "']'", "'('", "')'", "'.'", "'!'", "'&'", "'<'", "'|'", "CLASS",
  "PUBLIC", "STATIC", "VOID", "MAIN", "STRING", "EXTENDS", "RETURN", "INT",
  "BOOLEAN", "IF", "ELSE", "WHILE", "PRINT", "LENGTH", "TRUE", "FALSE",
  "THIS", "NEW", "INTEGER_LITERAL", "ID", "'{'", "'}'", "';'", "','",
  "'='", "$accept", "Program", "ClassDecls", "MainClass", "ClassDecl",
  "VarDecls", "MethodDecls", "VarDecl", "MethodDecl", "Statements",
  "FormalList", "FormalRests", "FormalRest", "Type", "Statement", "Exp",
  "ExpList", "ExpRests", "ExpRest", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    43,    45,    42,   258,    91,    93,    40,
      41,    46,    33,    38,    60,   124,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   123,   125,    59,
      44,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    43,    44,    44,    45,    46,    46,    46,
      46,    46,    46,    46,    46,    47,    47,    48,    48,    49,
      50,    50,    50,    50,    51,    51,    52,    52,    52,    53,
      53,    54,    55,    55,    55,    55,    56,    56,    56,    56,
      56,    56,    56,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    58,    58,    58,    59,    59,    60
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,    17,     6,     5,     5,
       4,     8,     7,     7,     6,     1,     2,     1,     2,     3,
      13,    12,    12,    11,     1,     2,     0,     3,     2,     1,
       2,     3,     3,     1,     1,     1,     3,     2,     7,     5,
       5,     4,     7,     2,     3,     3,     3,     3,     3,     3,
       4,     3,     6,     1,     1,     1,     1,     1,     5,     4,
       2,     3,     0,     1,     2,     1,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,     1,     0,     3,     4,     0,
       0,     5,     0,     0,     0,     0,     0,     0,    34,    33,
      35,    10,     0,     0,    15,    17,     0,     0,     0,     0,
       0,     9,     0,    16,     8,    18,     0,     0,    14,     0,
       0,     0,    32,     7,    19,     0,    13,     0,    12,    26,
       0,    11,     0,     0,     0,     0,    28,     0,     0,     0,
      27,    29,     0,     0,     0,     0,     0,    35,     0,     0,
       0,    24,     0,    30,     0,     0,     0,     0,    54,    55,
      57,     0,    53,    56,     0,     0,     0,     0,     0,     0,
       0,    37,     0,     0,     0,     0,    25,    31,     0,    43,
       0,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,    61,     0,     0,    44,    48,    49,     0,
      51,     0,    46,    45,    47,    23,     0,     0,     0,     0,
      41,     0,     0,     0,     0,     0,    59,    50,    62,     0,
      39,    40,     0,    22,     0,    21,     6,    58,    63,     0,
       0,     0,    20,     0,    64,    65,    52,    38,    42,    67,
      66
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,     3,     8,    22,    23,    24,    25,    70,
      52,    60,    61,    26,    71,    84,   159,   164,   165
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -75
static const yytype_int16 yypact[] =
{
      -7,   -11,    44,    38,     8,   -75,    19,    38,   -75,    39,
      20,   -75,    55,    45,   100,    63,    47,    85,    81,   -75,
     -75,   -75,   135,   -12,   -75,   -75,    58,    76,   144,    62,
      92,   -75,    -9,   -75,   -75,   -75,    68,   104,   -75,   159,
       3,   114,   -75,   -75,   -75,   113,   -75,    10,   -75,    85,
     130,   -75,   134,   112,   143,   125,   110,   129,   175,    85,
     110,   -75,   160,   154,   155,   163,   165,    -3,   305,   190,
     194,   -75,   139,   -75,   140,   154,   154,   154,   -75,   -75,
     -75,    -8,   -75,   -75,    72,   154,   154,   154,   154,   154,
      -3,   -75,   318,   154,   206,   154,   -75,   -75,   335,   195,
     234,   -75,   171,   170,   154,   154,   154,   154,    29,   154,
     154,   154,   153,   247,   260,   273,   286,    88,   -75,   101,
     154,   115,   322,   -75,   154,   182,   362,   362,   195,   299,
     -75,   184,   -75,   -75,   -75,   -75,   335,   335,   157,   164,
     -75,   156,   128,   169,   183,   312,   -75,   -75,   154,   197,
     -75,   -75,   154,   -75,   187,   -75,   -75,   -75,    57,   218,
     335,   142,   -75,   154,   193,   -75,   -75,   -75,   -75,   325,
     -75
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -75,   -75,   -75,   -75,   229,   -18,    41,   -16,    11,   -51,
     -75,   -75,   180,   -10,   -70,   -74,   -75,   -75,    82
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      96,    99,   100,   101,    88,    17,    33,    29,    17,     1,
      39,   113,   114,   115,   116,   117,   102,    92,    94,   119,
      17,   121,    96,    33,    96,     4,    34,    17,   103,    43,
     126,   127,   128,   129,    35,   132,   133,   134,    89,    53,
      69,    48,    13,    35,     5,     9,   142,   122,    51,    72,
     145,    35,    96,    33,     6,    10,    12,    14,    35,   130,
     104,   105,   106,    32,   107,   131,   149,   150,   108,    40,
     109,   110,   111,    15,   158,   104,   105,   106,   161,   107,
      47,    16,    27,   108,    28,   109,   110,   111,    30,   169,
     167,   104,   105,   106,    36,   107,    37,   163,    41,   108,
      42,   109,   110,   111,   104,   105,   106,    44,   107,    18,
      19,   112,   108,    45,   109,   110,   111,    17,   104,   105,
     106,    20,   107,    49,    18,    19,   108,   140,   109,   110,
     111,   104,   105,   106,    50,   107,    20,    54,    21,   108,
     141,   109,   110,   111,    55,   104,   105,   106,    56,   107,
      59,    57,    17,   108,   143,   109,   110,   111,    75,    18,
      19,    17,    58,    76,    85,    62,    77,   154,    18,    19,
      74,    20,    86,    31,    87,    97,    17,    98,   124,   125,
      20,   168,    38,    18,    19,    78,    79,    80,    81,    82,
      83,   135,   146,   148,   153,    20,   151,    46,    63,    18,
      19,    64,   107,    65,    66,   152,   108,   155,   109,   110,
     111,    67,    68,    93,    18,    19,    64,    95,    65,    66,
      64,   156,    65,    66,   160,   162,    67,    68,   166,   120,
      90,    68,    64,   163,    65,    66,    11,   104,   105,   106,
      73,   107,    90,    68,   123,   108,   170,   109,   110,   111,
     104,   105,   106,     0,   107,     0,     0,   136,   108,     0,
     109,   110,   111,   104,   105,   106,     0,   107,     0,     0,
     137,   108,     0,   109,   110,   111,   104,   105,   106,     0,
     107,     0,     0,   138,   108,     0,   109,   110,   111,   104,
     105,   106,     0,   107,   139,     0,     0,   108,     0,   109,
     110,   111,   104,   105,   106,     0,   107,   147,     0,     0,
     108,     0,   109,   110,   111,   104,   105,   106,     0,   107,
     157,     0,     0,   108,     0,   109,   110,   111,   104,   105,
     106,    64,   107,    65,    66,     0,   108,     0,   109,   110,
     111,    90,    68,    91,    64,     0,    65,    66,    64,     0,
      65,    66,     0,     0,    90,    68,   118,     0,    90,    68,
     144,    64,     0,    65,    66,     0,     0,   106,     0,   107,
       0,    90,    68,   108,     0,   109,   110,   111
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-75)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      70,    75,    76,    77,     7,    17,    22,    17,    17,    16,
      28,    85,    86,    87,    88,    89,    24,    68,    69,    93,
      17,    95,    92,    39,    94,    36,    38,    17,    36,    38,
     104,   105,   106,   107,    23,   109,   110,   111,    41,    49,
      58,    38,    22,    32,     0,    37,   120,    98,    38,    59,
     124,    40,   122,    69,    16,    36,    17,    37,    47,    30,
       3,     4,     5,    22,     7,    36,   136,   137,    11,    28,
      13,    14,    15,    18,   148,     3,     4,     5,   152,     7,
      39,    36,    19,    11,    37,    13,    14,    15,     7,   163,
     160,     3,     4,     5,    36,     7,    20,    40,    36,    11,
       8,    13,    14,    15,     3,     4,     5,    39,     7,    24,
      25,    39,    11,     9,    13,    14,    15,    17,     3,     4,
       5,    36,     7,     9,    24,    25,    11,    39,    13,    14,
      15,     3,     4,     5,    21,     7,    36,     7,    38,    11,
      39,    13,    14,    15,    10,     3,     4,     5,    36,     7,
      40,     8,    17,    11,    39,    13,    14,    15,     4,    24,
      25,    17,    37,     9,     9,    36,    12,    39,    24,    25,
      10,    36,     9,    38,     9,    36,    17,    37,     7,     9,
      36,    39,    38,    24,    25,    31,    32,    33,    34,    35,
      36,    38,    10,     9,    38,    36,    39,    38,    23,    24,
      25,    26,     7,    28,    29,    41,    11,    38,    13,    14,
      15,    36,    37,    23,    24,    25,    26,    23,    28,    29,
      26,    38,    28,    29,    27,    38,    36,    37,    10,    23,
      36,    37,    26,    40,    28,    29,     7,     3,     4,     5,
      60,     7,    36,    37,    10,    11,   164,    13,    14,    15,
       3,     4,     5,    -1,     7,    -1,    -1,    10,    11,    -1,
      13,    14,    15,     3,     4,     5,    -1,     7,    -1,    -1,
      10,    11,    -1,    13,    14,    15,     3,     4,     5,    -1,
       7,    -1,    -1,    10,    11,    -1,    13,    14,    15,     3,
       4,     5,    -1,     7,     8,    -1,    -1,    11,    -1,    13,
      14,    15,     3,     4,     5,    -1,     7,     8,    -1,    -1,
      11,    -1,    13,    14,    15,     3,     4,     5,    -1,     7,
       8,    -1,    -1,    11,    -1,    13,    14,    15,     3,     4,
       5,    26,     7,    28,    29,    -1,    11,    -1,    13,    14,
      15,    36,    37,    38,    26,    -1,    28,    29,    26,    -1,
      28,    29,    -1,    -1,    36,    37,    38,    -1,    36,    37,
      38,    26,    -1,    28,    29,    -1,    -1,     5,    -1,     7,
      -1,    36,    37,    11,    -1,    13,    14,    15
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    16,    43,    45,    36,     0,    16,    44,    46,    37,
      36,    46,    17,    22,    37,    18,    36,    17,    24,    25,
      36,    38,    47,    48,    49,    50,    55,    19,    37,    55,
       7,    38,    48,    49,    38,    50,    36,    20,    38,    47,
      48,    36,     8,    38,    39,     9,    38,    48,    38,     9,
      21,    38,    52,    55,     7,    10,    36,     8,    37,    40,
      53,    54,    36,    23,    26,    28,    29,    36,    37,    47,
      51,    56,    55,    54,    10,     4,     9,    12,    31,    32,
      33,    34,    35,    36,    57,     9,     9,     9,     7,    41,
      36,    38,    51,    23,    51,    23,    56,    36,    37,    57,
      57,    57,    24,    36,     3,     4,     5,     7,    11,    13,
      14,    15,    39,    57,    57,    57,    57,    57,    38,    57,
      23,    57,    51,    10,     7,     9,    57,    57,    57,    57,
      30,    36,    57,    57,    57,    38,    10,    10,    10,     8,
      39,    39,    57,    39,    38,    57,    10,     8,     9,    56,
      56,    39,    41,    38,    39,    38,    38,     8,    57,    58,
      27,    57,    38,    40,    59,    60,    10,    56,    39,    57,
      60
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
      yyerror (hasError, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


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
		  Type, Value, hasError); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, int* hasError)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, hasError)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    int* hasError;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (hasError);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, int* hasError)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, hasError)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    int* hasError;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, hasError);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, int* hasError)
#else
static void
yy_reduce_print (yyvsp, yyrule, hasError)
    YYSTYPE *yyvsp;
    int yyrule;
    int* hasError;
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
		       		       , hasError);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, hasError); \
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, int* hasError)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, hasError)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    int* hasError;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (hasError);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

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
yyparse (int* hasError)
#else
int
yyparse (hasError)
    int* hasError;
#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
        case 2:
/* Line 1792 of yacc.c  */
#line 113 "tokens.y"
    { (yyval.program) = new CProgram((yyvsp[(1) - (1)].mainClass), nullptr, yylineno); program = (yyval.program); }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 114 "tokens.y"
    { (yyval.program) = new CProgram((yyvsp[(1) - (2)].mainClass), (yyvsp[(2) - (2)].classDecls), yylineno); program = (yyval.program); }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 115 "tokens.y"
    { (yyval.classDecls) = new CClassDeclList((yyvsp[(1) - (1)].classDecl), yylineno); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 116 "tokens.y"
    { 
		std::vector< IClassDecl* > decls = dynamic_cast< CClassDeclList* >((yyvsp[(1) - (2)].classDecls))->ClassDeclList();
		decls.push_back((yyvsp[(2) - (2)].classDecl));
		(yyval.classDecls) = new CClassDeclList(decls, yylineno); 
	}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 121 "tokens.y"
    { (yyval.mainClass) = new CMainClass( std::string((yyvsp[(2) - (17)].sval)), (yyvsp[(15) - (17)].statements), yylineno ); }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 122 "tokens.y"
    { (yyval.classDecl) = new CClassDecl( std::string((yyvsp[(2) - (6)].sval)), "", (yyvsp[(4) - (6)].varDecls), (yyvsp[(5) - (6)].methodDecls), yylineno ); }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 123 "tokens.y"
    { (yyval.classDecl) = new CClassDecl(std::string((yyvsp[(2) - (5)].sval)), "", nullptr, (yyvsp[(4) - (5)].methodDecls), yylineno ); }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 124 "tokens.y"
    { (yyval.classDecl) = new CClassDecl(std::string((yyvsp[(2) - (5)].sval)), "", (yyvsp[(4) - (5)].varDecls), nullptr, yylineno ); }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 125 "tokens.y"
    { (yyval.classDecl) = new CClassDecl(std::string((yyvsp[(2) - (4)].sval)), "", nullptr, nullptr, yylineno ); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 126 "tokens.y"
    { (yyval.classDecl) = new CClassDecl(std::string((yyvsp[(2) - (8)].sval)), std::string((yyvsp[(4) - (8)].sval)), (yyvsp[(6) - (8)].varDecls), (yyvsp[(7) - (8)].methodDecls), yylineno ); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 127 "tokens.y"
    { (yyval.classDecl) = new CClassDecl(std::string((yyvsp[(2) - (7)].sval)), std::string((yyvsp[(4) - (7)].sval)), nullptr, (yyvsp[(6) - (7)].methodDecls), yylineno ); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 128 "tokens.y"
    { (yyval.classDecl) = new CClassDecl(std::string((yyvsp[(2) - (7)].sval)), std::string((yyvsp[(4) - (7)].sval)), (yyvsp[(6) - (7)].varDecls), nullptr, yylineno ); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 129 "tokens.y"
    { (yyval.classDecl) = new CClassDecl(std::string((yyvsp[(2) - (6)].sval)), std::string((yyvsp[(4) - (6)].sval)), nullptr, nullptr, yylineno ); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 130 "tokens.y"
    { (yyval.varDecls) = new CVarDeclList( (yyvsp[(1) - (1)].varDecl), yylineno ); }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 131 "tokens.y"
    { 
		std::vector< IVarDecl* > decls = dynamic_cast<CVarDeclList*>((yyvsp[(1) - (2)].varDecls))->VarDeclList();
		decls.push_back((yyvsp[(2) - (2)].varDecl));
		(yyval.varDecls) = new CVarDeclList(decls, yylineno); 
	}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 136 "tokens.y"
    { (yyval.methodDecls) = new CMethodDeclList( (yyvsp[(1) - (1)].methodDecl), yylineno ); }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 137 "tokens.y"
    { 
		std::vector< IMethodDecl* > decls = dynamic_cast<CMethodDeclList*>((yyvsp[(1) - (2)].methodDecls))->MethodDeclList();
		decls.push_back((yyvsp[(2) - (2)].methodDecl));
		(yyval.methodDecls) = new CMethodDeclList(decls, yylineno); 
	}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 142 "tokens.y"
    { (yyval.varDecl) = new CVarDecl( (yyvsp[(1) - (3)].type), std::string((yyvsp[(2) - (3)].sval)), yylineno ); }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 143 "tokens.y"
    {
		(yyval.methodDecl) = new CMethodDecl( 
			(yyvsp[(2) - (13)].type), 
			std::string((yyvsp[(3) - (13)].sval)),
			(yyvsp[(5) - (13)].formalList),
			(yyvsp[(8) - (13)].varDecls),
			(yyvsp[(9) - (13)].statements),
			(yyvsp[(11) - (13)].exp), 
			yylineno
			);
	}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 154 "tokens.y"
    {
		(yyval.methodDecl) = new CMethodDecl( 
			(yyvsp[(2) - (12)].type), 
			std::string((yyvsp[(3) - (12)].sval)),
			(yyvsp[(5) - (12)].formalList),
			nullptr,
			(yyvsp[(8) - (12)].statements),
			(yyvsp[(10) - (12)].exp), 
			yylineno
			);
	}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 165 "tokens.y"
    {
		(yyval.methodDecl) = new CMethodDecl( 
			(yyvsp[(2) - (12)].type), 
			std::string((yyvsp[(3) - (12)].sval)),
			(yyvsp[(5) - (12)].formalList),
			(yyvsp[(8) - (12)].varDecls),
			nullptr,
			(yyvsp[(10) - (12)].exp), 
			yylineno
			);
	}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 176 "tokens.y"
    {
		(yyval.methodDecl) = new CMethodDecl( 
			(yyvsp[(2) - (11)].type), 
			std::string((yyvsp[(3) - (11)].sval)),
			(yyvsp[(5) - (11)].formalList),
			nullptr,
			nullptr,
			(yyvsp[(9) - (11)].exp), 
			yylineno
			);
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 187 "tokens.y"
    { (yyval.statements) = new CStatementList((yyvsp[(1) - (1)].statement), yylineno); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 188 "tokens.y"
    { 
		std::vector< IStatement* > decls = dynamic_cast< CStatementList* >((yyvsp[(1) - (2)].statements))->StatementList();
		decls.push_back((yyvsp[(2) - (2)].statement));
		(yyval.statements) = new CStatementList(decls, yylineno); 
	}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 193 "tokens.y"
    { (yyval.formalList) = nullptr; }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 194 "tokens.y"
    { 
		CFormalListElement* var = new CFormalListElement( (yyvsp[(1) - (3)].type), std::string((yyvsp[(2) - (3)].sval)), yylineno );
		std::vector< CFormalListElement* > decls = dynamic_cast< CFormalList* >((yyvsp[(3) - (3)].formalList))->List();
		decls.insert(decls.begin(), var);
		(yyval.formalList) = new CFormalList( decls, yylineno );
	}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 200 "tokens.y"
    { (yyval.formalList) = new CFormalList( new CFormalListElement( (yyvsp[(1) - (2)].type), std::string((yyvsp[(2) - (2)].sval)), yylineno ), yylineno ); }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 201 "tokens.y"
    { (yyval.formalList) = new CFormalList((yyvsp[(1) - (1)].formalListElement), yylineno); }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 202 "tokens.y"
    {
		std::vector< CFormalListElement* > decls = dynamic_cast< CFormalList* >((yyvsp[(1) - (2)].formalList))->List();
		decls.push_back( (yyvsp[(2) - (2)].formalListElement) );
		(yyval.formalList) = new CFormalList( decls, yylineno );
	}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 207 "tokens.y"
    { (yyval.formalListElement) = new CFormalListElement( (yyvsp[(2) - (3)].type), std::string((yyvsp[(3) - (3)].sval)), yylineno ); }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 208 "tokens.y"
    { (yyval.type) = new CType( "int[]", yylineno ); }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 209 "tokens.y"
    { (yyval.type) = new CType( "boolean", yylineno ); }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 210 "tokens.y"
    { (yyval.type) = new CType( "int", yylineno ); }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 211 "tokens.y"
    { (yyval.type) = new CType( (yyvsp[(1) - (1)].sval), yylineno ); }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 212 "tokens.y"
    { (yyval.statement) = new CStatementBlock((yyvsp[(2) - (3)].statements), yylineno); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 213 "tokens.y"
    { (yyval.statement) = nullptr; }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 214 "tokens.y"
    { (yyval.statement) = new CIfStatement( (yyvsp[(3) - (7)].exp), (yyvsp[(5) - (7)].statement), (yyvsp[(7) - (7)].statement), yylineno ); }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 215 "tokens.y"
    { (yyval.statement) = new CWhileStatement( (yyvsp[(3) - (5)].exp), (yyvsp[(5) - (5)].statement), yylineno ); }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 216 "tokens.y"
    { (yyval.statement) = new CPrintStatement( (yyvsp[(3) - (5)].exp), yylineno ); }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 217 "tokens.y"
    { (yyval.statement) = new CAssignmentStatement( std::string( (yyvsp[(1) - (4)].sval) ), (yyvsp[(3) - (4)].exp), yylineno ); }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 218 "tokens.y"
    { (yyval.statement) = new CElementAssignment( std::string((yyvsp[(1) - (7)].sval)), (yyvsp[(3) - (7)].exp), (yyvsp[(6) - (7)].exp), yylineno ); }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 219 "tokens.y"
    { (yyval.exp) = new CUnExp( (yyvsp[(2) - (2)].exp), "-", yylineno ); }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 220 "tokens.y"
    { (yyval.exp) = new CBinExp( (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), "+", yylineno ); }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 221 "tokens.y"
    { (yyval.exp) = new CBinExp( (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), "<", yylineno ); }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 222 "tokens.y"
    { (yyval.exp) = new CBinExp( (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), "&", yylineno ); }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 223 "tokens.y"
    { (yyval.exp) = new CBinExp( (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), "|", yylineno ); }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 224 "tokens.y"
    { (yyval.exp) = new CBinExp( (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), "-", yylineno ); }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 225 "tokens.y"
    { (yyval.exp) = new CBinExp( (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), "*", yylineno ); }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 226 "tokens.y"
    { (yyval.exp) = new CBinExp( (yyvsp[(1) - (4)].exp), (yyvsp[(3) - (4)].exp), "[]", yylineno ); }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 227 "tokens.y"
    { (yyval.exp) = new CLengthExp( (yyvsp[(1) - (3)].exp), yylineno ); }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 228 "tokens.y"
    { (yyval.exp) = new CMethodCall( (yyvsp[(1) - (6)].exp), (yyvsp[(3) - (6)].sval), (yyvsp[(5) - (6)].expList), yylineno ); }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 229 "tokens.y"
    { (yyval.exp) = new CNumber((yyvsp[(1) - (1)].ival), yylineno); }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 230 "tokens.y"
    { (yyval.exp) = new CNumber(1, yylineno); }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 231 "tokens.y"
    { (yyval.exp) = new CNumber(0, yylineno); }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 232 "tokens.y"
    { (yyval.exp) = new CId((yyvsp[(1) - (1)].sval), yylineno); }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 233 "tokens.y"
    { (yyval.exp) = new CId("this", yylineno); }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 234 "tokens.y"
    { (yyval.exp) = new CNewInt( (yyvsp[(4) - (5)].exp), yylineno ); }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 235 "tokens.y"
    { (yyval.exp) = new CConstructor( (yyvsp[(2) - (4)].sval), yylineno ); }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 236 "tokens.y"
    { (yyval.exp) = new CUnExp( (yyvsp[(2) - (2)].exp), "!", yylineno ); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 237 "tokens.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 238 "tokens.y"
    { (yyval.expList) = nullptr; }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 239 "tokens.y"
    { (yyval.expList) = new CExpList( (yyvsp[(1) - (1)].exp), yylineno ); }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 240 "tokens.y"
    { 
		std::vector< IExp* > exps = dynamic_cast<CExpList*>((yyvsp[(2) - (2)].expList))->Expressions();
		exps.insert(exps.begin(), (yyvsp[(1) - (2)].exp));
		(yyval.expList) = new CExpList(exps, yylineno); 
	}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 245 "tokens.y"
    { (yyval.expList) = new CExpList( (yyvsp[(1) - (1)].exp), yylineno ); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 246 "tokens.y"
    { 
		std::vector< IExp* > exps = dynamic_cast<CExpList*>((yyvsp[(1) - (2)].expList))->Expressions();
		exps.push_back((yyvsp[(2) - (2)].exp));
		(yyval.expList) = new CExpList(exps, yylineno); 
	}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 251 "tokens.y"
    { (yyval.exp) = (yyvsp[(2) - (2)].exp); }
    break;


/* Line 1792 of yacc.c  */
#line 2059 "tokens.tab.cpp"
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
      yyerror (hasError, YY_("syntax error"));
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
        yyerror (hasError, yymsgp);
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
		      yytoken, &yylval, hasError);
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
		  yystos[yystate], yyvsp, hasError);
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
  yyerror (hasError, YY_("memory exhausted"));
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
                  yytoken, &yylval, hasError);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, hasError);
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


/* Line 2055 of yacc.c  */
#line 252 "tokens.y"


/* Функция обработки ошибки. */
void yyerror( int*, const char* str )
{
	std::cout << str << std::endl;
}

int main()
{
    yyparse(0);
//    CPrettyPrinter printer;
//    printer.Visit( (CProgram*) program );

	CSymbTableBuilder tableBuilder;
	tableBuilder.Visit( (CProgram*) program );

	CTypeChecker checker( tableBuilder.GetSymbolTable() );
	checker.Visit( (CProgram*) program );

	CIRTranslator IRTranslator( tableBuilder.GetSymbolTable(), checker.GetExpTypesTable() );
	IRTranslator.Visit( (CProgram*) program );

	// Вывод IR-деревьев в "просматриваемый вид".
	std::stack< CFrame* > frames = IRTranslator.GetFramesList();
	while( !frames.empty() ) {
		CCanon canonizer;
		CTracer tracer;
		CFrame* frame = frames.top();
		frame->SetRootStatement(tracer.Transform (canonizer.Linearize(frame->GetRoot()))); // линеаризация IR-дерева фрейма
		frames.pop();
		CIRTreePrettyVisitor IRTreePrettyPrinter( std::string( "graph\\IRTree_" ) + frame->GetName() + std::string( ".dot" ) );
		frame->GetRoot()->Accept( &IRTreePrettyPrinter );
		IRTreePrettyPrinter.Flush();
	}


	frames = IRTranslator.GetFramesList();
	while( !frames.empty() ) {
		std::ofstream out;
		
		CCanon canonizer;
		CTracer tracer;
		CFrame* frame = frames.top();

		std::cout << frame->GetName() << std::endl;
		out.open( std::string( "asm\\Asm_" ) + frame->GetName() + std::string( ".asm" ), std::ofstream::out );

		frame->SetRootStatement( tracer.Transform ( canonizer.Linearize( frame->GetRoot() ) ) );
		CodeGeneration::CAsmTreeMaker asmTreeMaker( frame );
		asmTreeMaker.InitializeTree( frame->GetRoot() );
		auto instructions = asmTreeMaker.GetAsmInstruction();
		for( auto instruction : instructions ) {
			std::cout << instruction->AsmCode;
		}

		CodeGeneration::CPrologEpilogBuilder prologEpilogBuilder( instructions );
		instructions = prologEpilogBuilder.AddPrologAndEpilog( frame );
		//CodeGeneration::CInterferenceGraph graph( instructions, frame->GetRegisters() );

		//auto code = graph.GetCode();
		//auto colors = graph.GetColors();

		/*for( auto cmd : code ) {
			out << cmd->Format( colors );
		}*/

		for( auto cmd : instructions ) {
			out << cmd->Format() << std::endl;
		}

		frames.pop();
		
		out.close();
	}


	system("pause");
	return 0;
}