/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "miniC.y"

#include "listaSimbolos.h"
#include <stdio.h>
#include "listaCodigo.h"

Lista lista;
int contCadenas = 0;
Tipo tipo;
void yyerror();
extern int yylex();
extern int yylineno;
extern int numErroresLex;
int numErroresSem = 0;
int numErroresSint = 0;
int cont = 1;

#line 88 "miniC.tab.c"

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

#include "miniC.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_EMPIEZA = 3,                    /* EMPIEZA  */
  YYSYMBOL_LEER = 4,                       /* LEER  */
  YYSYMBOL_ESCRIBIR = 5,                   /* ESCRIBIR  */
  YYSYMBOL_A_PAREN = 6,                    /* A_PAREN  */
  YYSYMBOL_C_PAREN = 7,                    /* C_PAREN  */
  YYSYMBOL_SEMICOLON = 8,                  /* SEMICOLON  */
  YYSYMBOL_COMA = 9,                       /* COMA  */
  YYSYMBOL_ASIG_OP = 10,                   /* ASIG_OP  */
  YYSYMBOL_MAS_OP = 11,                    /* MAS_OP  */
  YYSYMBOL_MENOS_OP = 12,                  /* MENOS_OP  */
  YYSYMBOL_A_LLAVE = 13,                   /* A_LLAVE  */
  YYSYMBOL_C_LLAVE = 14,                   /* C_LLAVE  */
  YYSYMBOL_VAR = 15,                       /* VAR  */
  YYSYMBOL_CONST = 16,                     /* CONST  */
  YYSYMBOL_SI = 17,                        /* SI  */
  YYSYMBOL_SINO = 18,                      /* SINO  */
  YYSYMBOL_MIENTRAS = 19,                  /* MIENTRAS  */
  YYSYMBOL_POR_OP = 20,                    /* POR_OP  */
  YYSYMBOL_DIV_OP = 21,                    /* DIV_OP  */
  YYSYMBOL_REAL = 22,                      /* REAL  */
  YYSYMBOL_STRING = 23,                    /* STRING  */
  YYSYMBOL_ID = 24,                        /* ID  */
  YYSYMBOL_NUM = 25,                       /* NUM  */
  YYSYMBOL_UMENOS = 26,                    /* UMENOS  */
  YYSYMBOL_YYACCEPT = 27,                  /* $accept  */
  YYSYMBOL_program = 28,                   /* program  */
  YYSYMBOL_29_1 = 29,                      /* $@1  */
  YYSYMBOL_declarations = 30,              /* declarations  */
  YYSYMBOL_31_2 = 31,                      /* $@2  */
  YYSYMBOL_32_3 = 32,                      /* $@3  */
  YYSYMBOL_identifier_list = 33,           /* identifier_list  */
  YYSYMBOL_asig = 34,                      /* asig  */
  YYSYMBOL_statement_list = 35,            /* statement_list  */
  YYSYMBOL_statement = 36,                 /* statement  */
  YYSYMBOL_print_list = 37,                /* print_list  */
  YYSYMBOL_print_item = 38,                /* print_item  */
  YYSYMBOL_read_list = 39,                 /* read_list  */
  YYSYMBOL_expression = 40                 /* expression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   100

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  36
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  77

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   281


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    40,    40,    40,    58,    58,    62,    62,    66,    69,
      70,    76,    79,    94,    98,   102,   118,   119,   170,   195,
     246,   247,   248,   251,   252,   258,   284,   318,   346,   376,
     387,   398,   409,   420,   428,   429,   439
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "EMPIEZA", "LEER",
  "ESCRIBIR", "A_PAREN", "C_PAREN", "SEMICOLON", "COMA", "ASIG_OP",
  "MAS_OP", "MENOS_OP", "A_LLAVE", "C_LLAVE", "VAR", "CONST", "SI", "SINO",
  "MIENTRAS", "POR_OP", "DIV_OP", "REAL", "STRING", "ID", "NUM", "UMENOS",
  "$accept", "program", "$@1", "declarations", "$@2", "$@3",
  "identifier_list", "asig", "statement_list", "statement", "print_list",
  "print_item", "read_list", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-32)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -32,    13,    -1,   -32,   -16,    28,    35,    33,   -32,   -11,
     -32,   -32,     2,    12,    12,    41,    27,    29,   -32,   -32,
      78,    79,    45,   -32,    76,     9,   -32,    49,   -32,   -32,
      60,     8,     8,   -32,   -32,   -32,    62,   -32,    17,    26,
       8,     8,     8,     8,   -32,    12,   -32,   -32,    63,    52,
     -32,   -32,    29,     8,     8,     8,     8,   -32,    54,    69,
      71,    17,   -32,   -32,   -32,   -32,    57,    57,   -32,   -32,
      43,    43,   -32,    70,   -32,    43,   -32
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,     0,     8,    14,
       4,     6,     0,     0,     0,     0,     0,     0,    14,     3,
       0,     0,     0,    13,    11,     0,     9,     0,    22,    27,
       0,     0,     0,    26,    35,    36,     0,    23,    25,     0,
       0,     0,     0,     0,     5,     0,     7,    21,     0,     0,
      33,    20,     0,     0,     0,     0,     0,    16,     0,     0,
       0,    12,    10,    28,    34,    24,    29,    30,    31,    32,
       0,     0,    15,    18,    19,     0,    17
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -32,   -32,   -32,   -32,   -32,   -32,    81,    51,    82,    23,
     -32,    47,   -32,   -31
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     9,    13,    14,    25,    26,    12,    23,
      36,    37,    30,    38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      49,    50,     4,    15,    10,    11,    16,    17,     5,    58,
      59,    60,    61,     3,    31,    18,    19,    44,    45,    20,
      32,    21,    66,    67,    68,    69,    22,    15,    53,    54,
      16,    17,    34,    35,     6,    31,    24,    55,    56,    18,
      57,    32,     7,    20,    15,    21,     8,    16,    17,    28,
      22,    29,    33,    34,    35,    42,    18,    46,    45,    64,
      20,    70,    21,    53,    54,    53,    54,    22,    47,    48,
      51,    52,    55,    56,    55,    56,    71,    55,    56,    72,
      53,    54,    53,    54,    40,    41,    43,    63,    75,    55,
      56,    55,    56,    73,    74,    27,    62,     0,    76,    65,
      39
};

static const yytype_int8 yycheck[] =
{
      31,    32,     3,     1,    15,    16,     4,     5,    24,    40,
      41,    42,    43,     0,     6,    13,    14,     8,     9,    17,
      12,    19,    53,    54,    55,    56,    24,     1,    11,    12,
       4,     5,    24,    25,     6,     6,    24,    20,    21,    13,
      14,    12,     7,    17,     1,    19,    13,     4,     5,     8,
      24,    24,    23,    24,    25,    10,    13,     8,     9,     7,
      17,     7,    19,    11,    12,    11,    12,    24,     8,     9,
       8,     9,    20,    21,    20,    21,     7,    20,    21,     8,
      11,    12,    11,    12,     6,     6,    10,    24,    18,    20,
      21,    20,    21,    70,    71,    14,    45,    -1,    75,    52,
      18
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    28,    29,     0,     3,    24,     6,     7,    13,    30,
      15,    16,    35,    31,    32,     1,     4,     5,    13,    14,
      17,    19,    24,    36,    24,    33,    34,    33,     8,    24,
      39,     6,    12,    23,    24,    25,    37,    38,    40,    35,
       6,     6,    10,    10,     8,     9,     8,     8,     9,    40,
      40,     8,     9,    11,    12,    20,    21,    14,    40,    40,
      40,    40,    34,    24,     7,    38,    40,    40,    40,    40,
       7,     7,     8,    36,    36,    18,    36
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    27,    29,    28,    31,    30,    32,    30,    30,    33,
      33,    34,    34,    35,    35,    36,    36,    36,    36,    36,
      36,    36,    36,    37,    37,    38,    38,    39,    39,    40,
      40,    40,    40,    40,    40,    40,    40
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     9,     0,     5,     0,     5,     0,     1,
       3,     1,     3,     2,     0,     4,     3,     7,     5,     5,
       3,     3,     2,     1,     3,     1,     1,     1,     3,     3,
       3,     3,     3,     2,     3,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* $@1: %empty  */
