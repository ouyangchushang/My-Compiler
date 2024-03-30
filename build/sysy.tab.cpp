/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 7 "/root/compiler/src/sysy.y"


#include <iostream>
#include <memory>
#include <string>
#include "AST.h"

// 声明 lexer 函数和错误处理函数
int yylex();
void yyerror(std::unique_ptr<BaseAST> &ast, const char *s);

using namespace std;


#line 85 "/root/compiler/build/sysy.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_ROOT_COMPILER_BUILD_SYSY_TAB_HPP_INCLUDED
# define YY_YY_ROOT_COMPILER_BUILD_SYSY_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "/root/compiler/src/sysy.y"

  #include <memory>
  #include <string>
  #include "AST.h"

#line 134 "/root/compiler/build/sysy.tab.cpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    VOID = 259,
    RETURN = 260,
    LESS_EQ = 261,
    GREAT_EQ = 262,
    EQUAL = 263,
    NOT_EQUAL = 264,
    AND = 265,
    OR = 266,
    CONST = 267,
    IF = 268,
    ELSE = 269,
    WHILE = 270,
    BREAK = 271,
    CONTINUE = 272,
    IDENT = 273,
    INT_CONST = 274
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 27 "/root/compiler/src/sysy.y"

  std::string *str_val;
  int int_val;
  BaseAST *ast_val;
  char char_val;

#line 172 "/root/compiler/build/sysy.tab.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (std::unique_ptr<BaseAST> &ast);

#endif /* !YY_YY_ROOT_COMPILER_BUILD_SYSY_TAB_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   212

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  174

#define YYUNDEFTOK  2
#define YYMAXUTOK   274


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,     2,     2,    34,     2,     2,
      20,    21,    32,    29,    22,    30,     2,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    27,
      35,    28,    36,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    23,     2,    24,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,     2,    26,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    47,    47,    54,    60,    81,    89,    98,   109,   116,
     124,   137,   143,   149,   163,   171,   179,   185,   192,   205,
     216,   225,   234,   242,   250,   264,   274,   288,   294,   299,
     305,   310,   319,   327,   335,   343,   351,   360,   369,   377,
     390,   398,   408,   419,   433,   448,   454,   459,   465,   469,
     477,   483,   490,   501,   510,   521,   530,   539,   550,   563,
     573,   581,   589,   600,   614,   619,   632,   637,   651,   659,
     668,   678,   687,   697,   705,   718,   727,   736,   746,   755,
     766,   775,   786,   795,   807,   819,   831,   840,   852,   864,
     873,   883,   892,   902,   908,   914,   920,   926,   932,   938,
     944,   950,   956,   962
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "VOID", "RETURN", "LESS_EQ",
  "GREAT_EQ", "EQUAL", "NOT_EQUAL", "AND", "OR", "CONST", "IF", "ELSE",
  "WHILE", "BREAK", "CONTINUE", "IDENT", "INT_CONST", "'('", "')'", "','",
  "'['", "']'", "'{'", "'}'", "';'", "'='", "'+'", "'-'", "'!'", "'*'",
  "'/'", "'%'", "'<'", "'>'", "$accept", "CompUnit", "GlobalFuncVarList",
  "GlobalFuncVar", "FuncDef", "FuncParams", "FuncParam", "BType", "Block",
  "BlockItemList", "BlockItem", "Decl", "ConstDecl", "ConstDefList",
  "ConstDef", "ConstInitVal", "ConstInitValList", "ConstExp",
  "ArrayIndexConstExpList", "ArrayIndexExpList", "VarDecl", "VarDefList",
  "VarDef", "InitVal", "InitValList", "Stmt", "MatchedStmt", "OpenStmt",
  "LVal", "LeVal", "Exp", "UnaryExp", "FuncCallParams", "PrimaryExp",
  "MultiExp", "AddExp", "RelExp", "EqExp", "LAndExp", "LOrExp", "Number",
  "UnaryOp", "BinaryAddOp", "BinaryMultiOp", "BinaryRelOp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
      40,    41,    44,    91,    93,   123,   125,    59,    61,    43,
      45,    33,    42,    47,    37,    60,    62
};
# endif

