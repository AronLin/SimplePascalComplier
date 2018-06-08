%{
#include <stdio.h>
#include "AbstractTree.h"
#include "parser.hpp"
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
"/" {return DIVI;}//普通除法，还有一个整除div
">=" {return GE;}//大于等于
">" {return GT;}//大于
"<=" {return LE;}//小于等于
"<>" {return UNEQUAL;}//不等
"<" {return LT;}//小于

 /* 关键字部分 */

and {return AND;}
abs {
    return SYS_FUNCT;
}
array {return ARRAY;}
begin {return _BEGIN;}
boolean {
    return SYS_TYPE;
}
case {return CASE;}
const {return CONST;}
char {
    return SYS_TYPE;
}
chr {
    return SYS_FUNCT;
}
downto {return DOWNTO;}
do {return DO;}
div {return DIV;}
end {return END;}
else {return ELSE;}
false {
    yylval.boolean_value=0;
    return SYS_BOOL;//待定
    }
for {return FOR;}
function {return FUNCTION;}
goto {return GOTO;}
integer {
    return SYS_TYPE;
}
if {return IF;}
maxint {
    yylval.int_value=32767;
    return SYS_CON;//返回整数类型
}
not {return NOT;}
odd {
    return SYS_FUNCT;
}
of {return OF;}
ord {
    return SYS_FUNCT;
}
or {return OR;}
pred {
    return SYS_FUNCT;
}
program {return PROGRAM;}
procedure {return PROCEDURE;}
read {
    return READ;
}
real {
    return SYS_TYPE;
}
record {return RECORD;}
repeat {return REPEAT;}
sqrt {
    return SYS_FUNCT;
}
sqr {
    return SYS_FUNCT;
}
string {return STRING;}
succ {
    return SYS_FUNCT;
}
to { return TO;}
then {return THEN;}
true {
    yylval.boolean_value=1;
    return SYS_BOOL;//待定
    }
type {
    return TYPE;
}
until {return UNTIL;}
var {return VAR;}
while {return WHILE;}
writeln {
    return SYS_PROC;
}
write {
    return SYS_PROC;
}

 /* 数字，变量名，字符和字符串 */

"'"{ANY}"'" {
    return CHAR;
}
"'"{ANY}{ANY}+"'" {
    return STRING;
}
{ID} { //和NAME一个形式，不区分
    return ID;
}
[ \t]+ ;//分隔符
{INTNUM} {
    int temp;
    sscanf(yytext,"%d",&temp);
    if (temp>32767 || temp <-32768)//加入溢出*******
    {
        fprintf(stderr,"Integer Overflow.\n");
        exit(1);
    }
    yylval.int_value=temp;
    return INTEGER;
}
{REALNUM} {
    float temp;
    sscanf(yytext,"%f",&temp);
    yylval.real_value=temp;
    return REAL;
}
. { fprintf(stderr,"lexical error.\n");exit(1);}//其余字符不被认可
%%
int yywrap(void)
{
    return 1;//一直算下去直至进程被手动终结。
}