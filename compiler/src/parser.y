%{
#include <iostream>
#include "ast.hpp"
ASTProgram* programAST;
%}

%union {
    int intVal;
    char* strVal;
    ASTProgram* program;
    ASTClass* classNode;
    ASTMethod* method;
    ASTExpr* expr;
}

%token CLASS MAIN INT_TYPE OBJECT
%token LBRACE RBRACE LPAREN RPAREN COLON SEMICOLON COMMA
%token PLUS MINUS MUL DIV
%token <intVal> INT
%token <strVal> ID

%type <program> program
%type <classNode> class
%type <method> method
%type <expr> expr

%%

program: class { programAST = new ASTProgram($1); }
       ;

class: CLASS ID LBRACE method RBRACE SEMICOLON {
          $$ = new ASTClass($2, $4);
     }
     ;

method: ID LPAREN RPAREN COLON ID LBRACE expr RBRACE SEMICOLON {
          $$ = new ASTMethod($1, $5, $7);
     }
     ;

expr: INT                    { $$ = new ASTInt($1); }
    | expr PLUS expr         { $$ = new ASTAdd($1, $3); }
    ;

%%

int yyerror(const char *msg) {
    std::cerr << "Parse error: " << msg << std::endl;
    return 1;
}
