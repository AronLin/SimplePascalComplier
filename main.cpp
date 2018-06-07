#include <iostream>

#include "CodeGenContext.h"
#include "AbstractTree.h"

extern AbstractTree::ProgramNode astRoot;

int main()
{
    CodeGenContext context;
    astRoot.CodeGen(context);
    context.Builder.CreateRetVoid();
    context.module->print(llvm::errs(), nullptr);
    return 0;
}