#define YYPACT_NINF (-137)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-68)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      20,  -137,  -137,    49,     6,  -137,    20,  -137,     0,  -137,
    -137,  -137,    13,  -137,  -137,    21,    23,    32,     5,    36,
      43,    49,   156,   126,    14,  -137,    56,   134,    47,  -137,
      13,    75,    84,    94,    -3,  -137,   156,  -137,  -137,  -137,
      93,  -137,  -137,  -137,  -137,    82,    52,     4,   111,   113,
     114,  -137,   156,    -4,  -137,  -137,   156,   126,    57,  -137,
     110,  -137,  -137,   134,  -137,   107,    49,   115,   148,   156,
     124,   116,  -137,  -137,  -137,  -137,   156,  -137,  -137,   156,
     156,   156,  -137,  -137,   156,   156,   156,   156,   156,  -137,
    -137,  -137,    76,   136,  -137,  -137,  -137,    87,  -137,    74,
    -137,  -137,   137,  -137,   112,   141,   146,   156,  -137,  -137,
      82,    52,    52,    52,     4,     4,   111,   113,   126,  -137,
    -137,   134,  -137,   153,   138,   161,   162,   163,    28,  -137,
      56,  -137,   165,    74,  -137,  -137,  -137,  -137,   160,   166,
     169,   156,  -137,  -137,   170,  -137,  -137,  -137,   168,   156,
     156,  -137,  -137,    60,  -137,  -137,   156,  -137,   173,  -137,
    -137,  -137,   176,   177,   172,    42,    42,  -137,  -137,   186,
    -137,    42,  -137,  -137
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    14,    15,     0,     0,     2,     3,     6,     0,     5,
      21,    37,     0,     1,     4,    41,     0,    40,     0,     0,
      23,     8,     0,     0,    43,    38,     0,     0,     0,    22,
       0,     0,     9,     0,    64,    93,     0,    94,    95,    96,
       0,    77,    32,    78,    69,    80,    82,    86,    89,    91,
      68,    76,     0,     0,    42,    45,     0,     0,    41,    39,
       0,    25,    27,     0,    24,     0,     8,    11,     0,     0,
      65,     0,    33,    99,   100,   101,     0,    97,    98,     0,
       0,     0,   102,   103,     0,     0,     0,     0,     0,    70,
      46,    48,     0,     0,    44,    28,    30,     0,    26,    17,
       7,    10,     0,    71,    73,     0,     0,     0,    75,    79,
      81,    84,    85,    83,    87,    88,    90,    92,     0,    47,
      34,     0,    29,     0,     0,     0,     0,     0,    64,    56,
       0,    55,     0,    17,    19,    20,    51,    50,     0,     0,
      12,     0,    72,    35,     0,    49,    31,    53,     0,     0,
       0,    60,    61,    65,    16,    18,     0,    57,    13,    74,
      36,    52,     0,     0,     0,     0,     0,    54,    62,    51,
      59,     0,    58,    63
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -137,  -137,   195,  -137,  -137,   139,  -137,    -2,   142,    69,
    -137,   -95,  -137,   174,  -137,   -55,  -137,   -13,   -16,    78,
    -137,   182,  -137,   -50,  -137,   -44,  -136,    38,  -137,  -137,
     -23,   -40,    62,  -137,   131,    27,    64,   125,   123,  -137,
    -137,  -137,  -137,  -137,  -137
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    31,    32,     8,   131,   132,
     133,     9,    10,    19,    20,    61,    97,    62,    24,    70,
      11,    16,    17,    54,    92,   135,   136,   137,    41,   138,
      42,    43,   105,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    79,    76,    84
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      55,    12,    28,    91,   134,    96,    13,    94,    98,    40,
      80,    81,    89,    71,    34,    35,    36,    68,    15,    33,
      69,    53,    90,     1,     2,    37,    38,    39,    22,   169,
      55,    18,     3,    27,    55,   172,   109,    56,   134,    82,
      83,    21,    57,    93,    22,   104,   106,   123,    68,    23,
      25,    69,     1,     2,    26,   124,   -66,   125,   126,   127,
     128,    35,    36,    29,    33,    30,   146,    99,   145,   129,
      56,    37,    38,    39,    58,    63,   139,     1,     2,   123,
      22,    77,    78,   107,   144,    23,     3,   124,   -67,   125,
     126,   127,   128,    35,    36,    55,    65,   130,   118,    99,
     148,   129,   119,    37,    38,    39,    66,   111,   112,   121,
     139,   113,    67,   122,    73,    74,    75,    72,   104,    85,
      86,   168,   170,    87,   158,    88,   162,   163,    34,    35,
      36,   130,    99,   164,   141,    60,    95,   108,   102,    37,
      38,    39,   139,   139,    34,    35,    36,   107,   139,   114,
     115,    53,    34,    35,    36,    37,    38,    39,   149,    60,
     120,   140,   142,    37,    38,    39,    34,    35,    36,   103,
     143,    34,    35,    36,    34,    35,    36,    37,    38,    39,
     147,   150,    37,    38,    39,    37,    38,    39,   156,   151,
     152,   154,    22,   157,   160,   161,    56,   165,   166,   167,
     171,    14,   155,   159,    64,   101,   153,   100,    59,   173,
     110,   117,   116
};

