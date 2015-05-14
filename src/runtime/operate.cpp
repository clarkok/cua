#include "operate.h"
#include "../exception.h"
#include "../casting.h"

using namespace CUA;
using namespace Operate;

Reference
CUA::Operate::add(Value *a, Value *b)
{
    return addnn(
        get_value(NumberValue, cast_value_to_number_ref(a)),
        get_value(NumberValue, cast_value_to_number_ref(b))
    );
}

Reference
CUA::Operate::addnn(NumberValue *a, NumberValue *b)
{
    return to_ref<std::int64_t>(
            a->getValue() + b->getValue()
        );
}

Reference
CUA::Operate::sub(Value *a, Value *b)
{
    return subnn(
        get_value(NumberValue, cast_value_to_number_ref(a)),
        get_value(NumberValue, cast_value_to_number_ref(b))
    );
}

Reference
CUA::Operate::subnn(NumberValue *a, NumberValue *b)
{
    return to_ref<std::int64_t>(
            a->getValue() - b->getValue()
        );
}

Reference
CUA::Operate::mul(Value *a, Value *b)
{
    return mulnn(
        get_value(NumberValue, cast_value_to_number_ref(a)),
        get_value(NumberValue, cast_value_to_number_ref(b))
    );
}

Reference
CUA::Operate::mulnn(NumberValue *a, NumberValue *b)
{
    return to_ref<std::int64_t>(
            a->getValue() * b->getValue()
        );
}

Reference
CUA::Operate::div(Value *a, Value *b)
{
    return divnn(
        get_value(NumberValue, cast_value_to_number_ref(a)),
        get_value(NumberValue, cast_value_to_number_ref(b))
    );
}

Reference
CUA::Operate::divnn(NumberValue *a, NumberValue *b)
{
    return to_ref<std::int64_t>(
            a->getValue() / b->getValue()
        );
}

Reference
CUA::Operate::mod(Value *a, Value *b)
{
    return modnn(
        get_value(NumberValue, cast_value_to_number_ref(a)),
        get_value(NumberValue, cast_value_to_number_ref(b))
    );
}

Reference
CUA::Operate::modnn(NumberValue *a, NumberValue *b)
{
    return to_ref<std::int64_t>(
            a->getValue() % b->getValue()
        );
}

Reference
CUA::Operate::index(Value *a, Value *b)
{
    if (a->getType() != Value::ValueType::V_TABLE)
        throw Exception("Unable to index value");
    return *dynamic_cast<TableValue*>(a)->getValue()->get(b);
}

Reference
CUA::Operate::copy(Value *a)
{
    switch (a->getType()) {
        case Value::ValueType::V_NUMBER:
            return to_ref<std::int64_t>(
                dynamic_cast<NumberValue*>(a)->getValue());
        case Value::ValueType::V_STRING:
            return to_ref<std::string>(
                dynamic_cast<StringValue*>(a)->getValue());
        case Value::ValueType::V_BOOLEAN:
            return to_ref<bool>(
                dynamic_cast<BooleanValue*>(a)->getValue());
        case Value::ValueType::V_TABLE:
            return Reference(a);
        default:
            return getGlobalRuntime()->newNil();
    }
}