#line 40 "miniC.y"
                   {lista=creaLS(); iniReg();}
#line 1161 "miniC.tab.c"
    break;

  case 3: /* program: $@1 EMPIEZA ID A_PAREN C_PAREN A_LLAVE declarations statement_list C_LLAVE  */
#line 40 "miniC.y"
                                                                                                                      {
					if (numErroresLex + numErroresSint + numErroresSem == 0) { // Generamos el código
						imprimirTablaS(lista);
						concatenaLC((yyvsp[-2].codigo), (yyvsp[-1].codigo));
						liberaLC((yyvsp[-1].codigo));
						imprimirListaC((yyvsp[-2].codigo));
					}
					else {
						printf("----------------------\n");
						printf("Errores lexicos: %d\n",numErroresLex);
						printf("Errores sintacticos: %d\n",numErroresSint);
						printf("Errores semanticos: %d\n",numErroresSem);
					}
					/* Liberar memoria de tabla de símbolos y lista de código */
					liberaLS(lista);
					liberaLC((yyvsp[-2].codigo)); }
#line 1182 "miniC.tab.c"
    break;

  case 4: /* $@2: %empty  */
#line 58 "miniC.y"
                                   {tipo = VARIABLE;}
#line 1188 "miniC.tab.c"
    break;

  case 5: /* declarations: declarations VAR $@2 identifier_list SEMICOLON  */
