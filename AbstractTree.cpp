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

// ProgramNode should be defined in the YACC file, and passed to the CodeGenContext to do the CodeGen
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
    std::cout << "CG Program Node\nAddr Routine: " << this->routine << std::endl;
    //std::cout << "Addr this: " << this << std::endl;
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
    std::cout << "CG RoutineHeadNode" << std::endl;
    return this->varDeclList->CodeGen(context);
}

llvm::Value *AbstractTree::IdNode::CodeGen(CodeGenContext &context)
{
    context.getValue(this->name);
    return context.Builder.CreateLoad(context.getValue(this->name));
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

llvm::Value *AbstractTree::IfStmtNode::CodeGen(CodeGenContext &context)
{
    llvm::Value *cond_value = condition->CodeGen(context);
    if (!cond_value)
        return nullptr;

    llvm::Function *TheFunction = context.Builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *then_block = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "then", context.curFunc);
    llvm::BasicBlock *else_block = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "else", context.curFunc);
    llvm::BasicBlock *merge_block = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "merge", context.curFunc);

    //条件分支
    context.Builder.CreateCondBr(cond_value, then_block, else_block);
    //
    // Emit then value.
    context.Builder.SetInsertPoint(then_block);

    llvm::Value *then_value = thenStmt->CodeGen(context);
    if (!then_value)
        return nullptr;

    context.Builder.CreateBr(merge_block);
    // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
    then_block = context.Builder.GetInsertBlock();

    // Emit else block.
    TheFunction->getBasicBlockList().push_back(else_block);
    context.Builder.SetInsertPoint(else_block);

    llvm::Value *else_value = elseStmt->CodeGen(context);
    if (!else_value)
        return nullptr;

    context.Builder.CreateBr(merge_block);
    // Codegen of 'Else' can change the current block, update ElseBB for the PHI.
    else_block = context.Builder.GetInsertBlock();

    // Emit merge block.
    TheFunction->getBasicBlockList().push_back(merge_block);
    context.Builder.SetInsertPoint(merge_block);
    llvm::PHINode *PN = context.Builder.CreatePHI(llvm::Type::getDoubleTy(GlobalLLVMContext::getGlobalContext()), 2, "iftmp");

    PN->addIncoming(then_value, then_block);
    PN->addIncoming(else_value, else_block);
    return PN;
}

