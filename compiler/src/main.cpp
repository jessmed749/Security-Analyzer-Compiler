// compiler/src/main.cpp

#include "../include/ast.hpp"
#include <iostream>

int main() {
    if (yyparse() == 0 && programAST) {
        programAST->codegen();  // Triggers real LLVM codegen
    }
    return 0;
}