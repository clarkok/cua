#ifndef _CUA_CASTING_H_
#define _CUA_CASTING_H_

#include <stdexcept>

#include "exception.h"

#include "runtime/value.h"
#include "runtime/runtime.h"

namespace CUA {
    
    template<typename T>
    T from_value(Value *value)
    { throw Exception("Can not cast"); }
    
    template <typename T>
    T from_ref(Reference ref)
    { throw Exception("Can not cast"); }
    
    template <typename T>
    Reference to_ref(T value)
    { throw Exception("Can not cast"); }
    
    template <> inline
    std::int64_t from_value<std::int64_t>(Value *value)
    {
        switch (value->getType()) {
            case Value::ValueType::V_NIL:
                return 0;
            case Value::ValueType::V_BOOLEAN:
                return dynamic_cast<BooleanValue*>(value)
                    ->getValue();
            case Value::ValueType::V_NUMBER:
                return dynamic_cast<NumberValue*>(value)
                    ->getValue();
            case Value::ValueType::V_STRING:
                try {
                    return std::stol(
                        dynamic_cast<StringValue*>(value)
                            ->getValue()
                    );
                } catch (const std::invalid_argument &e) {
                    return 0;
                }
            case Value::ValueType::V_TABLE:
                return dynamic_cast<TableValue*>(value)->getID();
            default:
                return 0;
        }
    }
    
    template <> inline
    std::string from_value(Value *value)
    {
        switch (value->getType()) {
            case Value::ValueType::V_NIL:
                return "nil";
            case Value::ValueType::V_BOOLEAN:
                return dynamic_cast<BooleanValue*>(value)
                    ->getValue() ? "true" : "false";
            case Value::ValueType::V_NUMBER:
                return std::to_string(dynamic_cast<NumberValue*>(value)
                    ->getValue());
            case Value::ValueType::V_STRING:
                return
                    dynamic_cast<StringValue*>(value)
                        ->getValue();
            case Value::ValueType::V_TABLE:
                return std::to_string(
                    dynamic_cast<TableValue*>(value)->getID()
                );
            default:
                return "UNKNOWN";
        }
    }
    
    template <> inline
    bool from_value(Value *value)
    {
        switch (value->getType()) {
            case Value::ValueType::V_NIL:
                return false;
            case Value::ValueType::V_BOOLEAN:
                return dynamic_cast<BooleanValue*>(value)
                    ->getValue();
            case Value::ValueType::V_NUMBER:
                return dynamic_cast<NumberValue*>(value)
                    ->getValue();
            case Value::ValueType::V_STRING:
                return dynamic_cast<StringValue*>(value)
                    ->getValue().length();
            case Value::ValueType::V_TABLE:
                return true;
            default:
                return false;
        }
    }
    
    template <> inline
    std::int64_t from_ref<std::int64_t>(Reference ref)
    { return from_value<std::int64_t>(ref.get()); }
    
    template <> inline
    std::string from_ref<std::string>(Reference ref)
    { return from_value<std::string>(ref.get()); }
    
    template <> inline
    bool from_ref<bool>(Reference ref)
    { return from_value<bool>(ref.get()); }
    
    template <> inline
    Reference to_ref<std::int64_t>(std::int64_t value)
    { return getGlobalRuntime()->newNumber(value); }
    
    template <> inline
    Reference to_ref<std::string>(std::string value)
    { return getGlobalRuntime()->newString(value); }
    
    template <> inline
    Reference to_ref<bool>(bool value)
    { return getGlobalRuntime()->newBoolean(value); }
    
    #define cast_value_to_number_ref(v) \
        to_ref<std::int64_t>(from_value<std::int64_t>(v))
    
    #define cast_value_to_string_ref(v) \
        to_ref<std::string>(from_value<std::string>(v))
        
    #define cast_value_to_boolean_ref(v) \
        to_ref<bool>(from_value<bool>(v))
        
    #define get_value(value_type, v) \
        (dynamic_cast<value_type*>(v.get()))
}

#endif // _CUA_CASTING_H_