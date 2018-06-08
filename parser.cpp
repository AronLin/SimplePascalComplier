/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "pascal.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "AbstractTree.h"
#include "parser.hpp"



AbstractTree::Node* astRoot;
int yylex(void);
void yyerror(char const *str);

//abs chr odd ord pred sqr sqrt succ read write writeln



#line 85 "parser.cpp" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
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
    ASSIGN = 258,
    LP = 259,
    RP = 260,
    LB = 261,
    RB = 262,
    DOT = 263,
    COMMA = 264,
    COLON = 265,
    SEMI = 266,
    ARRAY = 267,
    _BEGIN = 268,
    SYS_TYPE = 269,
    CONST = 270,
    END = 271,
    FUNCTION = 272,
    PROGRAM = 273,
    PROCEDURE = 274,
    RECORD = 275,
    VAR = 276,
    ID = 277,
    TYPE = 278,
    EQUAL = 279,
    UNEQUAL = 280,
    GE = 281,
    GT = 282,
    LE = 283,
    LT = 284,
    AND = 285,
    OR = 286,
    NOT = 287,
    PLUS = 288,
    MINUS = 289,
    MUL = 290,
    DIV = 291,
    DIVI = 292,
    MOD = 293,
    INTEGER = 294,
    REAL = 295,
    CHAR = 296,
    STRING = 297,
    SYS_BOOL = 298,
    SYS_CON = 299,
    READ = 300,
    SYS_PROC = 301,
    SYS_FUNCT = 302,
    DOWNTO = 303,
    DO = 304,
    REPEAT = 305,
    TO = 306,
    THEN = 307,
    WHILE = 308,
    UNTIL = 309,
    FOR = 310,
    IF = 311,
    ELSE = 312,
    CASE = 313,
    OF = 314,
    GOTO = 315
  };
#endif
/* Tokens.  */
#define ASSIGN 258
#define LP 259
#define RP 260
#define LB 261
#define RB 262
#define DOT 263
#define COMMA 264
#define COLON 265
#define SEMI 266
#define ARRAY 267
#define _BEGIN 268
#define SYS_TYPE 269
#define CONST 270
#define END 271
#define FUNCTION 272
#define PROGRAM 273
#define PROCEDURE 274
#define RECORD 275
#define VAR 276
#define ID 277
#define TYPE 278
#define EQUAL 279
#define UNEQUAL 280
#define GE 281
#define GT 282
#define LE 283
#define LT 284
#define AND 285
#define OR 286
#define NOT 287
#define PLUS 288
#define MINUS 289
#define MUL 290
#define DIV 291
#define DIVI 292
#define MOD 293
#define INTEGER 294
#define REAL 295
#define CHAR 296
#define STRING 297
#define SYS_BOOL 298
#define SYS_CON 299
#define READ 300
#define SYS_PROC 301
#define SYS_FUNCT 302
#define DOWNTO 303
#define DO 304
#define REPEAT 305
#define TO 306
#define THEN 307
#define WHILE 308
#define UNTIL 309
#define FOR 310
#define IF 311
#define ELSE 312
#define CASE 313
#define OF 314
#define GOTO 315

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "pascal.y" /* yacc.c:355  */

    char*                             debug;
    AbstractTree::Node*               ast_Node; 
    AbstractTree::IdNode*             ast_Id;
    AbstractTree::ProgramNode*        ast_Program;
    AbstractTree::RoutineNode*        ast_Routine;
    AbstractTree::RoutineHeadNode*    ast_RoutineHead;
    AbstractTree::StmtNode*           ast_Stmt;
    AbstractTree::StmtListNode*       ast_StmtList;
    AbstractTree::ExpNode*            ast_Exp;
    AbstractTree::ExpListNode*        ast_ExpList;
    AbstractTree::VarDeclNode*        ast_VarDecl;
    AbstractTree::VarDeclListNode*    ast_VarDeclList;
    AbstractTree::TypeDeclNode*       ast_TypeDecl;
    AbstractTree::RoutineBodyNode*    ast_RoutineBody;
    AbstractTree::ConstValueNode*     ast_ConstValue;
    AbstractTree::IntegerTypeNode*    ast_IntegerType;
    AbstractTree::RealTypeNode*       ast_RealType;
    AbstractTree::CharTypeNode*       ast_CharType;
    AbstractTree::BooleanTypeNode*    ast_BooleanType;
    AbstractTree::AssignStmtNode*     ast_AssignStmt;
    AbstractTree::ProcStmtNode*       ast_ProcStmt;
    AbstractTree::SysProcStmtNode*    ast_SysProcStmt;
    AbstractTree::NameListNode*       ast_NameList;
