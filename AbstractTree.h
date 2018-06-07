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
class IdNode;
class NameListNode;
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

//list node
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
        int type = NODE;
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
            this->type = PROGRAM;
        }
        ProgramNode(IdNode* program_head,RoutineNode* routine){
            this->type = PROGRAM;
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
            this->type = ROUTINE;
        }
        RoutineNode(RoutineHeadNode* routine_head,RoutineBodyNode* routine_body){
            //routine head
            this->type = ROUTINE;
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
        VarDeclListNode* varDeclList;
        RoutineHeadNode(VarDeclListNode* node): varDeclList(node) {};
        virtual llvm::Value* CodeGen(CodeGenContext& context);
    }

    class IdNode: public Node
    {
    public:
        std::string name;
        IdNode(const std::string& name): name(name){};
        IdNode(const char* name): name(*(new std::string(name))){};
        virtual llvm::Value* CodeGen(CodeGenContext& context);
    };

    class NameListNode: public Node
    {
    public:
        std::vector<std::string> list;
        void insert(const char* node) { std::string st(node); list.push_back(st);};
    }

    class StmtListNode:public Node{
    public:
        StmtListNode():type(STMT_LIST){}
        std::vector<StmtNode*> list;
        void insert(StmtNode* node) {list.push_back(node);};

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
        void insertNode(ExpNode* node) {list.push_back(node);};
        std::vector<ExpNode*>* getListPtr() {return &list;};
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
        NameListNode* nameList;
        TypeDeclNode* type;
        VarDeclNode* (NameListNode* names, TypeDeclNode* type): nameList(names), type(type)
        {
            //Put Children
        };
        virtual llvm::Value* CodeGen(CodeGenContext& context);

    };

    class TypeDeclNode: public Node
    {
    public:
        enum class TypeName
        {
            integer, real, character, boolean, error
        };
        std::string rawName = "";
        TypeName sysName = TypeName::error;
        TypeDeclNode(const std::string &str) : rawName(str){init();}
        TypeDeclNode(const char * ptr_c) : rawName(*(new std::string(ptr_c))) {init();}

        void init();
        virtual llvm::Value* CodeGen(CodeGenContext& context) {};
        llvm::Type* toLLVMType();
    };

    //TODO:: all func below need codegen
    class ConstValueNode: public ExpNode
    {
    public:
        TypeDeclNode::TypeName type;
        TypeDeclNode::TypeName getConstType() {return type;};
        virtual llvm::Value* CodeGen(CodeGenContext& context) = 0;
    };

    class IntegerTypeNode: public ConstValueNode
    {
    public:
        int val;
        IntegerTypeNode(int value):val(value) {type = TypeDeclNode::TypeName::integer;};
        virtual llvm::Value* CodeGen(CodeGenContext& context);
    };

    class RealTypeNode: public ConstValueNode
    {
    public:
        double val;
        RealTypeNode(double value):val(value) {type = TypeDeclNode::TypeName::real;};
        virtual llvm::Value* CodeGen(CodeGenContext& context);
    };

    class CharTypeNode: public ConstValueNode
    {
    public:
        char val;
        CharTypeNode(const char * p_str) : val(*(p_str)) {type = TypeDeclNode::TypeName::character;};
        virtual llvm::Value* CodeGen(CodeGenContext& context); 
    };

    class BooleanTypeNode: public ConstValueNode
    {
    public:
        int val;
        BooleanTypeNode(const char * str) : val(std::string(str) == "true" ? 1 : 0) {type = TypeDeclNode::TypeName::boolean;};
        virtual llvm::Value* CodeGen(CodeGenContext& context);   
    };


    class AssignStmtNode: public StmtNode
    {
    public:
        IdNode* lhs;
        ExpNode* rhs;
        AssignStmtNode(IdNode* lhs, ExpNode* rhs): lhs(lhs), rhs(rhs) {};
        virtual llvm::Value* CodeGen(CodeGenContext& context);
    };

    class ProcStmtNode: public StmtNode
    {
    public:
        IdNode* id;
        ExpListNode* args;
    }

    class SysProcStmtNode: public ProcStmtNode
    {
    public:
        SysProcStmtNode(IdNode* idd): id(idd){};
        SysProcStmtNode(IdNode* idd, ExpListNode* arg): id(idd), args(arg){};
        llvm::Value* callPrintf(CodeGenContext& context, bool writeln);
        virtual llvm::Value *CodeGen(CodeGenContext& context);
    }    
    
    class RoutineBodyNode: public Node
    {
    public:
        StmtListNode* stmtList;
        RoutineBodyNode(StmtListNode* node):stmtList(node) {};
        virtual llvm::Value* CodeGen(CodeGenContext& context);
    }

};


#endif //SIMPLEPASCALCOMPILER_ABSTRACTTREE_H
