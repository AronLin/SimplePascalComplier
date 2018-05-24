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
%token ASSIGN LP RP LB RB DOT COMMA COLON SEMI
ARRAY BEGIN SYS_TYPE CONST END FUNCTION PROGRAM
PROCEDURE RECORD VAR ID TYPE 
%token EQUAL UNEQUAL GE GT LE LT AND OR NOT //布尔表达式符号
%token PLUS MINUS MUL DIV DIVI MOD //运算符
%token INTEGER REAL CHAR STRING SYS_BOOL SYS_CON //变量值
%token READ SYS_PROC SYS_FUNCT //系统函数和过程
%token DOWNTO DO REPEAT TO THEN WHILE UNTIL FOR
IF ELSE CASE OF GOTO //语句
%start program


%%
// 注意NAME和ID其实是一样的，所以我将语法中的NAME全换成了ID
program: program_head routine DOT {}
;
program_head : PROGRAM ID SEMI {}
;
routine: routine_head routine_body {}
;
sub_routine: routine_head routine_body {}
;
routine_head: label_part const_part type_part var_part routine_part {}
;
label_part:
    {}
;
const_part:
    CONST const_expr_list {}
	| 	{}
;
const_expr_list:
	const_expr_list ID EQUAL const_value SEMI {}
	| ID EQUAL const_value SEMI {}
;
const_value:
	INTEGER 	{}
	| REAL 		{}
	| CHAR 		{}
	| STRING 	{}
	| SYS_CON   {}
    | SYS_BOOL  {}
;
type_part:
	TYPE type_decl_list {}
	| {}
;
type_decl_list:
	type_decl_list type_definition {}
	| type_definition {}
;
type_definition:
	ID EQUAL type_decl SEMI {}
;
type_decl:
	simple_type_decl	{}
	| array_type_decl 	{}
	| record_type_decl	{}
;
simple_type_decl:
	SYS_TYPE	
	| ID  {}
	| LP name_list RP {}
    | INTEGER DOT DOT INTEGER 	{}
    | CHAR DOT DOT CHAR 	{}
    | SYS_BOOL DOT DOT SYS_BOOL {} 
    | MINUS INTEGER DOT DOT INTEGER	{}
    | MINUS INTEGER DOT DOT MINUS INTEGER {}
    | STRING DOT DOT STRING {}
    | ID DOT DOT ID {}	
;
array_type_decl:
	ARRAY LB simple_type_decl RB OF type_decl {}
;
record_type_decl:
	RECORD field_decl_list END 	{}
;
field_decl_list:
	field_decl_list field_decl {}
    | field_decl {}
;
field_decl:
	name_list COLON type_decl SEMI {}
;
name_list:
	name_list COMMA ID 	{}
    | ID {}	
;
var_part:
	VAR var_decl_list {}
    |  		{}
;
var_decl_list:
	var_decl_list var_decl 	{}
    | var_decl 	{}	
;
var_decl:
	name_list COLON type_decl SEMI {}
;
routine_part: //做了修改，可以为空的话，function_decl 和 procedure_decl就有点多余了
	routine_part function_decl {}
    | routine_part procedure_decl {}
    | {} 
;
function_decl: 
	function_head SEMI sub_routine SEMI {}
;
function_head:
	FUNCTION ID parameters COLON simple_type_decl {} 
;
procedure_decl:
	procedure_head SEMI sub_routine SEMI {}	
    ;
procedure_head:
	PROCEDURE ID parameters {}	
    ;
parameters:
	LP para_decl_list RP {}
	| 	{}
    ;
para_decl_list:
	para_decl_list SEMI para_type_list 	{}
    | para_type_list {}	
    ;
para_type_list:
	var_para_list COLON simple_type_decl {}	
    | val_para_list COLON simple_type_decl 	{}
;
var_para_list: 
    VAR name_list {}
;
val_para_list:
    name_list {}
;

routine_body:  
	compound_stmt {}
;
compound_stmt: 
	BEGIN stmt_list END {}
;
stmt_list: 
	stmt_list  stmt  SEMI {}
    | 	{}
    ;
stmt: 
	non_label_stmt {}
    | INTEGER COLON non_label_stmt {}
;
non_label_stmt: 
	|assign_stmt {}
	| proc_stmt {}
    | compound_stmt {}
    | if_stmt {}
    | repeat_stmt {}
    | while_stmt {}
    | for_stmt	{}
    | case_stmt {}
    | goto_stmt	{}
    ;
assign_stmt: 
	ID  ASSIGN  expression {}
    | ID LB expression RB ASSIGN expression {}
    | ID DOT ID ASSIGN expression  {} 
    ;
proc_stmt: 
	ID {}    
    | ID LP expression_list RP {}
    | SYS_PROC	{}
    | SYS_PROC LP expression_list RP {}
    | READ LP factor RP {}
    ;
if_stmt: 
	IF expression THEN stmt else_clause {}
    ;
else_clause: 
	ELSE stmt {}
    | 	{}	
    ;
repeat_stmt: 
	REPEAT stmt_list UNTIL expression {}
    ;
while_stmt: 
	WHILE expression DO stmt {}
    ;
for_stmt: 
	FOR ID ASSIGN expression direction expression DO stmt {}
;
direction:
    TO {}
    | DOWNTO {}
    ;
case_stmt: 
	CASE expression OF case_expr_list END {}
    ;
case_expr_list: 
	case_expr_list  case_expr {}
    | case_expr {}
    ;
case_expr: 
	const_value COLON stmt SEMI {}
    | ID COLON stmt SEMI {}
    ;
goto_stmt: 
	GOTO INTEGER {}
    ;
expression_list: 
	expression_list COMMA expression {} 
    | expression {} 
    ;
expression:
    expression GE expr {} 
    | expression GT expr {}
    | expression LE expr {}
    | expression LT expr {}
    | expression EQUAL expr {}
    | expression UNEQUAL expr {}
    | expr {}
    ;
expr: 
	expr PLUS term {}
	| expr MINUS term {}
    | expr OR term {}
	| term {}
;
term: 
	factor {}
	| term MUL factor {}
	| term DIV factor {}
    | term DIVI factor {}
    | term MOD factor {}
    | term AND factor {} 
    ;
factor: 
	ID {} 	
    | ID LP expression_list RP {}
    | SYS_FUNCT {}
    | SYS_FUNCT LP expression_list RP {}
    | const_value {}
    | LP expression RP {}
    | NOT factor {}
    | MINUS factor {}
    | ID LB expression_list RB
    | ID DOT ID {}
    ;
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

