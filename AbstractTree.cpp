//
// Created by apple on 2018/6/5.
//
#include "llvm/IR/Value.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/LLVMContext.h"


#include "CodeGenContext.h"
#include "AbstractTree.h"
//Author: Ken
//file: AbstractTree.cpp
// Created by Ken on 2018/6/5. 
//QAQ

llvm::Value* AbstractTree::ProgramNode::CodeGen(CodeGenContext& context)
{
    return this->routine->CodeGen(context);
}

llvm::Value* AbstractTree::RoutineNode::CodeGen(CodeGenContext& context)
{
    //return this->routineBody->CodeGen(context);
}

void AbstractTree::TypeDeclNode::init()
{
    if (rawName == "integer")          
        sysName = AbstractTree::TypeName::integer;
    else if (rawName == "real")        
        sysName = AbstractTree::TypeName::real;
    else if (rawName == "char")        
        sysName = AbstractTree::TypeName::character;
    else if (rawName == "boolean")     
        sysName = AbstractTree::TypeName::boolean;
}

llvm::Type* AbstractTree::TypeDeclNode::toLLVMType()
{
    this->init();    
    switch(this->sysName) {
        case AbstractTree::TypeName::integer:  
            return llvm::Type::getInt32Ty(GlobalLLVMContext::getGlobalContext());    
            break;
        case AbstractTree::TypeName::real:     
            return llvm::Type::getDoubleTy(GlobalLLVMContext::getGlobalContext());    
            break;
        case AbstractTree::TypeName::character:
            return llvm::Type::getInt8Ty(GlobalLLVMContext::getGlobalContext());     
            break;
        case AbstractTree::TypeName::boolean:  
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

