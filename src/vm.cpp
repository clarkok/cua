#include "runtime/operate.h"
#include "vm.h"

using namespace CUA;

void
VM::run(InstrumentList)
{ }

void
NaiveVM::execInstrument(
    const Instrument &ins,
    InstrumentList &inss,
    InstrumentList::iterator &iter)
{
    switch (ins.type) {
        case InstrumentType::I_ADD:
            current_scope->getReferenceByName(ins.rd)->reset(
                Operate::add(
                    *current_scope->getReferenceByName(ins.rs),
                    *current_scope->getReferenceByName(ins.rt)
                )
            );
            break;
        case InstrumentType::I_SUB:
            current_scope->getReferenceByName(ins.rd)->reset(
                Operate::sub(
                    *current_scope->getReferenceByName(ins.rs),
                    *current_scope->getReferenceByName(ins.rt)
                )
            );
            break;
        case InstrumentType::I_MUL:
            current_scope->getReferenceByName(ins.rd)->reset(
                Operate::mul(
                    *current_scope->getReferenceByName(ins.rs),
                    *current_scope->getReferenceByName(ins.rt)
                )
            );
            break;
        case InstrumentType::I_DIV:
            current_scope->getReferenceByName(ins.rd)->reset(
                Operate::div(
                    *current_scope->getReferenceByName(ins.rs),
                    *current_scope->getReferenceByName(ins.rt)
                )
            );
            break;
        case InstrumentType::I_MOD:
            current_scope->getReferenceByName(ins.rd)->reset(
                Operate::mod(
                    *current_scope->getReferenceByName(ins.rs),
                    *current_scope->getReferenceByName(ins.rt)
                )
            );
            break;
        case InstrumentType::I_INDEX:
            *current_scope->getReferenceByName(ins.rd) =
                Operate::index(
                    *current_scope->getReferenceByName(ins.rs),
                    *current_scope->getReferenceByName(ins.rt)
                );
            break;
        case InstrumentType::I_MOVE:
            current_scope->getReferenceByName(ins.rd)->reset(
                *current_scope->getReferenceByName(ins.rs)
            );
            break;
        case InstrumentType::I_COPY:
            current_scope->getReferenceByName(ins.rd)->reset(
                Operate::copy(
                    *current_scope->getReferenceByName(ins.rs))
            );
            break;
        default:
            throw Exception("Unknown instrument type");
    }
    ++iter;
}

void
NaiveVM::run(InstrumentList inss)
{
    auto i = inss.begin();
    
    current_scope = getGlobalRuntime()->createScope();
    while (i != inss.end()) {
        execInstrument(*i, inss, i);
    }
}