static const yytype_uint8 yycheck[] =
{
      23,     3,    18,    53,    99,    60,     0,    57,    63,    22,
       6,     7,    52,    36,    18,    19,    20,    20,    18,    21,
      23,    25,    26,     3,     4,    29,    30,    31,    23,   165,
      53,    18,    12,    28,    57,   171,    76,    23,   133,    35,
      36,    20,    28,    56,    23,    68,    69,     5,    20,    28,
      27,    23,     3,     4,    22,    13,    28,    15,    16,    17,
      18,    19,    20,    27,    66,    22,   121,    25,   118,    27,
      23,    29,    30,    31,    18,    28,    99,     3,     4,     5,
      23,    29,    30,    23,   107,    28,    12,    13,    28,    15,
      16,    17,    18,    19,    20,   118,    21,    99,    22,    25,
     123,    27,    26,    29,    30,    31,    22,    80,    81,    22,
     133,    84,    18,    26,    32,    33,    34,    24,   141,     8,
       9,   165,   166,    10,   140,    11,   149,   150,    18,    19,
      20,   133,    25,   156,    22,    25,    26,    21,    23,    29,
      30,    31,   165,   166,    18,    19,    20,    23,   171,    85,
      86,    25,    18,    19,    20,    29,    30,    31,    20,    25,
      24,    24,    21,    29,    30,    31,    18,    19,    20,    21,
      24,    18,    19,    20,    18,    19,    20,    29,    30,    31,
      27,    20,    29,    30,    31,    29,    30,    31,    28,    27,
      27,    26,    23,    27,    24,    27,    23,    21,    21,    27,
      14,     6,   133,   141,    30,    66,   128,    65,    26,   171,
      79,    88,    87
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,    12,    38,    39,    40,    41,    44,    48,
      49,    57,    44,     0,    39,    18,    58,    59,    18,    50,
      51,    20,    23,    28,    55,    27,    22,    28,    55,    27,
      22,    42,    43,    44,    18,    19,    20,    29,    30,    31,
      54,    65,    67,    68,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    25,    60,    67,    23,    28,    18,    58,
      25,    52,    54,    28,    50,    21,    22,    18,    20,    23,
      56,    67,    24,    32,    33,    34,    80,    29,    30,    79,
       6,     7,    35,    36,    81,     8,     9,    10,    11,    68,
      26,    60,    61,    54,    60,    26,    52,    53,    52,    25,
      45,    42,    23,    21,    67,    69,    67,    23,    21,    68,
      71,    72,    72,    72,    73,    73,    74,    75,    22,    26,
      24,    22,    26,     5,    13,    15,    16,    17,    18,    27,
      44,    45,    46,    47,    48,    62,    63,    64,    66,    67,
      24,    22,    21,    24,    67,    60,    52,    27,    67,    20,
      20,    27,    27,    56,    26,    46,    28,    27,    55,    69,
      24,    27,    67,    67,    67,    21,    21,    27,    62,    63,
      62,    14,    63,    64
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    40,    41,    42,    42,
      42,    43,    43,    43,    44,    44,    45,    46,    46,    47,
      47,    48,    49,    50,    50,    51,    51,    52,    52,    52,
      53,    53,    54,    55,    55,    56,    56,    48,    57,    58,
      58,    59,    59,    59,    59,    60,    60,    60,    61,    61,
      62,    62,    63,    63,    63,    63,    63,    63,    63,    64,
      63,    63,    64,    64,    65,    65,    66,    66,    67,    68,
      68,    68,    68,    69,    69,    70,    70,    70,    71,    71,
      72,    72,    73,    73,    73,    73,    74,    74,    74,    75,
      75,    76,    76,    77,    78,    78,    78,    79,    79,    80,
      80,    80,    81,    81
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     6,     0,     1,
       3,     2,     4,     5,     1,     1,     3,     0,     2,     1,
       1,     1,     4,     1,     3,     3,     4,     1,     2,     3,
       1,     3,     1,     3,     4,     3,     4,     1,     3,     3,
       1,     1,     3,     2,     4,     1,     2,     3,     1,     3,
       1,     1,     3,     2,     4,     1,     1,     2,     7,     5,
       2,     2,     5,     7,     1,     2,     1,     2,     1,     1,
       2,     3,     4,     1,     3,     3,     1,     1,     1,     3,
       1,     3,     1,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        yyerror (ast, YY_("syntax error: cannot back up")); \
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
                  Type, Value, ast); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, std::unique_ptr<BaseAST> &ast)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (ast);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, std::unique_ptr<BaseAST> &ast)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, ast);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, std::unique_ptr<BaseAST> &ast)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              , ast);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, ast); \
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, std::unique_ptr<BaseAST> &ast)
{
  YYUSE (yyvaluep);
  YYUSE (ast);
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
yyparse (std::unique_ptr<BaseAST> &ast)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
      yychar = yylex ();
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2:
#line 47 "/root/compiler/src/sysy.y"
                      {
    auto comp_unit = unique_ptr<CompUnitAST>((CompUnitAST *)(yyvsp[0].ast_val));
    ast = move(comp_unit);
  }
#line 1486 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 3:
#line 54 "/root/compiler/src/sysy.y"
                  {
    (yyval.ast_val) = (yyvsp[0].ast_val);
  }
#line 1494 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 4:
#line 60 "/root/compiler/src/sysy.y"
                                   {
    auto comp_unit = new CompUnitAST();
    auto comp1 = unique_ptr<CompUnitAST>((CompUnitAST *)(yyvsp[-1].ast_val));
    auto comp2 = unique_ptr<CompUnitAST>((CompUnitAST *)(yyvsp[0].ast_val));
    for(auto &f : comp1->func_defs){
        comp_unit->func_defs.emplace_back(f.release());
    }
    for(auto &f : comp2->func_defs){
        comp_unit->func_defs.emplace_back(f.release());
    }
    for(auto &d : comp1->decls){
        comp_unit->decls.emplace_back(d.release());
    }
    for(auto &d : comp2->decls){
        comp_unit->decls.emplace_back(d.release());
    }
    (yyval.ast_val) = comp_unit;
  }
#line 1517 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 5:
#line 81 "/root/compiler/src/sysy.y"
         {
    auto comp_unit = new CompUnitAST();
    comp_unit->decls.emplace_back((DeclAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = comp_unit;
  }
#line 1527 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 6:
#line 89 "/root/compiler/src/sysy.y"
            {
    auto comp_unit = new CompUnitAST();
    comp_unit->func_defs.emplace_back((FuncDefAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = comp_unit;
  }
#line 1537 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 7:
#line 98 "/root/compiler/src/sysy.y"
                                         {
    auto func_def = new FuncDefAST();
    func_def->func_type = unique_ptr<BTypeAST>((BTypeAST *)(yyvsp[-5].ast_val));
    func_def->ident = *unique_ptr<string>((yyvsp[-4].str_val));
    func_def->func_params = unique_ptr<FuncParamsAST>((FuncParamsAST *)(yyvsp[-2].ast_val));
    func_def->block = unique_ptr<BlockAST>((BlockAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = func_def;
  }
#line 1550 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 8:
#line 109 "/root/compiler/src/sysy.y"
    {
    auto funcparam = new FuncParamsAST();
    (yyval.ast_val) = funcparam;
  }
#line 1559 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 9:
#line 116 "/root/compiler/src/sysy.y"
              {
    auto func_params = new FuncParamsAST();
    func_params->func_params.emplace_back((FuncParamAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = func_params;
  }
#line 1569 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 10:
#line 124 "/root/compiler/src/sysy.y"
                             {
    auto func_params_ast = new FuncParamsAST();
    func_params_ast->func_params.emplace_back((FuncParamAST *)(yyvsp[-2].ast_val));
    auto params = unique_ptr<FuncParamsAST>((FuncParamsAST *)((yyvsp[0].ast_val)));
    int n = params->func_params.size();
    for(int i = 0; i < n; ++i){
        func_params_ast->func_params.emplace_back(params->func_params[i].release());
    }
    (yyval.ast_val) = func_params_ast;
  }
#line 1584 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 11:
#line 137 "/root/compiler/src/sysy.y"
                {
    auto func_param = new FuncParamAST();
    func_param->is_array = false;
    func_param->btype.reset((BTypeAST *)(yyvsp[-1].ast_val));
    func_param->ident = *unique_ptr<string>((yyvsp[0].str_val));
    (yyval.ast_val) = func_param;
  }
#line 1596 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 12:
#line 143 "/root/compiler/src/sysy.y"
                          {
    auto func_param = new FuncParamAST();
    func_param->is_array = true;
    func_param->btype.reset((BTypeAST *)(yyvsp[-3].ast_val));
    func_param->ident = *unique_ptr<string>((yyvsp[-2].str_val));
    (yyval.ast_val) = func_param;
  }
#line 1608 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 13:
#line 149 "/root/compiler/src/sysy.y"
                                                 {
    auto func_param = new FuncParamAST();
    func_param->is_array = true;
    func_param->btype.reset((BTypeAST *)(yyvsp[-4].ast_val));
    func_param->ident = *unique_ptr<string>((yyvsp[-3].str_val));
    unique_ptr<ArrayIndexConstExpListAST> p((ArrayIndexConstExpListAST *)(yyvsp[0].ast_val));
    for(auto &ce : p->const_exps){
        func_param->const_exps.emplace_back(ce.release());
    }
    (yyval.ast_val) = func_param;
  }
#line 1624 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 14:
#line 163 "/root/compiler/src/sysy.y"
        {
    auto type_ast = new BTypeAST();
    type_ast->type = "int";
    (yyval.ast_val) = type_ast;
  }
#line 1634 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 15:
#line 171 "/root/compiler/src/sysy.y"
         {
    auto type_ast = new BTypeAST();
    type_ast->type = "void";
    (yyval.ast_val) = type_ast;
  }
#line 1644 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 16:
#line 179 "/root/compiler/src/sysy.y"
                          {
    (yyval.ast_val) = (yyvsp[-1].ast_val);
  }
#line 1652 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 17:
#line 185 "/root/compiler/src/sysy.y"
     {
    auto block = new BlockAST();
    (yyval.ast_val) = block;
  }
#line 1661 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 18:
#line 192 "/root/compiler/src/sysy.y"
                            {
    auto block = new BlockAST();
    auto block_lst = unique_ptr<BlockAST>((BlockAST *)(yyvsp[0].ast_val));
    block->block_items.emplace_back((BlockItemAST *)(yyvsp[-1].ast_val));
    int n = block_lst->block_items.size();
    for(int i = 0; i < n; ++i){
        block->block_items.emplace_back(block_lst->block_items[i].release());
    }
    (yyval.ast_val) = block;
  }
#line 1676 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 19:
#line 205 "/root/compiler/src/sysy.y"
         {
    auto block_item = new BlockItemAST();
    block_item->type = "decl";
    block_item->decl = unique_ptr<DeclAST>((DeclAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = block_item;
  }
#line 1687 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 20:
#line 216 "/root/compiler/src/sysy.y"
         {
    auto block_item = new BlockItemAST();
    block_item->type = "stmt";
    block_item->stmt = unique_ptr<StmtAST>((StmtAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = block_item;
  }
#line 1698 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 21:
#line 225 "/root/compiler/src/sysy.y"
              {
    auto decl = new DeclAST();
    decl->is_const = true;
    decl->const_decl = unique_ptr<ConstDeclAST>((ConstDeclAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = decl;
  }
#line 1709 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 22:
#line 234 "/root/compiler/src/sysy.y"
                                {
    auto const_decl = (ConstDeclAST *)(yyvsp[-1].ast_val);
    const_decl->btype = unique_ptr<BTypeAST>((BTypeAST *)(yyvsp[-2].ast_val));
    (yyval.ast_val) = const_decl;
  }
#line 1719 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 23:
#line 242 "/root/compiler/src/sysy.y"
             {
    auto const_decl = new ConstDeclAST();
    const_decl->const_defs.emplace_back((ConstDefAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = const_decl;
  }
#line 1729 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 24:
#line 250 "/root/compiler/src/sysy.y"
                              {
    auto const_decl = new ConstDeclAST();
    auto const_decl_2 = unique_ptr<ConstDeclAST>((ConstDeclAST *)(yyvsp[0].ast_val));
    const_decl->const_defs.emplace_back((ConstDefAST *)(yyvsp[-2].ast_val));
    int n = const_decl_2->const_defs.size();
    for(int i = 0; i < n; ++i){
        const_decl->const_defs.emplace_back(const_decl_2->const_defs[i].release());
    }
    (yyval.ast_val) = const_decl;
  }
#line 1744 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 25:
#line 264 "/root/compiler/src/sysy.y"
                           {
    auto const_def = new ConstDefAST();
    const_def->is_array = false;
    const_def->ident = *unique_ptr<string>((yyvsp[-2].str_val));
    const_def->const_init_val = unique_ptr<ConstInitValAST>((ConstInitValAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = const_def;
  }
#line 1756 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 26:
#line 274 "/root/compiler/src/sysy.y"
                                                  {
    auto const_def = new ConstDefAST();
    unique_ptr<ArrayIndexConstExpListAST> p( (ArrayIndexConstExpListAST *)(yyvsp[-2].ast_val));
    const_def->is_array = true;
    const_def->ident = *unique_ptr<string>((yyvsp[-3].str_val));
    for(auto &ce : p->const_exps){
        const_def->const_exps.emplace_back(ce.release());
    }
    const_def->const_init_val = unique_ptr<ConstInitValAST>((ConstInitValAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = const_def;
  }
#line 1772 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 27:
#line 288 "/root/compiler/src/sysy.y"
             {
    auto const_init_val = new ConstInitValAST();
    const_init_val->is_exp = true;
    const_init_val->is_list = false;
    const_init_val->const_exp = unique_ptr<ConstExpAST>((ConstExpAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = const_init_val;
  }
#line 1784 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 28:
#line 294 "/root/compiler/src/sysy.y"
             {
    auto const_init_val = new ConstInitValAST();
    const_init_val->is_exp = false;
    const_init_val->is_list = true;
    (yyval.ast_val) = const_init_val;
  }
#line 1795 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 29:
#line 299 "/root/compiler/src/sysy.y"
                               {
    (yyval.ast_val) = (yyvsp[-1].ast_val);
  }
#line 1803 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 30:
#line 305 "/root/compiler/src/sysy.y"
                 {
    auto init_val = new ConstInitValAST();
    init_val->is_list = true;
    init_val->inits.emplace_back((ConstInitValAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = init_val;
  }
#line 1814 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 31:
#line 310 "/root/compiler/src/sysy.y"
                                        {
    auto init_val = (ConstInitValAST *)(yyvsp[-2].ast_val);
    init_val->inits.emplace_back((ConstInitValAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = init_val;
  }
#line 1824 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 32:
#line 319 "/root/compiler/src/sysy.y"
        {
    auto const_exp = new ConstExpAST();
    const_exp->exp = unique_ptr<ExpAST>((ExpAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = const_exp;
  }
#line 1834 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 33:
#line 327 "/root/compiler/src/sysy.y"
                     {
    auto p = new ArrayIndexConstExpListAST();
    p->const_exps.emplace_back((ConstExpAST *)(yyvsp[-1].ast_val));
    (yyval.ast_val) = p;
  }
#line 1844 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 34:
#line 335 "/root/compiler/src/sysy.y"
                                            {
    auto p = (ArrayIndexConstExpListAST *)(yyvsp[-3].ast_val);
    p->const_exps.emplace_back((ConstExpAST *)(yyvsp[-1].ast_val));
    (yyval.ast_val) = p;
  }
#line 1854 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 35:
#line 343 "/root/compiler/src/sysy.y"
                {
    auto p = new ArrayIndexExpListAST();
    p->exps.emplace_back((ExpAST *)(yyvsp[-1].ast_val));
    (yyval.ast_val) = p;
  }
#line 1864 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 36:
#line 351 "/root/compiler/src/sysy.y"
                                  {
    auto p = (ArrayIndexExpListAST *)(yyvsp[-3].ast_val);
    p->exps.emplace_back((ExpAST *)(yyvsp[-1].ast_val));
    (yyval.ast_val) = p;
  }
#line 1874 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 37:
#line 360 "/root/compiler/src/sysy.y"
            {
    auto decl = new DeclAST();
    decl->is_const = false;
    decl->var_decl = unique_ptr<VarDeclAST>((VarDeclAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = decl;
  }
#line 1885 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 38:
#line 369 "/root/compiler/src/sysy.y"
                         {
    auto var_decl = (VarDeclAST *)(yyvsp[-1].ast_val);
    var_decl->btype = unique_ptr<BTypeAST>((BTypeAST *) (yyvsp[-2].ast_val));
    (yyval.ast_val) = var_decl;
  }
#line 1895 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 39:
#line 377 "/root/compiler/src/sysy.y"
                          {
    auto var_decl = new VarDeclAST();
    auto var_decl_2 = unique_ptr<VarDeclAST>((VarDeclAST *)(yyvsp[0].ast_val));
    var_decl->var_defs.emplace_back((VarDefAST *)(yyvsp[-2].ast_val));
    int n = var_decl_2->var_defs.size();
    for(int i = 0; i < n; ++i){
        var_decl->var_defs.emplace_back(var_decl_2->var_defs[i].release());
    }
    (yyval.ast_val) = var_decl;
  }
#line 1910 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 40:
#line 390 "/root/compiler/src/sysy.y"
           {
    auto var_decl = new VarDeclAST();
    var_decl->var_defs.emplace_back((VarDefAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = var_decl;
  }
#line 1920 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 41:
#line 398 "/root/compiler/src/sysy.y"
          {
    auto var_def = new VarDefAST();
    var_def->is_array = false;
    var_def->ident = *unique_ptr<string>((yyvsp[0].str_val));
    var_def->has_value = false;
    (yyval.ast_val) = var_def;
  }
#line 1932 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 42:
#line 408 "/root/compiler/src/sysy.y"
                      {
    auto var_def = new VarDefAST();
    var_def->is_array = false;
    var_def->ident = *unique_ptr<string>((yyvsp[-2].str_val));
    var_def->has_value = true;
    var_def->init_val = unique_ptr<InitValAST>((InitValAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = var_def;
  }
#line 1945 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 43:
#line 419 "/root/compiler/src/sysy.y"
                                 {
    auto var_def = new VarDefAST();
    var_def->is_array = true;
    var_def->ident = *unique_ptr<string>((yyvsp[-1].str_val));
    var_def->has_value = false;
    unique_ptr<ArrayIndexConstExpListAST> p((ArrayIndexConstExpListAST *)(yyvsp[0].ast_val));
    for(auto &ce : p->const_exps){
        var_def->const_exps.emplace_back(ce.release());
    }
    (yyval.ast_val) = var_def;
  }
#line 1961 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 44:
#line 433 "/root/compiler/src/sysy.y"
                                             {
    auto var_def = new VarDefAST();
    var_def->is_array = true;
    var_def->has_value = true;
    var_def->ident = *unique_ptr<string>((yyvsp[-3].str_val));
    unique_ptr<ArrayIndexConstExpListAST> p((ArrayIndexConstExpListAST *)(yyvsp[-2].ast_val));
    for(auto &ce : p->const_exps){
        var_def->const_exps.emplace_back(ce.release());
    }
    var_def->init_val = unique_ptr<InitValAST>((InitValAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = var_def;
  }
#line 1978 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 45:
#line 448 "/root/compiler/src/sysy.y"
       {
    auto init_val = new InitValAST();
    init_val->is_exp = true;
    init_val->is_list = false;
    init_val->exp.reset((ExpAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = init_val;
  }
#line 1990 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 46:
#line 454 "/root/compiler/src/sysy.y"
              {
    auto init_val = new InitValAST();
    init_val->is_exp = false;
    init_val->is_list = true;
    (yyval.ast_val) = init_val;
  }
#line 2001 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 47:
#line 459 "/root/compiler/src/sysy.y"
                          {
    (yyval.ast_val) = (yyvsp[-1].ast_val);
  }
#line 2009 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 48:
#line 465 "/root/compiler/src/sysy.y"
            {
    auto init_val = new InitValAST();
    init_val->inits.emplace_back((InitValAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = init_val;
  }
#line 2019 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 49:
#line 469 "/root/compiler/src/sysy.y"
                              {
    auto init_val = (InitValAST *)(yyvsp[-2].ast_val);
    init_val->inits.emplace_back((InitValAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = init_val;
  }
#line 2029 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 50:
#line 477 "/root/compiler/src/sysy.y"
             {
     (yyval.ast_val) = (yyvsp[0].ast_val);
  }
#line 2037 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 51:
#line 483 "/root/compiler/src/sysy.y"
                {
     (yyval.ast_val) = (yyvsp[0].ast_val);
  }
#line 2045 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 52:
#line 490 "/root/compiler/src/sysy.y"
                   {
    auto stmt_ast = new StmtAST();
    stmt_ast->tag = StmtAST::RETURN;
    stmt_ast->has_exp = true;
    stmt_ast->exp = unique_ptr<ExpAST>((ExpAST*)(yyvsp[-1].ast_val));
    (yyval.ast_val) = stmt_ast;
  }
#line 2057 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 53:
#line 501 "/root/compiler/src/sysy.y"
                {
    auto stmt = new StmtAST();
    stmt->has_exp = false;
    stmt->tag = StmtAST::RETURN;
    (yyval.ast_val) = stmt;
  }
#line 2068 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 54:
#line 510 "/root/compiler/src/sysy.y"
                      {
    auto stmt = new StmtAST();
    stmt->tag = StmtAST::ASSIGN;
    stmt->has_exp = true;
    stmt->exp.reset((ExpAST *) (yyvsp[-1].ast_val));
    stmt->lval.reset((LeValAST *) (yyvsp[-3].ast_val));
    (yyval.ast_val) = stmt;
  }
#line 2081 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 55:
#line 521 "/root/compiler/src/sysy.y"
          {
    auto stmt = new StmtAST();
    stmt->tag = StmtAST::BLOCK;
    stmt->block.reset((BlockAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = stmt;
  }
#line 2092 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 56:
#line 530 "/root/compiler/src/sysy.y"
        {
    auto stmt = new StmtAST();
    stmt->has_exp = false;
    stmt->tag = StmtAST::EXP;
    (yyval.ast_val) = stmt;
  }
#line 2103 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 57:
#line 539 "/root/compiler/src/sysy.y"
            {
    auto stmt = new StmtAST();
    stmt->tag = StmtAST::EXP;
    stmt->has_exp = true;
    stmt->exp.reset((ExpAST *)(yyvsp[-1].ast_val));
    (yyval.ast_val) = stmt;
  }
#line 2115 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 58:
#line 550 "/root/compiler/src/sysy.y"
                                                {
    auto mat_stmt = new StmtAST();
    mat_stmt->tag = StmtAST::IF;
    mat_stmt->has_exp = true;
    mat_stmt->has_else = true;      
    mat_stmt->exp.reset((ExpAST *) (yyvsp[-4].ast_val));
    mat_stmt->if_stmt.reset((StmtAST *)(yyvsp[-2].ast_val));
    mat_stmt->else_stmt.reset((StmtAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = mat_stmt;
  }
#line 2130 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 59:
#line 563 "/root/compiler/src/sysy.y"
                           {
    auto stmt = new StmtAST();
    stmt->tag = StmtAST::WHILE;
    stmt->exp.reset((ExpAST *)(yyvsp[-2].ast_val));
    stmt->stmt.reset((StmtAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = stmt;
  }
#line 2142 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 60:
#line 573 "/root/compiler/src/sysy.y"
              {
    auto stmt = new StmtAST();
    stmt->tag = StmtAST::BREAK;
    (yyval.ast_val) = stmt;
  }
#line 2152 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 61:
#line 581 "/root/compiler/src/sysy.y"
                 {
    auto stmt = new StmtAST();
    stmt->tag = StmtAST::CONTINUE;
    (yyval.ast_val) = stmt;
  }
#line 2162 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 62:
#line 589 "/root/compiler/src/sysy.y"
                        {
    auto open_stmt = new StmtAST();
    open_stmt->tag = StmtAST::IF;
    open_stmt->has_exp = true;
    open_stmt->exp.reset((ExpAST *)(yyvsp[-2].ast_val));
    open_stmt->if_stmt.reset((StmtAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = open_stmt;
  }
#line 2175 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 63:
#line 600 "/root/compiler/src/sysy.y"
                                             {
    auto open_stmt = new StmtAST();
    open_stmt->tag = StmtAST::IF;
    open_stmt ->has_exp = true;
    open_stmt->exp.reset((ExpAST *)(yyvsp[-4].ast_val));
    open_stmt->if_stmt.reset((StmtAST *)(yyvsp[-2].ast_val));
    open_stmt->has_else = true;
    open_stmt->else_stmt.reset((StmtAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = open_stmt;
  }
#line 2190 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 64:
#line 614 "/root/compiler/src/sysy.y"
          {
    auto lval = new LValAST();
    lval->is_array = false;
    lval->ident = *unique_ptr<string>((yyvsp[0].str_val));
    (yyval.ast_val) = lval;
  }
#line 2201 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 65:
#line 619 "/root/compiler/src/sysy.y"
                              {
    auto lval = new LValAST();
    unique_ptr<ArrayIndexExpListAST> p((ArrayIndexExpListAST *)(yyvsp[0].ast_val));
    lval->is_array = true;
    lval->ident = *unique_ptr<string>((yyvsp[-1].str_val));
    for(auto &e : p->exps){
        lval->exps.emplace_back(e.release());
    }
    (yyval.ast_val) = lval;
  }
#line 2216 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 66:
#line 632 "/root/compiler/src/sysy.y"
          {
    auto lval = new LeValAST();
    lval->is_array = false;
    lval->ident = *unique_ptr<string>((yyvsp[0].str_val));
    (yyval.ast_val) = lval;
  }
#line 2227 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 67:
#line 637 "/root/compiler/src/sysy.y"
                               {
    auto lval = new LeValAST();
    unique_ptr<ArrayIndexExpListAST> p((ArrayIndexExpListAST *)(yyvsp[0].ast_val));
    lval->is_array = true;
    lval->ident = *unique_ptr<string>((yyvsp[-1].str_val));
    for(auto &e : p->exps){
        lval->exps.emplace_back(e.release());
    }
    (yyval.ast_val) = lval;
  }
#line 2242 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 68:
#line 651 "/root/compiler/src/sysy.y"
           {
    auto exp_ast = new ExpAST();
    exp_ast->lorexp = unique_ptr<LOrExpAST>((LOrExpAST*)(yyvsp[0].ast_val));
    (yyval.ast_val) = exp_ast;
  }
#line 2252 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 69:
#line 659 "/root/compiler/src/sysy.y"
               {
    auto unaryexp_ast = new UnaryExpAST();
    unaryexp_ast->HasOp = false;
    unaryexp_ast->primaryexp = unique_ptr<PrimaryExpAST>((PrimaryExpAST*)(yyvsp[0].ast_val));
    (yyval.ast_val) = unaryexp_ast;
  }
#line 2263 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 70:
#line 668 "/root/compiler/src/sysy.y"
                     {
    auto unaryexp_ast = new UnaryExpAST();
    unaryexp_ast->HasOp = true;
    unaryexp_ast->unary_op = (yyvsp[-1].char_val);
    unaryexp_ast->unaryexp = unique_ptr<UnaryExpAST>((UnaryExpAST*)(yyvsp[0].ast_val));
    (yyval.ast_val) = unaryexp_ast;
  }
#line 2275 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 71:
#line 678 "/root/compiler/src/sysy.y"
                  {
    auto unary_exp = new UnaryExpAST();
    unary_exp->is_call = true;
    unary_exp->ident = *unique_ptr<string>((yyvsp[-2].str_val));
    (yyval.ast_val) = unary_exp;
  }
#line 2286 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 72:
#line 687 "/root/compiler/src/sysy.y"
                                 {
    auto unary_exp = new UnaryExpAST();
    unary_exp->is_call = true;
    unary_exp->ident = *unique_ptr<string>((yyvsp[-3].str_val));
    unary_exp->func_params.reset((FuncCallParamsAST *)(yyvsp[-1].ast_val));
    (yyval.ast_val) = unary_exp;
  }
#line 2298 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 73:
#line 697 "/root/compiler/src/sysy.y"
        {
    auto params = new FuncCallParamsAST();
    params->exps.emplace_back((ExpAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = params;
  }
#line 2308 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 74:
#line 705 "/root/compiler/src/sysy.y"
                           {
    auto params = new FuncCallParamsAST();
    params->exps.emplace_back((ExpAST *)(yyvsp[-2].ast_val));
    auto p2 = unique_ptr<FuncCallParamsAST>((FuncCallParamsAST *)(yyvsp[0].ast_val));
    int n = p2->exps.size();
    for(int i = 0; i < n; ++i){
        params->exps.emplace_back(p2->exps[i].release());
    }
    (yyval.ast_val) = params;
  }
#line 2323 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 75:
#line 718 "/root/compiler/src/sysy.y"
               {
    auto primaryexp_ast=new PrimaryExpAST();
    primaryexp_ast->type = "exp";
    primaryexp_ast->exp = unique_ptr<ExpAST>((ExpAST*)(yyvsp[-1].ast_val));
    (yyval.ast_val) = primaryexp_ast;
  }
#line 2334 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 76:
#line 727 "/root/compiler/src/sysy.y"
           {
    auto primaryexp_ast=new PrimaryExpAST();
    primaryexp_ast->type = "number";
    primaryexp_ast->number = (yyvsp[0].int_val);
    (yyval.ast_val) = primaryexp_ast;
  }
#line 2345 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 77:
#line 736 "/root/compiler/src/sysy.y"
         {
    auto primary_exp = new PrimaryExpAST();
    primary_exp->type = "lval";
    primary_exp->lval =  unique_ptr<LValAST>((LValAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = primary_exp;
  }
#line 2356 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 78:
#line 746 "/root/compiler/src/sysy.y"
            {
    auto multi_exp = new MultiExpAST();
    multi_exp->HasOp = false;
    multi_exp->unary_exp = unique_ptr<UnaryExpAST>((UnaryExpAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = multi_exp;
  }
#line 2367 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 79:
#line 755 "/root/compiler/src/sysy.y"
                                   {
    auto multi_exp = new MultiExpAST();
    multi_exp->HasOp = true;
    multi_exp->multi_exp = unique_ptr<MultiExpAST>((MultiExpAST *)(yyvsp[-2].ast_val));
    multi_exp->unary_exp = unique_ptr<UnaryExpAST>((UnaryExpAST *)(yyvsp[0].ast_val));
    multi_exp->multi_op = (yyvsp[-1].char_val);
    (yyval.ast_val) = multi_exp;
  }
#line 2380 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 80:
#line 766 "/root/compiler/src/sysy.y"
             {
    auto add_exp = new AddExpAST();
    add_exp->HasOp = false;
    add_exp->multi_exp = unique_ptr<MultiExpAST>((MultiExpAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = add_exp;
  }
#line 2391 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 81:
#line 775 "/root/compiler/src/sysy.y"
                                {
    auto add_exp = new AddExpAST();
    add_exp->HasOp = true;
    add_exp->add_exp = unique_ptr<AddExpAST>((AddExpAST *)(yyvsp[-2].ast_val));
    add_exp->multi_exp = unique_ptr<MultiExpAST>((MultiExpAST *)(yyvsp[0].ast_val));
    add_exp->add_op = (yyvsp[-1].char_val);
    (yyval.ast_val) = add_exp;
  }
#line 2404 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 82:
#line 786 "/root/compiler/src/sysy.y"
          {
    auto rel_exp = new RelExpAST();
    rel_exp->HasOp = false;
    rel_exp->add_exp = unique_ptr<AddExpAST>((AddExpAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = rel_exp;
  }
#line 2415 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 83:
#line 795 "/root/compiler/src/sysy.y"
                             {
    auto rel_exp = new RelExpAST();
    rel_exp->HasOp = true;
    rel_exp->rel_exp = unique_ptr<RelExpAST>((RelExpAST *)(yyvsp[-2].ast_val));
    rel_exp->add_exp = unique_ptr<AddExpAST>((AddExpAST *)(yyvsp[0].ast_val));
    rel_exp->rel_op[0] = (yyvsp[-1].char_val);
    rel_exp->rel_op[1] = 0;
    (yyval.ast_val) = rel_exp;
  }
#line 2429 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 84:
#line 807 "/root/compiler/src/sysy.y"
                         {
    auto rel_exp = new RelExpAST();
    rel_exp->HasOp = true;
    rel_exp->rel_exp = unique_ptr<RelExpAST>((RelExpAST *)(yyvsp[-2].ast_val));
    rel_exp->add_exp = unique_ptr<AddExpAST>((AddExpAST *)(yyvsp[0].ast_val));
    rel_exp->rel_op[0] = '<';
    rel_exp->rel_op[1] = '=';
    (yyval.ast_val) = rel_exp;
  }
#line 2443 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 85:
#line 819 "/root/compiler/src/sysy.y"
                          {
    auto rel_exp = new RelExpAST();
    rel_exp->HasOp = true;
    rel_exp->rel_exp = unique_ptr<RelExpAST>((RelExpAST *)(yyvsp[-2].ast_val));
    rel_exp->add_exp = unique_ptr<AddExpAST>((AddExpAST *)(yyvsp[0].ast_val));
    rel_exp->rel_op[0] = '>';
    rel_exp->rel_op[1] = '=';
    (yyval.ast_val) = rel_exp;
  }
#line 2457 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 86:
#line 831 "/root/compiler/src/sysy.y"
          {
    auto eq_exp = new EqExpAST();
    eq_exp->HasOp = false;
    eq_exp->rel_exp = unique_ptr<RelExpAST>((RelExpAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = eq_exp;
  }
#line 2468 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 87:
#line 840 "/root/compiler/src/sysy.y"
                      {
    auto eq_exp = new EqExpAST();
    eq_exp->HasOp = true;
    eq_exp->eq_exp = unique_ptr<EqExpAST>((EqExpAST *)(yyvsp[-2].ast_val));
    eq_exp->rel_exp = unique_ptr<RelExpAST>((RelExpAST *)(yyvsp[0].ast_val));
    eq_exp->eq_op[0] = '=';
    eq_exp->eq_op[1] = '=';
    (yyval.ast_val) = eq_exp;
  }
#line 2482 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 88:
#line 852 "/root/compiler/src/sysy.y"
                          {
    auto eq_exp = new EqExpAST();
    eq_exp->HasOp = true;
    eq_exp->eq_exp = unique_ptr<EqExpAST>((EqExpAST *)(yyvsp[-2].ast_val));
    eq_exp->rel_exp = unique_ptr<RelExpAST>((RelExpAST *)(yyvsp[0].ast_val));
    eq_exp->eq_op[0] = '!';
    eq_exp->eq_op[1] = '=';
    (yyval.ast_val) = eq_exp;
  }
#line 2496 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 89:
#line 864 "/root/compiler/src/sysy.y"
          {
    auto l_and_exp = new LAndExpAST();
    l_and_exp->HasOp = false;
    l_and_exp->eq_exp = unique_ptr<EqExpAST>((EqExpAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = l_and_exp;
  }
#line 2507 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 90:
#line 873 "/root/compiler/src/sysy.y"
                     {
    auto l_and_exp = new LAndExpAST();
    l_and_exp->HasOp = true;
    l_and_exp->l_and_exp = unique_ptr<LAndExpAST>((LAndExpAST *)(yyvsp[-2].ast_val));
    l_and_exp->eq_exp = unique_ptr<EqExpAST>((EqExpAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = l_and_exp;
  }
#line 2519 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 91:
#line 883 "/root/compiler/src/sysy.y"
            {
    auto l_or_exp = new LOrExpAST();
    l_or_exp->HasOp = false;
    l_or_exp->l_and_exp = unique_ptr<LAndExpAST>((LAndExpAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = l_or_exp;
  }
#line 2530 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 92:
#line 892 "/root/compiler/src/sysy.y"
                      {
    auto l_or_exp = new LOrExpAST();
    l_or_exp->HasOp = true;
    l_or_exp->l_or_exp = unique_ptr<LOrExpAST>((LOrExpAST *)(yyvsp[-2].ast_val));
    l_or_exp->l_and_exp = unique_ptr<LAndExpAST>((LAndExpAST *)(yyvsp[0].ast_val));
    (yyval.ast_val) = l_or_exp;
  }
#line 2542 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 93:
#line 902 "/root/compiler/src/sysy.y"
              {
    (yyval.int_val) = (yyvsp[0].int_val);
  }
#line 2550 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 94:
#line 908 "/root/compiler/src/sysy.y"
        {
    (yyval.char_val) = '+';
  }
#line 2558 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 95:
#line 914 "/root/compiler/src/sysy.y"
        {
    (yyval.char_val) = '-';
  }
#line 2566 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 96:
#line 920 "/root/compiler/src/sysy.y"
        {
    (yyval.char_val) = '!';
  }
#line 2574 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 97:
#line 926 "/root/compiler/src/sysy.y"
       {
    (yyval.char_val) = '+';
  }
#line 2582 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 98:
#line 932 "/root/compiler/src/sysy.y"
       {
    (yyval.char_val) = '-';
  }
#line 2590 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 99:
#line 938 "/root/compiler/src/sysy.y"
       {
    (yyval.char_val) = '*';
  }
#line 2598 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 100:
#line 944 "/root/compiler/src/sysy.y"
       {
    (yyval.char_val) = '/';
  }
#line 2606 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 101:
#line 950 "/root/compiler/src/sysy.y"
       {
    (yyval.char_val) = '%';
  }
#line 2614 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 102:
#line 956 "/root/compiler/src/sysy.y"
       {
    (yyval.char_val) = '<';
  }
#line 2622 "/root/compiler/build/sysy.tab.cpp"
    break;

  case 103:
#line 962 "/root/compiler/src/sysy.y"
       {
    (yyval.char_val) = '>';
  }
#line 2630 "/root/compiler/build/sysy.tab.cpp"
    break;


#line 2634 "/root/compiler/build/sysy.tab.cpp"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
      yyerror (ast, YY_("syntax error"));
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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
        yyerror (ast, yymsgp);
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
                      yytoken, &yylval, ast);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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
                  yystos[yystate], yyvsp, ast);
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
  yyerror (ast, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, ast);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, ast);
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
#line 969 "/root/compiler/src/sysy.y"


// 定义错误处理函数, 其中第二个参数是错误信息
// parser 如果发生错误 (例如输入的程序出现了语法错误), 就会调用这个函数
// void yyerror(unique_ptr<BaseAST> &ast, const char *s) {
//     extern int yylineno;    // defined and maintained in lex
//     extern char *yytext;    // defined and maintained in lex
//     int len= strlen(yytext);
//     int i;
//     char buf[512]={0};
//     for (i=0;i<len;++i)
//     {
//         sprintf(buf,"%s%d ",buf,yytext[i]);
//     }
//     fprintf(stderr, "ERROR: %s at symbol '%s' on line %d\n", s, buf, yylineno);
// }
void yyerror(unique_ptr<BaseAST> &ast, const char *s) {
  cerr << "error: " << s << endl;
}
