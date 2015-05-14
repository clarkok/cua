#ifndef _CUA_SCOPE_H_
#define _CUA_SCOPE_H_

#include <string>

#include "runtime.h"
#include "value.h"
#include "table.h"

namespace CUA {
    class Scope : public TableValue
    {
        static StringValue *CHILD_SCOPE_KEY;
        static StringValue *UPPER_SCOPE_KEY;
        
        Table *this_table;
        Table *child_scope_table;
        Scope *upper_scope;
        Config::T_OID internal_ref_count;
        
        inline Reference*
        getOwnReferenceByName(std::string name)
        {
            return this_table->getFromString(
                dynamic_cast<StringValue*>(
                    getGlobalRuntime()
                        ->newString(name).get()
                ));
        }
        
        Reference*
        lookup(std::string name)
        {
            auto ref = getOwnReferenceByName(name);
            if (ref->getType() == Value::ValueType::V_NIL &&
                upper_scope)
                ref = upper_scope->lookup(name);
            if (ref->getType() != Value::ValueType::V_NIL)
                this_table->getFromString(
                        dynamic_cast<StringValue*>(
                            getGlobalRuntime()->newString(name).get()
                        )
                    )->reset(ref->get());
            return ref;
        }
    public:
        Scope(Scope *upper_scope)
        :
            TableValue(new Table()),
            this_table(getValue()),
            upper_scope(upper_scope),
            internal_ref_count(0)
        {
            if (upper_scope)
                this_table->getFromString(UPPER_SCOPE_KEY)->reset(
                    upper_scope);
                    
            auto child_scopes = getGlobalRuntime()->newTable();
            this_table->getFromString(CHILD_SCOPE_KEY)->reset(
                child_scopes);
                    
            child_scope_table = dynamic_cast<TableValue*>(
                child_scopes.get())->getValue();
            
            // TODO initialize child_scopes as Array
            child_scope_table->getFromString(
                dynamic_cast<StringValue*>(
                    getGlobalRuntime()
                        ->newString(Config::LENGTH_KEY).get()
                )
            )->reset(getGlobalRuntime()->newNumber(0));
        }
        
        inline Reference*
        getReferenceByName(std::string name)
        {
            if (name.substr(0, std::strlen(Config::SCOPE_LOCAL_PREFIX))
                == Config::SCOPE_LOCAL_PREFIX)
                return getOwnReferenceByName(name);
            auto ref = lookup(name);
            if (ref->getType() == Value::ValueType::V_NIL)
                return getOwnReferenceByName(name);
            return ref;
        }
        
        inline std::string
        createTemplateName()
        { 
            return
                Config::SCOPE_LOCAL_PREFIX +
                std::to_string(++internal_ref_count);
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
                
            child_scope_table->get(
                getGlobalRuntime()->newNumber(length).get())->reset(
                ret
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