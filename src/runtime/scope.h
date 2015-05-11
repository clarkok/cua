#ifndef _CUA_SCOPE_H_
#define _CUA_SCOPE_H_

#include <string>

#include "runtime.h"
#include "value.h"
#include "table.h"

namespace CUA {
    class Scope
    {
        static Value *CHILD_SCOPE_KEY;
        
        Scope *upper_scope;
        Reference table_ref;
        Table *table;
        Table *child_scope_table;
    public:
        Scope(Scope *upper_scope)
        :
            upper_scope(upper_scope),
            table_ref(getGlobalRuntime()->newTable()),
            table(dynamic_cast<TableValue*>(
                table_ref.get()
                )->getValue())
        {
            auto child_scopes = getGlobalRuntime()->newTable();
            table->set(CHILD_SCOPE_KEY, child_scopes);
            child_scope_table = dynamic_cast<TableValue*>(
                child_scopes.get()
            )->getValue();
            
            // TODO initialize child_scopes as Array
            child_scope_table->getFromString(
                dynamic_cast<StringValue*>(
                    getGlobalRuntime()
                        ->newString(Config::LENGTH_KEY).get()
                )
            )->reset(getGlobalRuntime()->newNumber(0));
        }
        
        inline Reference*
        getReferenceByName(std::string name) const
        {
            auto ref = table->getFromString(
                dynamic_cast<StringValue*>(
                    getGlobalRuntime()
                        ->newString(name).get()
                ));
            if (
                ref->get()->getType() == Value::ValueType::V_NIL &&
                upper_scope
            )
                return upper_scope->getReferenceByName(name);
            return ref;
        }
        
        inline Scope *
        createChildScope()
        {
            auto ret = new Scope(this);
            auto length_key = 
                getGlobalRuntime()
                    ->newString(Config::LENGTH_KEY).get();
            auto length = 
                dynamic_cast<NumberValue*>(
                    child_scope_table->get(
                        length_key
                    )->get()
                )->getValue();
                
            child_scope_table->set(
                getGlobalRuntime()->newNumber(length).get(),
                ret->table_ref
            );
            child_scope_table->set(
                length_key,
                getGlobalRuntime()->newNumber(length+1)
            );
            
            return ret;
        }
    };
}

#endif // _CUA_SCOPE_H_