#ifndef _CUA_COMPILER_H_
#define _CUA_COMPILER_H_

#include <list>

#include "ast.h"
#include "runtime/runtime.h"
#include "runtime/value.h"
#include "runtime/scope.h"
#include "visitor.h"
#include "instrument.h"

namespace CUA {
    
    struct InstrumentList : public std::list<Instrument>
    {
        std::string last_result;
    };
    
    class Compiler : public Visitor
    {
    public:
        virtual InstrumentList compile(ASTNode *);
    };
}

#endif // _CUA_COMPILER_H_