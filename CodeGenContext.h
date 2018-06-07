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

class CodeGenBlock
{
public:
    llvm::BasicBlock *block;
    llvm::Value *returnValue;
    CodeGenBlock * parent;
    std::map<std::string, llvm::Value*> locals;
};

class CodeGenContext
{
private:
    std::stack<CodeGenBlock*> blocks;
public:
    llvm::Module* module;
    llvm::Function* curFunc;
    llvm::Function* mainFunc;
    llvm::IRBuilder<> Builder;
    llvm::Value* getValue(std::string name);
    std::map<std::string, llvm::Value*>& locals() { return blocks.top()->locals; }
    void putValue(std::string name, llvm::Value* value);
    llvm::BasicBlock* curBlock() {return blocks.top()->block;};
    void pushBlock(llvm::BasicBlock *block);
    void popBlock() { CodeGenBlock *top = blocks.top(); blocks.pop(); delete top; }
    CodeGenContext();
};
