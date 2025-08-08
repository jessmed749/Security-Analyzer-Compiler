%{
#include "parser.tab.h"
#include <cstdlib>
%}

%%
"class"     return CLASS;
"main"      return MAIN;
"Int"       return INT_TYPE;
"Object"    return OBJECT;
"{"         return LBRACE;
"}"         return RBRACE;
"("         return LPAREN;
")"         return RPAREN;
":"         return COLON;
";"         return SEMICOLON;
","         return COMMA;
"+"         return PLUS;
"-"         return MINUS;
"*"         return MUL;
"/"         return DIV;
[0-9]+      { yylval.intVal = atoi(yytext); return INT; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.strVal = strdup(yytext); return ID; }
[ \t\n\r]+  ; // skip whitespace
.           return *yytext;
%%

}
