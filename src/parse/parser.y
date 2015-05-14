%skeleton "lalr1.cc"
%require "3.0.4"
%defines

%define parser_class_name {yyParser}
%debug

%{
    #include <iostream>
    #include "../ast.h"
    #include "../exception.h"
%}

%code {
    #include "driver.h"
    #include <iostream>
    #define YY_DECL yy::yyParser::symbol_type yylex(Driver &driver)
    YY_DECL;
}

%define api.value.type variant
%define api.token.constructor

%code requires {
    class Driver;
}

%param { Driver &driver }
%locations

%define api.token.prefix {T_}
%token 
    EOF 0
    SEMICOLON ";"
    DO "do"
    END "end"
    EQ "="
    NE "~="
    LE "<="
    LT "<"
    GT ">"
    GE ">="
    ADD "+"
    SUB "-"
    MUL "*"
    DIV "/"
    MOD "%"
    COMMA ","
    AND "and"
    OR "or"
    NOT "not"
    GOTO "goto"
    LEFT_PAREN "("
    RIGHT_PAREN ")"
    LEFT_BRACKET "["
    RIGHT_BRACKET "]"
    DOT "."
    IF "if"
    THEN "then"
    ELSE "else"
    ;
    
%token <std::string> ID STRING LABEL
%token <int> INT
%token <bool> TRUE FALSE

%type <CUA::ASTNode *> chunk block stmt_list stmt var_list expr_list var
%type <CUA::ASTNode *> expr compare_expr additive_expr logic_and_expr
%type <CUA::ASTNode *> multiple_expr unary_expr prefix_expr if_stmt
%type <CUA::ASTNode *> logic_or_expr
%type <CUA::ASTBinaryExpr::Operator> compare_op
%type <CUA::ASTUnaryExpr::Operator> unary_op
    
%%

chunk : block { driver.root = new CUA::ASTChunk($1); }

block : stmt_list { $$ = $1; }

stmt_list : stmt { $$ = new CUA::ASTStatList($1); }
    | stmt_list stmt
        {
            if ($2)
                dynamic_cast<CUA::ASTStatList*>($1)->list.push_back($2);
            $$ = $1;
        }

stmt : SEMICOLON { $$ = nullptr; }
    | DO block END { $$ = $2; }
    | var_list EQ expr_list { $$ = new CUA::ASTAssignment($1, $3); }
    | LABEL { $$ = new CUA::ASTLabel($1); }
    | GOTO ID { $$ = new CUA::ASTGoto($2); }
    | if_stmt { $$ = $1; }
    
if_stmt : 
    IF expr THEN stmt_list END
        { $$ = new CUA::ASTIf($2, $4); }
    | IF expr THEN stmt_list ELSE stmt_list END
        { $$ = new CUA::ASTIf($2, $4, $6); }
    
var_list : var { $$ = new CUA::ASTVarList($1); }
    | var_list COMMA var
        {
            dynamic_cast<CUA::ASTVarList*>($1)->list.push_back($3);
            $$ = $1;
        }
    
expr_list : expr { $$ = new CUA::ASTExprList($1); }
    | expr_list COMMA expr
        {
            dynamic_cast<CUA::ASTExprList*>($1)->list.push_back($3);
            $$ = $1;
        }
    
expr : logic_or_expr

logic_or_expr : logic_and_expr { $$ = $1; }
    | logic_or_expr OR logic_and_expr
        {
            $$ = new CUA::ASTBinaryExpr(
                $1,
                CUA::ASTBinaryExpr::O_OR,
                $3
            );
        }
        
logic_and_expr : compare_expr { $$ = $1; }
    | logic_and_expr AND compare_expr
        {
            $$ = new CUA::ASTBinaryExpr(
                $1,
                CUA::ASTBinaryExpr::O_AND,
                $3
            );
        }

compare_expr : additive_expr { $$ = $1; }
    | compare_expr compare_op additive_expr
        { $$ = new CUA::ASTBinaryExpr($1, $2, $3); }
    
compare_op : EQ { $$ = CUA::ASTBinaryExpr::O_EQ; }
    | NE { $$ = CUA::ASTBinaryExpr::O_NE; }
    | LE { $$ = CUA::ASTBinaryExpr::O_LE; }
    | LT { $$ = CUA::ASTBinaryExpr::O_LT; }
    | GT { $$ = CUA::ASTBinaryExpr::O_GT; }
    | GE { $$ = CUA::ASTBinaryExpr::O_GE; }

additive_expr : multiple_expr { $$ = $1; }
    | additive_expr ADD multiple_expr
        { $$ = new CUA::ASTBinaryExpr(
            $1,
            CUA::ASTBinaryExpr::O_ADD,
            $3); }
    | additive_expr SUB multiple_expr
        { $$ = new CUA::ASTBinaryExpr(
            $1,
            CUA::ASTBinaryExpr::O_SUB,
            $3); }
    
multiple_expr : unary_expr { $$ = $1; }
    | multiple_expr MUL unary_expr
        { $$ = new CUA::ASTBinaryExpr(
            $1,
            CUA::ASTBinaryExpr::O_MUL,
            $3); }
    | multiple_expr DIV unary_expr
        { $$ = new CUA::ASTBinaryExpr(
            $1,
            CUA::ASTBinaryExpr::O_DIV,
            $3); }
    | multiple_expr MOD unary_expr
        { $$ = new CUA::ASTBinaryExpr(
            $1,
            CUA::ASTBinaryExpr::O_MOD,
            $3); }
    
unary_expr : prefix_expr { $$ = $1; }
    | unary_op prefix_expr
        { $$ = new CUA::ASTUnaryExpr($1, $2); }
    
unary_op : NOT { $$ = CUA::ASTUnaryExpr::O_NOT; }
    | SUB { $$ = CUA::ASTUnaryExpr::O_SUB; }
    | ADD { $$ = CUA::ASTUnaryExpr::O_ADD; }

prefix_expr : var { $$ = $1; }
    | LEFT_PAREN expr RIGHT_PAREN { $$ = $2; }
    | INT { $$ = new CUA::ASTNumber($1); }
    | STRING { $$ = new CUA::ASTString($1); }
    | TRUE { $$ = new CUA::ASTBoolean($1); }
    | FALSE { $$ = new CUA::ASTBoolean($1); }
    
var : ID { $$ = new CUA::ASTID($1); }
    | var LEFT_BRACKET expr RIGHT_BRACKET
        { $$ = new CUA::ASTOffsetExpr($1, $3); }

%%

int
Driver::parse()
{
    scanner_begin(content);
    yy::yyParser parser(*this);
    // parser.set_debug_level(1);
    auto ret = parser.parse();
    scanner_end();
    return ret;
}

void
yy::yyParser::error(
    const location_type &loc,
    const std::string &m
) {
    auto e = CUA::Exception("Syntax error");
    e.printf("%d:%d", loc.begin.line, loc.begin.column);
    throw e;
}