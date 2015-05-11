#ifndef _CUA_VALUE_H_
#define _CUA_VALUE_H_

#include <map>
#include <string>
#include <cstdint>
#include <memory>

#include "../config.h"
#include "hash.h"

namespace CUA {
    class Value
    {
    public:
        enum class ValueType
        {
            V_UNKNOWN,
            V_NUMBER,
            V_STRING,
            V_BOOLEAN,
            V_NIL,
            V_TABLE
        };
        
        virtual ValueType 
        getType() const
        { return ValueType::V_UNKNOWN; }
    };
    
    class NumberValue : public Value
    {
        std::int64_t value;
    public:
        NumberValue(std::int64_t value)
        : value(value)
        { }
    
        virtual ValueType
        getType() const
        { return ValueType::V_NUMBER; }
        
        auto
        getValue() const -> decltype(value)
        { return value; }
    };
    
    class StringValue : public Value
    {
        std::string value;
        Config::T_OID hash;
    public:
        StringValue(std::string value)
        : value(value), hash(getDefaultHasher()(value))
        { }
    
        virtual ValueType
        getType() const
        { return ValueType::V_STRING; }
        
        auto
        getValue() const -> decltype(value)
        { return value; }
        
        auto
        getHash() const -> decltype(hash)
        { return hash; }
    };
    
    class BooleanValue : public Value
    {
        bool value;
    public:
        BooleanValue(bool value)
        : value(value)
        { }
    
        virtual ValueType
        getType() const
        { return ValueType::V_BOOLEAN; }
        
        auto
        getValue() const -> decltype(value)
        { return value; }
    };
    
    class NilValue : public Value
    {
    public:
        virtual ValueType
        getType() const
        { return ValueType::V_NIL; }
    };
    
    class Table;
    class TableValue : public Value
    {
        static Config::T_OID counter;
        
        Config::T_OID id;
        Table *ptr;
        
    public:
        TableValue(Table *pt)
        : id(++counter), ptr(pt)
        { }
        
        ~TableValue();
    
        virtual ValueType
        getType() const
        { return ValueType::V_TABLE; }
        
        Config::T_OID
        getID() const
        { return id; }
        
        inline Table *
        getValue() const
        { return ptr; }
    };
    
    class Reference
    {
        Value::ValueType type;
        Value *reference;
    public:
        Reference(Value *ref)
        { reset(ref); }
    
        inline Value::ValueType
        getType() const
        { return type; }
        
        inline Value *
        reset(Value *ref)
        {
            reference = ref;
            type = ref->getType();
            return ref;
        }
        
        inline Value *
        get() const
        { return reference; }
        
        inline
        operator Value* ()
        { return get(); }
    };
}

#endif // _CUA_VALUE_H_