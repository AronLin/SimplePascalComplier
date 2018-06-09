#include <iostream>
#include "AbstractTree.h"
#include "parser.hpp"
#include "CodeGenContext.h"
#include "errorhandle.h"

extern int yyparse();
extern AbstractTree::ProgramNode* astRoot;
int ParseError=0;
FILE* file;

int main()
{
    file = fopen("/home/qian/SharedFolders/Compiler/Code/SimplePascalComplier/pas/1.pas", "r");
    init_error_handle();
    yyparse();
    close_error_handle();
    if (ParseError) return 0;
    CodeGenContext context;
    astRoot->CodeGen(context);
    context.Builder.CreateRetVoid();
    context.module->print(llvm::errs(), nullptr);
    return 0;
}