llvm::Value *AbstractTree::BinaryNode::CodeGen(CodeGenContext &context)
{
    llvm::Value *L = lhs->CodeGen(context);
    llvm::Value *R = rhs->CodeGen(context);
    if (!L || !R)
        return nullptr;
    if (L->getType()->isDoubleTy() || R->getType()->isDoubleTy())
    {
        //only arithmetic
        if (!L->getType()->isDoubleTy())
        { //L is a int; change it to double;
            L = context.Builder.CreateUIToFP(L, llvm::Type::getDoubleTy(GlobalLLVMContext::getGlobalContext()));
        }
        if (!R->getType()->isDoubleTy())
        { //R is a int; change it to double;
            R = context.Builder.CreateUIToFP(R, llvm::Type::getDoubleTy(GlobalLLVMContext::getGlobalContext()));
        }
        switch (op)
        {
        case OpType::PLUS:
            return context.Builder.CreateFAdd(L, R, "add");
        case OpType::MINUS:
            return context.Builder.CreateFSub(L, R, "sub");
        case OpType::MUL:
            return context.Builder.CreateFMul(L, R, "mul");
        case OpType::DIV:
            return context.Builder.CreateFDiv(L, R, "div");
        case OpType::MOD:
            return context.Builder.CreateFRem(L, R, "mod");

        case OpType::LT:
            return context.Builder.CreateFCmpULT(L, R, "lt_cmp");
        case OpType::LE:
            return context.Builder.CreateFCmpULT(L, R, "le_cmp");
        case OpType::GT:
            return context.Builder.CreateFCmpUGT(L, R, "gt_cmp");
        case OpType::GE:
            return context.Builder.CreateFCmpUGE(L, R, "ge_cmp");
        case OpType::UNEQUAL:
            return context.Builder.CreateFCmpUNE(L, R, "ne_cmp");
        case OpType::EQUAL:
            return context.Builder.CreateFCmpUEQ(L, R, "eq_cmp");
        default:
            std::cout << "invalid binary operator" << std::endl;
        }
    }
    else
    { // bool and char are also int
        switch (op)
        {
        case OpType::PLUS:
            return context.Builder.CreateAdd(L, R, "add");
        case OpType::MINUS:
            return context.Builder.CreateSub(L, R, "sub");
        case OpType::MUL:
            return context.Builder.CreateMul(L, R, "mul");
        case OpType::DIV:
            return context.Builder.CreateSDiv(L, R, "div"); //有符号除法
        case OpType::MOD:
            return context.Builder.CreateSRem(L, R, "mod");
        case OpType::LT:
            return context.Builder.CreateICmpSLT(L, R, "lt_cmp"); //统统用有符号比较 正常的字母小于128...
        case OpType::LE:
            return context.Builder.CreateICmpSLT(L, R, "le_cmp");
        case OpType::GT:
            return context.Builder.CreateICmpSGT(L, R, "gt_cmp");
        case OpType::GE:
            return context.Builder.CreateICmpSGE(L, R, "ge_cmp");
        case OpType::UNEQUAL:
            return context.Builder.CreateICmpNE(L, R, "ne_cmp");
        case OpType::EQUAL:
            return context.Builder.CreateICmpEQ(L, R, "eq_cmp");
        case OpType::AND:
            return context.Builder.CreateAnd(L, R, "and");
        case OpType::OR:
            return context.Builder.CreateOr(L, R, "or");
        case OpType::XOR:
            return context.Builder.CreateXor(L, R, "xor");

        default:
            std::cout << "invalid binary operator" << std::endl;
        }
    }
}

llvm::Value *AbstractTree::ConstExprNode::CodeGen(CodeGenContext &context)
{
    auto alloc = context.Builder.CreateAlloca(this->constType->toLLVMType(), 0, nullptr, this->id->name.c_str());
    auto store = context.Builder.CreateStore(this->const_value->CodeGen(context), alloc);
    return store;
}

llvm::Value *AbstractTree::ConstExprListNode::CodeGen(CodeGenContext &context)
{
    llvm::Value *ret;
    for (auto x : this->const_expr_list)
    {
        ret = x->CodeGen(context);
    }
    return ret;
}

llvm::Value *AbstractTree::WhileStmtNode::CodeGen(CodeGenContext &context)
{
    llvm::BasicBlock *loopStartB = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "loopStart", context.curFunc);
    llvm::BasicBlock *loopStmtB = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "loopStmt", context.curFunc);
    llvm::BasicBlock *loopEndB = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "loopEnd", context.curFunc);

    context.Builder.CreateBr(loopStartB);
    context.pushBlock(loopStartB);
    // Loop Start, Cond
    context.Builder.SetInsertPoint(loopStartB);
    llvm::Value *test = this->condition->CodeGen(context);
    llvm::Value *ret = context.Builder.CreateCondBr(test, loopStmtB, loopEndB);

    context.pushBlock(loopStmtB);
    context.Builder.SetInsertPoint(loopStmtB);
    this->loopStmt->CodeGen(context);
    context.Builder.CreateBr(loopStartB);

    context.popBlock();
    context.pushBlock(loopEndB);
    context.Builder.SetInsertPoint(loopEndB);

    return ret;
}

