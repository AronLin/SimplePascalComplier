%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "lex.yy.c"
int yylex(void);
void yyerror(char const *str);

//abs chr odd ord pred sqr sqrt succ read write writeln


%}
//设置类型集合
%union {
    short int_value;//pascal 中int是2个字节,这里用short了
    float real_value;//用单精度实数
    char* string_value;
    char boolean_value;
}
//终结符集合
%token ASSIGN EQUAL LP RP LB RB DOT COMMA COLON SEMI
PLUS MINUS MUL DIVI GE GT LE UNEQUAL LT AND SYS_FUNCT
ARRAY BEGIN SYS_TYPE CASE CONST DOWNTO DO DIV END 
ELSE FALSEFIR FUNCTION GOTO IF INTEGER NOT OF OR
PROGRAM PROCEDURE RECORD REPEAT STRING TO THEN TRUE
UNTIL VAR WHILE SYS_PROC CHAR ID REAL
%start program

//运算符优先级部分


%%
program: program_head routine DOT
program_head : PROGRAM ID SEMI
routine : routine_head routine_body
routine_head: BEGIN
routine_body: END
 /* 上边这个错误的，暂时不想继续写了 */

%%

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