#line 48 "pascal.y" /* yacc.c:355  */

    short int_value;//pascal 中int是2个字节,这里用short了
    float real_value;//用单精度实数
    char* string_value;
    char boolean_value;

#line 277 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 294 "parser.cpp" /* yacc.c:358  */

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   338

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  130
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  274

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   315

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
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    90,    90,    92,    92,    94,    96,    98,   101,   104,
     105,   108,   109,   112,   113,   114,   115,   116,   117,   120,
     121,   124,   125,   128,   131,   132,   133,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   148,   151,   154,
     155,   158,   161,   162,   165,   166,   169,   170,   173,   176,
     177,   178,   181,   184,   187,   190,   193,   194,   197,   198,
     201,   202,   205,   208,   212,   215,   218,   219,   222,   223,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     237,   238,   239,   242,   243,   244,   245,   246,   249,   252,
     253,   256,   259,   262,   265,   266,   269,   272,   273,   276,
     277,   280,   283,   284,   287,   288,   289,   290,   291,   292,
     293,   296,   297,   298,   299,   302,   303,   304,   305,   306,
     307,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ASSIGN", "LP", "RP", "LB", "RB", "DOT",
  "COMMA", "COLON", "SEMI", "ARRAY", "_BEGIN", "SYS_TYPE", "CONST", "END",
  "FUNCTION", "PROGRAM", "PROCEDURE", "RECORD", "VAR", "ID", "TYPE",
  "EQUAL", "UNEQUAL", "GE", "GT", "LE", "LT", "AND", "OR", "NOT", "PLUS",
  "MINUS", "MUL", "DIV", "DIVI", "MOD", "INTEGER", "REAL", "CHAR",
  "STRING", "SYS_BOOL", "SYS_CON", "READ", "SYS_PROC", "SYS_FUNCT",
  "DOWNTO", "DO", "REPEAT", "TO", "THEN", "WHILE", "UNTIL", "FOR", "IF",
  "ELSE", "CASE", "OF", "GOTO", "$accept", "program", "program_head",
  "routine", "sub_routine", "routine_head", "label_part", "const_part",
  "const_expr_list", "const_value", "type_part", "type_decl_list",
  "type_definition", "type_decl", "simple_type_decl", "array_type_decl",
  "record_type_decl", "field_decl_list", "field_decl", "name_list",
  "var_part", "var_decl_list", "var_decl", "routine_part", "function_decl",
  "function_head", "procedure_decl", "procedure_head", "parameters",
  "para_decl_list", "para_type_list", "var_para_list", "val_para_list",
  "routine_body", "compound_stmt", "stmt_list", "stmt", "non_label_stmt",
  "assign_stmt", "proc_stmt", "if_stmt", "else_clause", "repeat_stmt",
  "while_stmt", "for_stmt", "direction", "case_stmt", "case_expr_list",
  "case_expr", "goto_stmt", "expression_list", "expression", "expr",
  "term", "factor", YY_NULLPTR
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315
};
# endif

