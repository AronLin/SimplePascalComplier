//
// Created by apple on 2018/6/5.
//

#ifndef SIMPLEPASCALCOMPILER_ABSTRACTTREE_H
#define SIMPLEPASCALCOMPILER_ABSTRACTTREE_H
//Author: Ken
//file: AbstractTree.cpp
// Created by Ken on 2018/6/5.
//QAQ

#include <string>
#include <map>
#include <list>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <climits>
#include "llvm/IR/Value.h"

#include "CodeGenContext.h"



//non-terminal node
class ProgramNode;
class IdNode;
class RoutineNode;
class RoutineHeadNode;
class RoutineBodyNode;
class LabelPartNode;
class ConstExprNode;
class TypeDeclNode;
class TypeDefineNode;
class VarDeclNode;
class RoutineDeclNode;//include procedure and fucntion node
class ConstValueNode;
class SimpleTypeDeclNode;
class ArrayTypeDeclNode;
class RecordTypeDeclNode;
class StmtListNode;
class StmtNode;
class AssignStmtNode;
class SysProcStmtNode;
class ProcStmtNode;
class ExpNode;
class ExpListNode;
class ConstValueNode;
class IntegerTypeNode;
class CharTypeNode;
class RealTypeNode;
class BooleanTypeNode;
class ParaDeclNode;

//list node
class ParaDeclListNode;
class ConstExprListNode;
class TypeDefineListNode;
class VarDeclListNode;
class RoutineDeclListNode;


namespace AbstractTree {
enum {
    NODE=0,PROGRAM,ID,ROUTINE,ROUTINE_HEAD,LABEL_PART,CONST_EXPR_LIST,CONST_EXPR,CONST_VALUE,TYPE_DEFINE_LIST,TYPE_DEFINITION,TYPE_DECL,SIMPLE_TYPE_DECL,ARRAY_TYPE_DECL,RECORD_TYPE_DECL,STMT_LIST
}NodeType;

    class Node {
    public:
        int _type = NODE;
        virtual ~Node() {}
        //virtual std::string info() = 0;
        virtual llvm::Value *CodeGen(CodeGenContext& context) = 0;

    };
    class SysCon{
    public:
        bool True = true;
        bool False = false;
        int maxint = INT_MAX;
        int minint = INT_MIN;
    };
    enum SysFuncAndProc{
      abs,chr,odd,ord,pred,sqr,sqrt,succ,write,writeln
    };
    enum SysType{
        Integer,Real,Char,Bool
    };


    class ProgramNode:public Node{
    public:

        RoutineNode* routine;

        ProgramNode(){
            this->_type = PROGRAM;
        }
        ProgramNode(IdNode* program_head,RoutineNode* routine){
            this->_type = PROGRAM;
            this->routine = routine;
        }

        //virtual std::string info(){
        //   return "Program:";
        //}
        virtual llvm::Value *CodeGen(CodeGenContext& context);
    };

    class RoutineNode:public Node{
    public:
        RoutineHeadNode* routineHead;
        RoutineBodyNode* routineBody;

        RoutineNode(){
            this->_type = ROUTINE;
        }
        RoutineNode(RoutineHeadNode* routine_head,RoutineBodyNode* routine_body){
            //routine head
            this->_type = ROUTINE;
            routineBody = routine_body;
            routineHead = routine_head;
        }
        virtual std::string info(){
            return "Routine:";
        }
        virtual llvm::Value *CodeGen(CodeGenContext& context);
    };

    class RoutineHeadNode : public Node
    {
    public:
        //LabelPartNode* labelPartNode;
        VarDeclListNode* varDeclList;
        //TypeDefineListNode* typeDefineNodeList;
        
        virtual llvm::Value* CodeGen(CodeGenContext& context);
    };