#line 58 "miniC.y"
                                                                                {
					(yyval.codigo)=(yyvsp[-4].codigo);
                    concatenaLC((yyval.codigo),(yyvsp[-1].codigo));
                    liberaLC((yyvsp[-1].codigo)); }
#line 1197 "miniC.tab.c"
    break;

  case 6: /* $@3: %empty  */
#line 62 "miniC.y"
                                     {tipo = CONSTANTE;}
#line 1203 "miniC.tab.c"
    break;

  case 7: /* declarations: declarations CONST $@3 identifier_list SEMICOLON  */
#line 62 "miniC.y"
                                                                                   {
			(yyval.codigo)=(yyvsp[-4].codigo);
			concatenaLC((yyval.codigo),(yyvsp[-1].codigo));
			liberaLC((yyvsp[-1].codigo)); }
#line 1212 "miniC.tab.c"
    break;

  case 8: /* declarations: %empty  */
#line 66 "miniC.y"
                          {(yyval.codigo) = creaLC();}
#line 1218 "miniC.tab.c"
    break;

  case 9: /* identifier_list: asig  */
#line 69 "miniC.y"
                       { (yyval.codigo) = (yyvsp[0].codigo); }
#line 1224 "miniC.tab.c"
    break;

  case 10: /* identifier_list: identifier_list COMA asig  */
#line 70 "miniC.y"
                                            {
			(yyval.codigo)=(yyvsp[-2].codigo);
			concatenaLC((yyval.codigo),(yyvsp[0].codigo));
			liberaLC((yyvsp[0].codigo)); }
#line 1233 "miniC.tab.c"
    break;

  case 11: /* asig: ID  */
#line 76 "miniC.y"
                     {if (!perteneceTablaS(lista, (yyvsp[0].lexema))) anyadeEntrada(lista, (yyvsp[0].lexema), tipo);
 			else { printf("Variable %s ya declarada \n",(yyvsp[0].lexema)); numErroresSem++;}
 			(yyval.codigo)=creaLC();}
#line 1241 "miniC.tab.c"
    break;

  case 12: /* asig: ID ASIG_OP expression  */
#line 79 "miniC.y"
                                        { if (!perteneceTablaS(lista, (yyvsp[-2].lexema))) anyadeEntrada(lista, (yyvsp[-2].lexema), tipo);
 						else { printf("Variable %s ya declarada \n",(yyvsp[-2].lexema)); numErroresSem++;}
 						(yyval.codigo)=(yyvsp[0].codigo);

						Operacion aux;
						aux.op="sw";
						aux.res=recuperaResLC((yyvsp[0].codigo));
						aux.arg1=concatena("_",(yyvsp[-2].lexema));
						aux.arg2=NULL;

						//Insertamos codigo
						insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);
						liberarReg(aux.res);}
#line 1259 "miniC.tab.c"
    break;

  case 13: /* statement_list: statement_list statement  */