#define YYPACT_NINF -176

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-176)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       1,    15,    47,  -176,    19,  -176,    34,    41,    44,  -176,
    -176,  -176,  -176,  -176,    43,    46,     0,    50,    61,    67,
      71,  -176,    25,    94,   104,   108,  -176,   155,    99,   155,
     155,    86,  -176,   116,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,   258,   113,   118,    67,  -176,   122,  -176,
     155,   155,   155,   124,   130,   155,   155,    60,   155,    30,
     155,   155,  -176,  -176,  -176,  -176,  -176,  -176,   144,  -176,
     221,    18,    42,  -176,   150,   200,   179,  -176,  -176,   143,
     258,    97,  -176,  -176,    77,   122,  -176,     8,   279,     5,
     279,   261,   154,  -176,   153,    39,   155,   255,   155,   155,
     139,  -176,  -176,   155,   155,   155,   155,   155,   155,   155,
     110,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     110,   252,  -176,   151,   122,   158,  -176,   122,   159,   132,
     161,   164,   165,   170,   168,  -176,  -176,  -176,   162,    97,
    -176,   169,   171,  -176,   190,  -176,   199,  -176,   155,   208,
     155,  -176,  -176,   279,  -176,    52,    59,  -176,    66,    18,
      18,    18,    18,    18,    18,  -176,    42,    42,    42,  -176,
    -176,  -176,  -176,  -176,   215,   156,   204,   206,   193,  -176,
    -176,    76,   178,    -5,  -176,   120,   210,   214,   222,   223,
     243,   251,  -176,  -176,   250,   260,   260,  -176,  -176,   279,
     155,   279,  -176,  -176,  -176,  -176,  -176,   155,   110,  -176,
     110,   110,  -176,  -176,  -176,   262,  -176,  -176,    97,   240,
     257,   228,   230,   231,   232,  -176,   129,   266,  -176,   304,
      41,   305,   279,   229,  -176,   306,   307,   213,   308,  -176,
     -16,  -176,  -176,  -176,  -176,   122,   268,    10,  -176,   310,
     311,   178,  -176,  -176,  -176,   110,  -176,  -176,    97,  -176,
     283,  -176,   268,  -176,   129,   178,   178,  -176,  -176,  -176,
    -176,  -176,  -176,  -176
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     8,     0,     1,     0,     0,    10,     3,
       2,    67,     5,    64,     0,    20,    70,     0,     9,     0,
      45,    65,    83,     0,     0,    85,    67,     0,     0,     0,
       0,     0,    73,     0,    68,    71,    72,    74,    75,    76,
      77,    78,    79,     0,     0,     0,    19,    22,     0,    51,
       0,     0,     0,     0,    70,     0,     0,    70,     0,   121,
       0,     0,    13,    14,    15,    16,    18,    17,   123,   125,
       0,   110,   114,   115,     0,     0,     0,   101,    66,     0,
       0,     0,    21,    43,     0,    44,    47,     7,    80,     0,
     103,     0,     0,    69,     0,     0,     0,     0,     0,     0,
       0,   127,   128,     0,     0,     0,     0,     0,     0,     0,
      70,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      70,     0,    12,     0,     0,     0,    27,     0,    28,     0,
       0,     0,     0,     0,     0,    24,    25,    26,     0,     0,
      46,     0,     0,    49,     0,    50,     0,    84,     0,     0,
       0,    87,    86,    91,   126,     0,     0,   130,     0,   108,
     109,   104,   105,   106,   107,    92,   113,   111,   112,   120,
     116,   117,   118,   119,     0,    90,     0,     0,     0,    98,
      11,     0,     0,     0,    40,     0,     0,     0,     0,     0,
       0,     0,    23,    42,     0,    57,    57,     8,     8,   102,
       0,    82,   122,   129,   124,    95,    94,     0,    70,    88,
      70,    70,    96,    97,    29,     0,    38,    39,     0,     0,
       0,     0,     0,     0,     0,    48,     0,     0,    55,     0,
       0,     0,    81,     0,    89,     0,     0,     0,     0,    36,
       0,    30,    31,    35,    32,     0,    63,     0,    59,     0,
       0,     0,    52,     6,    54,    70,   100,    99,     0,    41,
       0,    33,    62,    56,     0,     0,     0,    53,    93,    37,
      34,    58,    60,    61
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -176,  -176,  -176,  -176,   125,   321,  -176,  -176,  -176,   -37,
    -176,  -176,   280,  -130,  -175,  -176,  -176,  -176,   142,  -119,
    -176,  -176,   242,  -176,  -176,  -176,  -176,  -176,   133,  -176,
      64,  -176,  -176,   100,    -7,   309,  -108,   277,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,   160,  -176,
     -36,   -26,   205,    22,   -20
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,   229,   230,     8,    15,    18,    69,
      20,    46,    47,   134,   135,   136,   137,   183,   184,    84,
      49,    85,    86,    87,   143,   144,   145,   146,   227,   247,
     248,   249,   250,    12,    32,    16,    33,    34,    35,    36,
      37,   209,    38,    39,    40,   207,    41,   178,   179,    42,
      89,    90,    71,    72,    73
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      13,    70,   165,    75,    76,   181,    79,   215,   185,   194,
     147,   216,   175,    11,   148,   263,    21,    83,   260,     1,
      95,   264,    22,   261,    88,   141,    91,   142,    50,    51,
       9,    52,    97,    53,    98,    94,    99,     4,   100,    23,
     101,   102,    10,   123,   152,    24,    25,     5,   148,   111,
      26,   112,   113,    27,    11,    28,    29,   202,    30,    14,
      31,   148,   155,   156,   185,    17,   203,   158,   148,    19,
     153,   204,   114,    11,    43,   148,   267,   115,   116,   117,
     118,   214,    22,    44,   177,   138,   138,   139,   238,    45,
     272,   273,    48,   174,   169,   170,   171,   172,   173,    23,
     234,   124,   235,   236,    54,    24,    25,   246,    55,   125,
      26,   126,    56,    27,    96,    28,    29,   127,    30,   128,
      31,    74,   199,    11,   201,    77,   262,    78,   269,   138,
     218,   129,    22,   166,   167,   168,   130,    80,   131,   132,
     133,   177,    81,    11,    83,   246,    92,   268,   103,    23,
     245,    83,    22,   119,   122,    24,    25,   150,   151,    58,
      26,   157,   180,    27,   182,    28,    29,   186,    30,   188,
      31,   187,   189,   190,   232,    24,    25,    59,   191,   192,
      26,   233,   124,    27,   193,    28,    29,    60,    30,    61,
      31,   195,   126,   196,    62,    63,    64,    65,    66,    67,
     128,   197,    68,   104,   105,   106,   107,   108,   109,   212,
     198,   200,   129,   208,   210,   176,   211,   130,   219,   131,
     132,   133,   220,    13,   104,   105,   106,   107,   108,   109,
     221,   222,    62,    63,    64,    65,    66,    67,   121,   104,
     105,   106,   107,   108,   109,   104,   105,   106,   107,   108,
     109,   223,   120,   104,   105,   106,   107,   108,   109,   224,
     154,   225,   239,   205,   226,   240,   206,   241,   149,   237,
     110,   242,   258,   243,   176,   244,   251,   138,   255,   104,
     105,   106,   107,   108,   109,   104,   105,   106,   107,   108,
     109,    62,    63,    64,    65,    66,    67,    62,    63,    64,
      65,    66,    67,   104,   105,   106,   107,   108,   109,   159,
     160,   161,   162,   163,   164,   252,   254,   256,   257,   259,
     265,   266,   270,   231,     7,   217,    82,   140,   271,   228,
     253,    93,     0,     0,     0,    57,     0,     0,   213
};

