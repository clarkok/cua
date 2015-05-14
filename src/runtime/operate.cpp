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
CUA::Operate::slt(Value *a, Value *b)
{
    if (
        a->getType() == Value::ValueType::V_STRING ||
        b->getType() == Value::ValueType::V_STRING
    )
        return sltss(
            get_value(StringValue, cast_value_to_string_ref(a)),
            get_value(StringValue, cast_value_to_string_ref(b))
        );
    else
        return sltnn(
            get_value(NumberValue, cast_value_to_number_ref(a)),
            get_value(NumberValue, cast_value_to_number_ref(b))
        );
}

Reference
CUA::Operate::sltnn(NumberValue *a, NumberValue *b)
{
    return to_ref<bool>(
            a->getValue() < b->getValue()
        );
}

Reference
CUA::Operate::sltss(StringValue *a, StringValue *b)
{
    return to_ref<bool>(
            a->getValue() < b->getValue()
        );
}

Reference
CUA::Operate::sle(Value *a, Value *b)
{
    if (
        a->getType() == Value::ValueType::V_STRING ||
        b->getType() == Value::ValueType::V_STRING
    )
        return sless(
            get_value(StringValue, cast_value_to_string_ref(a)),
            get_value(StringValue, cast_value_to_string_ref(b))
        );
    else
        return slenn(
            get_value(NumberValue, cast_value_to_number_ref(a)),
            get_value(NumberValue, cast_value_to_number_ref(b))
        );
}

Reference
CUA::Operate::slenn(NumberValue *a, NumberValue *b)
{
    return to_ref<bool>(
            a->getValue() <= b->getValue()
        );
}

Reference
CUA::Operate::sless(StringValue *a, StringValue *b)
{
    return to_ref<bool>(
            a->getValue() <= b->getValue()
        );
}

Reference
CUA::Operate::seq(Value *a, Value *b)
{
    if (a->getType() != b->getType())
        return to_ref<bool>(false);
    switch (a->getType()) {
        case Value::ValueType::V_NUMBER:
            return to_ref<bool>(
                    dynamic_cast<NumberValue*>(a)->getValue() ==
                    dynamic_cast<NumberValue*>(b)->getValue()
                );
        case Value::ValueType::V_STRING:
            return to_ref<bool>(
                    dynamic_cast<StringValue*>(a)->getValue() ==
                    dynamic_cast<StringValue*>(b)->getValue()
                );
        case Value::ValueType::V_BOOLEAN:
            return to_ref<bool>(
                    dynamic_cast<BooleanValue*>(a)->getValue() ==
                    dynamic_cast<BooleanValue*>(b)->getValue()
                );
        case Value::ValueType::V_TABLE:
            return to_ref<bool>(
                    dynamic_cast<TableValue*>(a)->getID() ==
                    dynamic_cast<TableValue*>(b)->getID()
                );
        default:
            return to_ref<bool>(false);
    }
}

Reference
CUA::Operate::land(Value *a, Value *b)
{
    return landbb(
        get_value(BooleanValue, cast_value_to_boolean_ref(a)),
        get_value(BooleanValue, cast_value_to_boolean_ref(b))
    );
}

Reference
CUA::Operate::landbb(BooleanValue *a, BooleanValue *b)
{
    return to_ref<bool>(
        a->getValue() && b->getValue()
    );
}

Reference
CUA::Operate::lor(Value *a, Value *b)
{
    return lorbb(
        get_value(BooleanValue, cast_value_to_boolean_ref(a)),
        get_value(BooleanValue, cast_value_to_boolean_ref(b))
    );
}

Reference
CUA::Operate::lorbb(BooleanValue *a, BooleanValue *b)
{
    return to_ref<bool>(
        a->getValue() || b->getValue()
    );
}

Reference
CUA::Operate::lnot(Value *a)
{
    return lnotb(
        get_value(BooleanValue, cast_value_to_boolean_ref(a))
    );
}

Reference
CUA::Operate::lnotb(BooleanValue *a)
{
    return to_ref<bool>(
        !a->getValue()
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