#line 94 "miniC.y"
                                           {
					(yyval.codigo)=(yyvsp[-1].codigo);
                    concatenaLC((yyval.codigo),(yyvsp[0].codigo));
                    liberaLC((yyvsp[0].codigo)); }
#line 1268 "miniC.tab.c"
    break;

  case 14: /* statement_list: %empty  */
#line 98 "miniC.y"
                                        {
                    (yyval.codigo)=creaLC(); }
#line 1275 "miniC.tab.c"
    break;

  case 15: /* statement: ID ASIG_OP expression SEMICOLON  */
#line 103 "miniC.y"
                                                        {if (!perteneceTablaS(lista, (yyvsp[-3].lexema))) {
 							printf("Variable %s no declarada \n",(yyvsp[-3].lexema)); numErroresSem++;}
							else if (esConstante(lista, (yyvsp[-3].lexema))) {
 							printf("Asignación a constante\n"); numErroresSem++;}
								(yyval.codigo)=(yyvsp[-1].codigo);
								Operacion aux;
								aux.op="sw";
								aux.res=recuperaResLC((yyvsp[-1].codigo));
								aux.arg1=concatena("_",(yyvsp[-3].lexema));
								aux.arg2=NULL;

								//Insertamos codigo
								insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);
								liberarReg(aux.res);}
#line 1294 "miniC.tab.c"
    break;

  case 16: /* statement: A_LLAVE statement_list C_LLAVE  */
#line 118 "miniC.y"
                                                 { (yyval.codigo) = (yyvsp[-1].codigo); }
#line 1300 "miniC.tab.c"
    break;

  case 17: /* statement: SI A_PAREN expression C_PAREN statement SINO statement  */
#line 119 "miniC.y"
                                                                         {
			(yyval.codigo)=(yyvsp[-4].codigo);
			//Etiqueta 1
			char * etiq1=nuevaEtiqueta();
			Operacion aux;
			aux.op="beqz";
			aux.res=recuperaResLC((yyvsp[-4].codigo));
			aux.arg1=etiq1;
			aux.arg2=NULL;

			//Insertamos codigo
			insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);

			//Añadir codigo statement
			concatenaLC((yyval.codigo),(yyvsp[-2].codigo));

			//liberamos temporal
			liberarReg(aux.res);
			liberaLC((yyvsp[-2].codigo));

			char * etiq2=nuevaEtiqueta();
			aux.op="b";
			aux.res=etiq2;
			aux.arg1=NULL;
			aux.arg2=NULL;

			//Insertamos codigo
			insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);

			//añadir etiqueta 1
			aux.op=concatena(etiq1,":");
			aux.res=NULL;
			aux.arg1=NULL;
			aux.arg2=NULL;

			//Insertamos codigo
			insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);

			//Añadimos codigo statement 2
			concatenaLC((yyval.codigo),(yyvsp[0].codigo));

			liberaLC((yyvsp[0].codigo));

			//Añadir etiqueta 2
			aux.op=concatena(etiq2,":");
			aux.res=NULL;
			aux.arg1=NULL;
			aux.arg2=NULL;

			//Insertamos codigo
			insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux); }
#line 1356 "miniC.tab.c"
    break;

  case 18: /* statement: SI A_PAREN expression C_PAREN statement  */
#line 170 "miniC.y"
                                                          {
			(yyval.codigo)=(yyvsp[-2].codigo);
			char * etiq=nuevaEtiqueta();

			Operacion aux;
			aux.op="beqz";
			aux.res=recuperaResLC((yyvsp[-2].codigo));
			aux.arg1=etiq;
			aux.arg2=NULL;

			//Insertamos codigo
			insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);

			liberarReg(aux.res);
			//Añadir statement
			concatenaLC((yyval.codigo),(yyvsp[0].codigo));

			//Añadir etiqueta
			aux.op=concatena(etiq,":");
			aux.res=NULL;
			aux.arg1=NULL;
			aux.arg2=NULL;

			//Insertar codigo
			insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux); }
#line 1386 "miniC.tab.c"
    break;

  case 19: /* statement: MIENTRAS A_PAREN expression C_PAREN statement  */
