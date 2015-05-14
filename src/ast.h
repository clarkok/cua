#ifndef _CUA_AST_H_
#define _CUA_AST_H_

#include <list>
#include <string>

#include "visitor.h"

namespace CUA {
    
#define visitor_accept  \
    virtual void        \
    accept(Visitor *v)  \
    { v->visit(this); }
    
    
    struct ASTNode
    {
        visitor_accept
    };
    
    struct ASTChunk : public ASTNode
    {
        ASTNode *root;
        
        ASTChunk(ASTNode *root)
        : root(root) { }
        
        visitor_accept
    };
    
    struct ASTStatList : public ASTNode
    {
        std::list<ASTNode *> list;
        
        ASTStatList(ASTNode *stat)
        { list.push_back(stat); }
        
        visitor_accept
    };
    
    struct ASTAssignment : public ASTNode
    {
        ASTNode *var_list;
        ASTNode *expr_list;
        
        ASTAssignment(ASTNode *var_list, ASTNode *expr_list)
        : var_list(var_list), expr_list(expr_list)
        { }
        
        visitor_accept
    };
    
    struct ASTVarList : public ASTNode
    {
        std::list<ASTNode *> list;
        
        ASTVarList(ASTNode *var)
        { list.push_back(var); }
        
        visitor_accept
    };
    
    struct ASTExprList : public ASTNode
    {
        std::list<ASTNode *> list;
        
        ASTExprList(ASTNode *var)
        { list.push_back(var); }
        
        visitor_accept
    };
    
    struct ASTBinaryExpr : public ASTNode
    {
        ASTNode *left, *right;
        
        enum Operator
        {
            O_UNKNOWN = 0,
            O_EQ,
            O_NE,
            O_LE,
            O_LT,
            O_GT,
            O_GE,
            O_ADD,
            O_SUB,
            O_MUL,
            O_DIV,
            O_MOD,
            O_AND,
            O_OR
        };
        
        Operator op;
        
        ASTBinaryExpr(ASTNode *left, Operator op, ASTNode *right)
        : left(left), right(right), op(op)
        { }
        
        visitor_accept
    };
    
    struct ASTUnaryExpr : public ASTNode
    {
        ASTNode *oprand;
        
        enum Operator
        {
            O_UNKNOWN = 0,
            O_NOT,
            O_SUB,
            O_ADD
        };
        
        Operator op;
        
        ASTUnaryExpr(Operator op, ASTNode *oprand)
        : op(op), oprand(oprand)
        { }
        
        visitor_accept
    };
    
    struct ASTOffsetExpr : public ASTNode
    {
        ASTNode *oprand;
        ASTNode *offset;
        
        ASTOffsetExpr(ASTNode *oprand, ASTNode *offset)
        : oprand(oprand), offset(offset)
        { }
        
        visitor_accept
    };
    
    struct ASTID : public ASTNode
    {
        std::string name;
        
        ASTID(std::string name)
        : name(name)
        { }
        
        visitor_accept
    };
    
    struct ASTNumber : public ASTNode
    {
        int value;
        
        ASTNumber(int value)
        : value(value)
        { }
        
        visitor_accept
    };
    
    struct ASTString : public ASTNode
    {
        std::string value;
        
        ASTString(std::string value)
        : value(value)
        { }
        
        visitor_accept
    };
    
    struct ASTBoolean : public ASTNode
    {
        bool value;
        ASTBoolean(bool value)
        : value(value)
        { }
        
        visitor_accept
    };
    
    struct ASTLabel : public ASTNode
    {
        std::string name;
        
        ASTLabel(std::string name)
        : name(name)
        { }
        
        visitor_accept
    };
    
    struct ASTGoto : public ASTNode
    {
        std::string dist;
        
        ASTGoto(std::string dist)
        : dist(dist)
        { }
        
        visitor_accept
    };
    
    struct ASTIf : public ASTNode
    {
        ASTNode *condition;
        ASTNode *then_stmt;
        ASTNode *else_stmt;
        
        ASTIf(
            ASTNode *condition,
            ASTNode *then_stmt,
            ASTNode *else_stmt = nullptr
        )
        : condition(condition),
          then_stmt(then_stmt),
          else_stmt(else_stmt)
        { }
        
        visitor_accept
    };
    
#undef visitor_accept
}

#endif // _CUA_AST_H_