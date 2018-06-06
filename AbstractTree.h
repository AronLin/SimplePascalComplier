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
#include <iostream>
#include <sstream>
#include <string>
#include <climits>
//non-terminal node
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

//list node
class ConstExprListNode;
class TypeDefineListNode;
class VarDeclListNode;
class RoutineDeclListNode;

typedef std::list<ConstExprNode*> ConstExprList;
typedef std::list<TypeDefineNode*> TypeDefineList;
typedef std::list<VarDeclNode*> VarDeclList;
typedef std::list<RoutineDeclNodel*> RoutineDeclList;

class AbstractTree {
enum {
    NODE=0,PROGRAM,ID,ROUTINE,ROUTINE_HEAD,LABEL_PART,CONST_EXPR_LIST,CONST_EXPR,CONST_VALUE,TYPE_DEFINE_LIST,TYPE_DEFINITION,TYPE_DECL,SIMPLE_TYPE_DECL,ARRAY_TYPE_DECL,RECORD_TYPE_DECL,STMT_LIST
}NodeType;
    class Node {
    public:
        std::list<Node*> child;
        int type = NODE;
        virtual ~Node() {}
        virtual bool addChild() = 0;
        virtual std::string info() = 0;
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

        ProgramNode(){
            this->type = PROGRAM;
        }
        ProgramNode(IdNode* program_head,RoutineNode* routine){
            this->type = PROGRAM;
            this->child.push_back(program_head);
            this->child.push_back(routine);
        }

        virtual std::string info(){
            return "Program:";
        }
        virtual llvm::Value *CodeGen(CodeGenContext& context);
    };

    class RoutineNode:public Node{
    public:

        RoutineNode(){
            this->type = ROUTINE;
        }
        RoutineNode(RoutineHeadNode routine_head,RoutineBodyNode routine_body){
            //routine head
            this->type = ROUTINE;
            // this->child.push_back(routine_head);
            this->child.push_back(routine_body);

        }
        virtual std::string info(){
            return "Routine:";
        }
        virtual llvm::Value *CodeGen(CodeGenContext& context);
    };



    class StmtListNode:public Node{
        StmtListNode():type(STMT_LIST){}

        virtual llvm::Value *CodeGen(CodeGenContext& context);
    };

    class StmtNode:public Node{
        string ProcCall;
        string argument;
        virtual llvm::Value *CodeGen(CodeGenContext& context);
    };





};


#endif //SIMPLEPASCALCOMPILER_ABSTRACTTREE_H
