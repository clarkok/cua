#ifndef _CUA_VM_H_
#define _CUA_VM_H_

#include <map>

#include "ast.h"
#include "visitor.h"
#include "runtime/value.h"
#include "instrument.h"
#include "compiler.h"

namespace CUA {
    class VM
    {
    public:
        virtual void run(InstrumentList);
    };
    
    class NaiveVM
    {
        void execInstrument(
            const Instrument &,
            InstrumentList &,
            InstrumentList::iterator &);
        void countLabel(InstrumentList &);
        std::map<std::string, InstrumentList::iterator> label_map;
    public:
        virtual void run(InstrumentList);
        Scope *current_scope;
    };
}

#endif // _CUA_VM_H_