llvm::Value *AbstractTree::ForStmtNode::CodeGen(CodeGenContext &context)
{
    llvm::BasicBlock *loopEntryB = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "loopEntry", context.curFunc);
    llvm::BasicBlock *loopStmtB = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "loopStmt", context.curFunc);
    llvm::BasicBlock *loopEndB = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "loopEnd", context.curFunc);
    llvm::BasicBlock *loopExitB = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "loopExit", context.curFunc);

    context.Builder.CreateBr(loopEntryB);
    context.pushBlock(loopEntryB);
    context.Builder.SetInsertPoint(loopEntryB);

    AbstractTree::AssignStmtNode *assign = new AbstractTree::AssignStmtNode(this->id, this->start);
    assign->CodeGen(context);
    context.Builder.CreateBr(loopStmtB);
    context.popBlock();
    context.pushBlock(loopStmtB);

    context.Builder.SetInsertPoint(loopStmtB);
    this->loopStmt->CodeGen(context);
    context.Builder.CreateBr(loopEndB);
    context.popBlock();
    context.pushBlock(loopEndB);

    context.Builder.SetInsertPoint(loopEndB);
    auto int1 = new AbstractTree::IntegerTypeNode(1);
    AbstractTree::BinaryNode *binOP;
    if (this->direction == 1)
    {
        binOP = new AbstractTree::BinaryNode(this->id, AbstractTree::BinaryNode::OpType::PLUS, int1);
    }
    else
    {
        binOP = new AbstractTree::BinaryNode(this->id, AbstractTree::BinaryNode::OpType::MINUS, int1);
    }
    binOP->CodeGen(context);
    auto testGE = new AbstractTree::BinaryNode(this->id, AbstractTree::BinaryNode::OpType::GT, this->end);
    auto test = testGE->CodeGen(context);
    auto ret = context.Builder.CreateCondBr(test, loopExitB, loopStmtB);

    context.popBlock();
    context.pushBlock(loopExitB);
    context.Builder.SetInsertPoint(loopExitB);

    return ret;
}

llvm::Value *AbstractTree::RepeatStmtNode::CodeGen(CodeGenContext &context)
{
    llvm::BasicBlock *loopStmtB = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "loopStmt", context.curFunc);
    llvm::BasicBlock *loopEndB = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "loopEnd", context.curFunc);

    context.Builder.CreateBr(loopStmtB);
    context.pushBlock(loopStmtB);
    loopStmt->CodeGen(context);
    context.Builder.SetInsertPoint(loopStmtB);
    llvm::Value *test = this->condition->CodeGen(context);
    llvm::Value *ret = context.Builder.CreateCondBr(test, loopEndB, loopStmtB);

    context.popBlock();
    context.pushBlock(loopEndB);
    context.Builder.SetInsertPoint(loopEndB);

    return ret;
}

AbstractTree::ConstExprNode::ConstExprNode(IdNode *in_id, ConstValueNode *in_const_value)
{
    this->_type = CONST_EXPR;
    this->id = in_id;
    this->const_value = in_const_value;
    this->constType = new TypeDeclNode(in_const_value->getConstType());
}

// AbstractTree::LabelStmtNode::CodeGen(CodeGenContext &context)
// {
//     context.Builder.CreateBr(context.labelBlock[label]);
//     // llvm::BranchInst::Create(context.labelBlock[label],context.currentBlock());
//     // context.pushBlock(context.labelBlock[label]);
//     return stmt->CodeGen(context);
// }

llvm::Value *AbstractTree::ProcStmtNode::CodeGen(CodeGenContext &context)
{
    llvm::Function *call = context.module->getFunction(this->id->name.c_str());
    if (!call)
        throw std::domain_error("function or procedure " + this->id->name + " is not defined.");
    std::vector<llvm::Value *> arguments;
    for (auto iter : *args->getListPtr())
    {
        arguments.push_back(iter->CodeGen(context));
    }
    return context.Builder.CreateCall(call, llvm::makeArrayRef(arguments));
}

// llvm::Value *AbstractTree::TypeDefineNode::CodeGen(CodeGenContext &context){
//     TypeDefineNode::id
// }

