#include "../include/ast.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/raw_ostream.h>

llvm::LLVMContext context;
llvm::Module* module = new llvm::Module("cool", context);
llvm::IRBuilder<> builder(context);

llvm::Value* ASTInt::codegen() {
    return llvm::ConstantInt::get(context, llvm::APInt(32, value));
}

llvm::Value* ASTAdd::codegen() {
    llvm::Value* l = left->codegen();
    llvm::Value* r = right->codegen();
    return builder.CreateAdd(l, r, "addtmp");
}

void ASTProgram::codegen() {
    llvm::FunctionType* FT = llvm::FunctionType::get(builder.getInt32Ty(), false);
    llvm::Function* mainFunc = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "main", module);
    llvm::BasicBlock* BB = llvm::BasicBlock::Create(context, "entry", mainFunc);
    builder.SetInsertPoint(BB);

    llvm::Value* val = mainClass->method->body->codegen();
    builder.CreateRet(val);
    module->print(llvm::outs(), nullptr);
}
