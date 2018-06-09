%{
#include <stdio.h>
#include "AbstractTree.h"
#include "parser.hpp"

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

":=" {return ASSIGN;}//赋值
"=" {return EQUAL;}
"(" {return LP;}//左括号
")" {return RP;}//右括号
"[" {return LB;}//左中括号
"]" {return RB;}//右中括号
"." {return DOT;}//点
"," {return COMMA;}//逗号
":" {return COLON;}//冒号
";" {return SEMI;}//分号

"+" {return PLUS;}//加
"-" {return MINUS;}//减
"*" {return MUL;}//乘
"/" {return DIV;}//普通除法，还有一个整除div
">=" {return GE;}//大于等于
">" {return GT;}//大于
"<=" {return LE;}//小于等于
"<>" {return UNEQUAL;}//不等
"<" {return LT;}//小于

 /* 关键字部分 */

and {return AND;}
abs {
    STORESTRING;
    return SYS_FUNCT;
}
array {return ARRAY;}
begin {return _BEGIN;}
boolean {
    STORESTRING;
    return SYS_TYPE;
}
case {return CASE;}
const {return CONST;}
char {
    STORESTRING;
    return SYS_TYPE;
}
chr {
    STORESTRING;
    return SYS_FUNCT;
}
downto {return DOWNTO;}
do {return DO;}
div {return DIVI;}
end {return END;}
else {return ELSE;}
false {
    STORESTRING;
    return SYS_BOOL;//待定
    }
for {return FOR;}
function {return FUNCTION;}
goto {return GOTO;}
integer {
    STORESTRING;
    return SYS_TYPE;
}
if {return IF;}
maxint {
    STORESTRING;
    return SYS_CON;//返回整数类型
}
not {return NOT;}
odd {
    STORESTRING;
    return SYS_FUNCT;
}
of {return OF;}
ord {
    STORESTRING;
    return SYS_FUNCT;
}
or {return OR;}
pred {
    STORESTRING;
    return SYS_FUNCT;
}
program {return PROGRAM;}
procedure {return PROCEDURE;}
read {
    return READ;
}
real {
    STORESTRING;
    return SYS_TYPE;
}
record {return RECORD;}
repeat {return REPEAT;}
sqrt {
    STORESTRING;
    return SYS_FUNCT;
}
sqr {
    STORESTRING;
    return SYS_FUNCT;
}
string {
    STORESTRING;
    return SYS_TYPE;}
succ {
    STORESTRING;
    return SYS_FUNCT;
}
to { return TO;}
then {return THEN;}
true {
    STORESTRING;
    return SYS_BOOL;//待定
    }
type {
    return TYPE;
}
until {return UNTIL;}
var {return VAR;}
while {return WHILE;}
writeln {
    STORESTRING;
    return SYS_PROC;
}
write {
    STORESTRING;
    return SYS_PROC;
}

 /* 数字，变量名，字符和字符串 */

"'"{ANY}"'" {
    STORESTRING;
    return CHAR;
}
"'"{ANY}{ANY}+"'" {
    STORESTRING;
    return STRING;
}
{ID} { //和NAME一个形式，不区分
    STORESTRING;
    return ID;
}
[ \t]+ ;//分隔符
{INTNUM} {
    STORESTRING;
    return INTEGER;
}
{REALNUM} {
    STORESTRING;
    return REAL;
}
. { fprintf(stderr,"lexical error.\n");exit(1);}//其余字符不被认可
%%
int yywrap(void)
{
    return 1;//一直算下去直至进程被手动终结。
}