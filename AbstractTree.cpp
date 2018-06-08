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
llvm::Value *AbstractTree::ProgramNode::CodeGen(CodeGenContext &context)
{
    // Create main func entry
    std::vector<llvm::Type *> args;
    llvm::FunctionType *fty = llvm::FunctionType::get(llvm::Type::getVoidTy(GlobalLLVMContext::getGlobalContext()), llvm::makeArrayRef(args), false);
    context.mainFunc = llvm::Function::Create(fty, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "main", context.module);
    llvm::BasicBlock *bb = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "entry", context.mainFunc);
    context.curFunc = context.mainFunc;
    context.pushBlock(bb);

    context.printf = context.getPrintfPrototype();
    // Important: IRBuilder InsertPoint should be reset everytime a new BB is created
    // IRBuilder tracks the insertion point of the Instruction
    context.Builder.SetInsertPoint(bb);
    return this->routine->CodeGen(context);
}

llvm::Value *AbstractTree::RoutineNode::CodeGen(CodeGenContext &context)
{
    this->routineHead->CodeGen(context);
    return this->routineBody->CodeGen(context);
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

llvm::Type *AbstractTree::TypeDeclNode::toLLVMType()
{
    this->init();
    switch (this->sysName)
    {
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

llvm::Value *AbstractTree::VarDeclNode::CodeGen(CodeGenContext &context)
{
    llvm::Value *ret;
    for (auto x : nameList->list)
    {
        auto go = new llvm::GlobalVariable(*context.module, this->type->toLLVMType(), false,
                                           llvm::GlobalValue::ExternalLinkage,
                                           llvm::ConstantInt::get(llvm::Type::getInt32Ty(GlobalLLVMContext::getGlobalContext()), 0, true), x);
        ret = go;
    }
    return ret;
}

llvm::Value *AbstractTree::VarDeclListNode::CodeGen(CodeGenContext &context)
{
    llvm::Value *ret;
    for (auto i : list)
    {
        ret = i->CodeGen(context);
    }
    return ret;
}

llvm::Value *AbstractTree::RoutineHeadNode::CodeGen(CodeGenContext &context)
{
    return this->varDeclList->CodeGen(context);
}

llvm::Value *AbstractTree::IdNode::CodeGen(CodeGenContext &context)
{
    context.getValue(this->name);
    return context.Builder.CreateLoad(context.getValue(this->name), this->name);
}

// Need refinement, get first or last?
llvm::Value *AbstractTree::StmtListNode::CodeGen(CodeGenContext &context)
{
    llvm::Value *ret;
    for (auto x : list)
    {
        ret = x->CodeGen(context);
    }
    return ret;
}

llvm::Value *AbstractTree::IntegerTypeNode::CodeGen(CodeGenContext &context)
{
    return llvm::ConstantInt::get(context.Builder.getInt32Ty(), this->val, true);
}

llvm::Value *AbstractTree::RealTypeNode::CodeGen(CodeGenContext &context)
{
    return llvm::ConstantFP::get(context.Builder.getDoubleTy(), val);
}

llvm::Value *AbstractTree::CharTypeNode::CodeGen(CodeGenContext &context)
{
    return llvm::ConstantInt::get(context.Builder.getInt8Ty(), this->val, true);
}

llvm::Value *AbstractTree::BooleanTypeNode::CodeGen(CodeGenContext &context)
{
    return llvm::ConstantInt::get(context.Builder.getInt1Ty(), this->val, true);
}

llvm::Value *AbstractTree::AssignStmtNode::CodeGen(CodeGenContext &context)
{
    return context.Builder.CreateStore(this->rhs->CodeGen(context), context.getValue(this->lhs->name));
}

llvm::Value *AbstractTree::ExpListNode::CodeGen(CodeGenContext &context)
{
    llvm::Value *ret;
    for (auto x : list)
    {
        ret = x->CodeGen(context);
    }
    return ret;
}

llvm::Value *AbstractTree::SysProcStmtNode::callPrintf(CodeGenContext &context, bool isWriteln)
{
    std::string printf_format;
    std::vector<llvm::Value *> printf_args;

    for (auto arg : *this->args->getListPtr())
    {
        auto arg_val = arg->CodeGen(context);
        if (arg_val->getType() == llvm::Type::getInt32Ty(GlobalLLVMContext::getGlobalContext()))
        {
            printf_format += "%d";
            printf_args.push_back(arg_val);
        }
        else if (arg_val->getType()->isDoubleTy())
        {
            printf_format += "%lf";
            printf_args.push_back(arg_val);
        }
        else if (arg_val->getType() == llvm::Type::getInt8PtrTy(GlobalLLVMContext::getGlobalContext()))
        {
            assert("print string" == "not implemented");
        }
    }

    if (isWriteln)
        printf_format += "\n";

    auto printf_format_const = llvm::ConstantDataArray::getString(GlobalLLVMContext::getGlobalContext(), printf_format.c_str());
    auto format_string_var = new llvm::GlobalVariable(*context.module,
                                                      llvm::ArrayType::get(llvm::IntegerType::get(GlobalLLVMContext::getGlobalContext(), 8), printf_format.size() + 1),
                                                      true, llvm::GlobalValue::PrivateLinkage, printf_format_const, ".str");
    auto zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(GlobalLLVMContext::getGlobalContext()));

    std::vector<llvm::Constant *> indices;
    indices.push_back(zero);
    indices.push_back(zero);
    auto var_ref = llvm::ConstantExpr::getGetElementPtr(format_string_var->getValueType(), format_string_var, indices);

    printf_args.insert(printf_args.begin(), var_ref);
    auto call = context.Builder.CreateCall(context.printf, llvm::makeArrayRef(printf_args), "");
    return call;
}

llvm::Value *AbstractTree::SysProcStmtNode::CodeGen(CodeGenContext &context)
{
    return this->callPrintf(context, this->id->name == "writeln");
}

llvm::Value *AbstractTree::RoutineBodyNode::CodeGen(CodeGenContext &context)
{
    return this->stmtList->CodeGen(context);
}

llvm : Value *AbstractTree::IfStmtNode::CodeGen(CodeGenContext &context)
{
    Value *cond_value = condition->CodeGen(context);
    if (!cond_value)
        return nullptr;
    
    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    BasicBlock *then_block = BasicBlock::Create(GlobalLLVMContext::
                                                    : getGlobalContext(), "then", context.currentFunction);
    BasicBlock *else_block = BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "else", context.currentFunction);
    BasicBlock *merge_block = BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "merge", context.currentFunction);

    //条件分支
    Builder.CreateCondBr(cond_value, then_block, else_block);
    //
    // Emit then value.
    Builder.SetInsertPoint(then_block);

    Value *then_value = thenStmt->codegen();
    if (!then_value)
        return nullptr;

    Builder.CreateBr(merge_block);
    // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
    then_block = Builder.GetInsertBlock();

    // Emit else block.
    TheFunction->getBasicBlockList().push_back(else_block);
    Builder.SetInsertPoint(else_block);

    Value *else_value = elseStmt->codegen();
    if (!else_value)
        return nullptr;

    Builder.CreateBr(merge_block);
    // Codegen of 'Else' can change the current block, update ElseBB for the PHI.
    else_block = Builder.GetInsertBlock();

    // Emit merge block.
    TheFunction->getBasicBlockList().push_back(merge_block);
    Builder.SetInsertPoint(merge_block);
    PHINode *PN = Builder.CreatePHI(Type::getDoubleTy(GlobalLLVMContext::getGlobalContext()), 2, "iftmp");

    PN->addIncoming(then_value, then_block);
    PN->addIncoming(else_value, else_block);
    return PN;
}

