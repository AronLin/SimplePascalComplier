#include <map>
#include <stack>
#include <vector>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/ValueSymbolTable.h>

#include "AbstractTree.h"

class GlobalLLVMContext
{
public:
    static llvm::LLVMContext& getGlobalContext()
    {
        static llvm::LLVMContext instance;
        return instance;
    }
private:
    GlobalLLVMContext() {};
public:
    GlobalLLVMContext(GlobalLLVMContext const&) = delete;
    void operator=(GlobalLLVMContext const&) = delete;
};

class CodeGenContext
{
public:
    llvm::Module* module;
    std::map<std::string, llvm::Value*> locals;
    llvm::IRBuilder<> Builder;
    llvm::Value* getValue(std::string name);
    void putValue(std::string name, llvm::Value* value);
    CodeGenContext();
};
