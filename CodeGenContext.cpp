#include <utility>

#include "CodeGenContext.h"

CodeGenContext::CodeGenContext() : Builder(GlobalLLVMContext::getGlobalContext())
{
    module = new llvm::Module("Pascal", GlobalLLVMContext::getGlobalContext());
}

llvm::Value *CodeGenContext::getValue(std::string name)
{
    llvm::Function *nowFunc = curFunc;

    if ((nowFunc->getValueSymbolTable()->lookup(name)) == NULL)
    {
        if (module->getGlobalVariable(name) == NULL)
        {
            throw std::logic_error("Undeclared variable " + name);
            return nullptr;
        }
        return module->getGlobalVariable(name);
    }
    return nowFunc->getValueSymbolTable()->lookup(name);
}

void CodeGenContext::putValue(std::string name, llvm::Value *value)
{
    blocks.top()->locals.insert(make_pair(name, value));
}

void CodeGenContext::pushBlock(llvm::BasicBlock *block)
{
    CodeGenBlock *newb = new CodeGenBlock();
    blocks.push(newb);
    blocks.top()->returnValue = nullptr;
    blocks.top()->block = block;
}

llvm::Function *CodeGenContext::getPrintfPrototype()
{
    llvm::LLVMContext &ctx = GlobalLLVMContext::getGlobalContext();
    std::vector<llvm::Type *> printf_arg_types;
    printf_arg_types.push_back(llvm::Type::getInt8PtrTy(ctx));

    llvm::FunctionType *printf_type =
            llvm::FunctionType::get(
                    llvm::Type::getInt32Ty(ctx), printf_arg_types, true);

    llvm::Function *func = llvm::Function::Create(
            printf_type, llvm::Function::ExternalLinkage,
            llvm::Twine("printf"),
            this->module
    );
    func->setCallingConv(llvm::CallingConv::C);
    return func;
}