// llvm::Value *AbstractTree::TypeDefineListNode::CodeGen(CodeGenContext &context){
//     llvm::Value *ret;
//     for (auto i : list)
//     {
//         ret = i->CodeGen(context);
//     }
//     return ret;
// }
llvm::Value *AbstractTree::ParaDeclNode::CodeGen(CodeGenContext &context)
{

    //这里是函数的变量声明，只调用了CreateAlloca在stack上分配内存，还未调用CreateStore/Load存值
    llvm::Value *ret;
    for (auto x : nameList->list)
    {
        auto alloc = context.Builder.CreateAlloca(this->type_decl->toLLVMType(), 0, x->name);
        context.insert(x->name, alloc);
        ret = alloc;
    }
    return ret;
}

llvm::Value *AbstractTree::RoutineDeclNode::CodeGen(CodeGenContext &context)
{
    std::vector<llvm::Type *> parameter_types;
    for(auto iter : *(this->para_decl_list->list){
        parameter_types.push_back(iter->type_decl->toLLVMType());
    }
    llvm::FunctionType *function_type; 
    if(this->type == PROCEDURE){
        //TODO:
        //context or GlobalLLVMContext::getGlobalContext())
        function_type = llvm::FunctionType::get(Type::llvm::Type::getVoidTy(GlobalLLVMContext::getGlobalContext()),
                                                llvm::makeArrayRef(parameter_types), false); //不可变参数
    }else{
        function_type = llvm::FunctionType::get(this->type_decl->toLLVMType(),
                                                llvm::makeArrayRef(parameter_types), false); //不可变参数
    }
    llvm::Function* function = Function::Create(function_type, llvm::Function::ExternalLinkage, 
    this->id->name.c_str(), context.module);// module from where?

    if (function->getName() != this->id->name ) {
        // Delete the one we just made and get the existing one.
        function->eraseFromParent();
        function = context.module->getFunction(this->id->name);
    }
    // If F already has a body, reject this.
    if (!function->empty()) {
        //ErrorF("redefinition of function");
        return 0;
    }
    llvm::BasicBlock *entryBB = llvm::BasicBlock::Create(GlobalLLVMContext::getGlobalContext(), "entry", function,NULL);
    auto old_function = context.curFunc;
    context.curFunc = function;
    context.funcParent[function] = old_function;
    context.Builder.SetInsertPoint(entryBB);

    auto old_block = context.curBlock();
    // push block and start routine
    context.pushBlock(block);

    //initial parameters
    llvm::Value* parameter_value;
    auto parameter_iter = function->arg_begin();
    for(auto iter : *(this->para_decl_list->list){
        iter->CodeGen(context);
        for (auto iter2 : iter->name_list->list)
        {
            parameter_value = parameter_iter++;
            parameter_value->setName(iter2.c_str());
            auto inst = new llvm::StoreInst(parameter_value, context.getValue(iter2), false, entryBB);
        }
        
    }

    //allocate return value
    if(this->type == FUNCTION){
        //TODO:
        auto alloc = context.Builder.CreateAlloca(this->type_decl->toLLVMType(), 0, this->id->name);
    }
    sub_routine->CodeGen(context);

    //func or proce
    if (this->type == FUNCTION) {
        auto return_load = context.Builder.CreateLoad(context.getValue(this->id->name), false, "");
        llvm::ReturnInst::Create(GlobalLLVMContext::getGlobalContext(), return_load, context.currentBlock());
    }
    else if(this->type == PROCEDURE ) {
        llvm::ReturnInst::Create(GlobalLLVMContext::getGlobalContext(), context.curBlock());
        
    }

    // pop local block
    while (context.curBlock() != old_block)
        context.popBlock();
    context.curFunc = old_function;
    return function;
}

llvm::Value *AbstractTree::RoutineHeadNode::CodeGen(CodeGenContext &context){
    
    constExprList->CodeGen();

    varDeclList->CodeGen();

    //TypeDefineListNode *typeDefineNodeList;
    RoutineDeclListNode *routineDeclList;
    for(auto iter : (*routineDeclList) ){
        iter->CodeGen(context);
    }
}

llvm::Value *AbstractTree::RoutineNode::CodeGen(CodeGenContext &context){
    routineHead->CodeGen();
    return routineBody->CodeGen();
}


}