#line 195 "miniC.y"
                                                                {
			char * etiq1=nuevaEtiqueta();
			char * etiq2=nuevaEtiqueta();

			(yyval.codigo)=creaLC();

			//Añadir etiqueta 1
			Operacion aux;
			aux.op=concatena(etiq1,":");
			aux.res=NULL;
			aux.arg1=NULL;
			aux.arg2=NULL;

			insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);

			concatenaLC((yyval.codigo),(yyvsp[-2].codigo));

			aux.op="beqz";
			aux.res=recuperaResLC((yyvsp[-2].codigo));
			aux.arg1=etiq2;
			aux.arg2=NULL;

			//Liberar lc
			liberaLC((yyvsp[-2].codigo));

			//Insertar codigo
			insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);

			liberarReg(aux.res);

			//Añadir statement
			concatenaLC((yyval.codigo),(yyvsp[0].codigo));

			//Liberar codigo
			liberaLC((yyvsp[0].codigo));

			//Añadir salto a etiqueta 1
			aux.op="b";
			aux.res=etiq1;
			aux.arg1=NULL;
			aux.arg2=NULL;

			//Insertar codigo
			insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);

			//Añadir etiqueta 2
			aux.op=concatena(etiq2,":");
			aux.res=NULL;
			aux.arg1=NULL;
			aux.arg2=NULL;
			insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux); }
#line 1442 "miniC.tab.c"
    break;

  case 20: /* statement: ESCRIBIR print_list SEMICOLON  */
#line 246 "miniC.y"
                                                { (yyval.codigo) = (yyvsp[-1].codigo); }
#line 1448 "miniC.tab.c"
    break;

  case 21: /* statement: LEER read_list SEMICOLON  */
#line 247 "miniC.y"
                                           { (yyval.codigo) = (yyvsp[-1].codigo); }
#line 1454 "miniC.tab.c"
    break;

  case 22: /* statement: error SEMICOLON  */
#line 248 "miniC.y"
                                  { (yyval.codigo) = creaLC(); }
#line 1460 "miniC.tab.c"
    break;

  case 23: /* print_list: print_item  */
#line 251 "miniC.y"
                             { (yyval.codigo) = (yyvsp[0].codigo); }
#line 1466 "miniC.tab.c"
    break;

  case 24: /* print_list: print_list COMA print_item  */
#line 252 "miniC.y"
                                             {
			(yyval.codigo)=(yyvsp[-2].codigo);
			concatenaLC((yyval.codigo),(yyvsp[0].codigo));
			liberaLC((yyvsp[0].codigo)); }
#line 1475 "miniC.tab.c"
    break;

  case 25: /* print_item: expression  */
#line 258 "miniC.y"
                             {
				(yyval.codigo)=(yyvsp[0].codigo);
				Operacion aux;
				aux.op="li";
				aux.res="$v0";
				aux.arg1="1";
				aux.arg2=NULL;

				//Insertamos codigo
				insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);
				aux.op="move";
				aux.res="$a0";
				aux.arg1=recuperaResLC((yyvsp[0].codigo));
				aux.arg2=NULL;

				//Insertamos codigo
				insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);

				liberarReg(aux.arg1);

				aux.op="syscall";
				aux.res=NULL;
				aux.arg1=NULL;
				aux.arg2=NULL;
				//Insertamos el codigo en la lista
				insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux); }
#line 1506 "miniC.tab.c"
    break;

  case 26: /* print_item: STRING  */
#line 284 "miniC.y"
                         {anyadeEntrada(lista, (yyvsp[0].lexema), CADENA);contCadenas++;

					int numCadena = anyadeCadena((yyvsp[0].lexema));

					(yyval.codigo)=creaLC();

                    Operacion aux;
                    aux.op="li";
                    aux.res="$v0";
                    aux.arg1="4";
                    aux.arg2=NULL;

                    //Insertar codigo
                    insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);

                    aux.op="la";
                    aux.res="$a0";

                    //Para hacer cadena que indica cadenas hay que hacer $str (4) + 000(3) + 0(1)=\0
                    char * cadena = (char *) malloc(4+3+1);
                    sprintf(cadena, "$str%d", numCadena);
                    aux.arg1 = cadena;
                    aux.arg2 = NULL;
                    //Insertamos el codigo en la lista
                    insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);
                    //syscall
                    aux.op="syscall";
                    aux.res=NULL;
                    aux.arg1=NULL;
                    aux.arg2=NULL;
                    //Insertamos el codigo en la lista
                    insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);}