static const yytype_int16 yycheck[] =
{
       7,    27,   110,    29,    30,   124,    43,   182,   127,   139,
       5,    16,   120,    13,     9,     5,    16,    22,    34,    18,
      56,    11,    22,    39,    50,    17,    52,    19,     3,     4,
      11,     6,    58,     8,     4,    55,     6,    22,     8,    39,
      60,    61,     8,    80,     5,    45,    46,     0,     9,    31,
      50,    33,    34,    53,    13,    55,    56,     5,    58,    15,
      60,     9,    98,    99,   183,    22,     7,   103,     9,    23,
      96,     5,    30,    13,    24,     9,   251,    35,    36,    37,
      38,     5,    22,    22,   121,     9,     9,    10,   218,    22,
     265,   266,    21,   119,   114,   115,   116,   117,   118,    39,
     208,     4,   210,   211,    10,    45,    46,   226,     4,    12,
      50,    14,     4,    53,    54,    55,    56,    20,    58,    22,
      60,    22,   148,    13,   150,    39,   245,    11,   258,     9,
      10,    34,    22,   111,   112,   113,    39,    24,    41,    42,
      43,   178,    24,    13,    22,   264,    22,   255,     4,    39,
      21,    22,    22,     3,    11,    45,    46,     3,     5,     4,
      50,    22,    11,    53,     6,    55,    56,     8,    58,     8,
      60,    39,     8,     8,   200,    45,    46,    22,     8,    11,
      50,   207,     4,    53,    22,    55,    56,    32,    58,    34,
      60,    22,    14,    22,    39,    40,    41,    42,    43,    44,
      22,    11,    47,    24,    25,    26,    27,    28,    29,    16,
      11,     3,    34,    57,    10,    22,    10,    39,     8,    41,
      42,    43,     8,   230,    24,    25,    26,    27,    28,    29,
       8,     8,    39,    40,    41,    42,    43,    44,    59,    24,
      25,    26,    27,    28,    29,    24,    25,    26,    27,    28,
      29,     8,    52,    24,    25,    26,    27,    28,    29,     8,
       5,    11,    22,    48,     4,     8,    51,    39,     7,     7,
      49,    41,    59,    42,    22,    43,    10,     9,    49,    24,
      25,    26,    27,    28,    29,    24,    25,    26,    27,    28,
      29,    39,    40,    41,    42,    43,    44,    39,    40,    41,
      42,    43,    44,    24,    25,    26,    27,    28,    29,   104,
     105,   106,   107,   108,   109,    11,    11,    11,    11,    11,
      10,    10,    39,   198,     3,   183,    46,    85,   264,   196,
     230,    54,    -1,    -1,    -1,    26,    -1,    -1,   178
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    62,    63,    22,     0,    64,    66,    67,    11,
       8,    13,    94,    95,    15,    68,    96,    22,    69,    23,
      71,    16,    22,    39,    45,    46,    50,    53,    55,    56,
      58,    60,    95,    97,    98,    99,   100,   101,   103,   104,
     105,   107,   110,    24,    22,    22,    72,    73,    21,    81,
       3,     4,     6,     8,    10,     4,     4,    96,     4,    22,
      32,    34,    39,    40,    41,    42,    43,    44,    47,    70,
     112,   113,   114,   115,    22,   112,   112,    39,    11,    70,
      24,    24,    73,    22,    80,    82,    83,    84,   112,   111,
     112,   112,    22,    98,   115,   111,    54,   112,     4,     6,
       8,   115,   115,     4,    24,    25,    26,    27,    28,    29,
      49,    31,    33,    34,    30,    35,    36,    37,    38,     3,
      52,    59,    11,    70,     4,    12,    14,    20,    22,    34,
      39,    41,    42,    43,    74,    75,    76,    77,     9,    10,
      83,    17,    19,    85,    86,    87,    88,     5,     9,     7,
       3,     5,     5,   112,     5,   111,   111,    22,   111,   113,
     113,   113,   113,   113,   113,    97,   114,   114,   114,   115,
     115,   115,   115,   115,   112,    97,    22,    70,   108,   109,
      11,    80,     6,    78,    79,    80,     8,    39,     8,     8,
       8,     8,    11,    22,    74,    22,    22,    11,    11,   112,
       3,   112,     5,     7,     5,    48,    51,   106,    57,   102,
      10,    10,    16,   109,     5,    75,    16,    79,    10,     8,
       8,     8,     8,     8,     8,    11,     4,    89,    89,    65,
      66,    65,   112,   112,    97,    97,    97,     7,    74,    22,
       8,    39,    41,    42,    43,    21,    80,    90,    91,    92,
      93,    10,    11,    94,    11,    49,    11,    11,    59,    11,
      34,    39,    80,     5,    11,    10,    10,    75,    97,    74,
      39,    91,    75,    75
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    62,    63,    63,    64,    65,    66,    67,    68,
      68,    69,    69,    70,    70,    70,    70,    70,    70,    71,
      71,    72,    72,    73,    74,    74,    74,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    76,    77,    78,
      78,    79,    80,    80,    81,    81,    82,    82,    83,    84,
      84,    84,    85,    86,    87,    88,    89,    89,    90,    90,
      91,    91,    92,    93,    94,    95,    96,    96,    97,    97,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      99,    99,    99,   100,   100,   100,   100,   100,   101,   102,
     102,   103,   104,   105,   106,   106,   107,   108,   108,   109,
     109,   110,   111,   111,   112,   112,   112,   112,   112,   112,
     112,   113,   113,   113,   113,   114,   114,   114,   114,   114,
     114,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     0,     2,     2,     5,     0,     2,
       0,     5,     4,     1,     1,     1,     1,     1,     1,     2,
       0,     2,     1,     4,     1,     1,     1,     1,     1,     3,
       4,     4,     4,     5,     6,     4,     4,     6,     3,     2,
       1,     4,     3,     1,     2,     0,     2,     1,     4,     2,
       2,     0,     4,     5,     4,     3,     3,     0,     3,     1,
       3,     3,     2,     1,     1,     3,     3,     0,     1,     3,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     6,     5,     1,     4,     1,     4,     4,     5,     2,
       0,     4,     4,     8,     1,     1,     5,     2,     1,     4,
       4,     2,     3,     1,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     3,     1,     1,     3,     3,     3,     3,
       3,     1,     4,     1,     4,     1,     3,     2,     2,     4,
       3
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
      yyerror (YY_("syntax error: cannot back up")); \
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
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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
yyparse (void)
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
        case 2:
#line 90 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_Program) = new AbstractTree::ProgramNode((yyvsp[-2].ast_Id), (yyvsp[-1].ast_Routine));}
#line 1585 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 92 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_Id) = new AbstractTree::IdNode((yyvsp[-1].debug)); }
#line 1591 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 92 "pascal.y" /* yacc.c:1646  */
    {}
#line 1597 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 94 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_Routine) = new AbstractTree::RoutineNode((yyvsp[-1].ast_RoutineHead), (yyvsp[0].ast_RoutineBody)); }
#line 1603 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 96 "pascal.y" /* yacc.c:1646  */
    {}
#line 1609 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 98 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_RoutineHead) = new AbstractTree::RoutineHeadNode((yyvsp[-1].ast_VarDeclList)); }
#line 1615 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 101 "pascal.y" /* yacc.c:1646  */
    {}
#line 1621 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 104 "pascal.y" /* yacc.c:1646  */
    {}
#line 1627 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 105 "pascal.y" /* yacc.c:1646  */
    {}
#line 1633 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 108 "pascal.y" /* yacc.c:1646  */
    {}
#line 1639 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 109 "pascal.y" /* yacc.c:1646  */
    {}
#line 1645 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 112 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_ConstValue) = new AbstractTree::IntegerTypeNode(atoi((yyvsp[0].debug)));}
#line 1651 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 113 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_ConstValue) = new AbstractTree::RealTypeNode(atof((yyvsp[0].debug)));}
#line 1657 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 114 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_ConstValue) = new AbstractTree::CharTypeNode((yyvsp[0].debug));}
#line 1663 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 115 "pascal.y" /* yacc.c:1646  */
    {}
#line 1669 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 116 "pascal.y" /* yacc.c:1646  */
    {}
#line 1675 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 117 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_ConstValue) = new AbstractTree::BooleanTypeNode((yyvsp[0].debug));}
#line 1681 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 120 "pascal.y" /* yacc.c:1646  */
    {}
#line 1687 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 121 "pascal.y" /* yacc.c:1646  */
    {}
#line 1693 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 124 "pascal.y" /* yacc.c:1646  */
    {}
#line 1699 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 125 "pascal.y" /* yacc.c:1646  */
    {}
#line 1705 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 128 "pascal.y" /* yacc.c:1646  */
    {}
#line 1711 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 131 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_TypeDecl) = (yyvsp[0].ast_TypeDecl);}
#line 1717 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 132 "pascal.y" /* yacc.c:1646  */
    {}
#line 1723 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 133 "pascal.y" /* yacc.c:1646  */
    {}
#line 1729 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 136 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_TypeDecl) = new AbstractTree::TypeDeclNode((yyvsp[0].debug));}
#line 1735 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 137 "pascal.y" /* yacc.c:1646  */
    {}
#line 1741 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 138 "pascal.y" /* yacc.c:1646  */
    {}
#line 1747 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 139 "pascal.y" /* yacc.c:1646  */
    {}
#line 1753 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 140 "pascal.y" /* yacc.c:1646  */
    {}
#line 1759 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 141 "pascal.y" /* yacc.c:1646  */
    {}
#line 1765 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 142 "pascal.y" /* yacc.c:1646  */
    {}
#line 1771 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 143 "pascal.y" /* yacc.c:1646  */
    {}
#line 1777 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 144 "pascal.y" /* yacc.c:1646  */
    {}
#line 1783 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 145 "pascal.y" /* yacc.c:1646  */
    {}
#line 1789 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 148 "pascal.y" /* yacc.c:1646  */
    {}
#line 1795 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 151 "pascal.y" /* yacc.c:1646  */
    {}
#line 1801 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 154 "pascal.y" /* yacc.c:1646  */
    {}
#line 1807 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 155 "pascal.y" /* yacc.c:1646  */
    {}
#line 1813 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 158 "pascal.y" /* yacc.c:1646  */
    {}
#line 1819 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 161 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_NameList) = (yyvsp[-2].ast_NameList); (yyval.ast_NameList)->insert((yyvsp[0].debug));}
#line 1825 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 162 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_NameList) = new AbstractTree::NameListNode(); (yyval.ast_NameList)->insert((yyvsp[0].debug));}
#line 1831 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 165 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_VarDeclList) = (yyvsp[0].ast_VarDeclList);}
#line 1837 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 166 "pascal.y" /* yacc.c:1646  */
    {}
#line 1843 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 169 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_VarDeclList) = (yyvsp[-1].ast_VarDeclList); (yyval.ast_VarDeclList)->insert((yyvsp[0].ast_VarDecl)); }
#line 1849 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 170 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_VarDeclList) = new AbstractTree::VarDeclListNode(); (yyval.ast_VarDeclList)->insert((yyvsp[0].ast_VarDecl)); }
#line 1855 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 173 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_VarDecl) = new AbstractTree::VarDeclNode((yyvsp[-3].ast_NameList), (yyvsp[-1].ast_TypeDecl)); }
#line 1861 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 176 "pascal.y" /* yacc.c:1646  */
    {}
#line 1867 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 177 "pascal.y" /* yacc.c:1646  */
    {}
#line 1873 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 178 "pascal.y" /* yacc.c:1646  */
    {}
#line 1879 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 181 "pascal.y" /* yacc.c:1646  */
    {}
#line 1885 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 184 "pascal.y" /* yacc.c:1646  */
    {}
#line 1891 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 187 "pascal.y" /* yacc.c:1646  */
    {}
#line 1897 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 190 "pascal.y" /* yacc.c:1646  */
    {}
#line 1903 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 193 "pascal.y" /* yacc.c:1646  */
    {}
#line 1909 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 194 "pascal.y" /* yacc.c:1646  */
    {}
#line 1915 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 197 "pascal.y" /* yacc.c:1646  */
    {}
#line 1921 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 198 "pascal.y" /* yacc.c:1646  */
    {}
#line 1927 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 201 "pascal.y" /* yacc.c:1646  */
    {}
#line 1933 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 202 "pascal.y" /* yacc.c:1646  */
    {}
#line 1939 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 205 "pascal.y" /* yacc.c:1646  */
    {}
#line 1945 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 208 "pascal.y" /* yacc.c:1646  */
    {}
#line 1951 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 212 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_RoutineBody) = new AbstractTree::RoutineBodyNode((yyvsp[0].ast_StmtList)); }
#line 1957 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 215 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_StmtList) = (yyvsp[-1].ast_StmtList); }
#line 1963 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 218 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_StmtList) = (yyvsp[-2].ast_StmtList); (yyvsp[-2].ast_StmtList) = (yyvsp[-2].ast_StmtList)->insert((yyvsp[-1].ast_Stmt)); }
#line 1969 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 219 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_StmtList) = new AbstractTree::StmtListNode(); }
#line 1975 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 222 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_Stmt) = (yyvsp[0].ast_Stmt); }
#line 1981 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 223 "pascal.y" /* yacc.c:1646  */
    {}
#line 1987 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 226 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_Stmt) = dynamic_cast<AbstractTree::StmtNode*>((yyvsp[0].ast_AssignStmt)); }
#line 1993 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 227 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_Stmt) = dynamic_cast<AbstractTree::StmtNode*>((yyvsp[0].ast_ProcStmt)); }
#line 1999 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 228 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_Stmt) = (yyvsp[0].ast_StmtList); }
#line 2005 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 229 "pascal.y" /* yacc.c:1646  */
    {}
#line 2011 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 230 "pascal.y" /* yacc.c:1646  */
    {}
#line 2017 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 231 "pascal.y" /* yacc.c:1646  */
    {}
#line 2023 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 232 "pascal.y" /* yacc.c:1646  */
    {}
#line 2029 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 233 "pascal.y" /* yacc.c:1646  */
    {}
#line 2035 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 234 "pascal.y" /* yacc.c:1646  */
    {}
#line 2041 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 237 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_AssignStmt) = new AbstractTree::AssignStmtNode(new AbstractTree::IdNode((yyvsp[-2].debug)), (yyvsp[0].ast_Exp)); }
#line 2047 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 238 "pascal.y" /* yacc.c:1646  */
    {}
#line 2053 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 239 "pascal.y" /* yacc.c:1646  */
    {}
#line 2059 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 242 "pascal.y" /* yacc.c:1646  */
    {}
#line 2065 "parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 243 "pascal.y" /* yacc.c:1646  */
    {}
#line 2071 "parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 244 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_ProcStmt) = dynamic_cast<AbstractTree::ProcStmtNode*>((yyvsp[0].debug)); }
#line 2077 "parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 245 "pascal.y" /* yacc.c:1646  */
    {}
#line 2083 "parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 246 "pascal.y" /* yacc.c:1646  */
    {}
#line 2089 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 249 "pascal.y" /* yacc.c:1646  */
    {}
#line 2095 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 252 "pascal.y" /* yacc.c:1646  */
    {}
#line 2101 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 253 "pascal.y" /* yacc.c:1646  */
    {}
#line 2107 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 256 "pascal.y" /* yacc.c:1646  */
    {}
#line 2113 "parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 259 "pascal.y" /* yacc.c:1646  */
    {}
#line 2119 "parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 262 "pascal.y" /* yacc.c:1646  */
    {}
#line 2125 "parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 265 "pascal.y" /* yacc.c:1646  */
    {}
#line 2131 "parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 266 "pascal.y" /* yacc.c:1646  */
    {}
#line 2137 "parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 269 "pascal.y" /* yacc.c:1646  */
    {}
#line 2143 "parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 272 "pascal.y" /* yacc.c:1646  */
    {}
#line 2149 "parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 273 "pascal.y" /* yacc.c:1646  */
    {}
#line 2155 "parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 276 "pascal.y" /* yacc.c:1646  */
    {}
#line 2161 "parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 277 "pascal.y" /* yacc.c:1646  */
    {}
#line 2167 "parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 280 "pascal.y" /* yacc.c:1646  */
    {}
#line 2173 "parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 283 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_ExpList) = (yyvsp[-2].ast_ExpList); (yyval.ast_ExpList)->insert((yyvsp[0].ast_Exp)); }
#line 2179 "parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 284 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_ExpList) = new AbstractTree::ExpListNode(); (yyval.ast_ExpList)->insert((yyvsp[0].ast_Exp)); }
#line 2185 "parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 287 "pascal.y" /* yacc.c:1646  */
    {}
#line 2191 "parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 288 "pascal.y" /* yacc.c:1646  */
    {}
#line 2197 "parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 289 "pascal.y" /* yacc.c:1646  */
    {}
#line 2203 "parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 290 "pascal.y" /* yacc.c:1646  */
    {}
#line 2209 "parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 291 "pascal.y" /* yacc.c:1646  */
    {}
#line 2215 "parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 292 "pascal.y" /* yacc.c:1646  */
    {}
#line 2221 "parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 293 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_Exp) = (yyvsp[0].ast_Exp); }
#line 2227 "parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 296 "pascal.y" /* yacc.c:1646  */
    {}
#line 2233 "parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 297 "pascal.y" /* yacc.c:1646  */
    {}
#line 2239 "parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 298 "pascal.y" /* yacc.c:1646  */
    {}
#line 2245 "parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 299 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_Exp) = (yyvsp[0].ast_Exp); }
#line 2251 "parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 302 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_Exp) = (yyvsp[0].ast_Exp); }
#line 2257 "parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 303 "pascal.y" /* yacc.c:1646  */
    {}
#line 2263 "parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 304 "pascal.y" /* yacc.c:1646  */
    {}
#line 2269 "parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 305 "pascal.y" /* yacc.c:1646  */
    {}
#line 2275 "parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 306 "pascal.y" /* yacc.c:1646  */
    {}
#line 2281 "parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 307 "pascal.y" /* yacc.c:1646  */
    {}
#line 2287 "parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 310 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_Exp) = new AbstractTree::IdNode((yyvsp[0].debug)); }
#line 2293 "parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 311 "pascal.y" /* yacc.c:1646  */
    {}
#line 2299 "parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 312 "pascal.y" /* yacc.c:1646  */
    {}
#line 2305 "parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 313 "pascal.y" /* yacc.c:1646  */
    {}
#line 2311 "parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 314 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_Exp) = (yyvsp[0].ast_ConstValue); }
#line 2317 "parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 315 "pascal.y" /* yacc.c:1646  */
    { (yyval.ast_Exp) = (yyvsp[-1].ast_Exp); }
#line 2323 "parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 316 "pascal.y" /* yacc.c:1646  */
    {}
#line 2329 "parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 317 "pascal.y" /* yacc.c:1646  */
    {}
#line 2335 "parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 319 "pascal.y" /* yacc.c:1646  */
    {}
#line 2341 "parser.cpp" /* yacc.c:1646  */
    break;


#line 2345 "parser.cpp" /* yacc.c:1646  */
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
                  yystos[yystate], yyvsp);
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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 321 "pascal.y" /* yacc.c:1906  */


void yyerror(char const *str)
{
    fprintf(stderr,"%s\n",str);
}
int main(void)
{
    printf("Simple Pascal\n");
    yyparse();
    return 0;
    
}

