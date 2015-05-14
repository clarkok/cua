#include <list>
#include <string>

#include "naive-compiler.h"

using namespace CUA;

InstrumentList
NaiveCompiler::compile(ASTNode *root)
{
    root->accept(this);
    ins_list.last_result = result_name;
    return ins_list;
}

void
NaiveCompiler::visit(ASTChunk *n)
{ n->root->accept(this); }

void
NaiveCompiler::visit(ASTStatList *n)
{
    for (auto nn : n->list)
        nn->accept(this);
}

void
NaiveCompiler::visit(ASTAssignment *n)
{
    std::list<std::string> temp_list;
    
    if (n->expr_list) {
        for (auto nn : dynamic_cast<ASTExprList*>(n->expr_list)->list) {
            nn->accept(this);
            auto tmp_var = getTempName();
            ins_list.push_back(Instrument(
                Instrument::Type::I_COPY,
                tmp_var,
                result_name
            ));
            temp_list.push_back(tmp_var);
        }
    }
    
    if (n->var_list) {
        auto it = temp_list.begin();
        for (auto nn : dynamic_cast<ASTVarList*>(n->var_list)->list) {
            nn->accept(this);
            ins_list.push_back(Instrument(
                Instrument::Type::I_MOVE,
                result_name,
                (it == temp_list.end() ? "nil" : *(it++))
            ));
        }
    }
}

void NaiveCompiler::visit(ASTExprList *) {}

void NaiveCompiler::visit(ASTVarList *) {}

void
NaiveCompiler::visit(ASTBinaryExpr *n)
{
    n->left->accept(this);
    auto left_temp = result_name;
    
    n->right->accept(this);
    auto right_temp = result_name;
    
    Instrument::Type type = Instrument::Type::I_UNKNOWN;
    
    switch (n->op) {
        case ASTBinaryExpr::Operator::O_ADD:
            type = Instrument::Type::I_ADD;
            break;
        case ASTBinaryExpr::Operator::O_SUB:
            type = Instrument::Type::I_SUB;
            break;
        case ASTBinaryExpr::Operator::O_MUL:
            type = Instrument::Type::I_MUL;
            break;
        case ASTBinaryExpr::Operator::O_DIV:
            type = Instrument::Type::I_DIV;
            break;
        case ASTBinaryExpr::Operator::O_MOD:
            type = Instrument::Type::I_MOD;
            break;
        default:
            throw Exception("Operator unsupport");
    }
    
    result_name = getTempName();
    ins_list.push_back(Instrument(
        type,
        result_name,
        left_temp,
        right_temp
    ));
}

void
NaiveCompiler::visit(ASTUnaryExpr *n)
{
    n->oprand->accept(this);
    auto oprand_temp = result_name;
    
    auto left_temp = getGlobalRuntime()->newLiteral(
        getGlobalRuntime()->newNumber(0).get()
        );
        
    auto type = Instrument::Type::I_UNKNOWN;
    switch(n->op) {
        case ASTUnaryExpr::Operator::O_SUB:
            type = Instrument::Type::I_SUB;
            break;
        case ASTUnaryExpr::Operator::O_ADD:
            type = Instrument::Type::I_ADD;
            break;
        default:
            throw Exception("Operator unsupport");
    }
    
    result_name = getTempName();
    ins_list.push_back(Instrument(
        type,
        result_name,
        left_temp,
        oprand_temp
    ));
}

void
NaiveCompiler::visit(ASTOffsetExpr *n)
{
    n->oprand->accept(this);
    auto oprand_temp = result_name;
    
    n->offset->accept(this);
    auto offset_temp = result_name;
    
    result_name = getTempName();
    ins_list.push_back(Instrument(
        Instrument::Type::I_INDEX,
        result_name,
        oprand_temp,
        offset_temp
    ));
}

void
NaiveCompiler::visit(ASTID *n)
{ result_name = n->name; }

void
NaiveCompiler::visit(ASTNumber *n)
{
    result_name = getGlobalRuntime()->newLiteral(
        getGlobalRuntime()->newNumber(n->value).get()
    );
}

void
NaiveCompiler::visit(ASTString *n)
{
    result_name = getGlobalRuntime()->newLiteral(
        getGlobalRuntime()->newString(n->value).get()
    );
}

void
NaiveCompiler::visit(ASTLabel *n)
{
    ins_list.push_back(Instrument(
        Instrument::Type::I_LABEL,
        n->name
    ));
}

void
NaiveCompiler::visit(ASTGoto *n)
{
    ins_list.push_back(Instrument(
        Instrument::Type::I_GOTO,
        "::" + n->dist + "::"
    ));
}