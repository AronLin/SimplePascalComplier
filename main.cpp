#include <iostream>
#include <fstream>
#include "AbstractTree.h"
#include "parser.hpp"
#include "CodeGenContext.h"
#include "errorhandle.h"
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>

extern int yyparse();
extern AbstractTree::ProgramNode* astRoot;
int ParseError=0;
FILE* file;

int main()
{
    file = fopen("/home/qian/SharedFolders/Compiler/Code/SimplePascalComplier/pas/2.pas", "r");
    std::error_code EC;
    llvm::raw_fd_ostream ir("/home/qian/SharedFolders/Compiler/Code/SimplePascalComplier/pas/2.ll", EC, llvm::sys::fs::F_None);
    init_error_handle();
    yyparse();
    close_error_handle();
    if (ParseError) return 0;
    CodeGenContext context;
    astRoot->CodeGen(context);
    std::cout << std::flush;
    context.Builder.CreateRetVoid();
    context.module->print(llvm::errs(), nullptr);
    context.module->print(ir, nullptr);
    return 0;
}