    class LabelPartNode:public  Node{
        //todo:how this label work? need a label table?
    public:
        int label;
        LabelPartNode(){
            this->_type = LABEL_PART;
            this->label = -1;
        }
        LabelPartNode(int input){
            this->_type = LABEL_PART;
            this->label = input;
        }
        virtual llvm::Value* CodeGen(CodeGenContext& context);
    };

    //const part:
     class ConstExprListNode:public Node
    {
    public:
        vector<ConstExprNode> const_expr_list;
        ConstExprListNode():{
            this->_type = CONST_EXPR_LIST;
        }

        ConstExprListNode(ConstExprNode const_expr){
            this->_type = CONST_EXPR_LIST;
            this->const_expr_list.push_back(const_expr);
        }
        ConstExprListNode(ConstExprList const_expr){
            this->_type = CONST_EXPR_LIST;
            for (auto iter:const_expr) {
                this->const_expr_list.push_back(iter);
            }
        }
        virtual llvm::Value* CodeGen(CodeGenContext& context);


    };
    class ConstExprNode:public Node
    {
    public:
        IdNode* id;
        ConstValueNode* const_value;
        ConstExprNode(){this->_type = CONST_EXPR;}
        ConstExprNode(IdNode* in_id,ConstValueNode* in_const_value){
            this->_type = CONST_EXPR;
            this->id = in_id;
            this->const_value = in_const_value;
        }
        virtual llvm::Value* CodeGen(CodeGenContext& context);
    };


    //type part:
    class TypeDefineListNode:public Node{
    public:
        vector<TypeDefineNode*> type_define_list;

        TypeDefineListNode(){this->_type = TYPE_DEFINE_LIST;}

        TypeDefineListNode(TypeDefineNode* type_define){
            this->_type = TYPE_DEFINE_LIST;
            //need clear ? 
            this->type_decl_list.push_back(type_define);
        }
        TypeDefineListNode(TypeDeclList* type_define_list){
            this->_type = TYPE_DEFINE_LIST;
            for (auto iter:*type_define_list) {
                this->type_define_list.push_back(iter);
            }
        }
        virtual llvm::Value* CodeGen(CodeGenContext& context);

    };
    class TypeDefineNode:public Node{
    public:
        IdNode* id;
        TypeDeclNode* type_decl;
        TypeDefineNode(){this->_type = TYPE_DEFINITION;}
        TypeDefineNode(IdNode* in_id,TypeDeclNode* in_type_decl)id(in_id),type_decl(in_type_decl){ 
            this->_type = TYPE_DEFINITION;
        }
    };
    //todo: only basic type for testing
    class TypeDeclNode: public Node
    {
    public:
        enum class TypeName
        {
            integer, real, character, boolean, error
        };
        std::string rawName = "";
        TypeName sysName = TypeName::error;
        TypeDeclNode(const std::string &str) : rawNname(str){init();}
        TypeDeclNode(const char * ptr_c) : rawNname(*(new std::string(ptr_c))) {init();}

        void init();
        virtual llvm::Value* CodeGen(CodeGenContext& context);
        llvm::Type* toLLVMType();
    };

    class RoutineBodyNode: public Node
    {
    public:
        StmtListNode* stmtList;
        RoutineBodyNode(StmtListNode* node):stmtList(node){}
        virtual llvm::Value* CodeGen(CodeGenContext& context);
    };

    class IdNode: public Node
    {
    public:
        std::string name;
        IdNode(const std::string& name): name(name){}
        IdNode(const char* name): name(*(new std::string(name))){}
        virtual llvm::Value* CodeGen(CodeGenContext& context);
    };

    class StmtListNode:public Node{
    public:
        StmtListNode():{this->_type = STMT_LIST;}
        std::vector<StmtNode*> list;
        void insert(StmtNode* node) {list.push_back(node);}

        virtual llvm::Value *CodeGen(CodeGenContext& context);
    };

    //Base Class, should not be implemented
    class StmtNode:public Node{
    public:
        virtual llvm::Value *CodeGen(CodeGenContext& context) = 0;
    };

