%{
    #include <iostream>
    #include "../exception.h"
    #include "../ast.h"
    #include "driver.h"
    #include "parser.yy.hpp"
    
    #undef yywrap
    
    static yy::location loc;
    #define YY_DECL yy::yyParser::symbol_type yylex(Driver &driver)
%}

id [a-zA-Z_$][a-zA-Z0-9_$]*
int [0-9]+
blanks [ \t\v\h]+
string \"(\\.|[^\\"])*\"
label ::{id}::

%{
    #define YY_USER_ACTION loc.columns (yyleng);
%}

%%

%{
    loc.step();
%}

{blanks}  loc.step();
[\n]+   loc.lines(yyleng); loc.step();

";" return yy::yyParser::make_SEMICOLON(loc);
"do" return yy::yyParser::make_DO(loc);
"end" return yy::yyParser::make_END(loc);
"and" return yy::yyParser::make_AND(loc);
"or" return yy::yyParser::make_OR(loc);
"not" return yy::yyParser::make_NOT(loc);
"goto" return yy::yyParser::make_GOTO(loc);
"if" return yy::yyParser::make_IF(loc);
"then" return yy::yyParser::make_THEN(loc);
"else" return yy::yyParser::make_ELSE(loc);
"true" return yy::yyParser::make_TRUE(true, loc);
"false" return yy::yyParser::make_FALSE(false, loc);
"=" return yy::yyParser::make_EQ(loc);
"," return yy::yyParser::make_COMMA(loc);
"(" return yy::yyParser::make_LEFT_PAREN(loc);
")" return yy::yyParser::make_RIGHT_PAREN(loc);
"[" return yy::yyParser::make_LEFT_BRACKET(loc);
"]" return yy::yyParser::make_RIGHT_BRACKET(loc);
"+" return yy::yyParser::make_ADD(loc);
"-" return yy::yyParser::make_SUB(loc);
"*" return yy::yyParser::make_MUL(loc);
"/" return yy::yyParser::make_DIV(loc);
"%" return yy::yyParser::make_MOD(loc);
"==" return yy::yyParser::make_EQ(loc);
"~=" return yy::yyParser::make_NE(loc);
"<=" return yy::yyParser::make_LE(loc);
"<" return yy::yyParser::make_LT(loc);
">=" return yy::yyParser::make_GE(loc);
">" return yy::yyParser::make_GT(loc);

{int} {
    long n = strtol(yytext, nullptr, 10);
    return yy::yyParser::make_INT(n, loc);
}

{id} return yy::yyParser::make_ID(yytext, loc);

{string} return yy::yyParser::make_STRING(yytext, loc);

{label} return yy::yyParser::make_LABEL(yytext, loc);

"." return yy::yyParser::make_DOT(loc);

. {
    auto e = CUA::Exception("Unexpect char");
    e.printf(
        "'%c'(#%d) at %d %d",
        yytext[0],
        yytext[0],
        loc.begin.line,
        loc.begin.column
    );
    throw e;
}

<<EOF>> return yy::yyParser::make_EOF(loc);

%%
int yywrap() {
    return 1;
}

void
Driver::scanner_begin(const char *content)
{
    loc = yy::location();
    if (content)
        this->content = content;
    else
        content = this->content;
    yy_scan_string(content);
}

void
Driver::scanner_end()
{ }