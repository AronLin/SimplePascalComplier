%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "AbstractTree.h"
#include "parser.hpp"
#include "errorhandle.h"


AbstractTree::ProgramNode* astRoot;
extern int yylex(void);
void yyerror(char const *str);

//abs chr odd ord pred sqr sqrt succ read write writeln


%}

%locations

%union{
    char*                             debug;//yytext存储
    AbstractTree::Node*               ast_Node; 
    AbstractTree::IdNode*             ast_Id;
    AbstractTree::ProgramNode*        ast_Program;
    AbstractTree::RoutineNode*        ast_Routine;
    AbstractTree::RoutineHeadNode*    ast_RoutineHead;
    AbstractTree::LabelPartNode*      ast_LabelPart;
    AbstractTree::StmtNode*           ast_Stmt;
    AbstractTree::ExpNode*            ast_Exp;
    AbstractTree::VarDeclNode*        ast_VarDecl;
    AbstractTree::TypeDeclNode*       ast_TypeDecl;
    AbstractTree::TypeDefineNode*     ast_TypeDefine;
    AbstractTree::RoutineDeclNode*    ast_RoutineDecl;
    AbstractTree::RoutineBodyNode*    ast_RoutineBody;
    AbstractTree::ParaDeclNode*       ast_ParaDecl;
    AbstractTree::ConstValueNode*     ast_ConstValue;
    AbstractTree::AssignStmtNode*     ast_AssignStmt;
    AbstractTree::CaseStmtNode*       ast_CaseStmt;
    AbstractTree::SwitchStmtNode*     ast_SwitchStmt;

    AbstractTree::StmtListNode*       ast_StmtList;
    AbstractTree::ExpListNode*        ast_ExpList;    
    AbstractTree::VarDeclListNode*    ast_VarDeclList;    
    AbstractTree::NameListNode*       ast_NameList;
    AbstractTree::ConstExprListNode*  ast_ConstDeclList;
    AbstractTree::TypeDefineListNode* ast_TypeDefineList;
    AbstractTree::RoutineDeclListNode* ast_RoutineList;
    AbstractTree::ParaDeclListNode*   ast_ParaDeclList;
}




//终结符集合
%token ASSIGN LP RP LB RB DOT COMMA COLON SEMI
%token ARRAY _BEGIN SYS_TYPE CONST END FUNCTION PROGRAM
%token PROCEDURE RECORD VAR ID TYPE 
%token EQUAL UNEQUAL GE GT LE LT AND OR NOT //布尔表达式符号
%token PLUS MINUS MUL DIV DIVI MOD //运算符
%token INTEGER REAL CHAR STRING SYS_BOOL SYS_CON //变量值
%token READ SYS_PROC SYS_FUNCT //系统函数和过程
%token DOWNTO DO REPEAT TO THEN WHILE UNTIL FOR
%token IF ELSE CASE OF GOTO //语句

%type <debug> ASSIGN LP RP LB RB DOT COMMA COLON SEMI
%type <debug> ARRAY _BEGIN SYS_TYPE CONST END FUNCTION PROGRAM
%type <debug> PROCEDURE RECORD VAR ID TYPE 
%type <debug> EQUAL UNEQUAL GE GT LE LT AND OR NOT //布尔表达式符号
%type <debug> PLUS MINUS MUL DIV DIVI MOD //运算符
%type <debug> INTEGER REAL CHAR STRING SYS_BOOL SYS_CON //变量值
%type <debug> READ SYS_PROC SYS_FUNCT //系统函数和过程
%type <debug> DOWNTO DO REPEAT TO THEN WHILE UNTIL FOR
%type <debug> IF ELSE CASE OF GOTO //语句


%type <ast_LabelPart> label_part
%type <ast_Program> program
%type <ast_Id> program_head
%type <ast_Routine> routine sub_routine
%type <ast_RoutineHead> routine_head
%type <ast_RoutineBody> routine_body
%type <ast_VarDecl> var_decl
%type <ast_TypeDecl> type_decl simple_type_decl array_type_decl record_type_decl
%type <ast_TypeDefine> type_definition
%type <ast_RoutineDecl> function_decl function_head procedure_decl procedure_head
%type <ast_ParaDecl> para_type_list
%type <ast_Stmt> stmt non_label_stmt proc_stmt if_stmt else_clause 
%type <ast_Stmt> for_stmt repeat_stmt while_stmt goto_stmt 
%type <ast_SwitchStmt> case_expr_list case_stmt
%type <ast_AssignStmt> assign_stmt
%type <ast_CaseStmt> case_expr
%type <ast_Exp> expr term factor expression
%type <ast_ConstValue> const_value