    class ExpNode: public Node
    {
    public:
        virtual llvm::Value* CodeGen(CodeGenContext& context) = 0;
    };

    class ExpListNode: public Node
    {
    public:
        std::vector<ExpNode*> list;
        void insertNode(ExpNode* node) {list.push_back(node);}
        std::vector<ExpNode*>* getListPtr() {return &list;}
        virtual llvm::Value* CodeGen(CodeGenContext& context);
    };

    class VarDeclListNode: public Node
    {
    public:
        std::vector<VarDeclNode*> list;
        void insert(VarDeclNode* node)
        {
            list.push_back(node);
        }
        virtual llvm::Value* CodeGen(CodeGenContext& context);
    }; 

    class VarDeclNode: public Node
    {
    public:
    //v1:
        IdNode* name;
        //v2:
        //std::list<IdNode*> name_list;
        TypeDeclNode* type;
        VarDeclNode* (IdNode* name, TypeDeclNode* type): name(name), type(type)
        {
            //Put Children
        };
        //v2
        // VarDeclNode* (IdNode* name, TypeDeclNode* type): 
        // {
        //     name_list.push_back(name);
        //     this->type  = type;
        // };
        }
        virtual llvm::Value* CodeGen(CodeGenContext& context);

    };

    

    //TODO:: all func below need codegen
    class ConstValueNode: public ExpNode
    {
    public:
        TypeDeclNode::TypeName type;
        TypeDeclNode::TypeName getConstType() {return type;}
        virtual llvm::Value* CodeGen(CodeGenContext& context) = 0;
    };

    class IntegerTypeNode: public ConstValueNode
    {
    public:
        int val;
        IntegerTypeNode(int value):val(value) {type = TypeDeclNode::TypeName::integer;}
        virtual llvm::Value* CodeGen(CodeGenContext& context);
    };

    class RealTypeNode: public ConstValueNode
    {
    public:
        double val;
        RealTypeNode(double value):val(value) {type = TypeDeclNode::TypeName::real;}
        virtual llvm::Value* CodeGen(CodeGenContext& context);
    };

    class CharTypeNode: public ConstValueNode
    {
    public:
        char val;
        CharTypeNode(const char * p_str) : val(*(p_str)) {type = TypeDeclNode::TypeName::character;}
        virtual llvm::Value* CodeGen(CodeGenContext& context); 
    };

    class BooleanTypeNode: public ConstValueNode
    {
    public:
        int val;
        BooleanTypeNode(const char * str) : val(std::string(str) == "true" ? 1 : 0) {type = TypeDeclNode::TypeName::boolean;}
        virtual llvm::Value* CodeGen(CodeGenContext& context);   
    };


    class AssignStmtNode: public StmtNode
    {
    public:
        IdNode* lhs;
        ExpNode* rhs;
        AssignStmtNode(IdNode* lhs, ExpNode* rhs): lhs(lhs), rhs(rhs) {}
        virtual llvm::Value* CodeGen(CodeGenContext& context);
    };

    class ProcStmtNode: public StmtNode
    {
    public:
        IdNode* id;
        ExpListNode* args;

        virtual llvm::Value* CodeGen(CodeGenContext& context);
    };

    class SysProcStmtNode: public ProcStmtNode
    {
    public:
        SysProcStmtNode(IdNode* idd): id(idd){};
        SysProcStmtNode(IdNode* idd, ExpListNode* arg): id(idd), args(arg){}
        llvm::Value* callPrintf(CodeGenContext& context, bool writeln);
        virtual llvm::Value *CodeGen(CodeGenContext& context);
    };    
    
    class RoutineDeclNode: public Node{
        enum{
            PROCEDURE,FUNCTION
        }
        int type;
        IdNode* id;
        ParaDeclList* para_decl_list;
        TypeDeclNode* type_decl;
        RoutineNode* sub_routine;
        
        RoutineDeclNode(int FuncorPro,IdNode* _id,ParaDeclList* _para_decl_list,TypeDeclNode* _type_decl,RoutineNode* _sub_routine = nullptr):type(FuncorPro),id(_id),para_decl_list(_para_decl_list),type_decl(_type_decl),sub_routine(_sub_routine){
            //initial child
        }

        virtual llvm::Value *CodeGen(CodeGenContext& context);
    }
    //v1: only for pascal left value? i.e : val_para_list int the PASCAL.doc
    class ParaDeclNode: public Node{
        std::vector<IdNode*> name_list;
        TypeDeclNode* type_decl;
        ParaDeclNode(std::vector<IdNode*>& _name_list,TypeDeclNode* _type_decl):name_list(_name_list),type_decl(_type_decl){

        }
        virtual llvm::Value *CodeGen(CodeGenContext& context);
    }

    class ParaDeclListNode: public Node{
        std::vector<ParaDeclNode*> list;
        void insertNode(ParaDeclNode* node) {list.push_back(node);};
        
        virtual llvm::Value* CodeGen(CodeGenContext& context);
    }
    
    class IfStmtNode: public StmtNode
    {
    public:
        ExpNode* condition;
        StmtNode* thenStmt;
        StmtNode* elseStmt;
        IfStmtNode(ExpNode* condition,StmtNode* thenStmt,StmtNode* elseStmt)
        :condition(condition),thenStmt(thenStmt),elseStmt(elseStmt){}
        virtual llvm::Value *CodeGen(CodeGenContext& context);
    };

    class WhileStmtNode: public StmtNode
    {
    public:
        ExpNode* condition;
        StmtNode* loopStmt;
        WhileStmtNode(ExpNode* condition,StmtNode* loopStmt)
        :condition(condition),loopStmt(loopStmt){}
        virtual llvm::Value *CodeGen(CodeGenContext& context);        
    };

    class ForStmtNode: public StmtNode
    {
    public:
        IdNode* id;
        ExpNode* start;
        ExpNode* end;
        int direction;//1 to. -1 downto
        StmtNode* loopStmt;

        ForStmtNode(IdNode* id,ExpNode* start,int direction, ExpNode* end,Stmt* loopStmt)
        :id(id),start(start),end(end),direction(direction),loopStmt(loopStmt){}
        virtual llvm::Value *CodeGen(CodeGenContext& context);
    };

    class RepeatStmtNode: public StmtNode
    {
    public:
        StmtNode* loopStmt;
        ExpNode* condition;
        RepeatStmtNode(StmtNode* loopStmt,ExpNode* condition)
        :loopStmt(loopStmt),condition(condition){}
        virtual llvm::Value *CodeGen(CodeGenContext& context);
    };

    class SwitchStmtNode: public StmtNode
    {
    public:
        ExpNode* condition;
        std::vector<CaseStmtNode*>* list;
        SwitchStmtNode(ExpNode* condition,std::vector<CaseStmtNode*>* list)
        :condition(condition),list(list){}
        virtual llvm::Value *CodeGen(CodeGenContext& context);
    };

    class CaseStmtNode: public StmtNode
    {
    public:
        ExpNode* condition;//there might be ID or const_value,so we use ExpNode to represent them
        StmtNode* Stmt;
        CaseStmtNode(ExpNode* condition,StmtNode* Stmt)
        :condtion(condition),Stmt(Stmt){}
        virtual llvm::Value *CodeGen(CodeGenContext& context);
    };

    class LabelStmtNode: public StmtNode
    {
    public:
        int label;
        StmtNode* stmt;
        LabelStmtNode(int label,StmtNode* stmt)
        :label(label),stmt(stmt){}
        virtual llvm::Value *CodeGen(CodeGenContext& context);
    };

    class GotoStmtNode: public StmtNode
    {
    public:
        int label;
        GotoStmtNode(int label){this->label=label;}
        virtual llvm::Value *CodeGen(CodeGenContext& context);
    }


};


#endif //SIMPLEPASCALCOMPILER_ABSTRACTTREE_H