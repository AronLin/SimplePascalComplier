#include <iostream>
#include "AbstractTree.h"
#include "parser.hpp"
#include "CodeGenContext.h"

extern int yyparse();
extern AbstractTree::ProgramNode astRoot;

int main()
{
    yyparse();
    CodeGenContext context;
    astRoot.CodeGen(context);
    context.Builder.CreateRetVoid();
    context.module->print(llvm::errs(), nullptr);
    return 0;
}