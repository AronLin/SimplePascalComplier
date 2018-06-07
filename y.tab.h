/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
#line 19 "pascal.y" /* yacc.c:1915  */

    
    Node*               ast_Node; 
    StmtList*           ast_StmtList;
    ProgramNode*        ast_Program;
    RoutineNode*        ast_Routine;
    Stmt*               ast_Stmt;
    Id*                 ast_Id;
    
#line 32 "pascal.y" /* yacc.c:1915  */

    short int_value;//pascal 中int是2个字节,这里用short了
    float real_value;//用单精度实数
    char* string_value;
    char boolean_value;

#line 191 "y.tab.h" /* yacc.c:1915  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
