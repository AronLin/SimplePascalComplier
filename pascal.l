%{
#include <stdio.h>
#include "AbstractTree.h"
#include "parser.hpp"
#include "errorhandle.h"

//重定义YY_INPUT，从FILE* file中读取，并做一些记录
#define YY_INPUT(buf,result,max_size)  {\
    result = GetNextChar(buf, max_size); \
    if (  result <= 0  ) \
      result = YY_NULL; \
    }

#define STORESTRING yylval.debug=strdup(yytext)
%}
ANY .
COMMENT "{"{ANY}*"}" 
DIGIT [0-9]
DIGITS {DIGIT}+
LETTER [_a-zA-Z]
ID {LETTER}({LETTER}|{DIGIT})*
POINT "."{DIGITS}
EXPONENT (e|E)("+"|"-")?{DIGITS}
INTNUM {DIGITS}
REALNUM {DIGITS}({POINT})?({EXPONENT})?
%%
COMMENT {}//do nothing

 /* 符号部分 */

":=" {BeginToken(yytext); return ASSIGN;}//赋值
"=" {BeginToken(yytext); return EQUAL;}
"(" {BeginToken(yytext); return LP;}//左括号
")" {BeginToken(yytext); return RP;}//右括号
"[" {BeginToken(yytext); return LB;}//左中括号
"]" {BeginToken(yytext); return RB;}//右中括号
"." {BeginToken(yytext); return DOT;}//点
"," {BeginToken(yytext); return COMMA;}//逗号
":" {BeginToken(yytext); return COLON;}//冒号
";" {BeginToken(yytext); return SEMI;}//分号

"+" {BeginToken(yytext); return PLUS;}//加
"-" {BeginToken(yytext); return MINUS;}//减
"*" {BeginToken(yytext); return MUL;}//乘
"/" {BeginToken(yytext); return DIV;}//普通除法，还有一个整除div
">=" {BeginToken(yytext); return GE;}//大于等于
">" {BeginToken(yytext); return GT;}//大于
"<=" {BeginToken(yytext); return LE;}//小于等于
"<>" {BeginToken(yytext); return UNEQUAL;}//不等
"<" {BeginToken(yytext); return LT;}//小于

 /* 关键字部分 */

and {BeginToken(yytext); return AND;}
abs {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_FUNCT;
}
array {BeginToken(yytext); return ARRAY;}
begin {BeginToken(yytext); return _BEGIN;}
boolean {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_TYPE;
}
case {BeginToken(yytext); return CASE;}
const {BeginToken(yytext); return CONST;}
char {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_TYPE;
}
chr {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_FUNCT;
}
downto {BeginToken(yytext); return DOWNTO;}
do {BeginToken(yytext); return DO;}
div {BeginToken(yytext); return DIVI;}
end {BeginToken(yytext); return END;}
else {BeginToken(yytext); return ELSE;}
false {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_BOOL;//待定
    }
for {BeginToken(yytext); return FOR;}
function {BeginToken(yytext); return FUNCTION;}
goto {BeginToken(yytext); return GOTO;}
integer {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_TYPE;
}
if {BeginToken(yytext); return IF;}
maxint {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_CON;//返回整数类型
}
not {BeginToken(yytext); return NOT;}
odd {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_FUNCT;
}
of {BeginToken(yytext); return OF;}
ord {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_FUNCT;
}
or {BeginToken(yytext); return OR;}
pred {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_FUNCT;
}
program {BeginToken(yytext); return PROGRAM;}
procedure {BeginToken(yytext); return PROCEDURE;}
read {
    BeginToken(yytext); 
    return READ;
}
real {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_TYPE;
}
record {BeginToken(yytext); return RECORD;}
repeat {BeginToken(yytext); return REPEAT;}
sqrt {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_FUNCT;
}
sqr {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_FUNCT;
}
string {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_TYPE;}
succ {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_FUNCT;
}
to {BeginToken(yytext);  return TO;}
then {BeginToken(yytext); return THEN;}
true {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_BOOL;//待定
    }
type {
    BeginToken(yytext); 
    return TYPE;
}
until {BeginToken(yytext); return UNTIL;}
var {BeginToken(yytext); return VAR;}
while {BeginToken(yytext); return WHILE;}
writeln {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_PROC;
}
write {
    BeginToken(yytext); 
    STORESTRING;
    return SYS_PROC;
}

 /* 数字，变量名，字符和字符串 */

"'"{ANY}"'" {
    BeginToken(yytext); 
    STORESTRING;
    return CHAR;
}
"'"{ANY}{ANY}+"'" {
    BeginToken(yytext); 
    STORESTRING;
    return STRING;
}
{ID} { //和NAME一个形式，不区分
    BeginToken(yytext); 
    STORESTRING;
    return ID;
}
[ \t]+ ;//分隔符
{INTNUM} {
    BeginToken(yytext); 
    STORESTRING;
    return INTEGER;
}
{REALNUM} {
    BeginToken(yytext); 
    STORESTRING;
    return REAL;
}
. { BeginToken(yytext);ParseError = 1; PrintError("Invalid Input");}//其余字符不被认可
%%
int yywrap(void)
{
    return 1;//一直算下去直至进程被手动终结。
}