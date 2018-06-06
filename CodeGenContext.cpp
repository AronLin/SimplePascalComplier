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

        return nowFunc->getValueSymbolTable()->lookup(name);
    }
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