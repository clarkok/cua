#include "visitor.h"

using namespace CUA;

void Visitor::visit(ASTChunk *) {}
void Visitor::visit(ASTStatList *) {}
void Visitor::visit(ASTAssignment *) {}
void Visitor::visit(ASTVarList *) {}
void Visitor::visit(ASTExprList *) {}
void Visitor::visit(ASTBinaryExpr *) {}
void Visitor::visit(ASTUnaryExpr *) {}
void Visitor::visit(ASTOffsetExpr *) {}
void Visitor::visit(ASTID *) {}
void Visitor::visit(ASTNumber *) {}
void Visitor::visit(ASTString *) {}
void Visitor::visit(ASTBoolean *) {}
void Visitor::visit(ASTLabel *) {}
void Visitor::visit(ASTGoto *) {}
void Visitor::visit(ASTIf *) {}