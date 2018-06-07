//
// Created by apple on 2018/6/5.
//
#include "llvm/IR/Value.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/LLVMContext.h"
#include <vector>


#include "CodeGenContext.h"
#include "AbstractTree.h"
//Author: Ken
//file: AbstractTree.cpp
// Created by Ken on 2018/6/5. 
//QAQ


// ProgramNode should be defined in the YACC file, and passed to the CodeGenContext to do the codegen
llvm::Value* AbstractTree::ProgramNode::CodeGen(CodeGenContext& context)
{
    //TODO: create initial func and bb in context
    std::vector<llvm::Type*> args;
    llvm::FunctionType* fty = llvm::FunctionType::get(llvm::Type::getVoidTy(GlobalLLVMContext::getGlobalContext()), llvm::makeArrayRef(args),false);
    context.mainFunc = llvm::Function::Create(fty, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "main", context.module);
    llvm::BasicBlock* bb = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "entry", context.mainFunc);
    context.curFunc = context.mainFunc;
    context.pushBlock(bb);
    // Important: IRBuilder InsertPoint should be reset everytime a new BB is created
    // IRBuilder tracks the insertion point of the Instruction
    context.Builder.SetInsertPoint(bb);
    return this->routine->CodeGen(context);
}

llvm::Value* AbstractTree::RoutineNode::CodeGen(CodeGenContext& context)
{
    this->routineHead->CodeGen(context);
    //return this->routineBody->CodeGen(context);
}

void AbstractTree::TypeDeclNode::init()
{
    if (rawName == "integer")          
        sysName = AbstractTree::TypeDeclNode::TypeName::integer;
    else if (rawName == "real")        
        sysName = AbstractTree::TypeDeclNode::TypeName::real;
    else if (rawName == "char")        
        sysName = AbstractTree::TypeDeclNode::TypeName::character;
    else if (rawName == "boolean")     
        sysName = AbstractTree::TypeDeclNode::TypeName::boolean;
}

llvm::Type* AbstractTree::TypeDeclNode::toLLVMType()
{
    this->init();    
    switch(this->sysName) {
        case AbstractTree::TypeDeclNode::TypeName::integer:  
            return llvm::Type::getInt32Ty(GlobalLLVMContext::getGlobalContext());    
            break;
        case AbstractTree::TypeDeclNode::TypeName::real:     
            return llvm::Type::getDoubleTy(GlobalLLVMContext::getGlobalContext());    
            break;
        case AbstractTree::TypeDeclNode::TypeName::character:
            return llvm::Type::getInt8Ty(GlobalLLVMContext::getGlobalContext());     
            break;
        case AbstractTree::TypeDeclNode::TypeName::boolean:  
            return llvm::Type::getInt1Ty(GlobalLLVMContext::getGlobalContext());     
            break;
    }
}

llvm::Value* AbstractTree::VarDeclNode::CodeGen(CodeGenContext& context)
{
    llvm::Value* ret;
    auto go = new llvm::GlobalVariable(*context.module, this->type->toLLVMType(), false, llvm::GlobalValue::ExternalLinkage , llvm::ConstantInt::get(llvm::Type::getInt32Ty(GlobalLLVMContext::getGlobalContext()), 0, true), this->name->name);
    ret = go;
    return ret;
}

llvm::Value* AbstractTree::VarDeclListNode::CodeGen(CodeGenContext& context)
{
    llvm::Value* ret;
    for (auto i:list)
    {
        ret = i->CodeGen(context);
    }
    return ret;
}

llvm::Value* AbstractTree::RoutineHeadNode::CodeGen(CodeGenContext& context)
{
    return this->varDeclList->CodeGen(context);
}

llvm::Value* AbstractTree::IdNode::CodeGen(CodeGenContext& context)
{
    context.getValue(this->name);
    return context.Builder.CreateLoad(context.getValue(this->name), this->name);
}


llvm::Value* AbstractTree::StmtListNode::CodeGen(CodeGenContext& context)
{
    llvm::Value* ret;
    for (auto x:list)
    {
        ret = x->CodeGen(context);
    }
    return ret;
}

llvm::Value* AbstractTree::IntegerTypeNode::CodeGen(CodeGenContext& context)
{
    return llvm::ConstantInt::get(context.Builder.getInt32Ty(), this->val, true);
}

llvm::Value* AbstractTree::RealTypeNode::CodeGen(CodeGenContext& context)
{
    return llvm::ConstantFP(context.Builder.getFloatTy(), llvm::APFloat(val));
}

llvm::Value* AbstractTree::CharTypeNode::CodeGen(CodeGenContext& context)
{
    return llvm::ConstantInt::get(context.Builder.getInt8Ty(), this->val, true);
}

lvm::Value* AbstractTree::BooleanTypeNode::CodeGen(CodeGenContext& context)
{
    return llvm::ConstantInt::get(context.Builder.getInt1Ty(), this->val, true);
}