%type <ast_NameList> name_list
%type <ast_ExpList> expression_list
%type <ast_VarDeclList> var_part var_decl_list
%type <ast_StmtList> compound_stmt stmt_list
%type <ast_ConstDeclList> const_part const_expr_list
%type <ast_TypeDefineList> type_decl_list type_part
%type <ast_RoutineList> routine_part
%type <ast_ParaDeclList> parameters para_decl_list

%start program
%%

program: program_head routine DOT { $$ = new AbstractTree::ProgramNode($1, $2);astRoot=$$;}
;
program_head : PROGRAM ID SEMI { 
        $$ = new AbstractTree::IdNode($2);
    } 
    |    { char* temp=strdup("none");  $$=new AbstractTree::IdNode(temp); }
;
routine: routine_head routine_body { $$ = new AbstractTree::RoutineNode($1, $2); std::cout << "Addr Routine: " << $$ << std::endl; }
;
sub_routine: routine_head routine_body {$$=new AbstractTree::RoutineNode($1,$2);}
;
routine_head: label_part const_part type_part var_part routine_part {
    $$ = new AbstractTree::RoutineHeadNode($1,$2,$3,$4,$5);
    }
;
label_part:  {$$=new AbstractTree::LabelPartNode();}
;
const_part:
    CONST const_expr_list {$$=$2;}
	|   {$$=new AbstractTree::ConstExprListNode();}
;
const_expr_list:
	const_expr_list ID EQUAL const_value SEMI {
        $$=$1;
        $$->const_expr_list.push_back(new AbstractTree::ConstExprNode(new AbstractTree::IdNode($2),$4));
    }
	| ID EQUAL const_value SEMI {
        $$=new AbstractTree::ConstExprListNode();
        $$->const_expr_list.push_back(new AbstractTree::ConstExprNode(new AbstractTree::IdNode($1),$3));
    }
;
const_value:
	INTEGER 	{ $$ = new AbstractTree::IntegerTypeNode(atoi($1));}
	| REAL 		{ $$ = new AbstractTree::RealTypeNode(atof($1));}
	| CHAR 		{ $$ = new AbstractTree::CharTypeNode($1);}
//	| STRING 	{ $$ = new AbstractTree::StringTypeNode($1);}
	| SYS_CON   { if (strcmp("maxint",$1) == 0) $$=new AbstractTree::IntegerTypeNode(32767);//maxint
                    else $$=new AbstractTree::IntegerTypeNode(32767);//There is only one SYS_CON
                }
    | SYS_BOOL  { $$ = new AbstractTree::BooleanTypeNode($1);}
;
type_part:
	TYPE type_decl_list {$$=$2;}
	| {$$=new AbstractTree::TypeDefineListNode();}
;
type_decl_list:
	type_decl_list type_definition {
        $$=$1;
        $$->type_define_list.push_back($2);
    }
	| type_definition {
        $$=new AbstractTree::TypeDefineListNode();
        $$->type_define_list.push_back($1);
    }
;
type_definition:
	ID EQUAL type_decl SEMI {
        $$=new AbstractTree::TypeDefineNode(new AbstractTree::IdNode($1),$3);
    }
;
type_decl:
	simple_type_decl	{ $$ = $1;}
	| array_type_decl 	{ $$ = $1;}
	| record_type_decl	{ $$ = $1;}
;
simple_type_decl:
	SYS_TYPE { $$ = new AbstractTree::TypeDeclNode($1);}	
    | ID  {}//not accomplished
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
	name_list COMMA ID 	{ $$ = $1; $$->insert($3);}
    | ID { $$ = new AbstractTree::NameListNode(); $$->insert($1);}	
;
var_part:
	VAR var_decl_list { $$ = $2;}
    |  	{$$=new AbstractTree::VarDeclListNode();}
;
var_decl_list:
	var_decl_list var_decl 	{ $$ = $1; $$->insert($2); }
    | var_decl 	{ $$ = new AbstractTree::VarDeclListNode(); $$->insert($1); }	
;
var_decl:
	name_list COLON type_decl SEMI { $$ = new AbstractTree::VarDeclNode($1, $3); }
;
routine_part: //做了修改，可以为空的话，function_decl 和 procedure_decl就有点多余了
	routine_part function_decl {
        $$=$1;
        $$->insert($2);
    }
    | routine_part procedure_decl {
        $$=$1;
        $$->insert($2);
    }
    |   {$$=new AbstractTree::RoutineDeclListNode();} 
