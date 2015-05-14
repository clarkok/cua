#ifndef _CUA_RUNTIME_H_
#define _CUA_RUNTIME_H_

#include <list>

#include "value.h"
#include "table.h"

namespace CUA {
    class Scope;
    
    class Runtime
    {
        std::list<Value *> value_pool;
        NilValue *nil_value;
        Scope *global_scope;
        mutable Reference nil_ref;
        Config::T_OID literal_count = 0;
    public:
        Runtime()
        : nil_value(new NilValue()),
          global_scope(nullptr),
          nil_ref(Reference(nil_value))
        { }
        
        inline Reference*
        getNilReference() const
        { return &nil_ref; }
        
        inline Reference
        newNumber(std::int64_t value)
        {
            auto p = new NumberValue(value);
            value_pool.push_back(p);
            return Reference(p);
        }
        
        inline Reference
        newString(std::string value)
        {
            auto p = new StringValue(value);
            value_pool.push_back(p);
            return Reference(p);
        }
        
        inline Reference
        newBoolean(bool value)
        {
            auto p = new BooleanValue(value);
            value_pool.push_back(p);
            return Reference(p);
        }
        
        inline Reference
        newTable()
        {
            auto t = new Table();
            auto p = new TableValue(t);
            value_pool.push_back(p);
            return Reference(p);
        }
        
        inline Reference
        newNil()
        { return *getNilReference(); }
        
        inline size_t
        valueCount() const
        { return value_pool.size(); }
        
        Scope*
        getGlobalScope();
        
        Scope*
        createScope();
        
        std::string
        newLiteral(Value *);
    };
    
    inline Runtime *
    getGlobalRuntime()
    {
        static Runtime global_runtime;
        return &global_runtime;
    }
}

#endif // _CUA_RUNTIME_H_