// llvm::Value* AbstractTree::RepeatStmtNode::CodeGen(CodeGenContext& context) {
//     BasicBlock *loop_block = BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "loop", context.currentFunction);
//     BasicBlock *exit_block = BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "eixt", context.currentFunction);    
//     llvm::BranchInst::Create(loop_block,context.currentBlock());

//     context.pushBlock(bloop);
//     loopStmt->CodeGen(context);
//     Value* test = condition->CodeGen( context );
//     llvm::Instruction *ret = llvm::BranchInst::Create(bexit,bloop,test,context.currentBlock());
//     context.popBlock();

//     context.pushBlock(bexit);

//     return ret;
// }
llvm::Value* AbstractTree::BinaryNode::CodeGen(CodeGenContext& context) {
    llvm::Instruction::BinaryOps instr;
    Value* op1_value = operand1->CodeGen(context);
    Value* op2_value = operand2->CodeGen(context);

    if (op1_value->getType()->isDoubleTy() || op2_value->getType()->isDoubleTy()) {
        switch (op) {
        // Arithmetic Operations
        case OpType::plus:    return llvm::BinaryOperator::Create( llvm::Instruction::FAdd,
                op1_val, op2_val, "", context.currentBlock());
        case OpType::minus:   return llvm::BinaryOperator::Create( llvm::Instruction::FSub,
                op1_val, op2_val, "", context.currentBlock());
        case OpType::mul:     return llvm::BinaryOperator::Create( llvm::Instruction::FMul,
                op1_val, op2_val, "", context.currentBlock());
        case OpType::div:     return llvm::BinaryOperator::Create( llvm::Instruction::SDiv,
                op1_val, op2_val, "", context.currentBlock());
        case OpType::mod:     return llvm::BinaryOperator::Create( llvm::Instruction::SRem,
                op1_val, op2_val, "", context.currentBlock());    
        case OpType::bit_and:     return llvm::BinaryOperator::Create( llvm::Instruction::And,
                op1_val, op2_val, "", context.currentBlock());  
        case OpType::bit_or:     return llvm::BinaryOperator::Create( llvm::Instruction::Or,
                op1_val, op2_val, "", context.currentBlock()); 
        case OpType::bit_xor:     return llvm::BinaryOperator::Create( llvm::Instruction::Xor,
                op1_val, op2_val, "", context.currentBlock()); 
        // Logical Operations
        
        case OpType::eq:  {auto ret = llvm::CmpInst::Create( llvm::Instruction::ICmp, llvm::CmpInst::ICMP_EQ,
                op1_val, op2_val, "", context.currentBlock()); 
                          std::cout << "boolean value is int1 " << ret->getType()->isIntegerTy() << std::endl;
                          return ret;}
        case OpType::ne:  return  llvm::CmpInst::Create( llvm::Instruction::ICmp, llvm::CmpInst::ICMP_NE,
                op1_val, op2_val, "", context.currentBlock());
        case OpType::lt:  return  llvm::CmpInst::Create( llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SLT,
                op1_val, op2_val, "", context.currentBlock());
        case OpType::gt:  return  llvm::CmpInst::Create( llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SGT,
                op1_val, op2_val, "", context.currentBlock());
        case OpType::le:  return  llvm::CmpInst::Create( llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SLE,
                op1_val, op2_val, "", context.currentBlock());
        case OpType::ge:  return  llvm::CmpInst::Create( llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SGE,
                op1_val, op2_val, "", context.currentBlock());
        //case OpType::and: return  llvm::cmp
        }
    } else 
    switch (op) {
    // Arithmetic Operations
    case OpType::plus:    return llvm::BinaryOperator::Create( llvm::Instruction::Add,
            op1_val, op2_val, "", context.currentBlock());
    case OpType::minus:   return llvm::BinaryOperator::Create( llvm::Instruction::Sub,
            op1_val, op2_val, "", context.currentBlock());
    case OpType::mul:     return llvm::BinaryOperator::Create( llvm::Instruction::Mul,
            op1_val, op2_val, "", context.currentBlock());
    case OpType::div:     return llvm::BinaryOperator::Create( llvm::Instruction::SDiv,
            op1_val, op2_val, "", context.currentBlock());
    case OpType::mod:     return llvm::BinaryOperator::Create( llvm::Instruction::SRem,
            op1_val, op2_val, "", context.currentBlock());    
    case OpType::bit_and:     return llvm::BinaryOperator::Create( llvm::Instruction::And,
            op1_val, op2_val, "", context.currentBlock());  
    case OpType::bit_or:     return llvm::BinaryOperator::Create( llvm::Instruction::Or,
            op1_val, op2_val, "", context.currentBlock()); 
    case OpType::bit_xor:     return llvm::BinaryOperator::Create( llvm::Instruction::Xor,
            op1_val, op2_val, "", context.currentBlock()); 
    // Logical Operations
    
    case OpType::eq:  {auto ret = llvm::CmpInst::Create( llvm::Instruction::ICmp, llvm::CmpInst::ICMP_EQ,
            op1_val, op2_val, "", context.currentBlock()); 
                      std::cout << "boolean value is int1 " << ret->getType()->isIntegerTy() << std::endl;
                      return ret;}
    case OpType::ne:  return  llvm::CmpInst::Create( llvm::Instruction::ICmp, llvm::CmpInst::ICMP_NE,
            op1_val, op2_val, "", context.currentBlock());
    case OpType::lt:  return  llvm::CmpInst::Create( llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SLT,
            op1_val, op2_val, "", context.currentBlock());
    case OpType::gt:  return  llvm::CmpInst::Create( llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SGT,
            op1_val, op2_val, "", context.currentBlock());
    case OpType::le:  return  llvm::CmpInst::Create( llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SLE,
            op1_val, op2_val, "", context.currentBlock());
    case OpType::ge:  return  llvm::CmpInst::Create( llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SGE,
            op1_val, op2_val, "", context.currentBlock());
    //case OpType::and: return  llvm::cmp
    }
    return nullptr;
llvm::Value* AbstractTree::ConstExprNode::CodeGen(CodeGenContext& context)
{
    auto alloc = context.Builder.CreateAlloca(this->constType->toLLVMType(), 0, nullptr, this->id->name.c_str());
    auto store = context.Builder.CreateStore(this->const_value->CodeGen(context), alloc);
    return store;
}

llvm::Value* AbstractTree::ConstExprListNode::CodeGen(CodeGenContext& context)
{
    llvm::Value* ret;
    for (auto x:this->const_expr_list)
    {
        ret = x->CodeGen(context);
    }
    return ret;
}

llvm::Value* AbstractTree::WhileStmtNode::CodeGen(CodeGenContext& context)
{
    llvm::BasicBlock* loopStartB = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "loopStart", context.curFunc);
    llvm::BasicBlock* loopStmtB = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "loopStmt", context.curFunc);
    llvm::BasicBlock* loopEndB = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "loopEnd", context.curFunc);

    context.Builder.CreateBr(loopStartB);
    context.pushBlock(loopStartB);
    // Loop Start, Cond
    context.Builder.SetInsertPoint(loopStartB);
    llvm::Value* test = this->condition->CodeGen(context);
    llvm::Value* ret = context.Builder.CreateCondBr(test, loopStmtB, loopEndB);

    context.pushBlock(loopStmtB);
    context.Builder.SetInsertPoint(loopStmtB);
    this->loopStmt->CodeGen(context);
    context.Builder.CreateBr(loopStartB);

    context.popBlock();
    context.pushBlock(loopEndB);
    context.Builder.SetInsertPoint(loopEndB);

    return ret;
}