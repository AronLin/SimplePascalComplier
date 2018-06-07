%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "lex.yy.c"

#include "AbstractTree.h"

Node* astRoot;
int yylex(void);
void yyerror(char const *str);

//abs chr odd ord pred sqr sqrt succ read write writeln


%}

%union{
    
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
}


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
%token IF ELSE CASE OF GOTO //语句

%start program

%type <ast_Program> program
%type <ast_Id> program_head
%type <ast_Routine> routine
%type <ast_RoutineHead> routine_head
%type <ast_RoutineBody> routine_body
%type <ast_VarDeclList> var_part, var_decl_list
%type <ast_VarDecl> var_decl
%type <ast_NameList> name_list
%type <ast_TypeDecl> type_decl, simple_type_decl;
%type <ast_StmtList> compound_stmt, stmt_list;
%type <ast_Stmt> stmt;
%type <ast_AssignStmt> assign_stmt
%type <ast_ProcStmt> proc_stmt
%type <ast_ExpList> expression_list
%type <ast_Exp> expr, term, factor
%type <ast_ConstValue> const_value

%%
// 注意NAME和ID其实是一样的，所以我将语法中的NAME全换成了ID
program: program_head routine DOT { $$ = new AbstractTree::ProgramNode($1, $2);}
;
program_head : PROGRAM ID SEMI { $$ = new AbstractTree::IdNode($2); } | {}
;
routine: routine_head routine_body { $$ = new AbstractTree::RoutineNode($1, $2); }
;
sub_routine: routine_head routine_body {}
;
routine_head: label_part const_part type_part var_part routine_part { $$ = new AbstractTree::RoutineHeadNode($4); }
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
	compound_stmt {$$ = $1}
;
compound_stmt: 
	BEGIN stmt_list END {$$ = $2}
;
stmt_list: 
	stmt_list  stmt  SEMI {$$ = $1;$$->child.push_back($2);}
    | 	{}
    ;
stmt: 
	non_label_stmt {$$=$1}
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

