#ifndef _CUA_VISITOR_H_
#define _CUA_VISITOR_H_

#include "exception.h"

namespace CUA {
    struct ASTNode;
    struct ASTChunk;
    struct ASTStatList;
    struct ASTAssignment;
    struct ASTVarList;
    struct ASTExprList;
    struct ASTBinaryExpr;
    struct ASTUnaryExpr;
    struct ASTOffsetExpr;
    struct ASTID;
    struct ASTNumber;
    
#define visitor_definations \
    virtual void visit(ASTChunk *);         \
    virtual void visit(ASTStatList *);      \
    virtual void visit(ASTAssignment *);    \
    virtual void visit(ASTVarList *);       \
    virtual void visit(ASTExprList *);      \
    virtual void visit(ASTBinaryExpr *);    \
    virtual void visit(ASTUnaryExpr *);     \
    virtual void visit(ASTOffsetExpr *);    \
    virtual void visit(ASTID *);            \
    virtual void visit(ASTNumber *);
    
    class Visitor
    {
    public:
        virtual ~Visitor() = 0;
        virtual void visit(ASTNode *)
        { throw Exception("Unknown AST node type"); }
        
        visitor_definations
    };
    
#undef visitor_definations
}

#endif // _CUA_VISITOR_H_