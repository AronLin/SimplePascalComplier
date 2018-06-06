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
    return this->routine->CodeGen();
}