;
function_decl: 
	function_head SEMI sub_routine SEMI {
        $$=$1;
        $$->sub_routine=$3;
    }
;
function_head:
	FUNCTION ID parameters COLON simple_type_decl {
        $$=new AbstractTree::RoutineDeclNode(AbstractTree::RoutineDeclNode::FUNCTION,
        new AbstractTree::IdNode($2),$3,$5);
    } 
;
procedure_decl:
	procedure_head SEMI sub_routine SEMI {
        $$=$1;
        $$->sub_routine=$3;
    }	
    ;
procedure_head:
	PROCEDURE ID parameters {
        $$=new AbstractTree::RoutineDeclNode(AbstractTree::RoutineDeclNode::PROCEDURE,
        new AbstractTree::IdNode($2),$3,nullptr);
    }	
    ;
parameters:
	LP para_decl_list RP {$$=$2;}
	|   {$$=new AbstractTree::ParaDeclListNode();}
    ;
para_decl_list:
	para_decl_list SEMI para_type_list 	{
        $$=$1;
        $$->insert($3);
    }
    | para_type_list {
        $$=new AbstractTree::ParaDeclListNode();
        $$->insert($1);
    }	
    ;
para_type_list://这两个有啥不同我还没有发现，先写成一样
	VAR name_list COLON simple_type_decl {
        $$=new AbstractTree::ParaDeclNode($2,$4);
    }	
    | name_list COLON simple_type_decl 	{
        $$=new AbstractTree::ParaDeclNode($1,$3);
    }
;


routine_body:  
	compound_stmt { $$ = new AbstractTree::RoutineBodyNode($1); std::cout << "Addr RoutineBody: " << $$ << std::endl; }
;
compound_stmt: 
	_BEGIN stmt_list END { $$ = $2; }
;
stmt_list: 
	stmt_list  stmt  SEMI { $$ = $1; $$->insert($2); }
    | 	{ $$ = new AbstractTree::StmtListNode(); }
    ;
stmt: 
	non_label_stmt { $$ = $1; }
    | INTEGER COLON non_label_stmt {
        $$=new AbstractTree::LabelStmtNode(atoi($1),$3);
    }
;
non_label_stmt: 
	assign_stmt { $$ = dynamic_cast<AbstractTree::StmtNode*>($1); }
	| proc_stmt { $$ = dynamic_cast<AbstractTree::StmtNode*>($1); }
    | compound_stmt { $$ = dynamic_cast<AbstractTree::StmtNode*>$1;}
    | if_stmt {$$ = dynamic_cast<AbstractTree::StmtNode*>($1);}
    | repeat_stmt {$$ = dynamic_cast<AbstractTree::StmtNode*>($1);}
    | while_stmt {$$ = dynamic_cast<AbstractTree::StmtNode*>($1);}
    | for_stmt	{$$ = dynamic_cast<AbstractTree::StmtNode*>($1);}
    | case_stmt {$$ = dynamic_cast<AbstractTree::StmtNode*>($1);}
    | goto_stmt	{$$ = dynamic_cast<AbstractTree::StmtNode*>($1);}
    ;
assign_stmt: 
	ID  ASSIGN  expression { $$ = new AbstractTree::AssignStmtNode(new AbstractTree::IdNode($1), $3); }
    | ID LB expression RB ASSIGN expression {}
    | ID DOT ID ASSIGN expression  {} 
    ;
proc_stmt: 
	ID {$$=new AbstractTree::ProcStmtNode(new AbstractTree::IdNode($1),nullptr);}    
    | ID LP expression_list RP {$$=new AbstractTree::ProcStmtNode(new AbstractTree::IdNode($1),$3);}
    | SYS_PROC	{$$ = new AbstractTree::SysProcStmtNode(new AbstractTree::IdNode($1), nullptr); }
    | SYS_PROC LP expression_list RP { $$ = new AbstractTree::SysProcStmtNode(new AbstractTree::IdNode($1), $3);}
    | READ LP factor RP {}//暂时没实现
    ;
if_stmt: 
	IF expression THEN stmt else_clause {
        $$=new AbstractTree::IfStmtNode($2,$4,$5);
    }
    ;
else_clause: 
	ELSE stmt {$$=$2;}
    |     {$$=nullptr;}	
    ;
repeat_stmt: 
	REPEAT stmt_list UNTIL expression {
        $$=new AbstractTree::RepeatStmtNode($2,$4);
    }
    ;
while_stmt: 
	WHILE expression DO stmt {
        $$=new AbstractTree::WhileStmtNode($2,$4);
    }
    ;