#line 1543 "miniC.tab.c"
    break;

  case 27: /* read_list: ID  */
#line 318 "miniC.y"
                     {if (!perteneceTablaS(lista, (yyvsp[0].lexema))) { printf("Variable %s no declarada \n",(yyvsp[0].lexema)); numErroresSem++;}
 		     else if (esConstante(lista, (yyvsp[0].lexema))) { printf("Asignación a constante\n"); numErroresSem++;}
                    (yyval.codigo)=creaLC();

                    Operacion aux;
                    aux.op="li";
                    aux.res="$v0";
                    aux.arg1="5";
                    aux.arg2=NULL;

                    //Insertar codigo
                    insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);

                    aux.op="syscall";
                    aux.res=NULL;
                    aux.arg1=NULL;
                    aux.arg2=NULL;

                    //Insertar codigo
                    insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);

                    aux.op="sw";
                    aux.res="$v0";
                    aux.arg1=concatena("_",(yyvsp[0].lexema));
                    aux.arg2=NULL;

                    //Insertar codigo
                    insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux); }
#line 1576 "miniC.tab.c"
    break;

  case 28: /* read_list: read_list COMA ID  */
#line 346 "miniC.y"
                                    {if (!perteneceTablaS(lista, (yyvsp[0].lexema))) { printf("Variable %s no declarada \n",(yyvsp[0].lexema)); numErroresSem++; }
				    else if (esConstante(lista, (yyvsp[0].lexema))) { printf("Asignación a constante\n"); numErroresSem++;}
						(yyval.codigo)=(yyvsp[-2].codigo);

						Operacion aux;
						aux.op="li";
						aux.res="$v0";
						aux.arg1="5";
						aux.arg2=NULL;

						//Insertar codigo
						insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);

						aux.op="syscall";
						aux.res=NULL;
						aux.arg1=NULL;
						aux.arg2=NULL;

						//Insertar codigo
						insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux);

						aux.op="sw";
						aux.res="$v0";
						aux.arg1=concatena("_",(yyvsp[0].lexema));
						aux.arg2=NULL;

						//Insertar codigo
						insertaLC((yyval.codigo),finalLC((yyval.codigo)),aux); }
#line 1609 "miniC.tab.c"
    break;

  case 29: /* expression: expression MAS_OP expression  */
#line 376 "miniC.y"
                                               {
							(yyval.codigo)=(yyvsp[-2].codigo);
							concatenaLC((yyval.codigo),(yyvsp[0].codigo));
							Operacion oper;
							oper.op = "add";
							oper.res = recuperaResLC((yyvsp[-2].codigo));
							oper.arg1 = recuperaResLC((yyvsp[-2].codigo));
							oper.arg2 = recuperaResLC((yyvsp[0].codigo));
							insertaLC((yyval.codigo),finalLC((yyval.codigo)),oper);
							liberaLC((yyvsp[0].codigo));
							liberarReg(oper.arg2); }
#line 1625 "miniC.tab.c"
    break;

  case 30: /* expression: expression MENOS_OP expression  */
#line 387 "miniC.y"
                                                 {
							(yyval.codigo) = (yyvsp[-2].codigo);
							concatenaLC((yyval.codigo),(yyvsp[0].codigo));
							Operacion oper;
							oper.op = "sub";
							oper.res = recuperaResLC((yyvsp[-2].codigo));
							oper.arg1 = recuperaResLC((yyvsp[-2].codigo));
							oper.arg2 = recuperaResLC((yyvsp[0].codigo));
							insertaLC((yyval.codigo),finalLC((yyval.codigo)),oper);
							liberaLC((yyvsp[0].codigo));
							liberarReg(oper.arg2); }
#line 1641 "miniC.tab.c"
    break;

  case 31: /* expression: expression POR_OP expression  */
