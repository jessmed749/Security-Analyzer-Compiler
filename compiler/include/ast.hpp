#pragma once
#include <string>
#include <memory>
#include <llvm/IR/Value.h>

class ASTExpr {
public:
    virtual ~ASTExpr() = default;
    virtual llvm::Value* codegen() = 0;
};

class ASTInt : public ASTExpr {
public:
    int value;
    ASTInt(int v) : value(v) {}
    llvm::Value* codegen() override;
};

class ASTAdd : public ASTExpr {
public:
    ASTExpr* left;
    ASTExpr* right;
    ASTAdd(ASTExpr* l, ASTExpr* r) : left(l), right(r) {}
    llvm::Value* codegen() override;
};

class ASTMethod {
public:
    std::string name;
    std::string returnType;
    ASTExpr* body;
    ASTMethod(char* n, char* rt, ASTExpr* b) : name(n), returnType(rt), body(b) {}
};

class ASTClass {
public:
    std::string name;
    ASTMethod* method;
    ASTClass(char* n, ASTMethod* m) : name(n), method(m) {}
};

class ASTProgram {
public:
    ASTClass* mainClass;
    ASTProgram(ASTClass* c) : mainClass(c) {}
    void codegen(); // still void because it prints the module
};
