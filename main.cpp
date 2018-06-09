#include <iostream>
#include "AbstractTree.h"
#include "parser.hpp"
#include "CodeGenContext.h"
#include "errorhandle.h"

extern int yyparse();
extern FILE* yyin;
extern AbstractTree::ProgramNode* astRoot;

int main()
{
    FILE* fh;
    fh = fopen("/home/qian/SharedFolders/Compiler/Code/SimplePascalComplier/pas/1.pas", "r");
    yyin = fh;
    yyparse();
    CodeGenContext context;
    astRoot->CodeGen(context);
    context.Builder.CreateRetVoid();
    context.module->print(llvm::errs(), nullptr);
    return 0;
}