#line 398 "miniC.y"
                                               {
							(yyval.codigo) = (yyvsp[-2].codigo);
							concatenaLC((yyval.codigo),(yyvsp[0].codigo));
							Operacion oper;
							oper.op = "mul";
							oper.res = recuperaResLC((yyvsp[-2].codigo));
							oper.arg1 = recuperaResLC((yyvsp[-2].codigo));
							oper.arg2 = recuperaResLC((yyvsp[0].codigo));
							insertaLC((yyval.codigo),finalLC((yyval.codigo)),oper);
							liberaLC((yyvsp[0].codigo));
							liberarReg(oper.arg2); }
#line 1657 "miniC.tab.c"
    break;

  case 32: /* expression: expression DIV_OP expression  */
#line 409 "miniC.y"
                                               {
							(yyval.codigo) = (yyvsp[-2].codigo);
							concatenaLC((yyval.codigo),(yyvsp[0].codigo));
							Operacion oper;
							oper.op = "div";
							oper.res = recuperaResLC((yyvsp[-2].codigo));
							oper.arg1 = recuperaResLC((yyvsp[-2].codigo));
							oper.arg2 = recuperaResLC((yyvsp[0].codigo));
							insertaLC((yyval.codigo),finalLC((yyval.codigo)),oper);
							liberaLC((yyvsp[0].codigo));
							liberarReg(oper.arg2); }
#line 1673 "miniC.tab.c"
    break;

  case 33: /* expression: MENOS_OP expression  */
#line 420 "miniC.y"
                                                   {
							(yyval.codigo) = (yyvsp[0].codigo);
							Operacion oper;
							oper.op = "neg";
							oper.res = obtenerReg();
							oper.arg1 = recuperaResLC((yyvsp[0].codigo));
							oper.arg2 = NULL;
							insertaLC((yyval.codigo), finalLC((yyval.codigo)), oper); }
#line 1686 "miniC.tab.c"
    break;

  case 34: /* expression: A_PAREN expression C_PAREN  */
#line 428 "miniC.y"
                                             {(yyval.codigo) = (yyvsp[-1].codigo);}
#line 1692 "miniC.tab.c"
    break;

  case 35: /* expression: ID  */
#line 429 "miniC.y"
                     {if (!perteneceTablaS(lista, (yyvsp[0].lexema))) printf("Variable %s no declarada \n",(yyvsp[0].lexema));
			(yyval.codigo) = creaLC();
 			Operacion oper;
 			oper.op = "lw";
 			oper.res = obtenerReg();
 			oper.arg1 = concatena("_",(yyvsp[0].lexema));
 			oper.arg2 = NULL;
 			insertaLC((yyval.codigo),finalLC((yyval.codigo)),oper);
 			guardaResLC((yyval.codigo),oper.res); }
#line 1706 "miniC.tab.c"
    break;

  case 36: /* expression: NUM  */
#line 439 "miniC.y"
                       { (yyval.codigo) = creaLC();
 			Operacion oper;
 			oper.op = "li";
 			oper.res = obtenerReg();
 			oper.arg1 = (yyvsp[0].lexema);
 			oper.arg2 = NULL;
 			insertaLC((yyval.codigo),finalLC((yyval.codigo)),oper);
 			guardaResLC((yyval.codigo),oper.res);  }
#line 1719 "miniC.tab.c"
    break;


#line 1723 "miniC.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 449 "miniC.y"


void yyerror()
{
	numErroresSint++;
	printf("Error sintactico en linea %d. \n",yylineno);
}

void imprimirCodigo(ListaC codigo) {
 PosicionListaC p = inicioLC(codigo);
 while (p != finalLC(codigo)) {
 	Operacion oper = recuperaLC(codigo,p);
 	printf("%s",oper.op);
 	if (oper.res) printf(" %s",oper.res);
 	if (oper.arg1) printf(",%s",oper.arg1);
 	if (oper.arg2) printf(",%s",oper.arg2);
 	printf("\n");
 	p = siguienteLC(codigo,p);
 }
}

int anyadeCadena(char * simbolo){
    Simbolo aux;
    aux.nombre=simbolo;
    aux.tipo=CADENA;
    aux.valor=contCadenas;

    insertaLS(lista,finalLS(lista),aux);
    return contCadenas;
}

