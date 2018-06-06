#include <utility>

#include "CodeGenContext.h"

CodeGenContext::CodeGenContext(): Builder(GlobalLLVMContext::getGlobalContext())
{
   
}

llvm::Value* CodeGenContext::getValue(std::string name)
{
    auto result = locals.find(name);
    if (result != locals.end())
    {
        return result->second;
    }
    else
    {
        printf("Variable %s not found!\n", name);
    }
    return nullptr;
}

void CodeGenContext::putValue(std::string name, llvm::Value* value)
{
    locals.insert(make_pair(name, value));
}