for_stmt: //简化，省得给TO和DOWNTO分个int类型
	FOR ID ASSIGN expression TO expression DO stmt {
        $$=new AbstractTree::ForStmtNode(new AbstractTree::IdNode($2),$4,1,$6,$8);
    }
    |FOR ID ASSIGN expression DOWNTO expression DO stmt {
        $$=new AbstractTree::ForStmtNode(new AbstractTree::IdNode($2),$4,-1,$6,$8);
    }
;
case_stmt: 
	CASE expression OF case_expr_list END {
        $$=$4;
        $$->condition=$2;
    }
    ;
case_expr_list: 
	case_expr_list  case_expr {
        $$=$1;
        $$->insert($2);
    }
    | case_expr {
        $$=new AbstractTree::SwitchStmtNode();
        $$->insert($1);
    }
    ;
case_expr: 
	const_value COLON stmt SEMI { $$ = new AbstractTree::CaseStmtNode($1,$3);}
    | ID COLON stmt SEMI {$$=new AbstractTree::CaseStmtNode(new AbstractTree::IdNode($1),$3);}
    ;
goto_stmt: 
	GOTO INTEGER {$$ = new AbstractTree::GotoStmtNode(atoi($2));}
    ;
expression_list: 
	expression_list COMMA expression { $$ = $1; $$->insert($3); } 
    | expression { $$ = new AbstractTree::ExpListNode(); $$->insert($1); } 
    ;
expression:
    expression GE expr {$$=new AbstractTree::BinaryNode($1,AbstractTree::BinaryNode::OpType::GE,$3);} 
    | expression GT expr {$$=new AbstractTree::BinaryNode($1,AbstractTree::BinaryNode::OpType::GT,$3);}
    | expression LE expr {$$=new AbstractTree::BinaryNode($1,AbstractTree::BinaryNode::OpType::LE,$3);}
    | expression LT expr {$$=new AbstractTree::BinaryNode($1,AbstractTree::BinaryNode::OpType::LT,$3);}
    | expression EQUAL expr {$$=new AbstractTree::BinaryNode($1,AbstractTree::BinaryNode::OpType::EQUAL,$3);}
    | expression UNEQUAL expr {$$=new AbstractTree::BinaryNode($1,AbstractTree::BinaryNode::OpType::UNEQUAL,$3);}
    | expr { $$ = $1; }
    ;
expr: 
	expr PLUS term {$$=new AbstractTree::BinaryNode($1,AbstractTree::BinaryNode::OpType::PLUS,$3);}
	| expr MINUS term {$$=new AbstractTree::BinaryNode($1,AbstractTree::BinaryNode::OpType::MINUS,$3);}
    | expr OR term {$$=new AbstractTree::BinaryNode($1,AbstractTree::BinaryNode::OpType::OR,$3);}
	| term { $$ = $1; }
;
term: 
	factor { $$ = $1; }
	| term MUL factor {$$=new AbstractTree::BinaryNode($1,AbstractTree::BinaryNode::OpType::MUL,$3);}
	| term DIV factor {$$=new AbstractTree::BinaryNode($1,AbstractTree::BinaryNode::OpType::DIV,$3);}
//    | term DIVI factor {$$=new AbstractTree::BinaryNode($1,AbstractTree::BinaryNode::OpType::DIVI,$3);}
    | term MOD factor {$$=new AbstractTree::BinaryNode($1,AbstractTree::BinaryNode::OpType::MOD,$3);}
    | term AND factor {$$=new AbstractTree::BinaryNode($1,AbstractTree::BinaryNode::OpType::AND,$3);} 
    ;
factor: 
	ID { $$ = new AbstractTree::IdNode($1); } 	
    | ID LP expression_list RP { $$ = new AbstractTree::FuncCallNode(new AbstractTree::IdNode($1), $3);}//FUNCTION_CALL
    | SYS_FUNCT {}
    | SYS_FUNCT LP expression_list RP {}
    | const_value { $$ = $1; }
    | LP expression RP { $$ = $2; }
    | NOT factor {$$=new AbstractTree::BinaryNode(new AbstractTree::BooleanTypeNode("true"),AbstractTree::BinaryNode::OpType::XOR,$2);}
    | MINUS factor {$$=new AbstractTree::BinaryNode(new AbstractTree::IntegerTypeNode(0),AbstractTree::BinaryNode::OpType::MINUS,$2);}
    | ID LB expression_list RB{}
    | ID DOT ID {}
    ;
%%

void yyerror(char const *str)
{
    PrintError(str);
	ParseError = 1;
}
// int main(void)
// {
//     printf("Simple Pascal\n");
//     yyparse();
//     return 0;
    
// }

