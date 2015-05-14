#include "runtime/operate.h"
#include "casting.h"
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
        case InstrumentType::I_LAND:
            current_scope->getReferenceByName(ins.rd)->reset(
                Operate::land(
                    *current_scope->getReferenceByName(ins.rs),
                    *current_scope->getReferenceByName(ins.rt)
                )
            );
            break;
        case InstrumentType::I_LOR:
            current_scope->getReferenceByName(ins.rd)->reset(
                Operate::lor(
                    *current_scope->getReferenceByName(ins.rs),
                    *current_scope->getReferenceByName(ins.rt)
                )
            );
            break;
        case InstrumentType::I_LNOT:
            current_scope->getReferenceByName(ins.rd)->reset(
                Operate::lnot(
                    *current_scope->getReferenceByName(ins.rs)
                )
            );
            break;
        case InstrumentType::I_EQ:
            current_scope->getReferenceByName(ins.rd)->reset(
                Operate::seq(
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
        case InstrumentType::I_LABEL:
            break;
        case InstrumentType::I_GOTO:
            {
                auto label_iter = label_map.find(ins.rd);
                if (label_iter == label_map.end())
                    throw Exception("No label found", ins.rd);
                iter = label_iter->second;
                break;
            }
        case InstrumentType::I_GOTOIF:
            {
                if (
                    from_ref<bool>(
                        *current_scope->getReferenceByName(ins.rs))
                ) {
                    auto label_iter = label_map.find(ins.rd);
                    if (label_iter == label_map.end())
                        throw Exception("No label found", ins.rd);
                    iter = label_iter->second;
                }
                break;
            }
        default:
            throw Exception("Unknown instrument type", 
                ERE(InstrumentType)
                    ->toString(iter->type));
    }
    ++iter;
}

void
NaiveVM::countLabel(InstrumentList &inss)
{
    label_map.clear();
    for (auto i = inss.begin(); i != inss.end(); ++i)
        if (i->type == InstrumentType::I_LABEL)
            label_map.insert(std::make_pair(i->rd, i));
}

void
NaiveVM::run(InstrumentList inss)
{
    countLabel(inss);
    auto i = inss.begin();
    current_scope = getGlobalRuntime()->createScope();
    while (i != inss.end()) {
        execInstrument(*i, inss, i);
    }
}