#include "../exception.h"

#include "runtime.h"
#include "value.h"
#include "table.h"

using namespace CUA;

Reference*
Table::get(Value *v)
{
    switch (v->getType()) {
        case Value::ValueType::V_UNKNOWN: {
            auto e = Exception("Internal error", "Unknown value type");
            e.printf(" at %s:%d", __FILE__, __LINE__);
            throw e;
        }
        case Value::ValueType::V_NUMBER: 
            return getFromNumber(dynamic_cast<NumberValue*>(v));
        case Value::ValueType::V_STRING:
            return getFromString(dynamic_cast<StringValue*>(v));
        case Value::ValueType::V_BOOLEAN:
            return getFromBoolean(dynamic_cast<BooleanValue*>(v));
        case Value::ValueType::V_TABLE:
            return getFromTable(dynamic_cast<TableValue*>(v));
        case Value::ValueType::V_NIL:
            return getGlobalRuntime()->getNilReference();
    }
}

void
Table::erase(Value *v)
{
    switch (v->getType()) {
        case Value::ValueType::V_UNKNOWN: {
            auto e = Exception("Internal error", "Unknown value type");
            e.printf(" at %s:%d", __FILE__, __LINE__);
            throw e;
        }
        case Value::ValueType::V_NUMBER: 
            return eraseFromNumber(dynamic_cast<NumberValue*>(v));
        case Value::ValueType::V_STRING:
            return eraseFromString(dynamic_cast<StringValue*>(v));
        case Value::ValueType::V_BOOLEAN:
            return eraseFromBoolean(dynamic_cast<BooleanValue*>(v));
        case Value::ValueType::V_TABLE:
            return eraseFromTable(dynamic_cast<TableValue*>(v));
        case Value::ValueType::V_NIL: ;
    }
}

Reference*
Table::getFromNumber(NumberValue *v)
{
    auto iter = table.find(v->getValue());
    if (iter != table.end())
        for (auto &p : iter->second)
            if (p.first->getType() == Value::ValueType::V_NUMBER)
                return &p.second;
    if (iter == table.end())
        iter = table.insert(
                iter, 
                std::make_pair(v->getValue(), std::list<Pair>()));
    iter->second.push_back(
        std::make_pair(
            dynamic_cast<Value*>(v),
            getGlobalRuntime()->newNil()));
    return &iter->second.back().second;
}

void
Table::eraseFromNumber(NumberValue *v)
{
    auto iter = table.find(v->getValue());
    if (iter != table.end())
        for (
            auto it = iter->second.begin();
            it != iter->second.end();
            ++it
        ) {
            auto &p = *it;
            if (p.first->getType() == Value::ValueType::V_NUMBER) {
                iter->second.erase(it);
                --size_;
                return;
            }
        }
}

Reference*
Table::getFromString(StringValue *v)
{
    auto iter = table.find(v->getHash());
    if (iter != table.end())
        for (auto &p : iter->second)
            if (
                p.first->getType() == Value::ValueType::V_STRING &&
                dynamic_cast<StringValue*>(p.first)->getValue() ==
                    v->getValue()
            )
                return &p.second;
    if (iter == table.end())
        iter = table.insert(
            iter, 
            std::make_pair(v->getHash(), std::list<Pair>()));
    iter->second.push_back(
        std::make_pair(
            dynamic_cast<Value*>(v),
            getGlobalRuntime()->newNil()));
    return &iter->second.back().second;
}

void
Table::eraseFromString(StringValue *v)
{
    auto iter = table.find(v->getHash());
    if (iter != table.end()) {
        for (
            auto it = iter->second.begin();
            it != iter->second.end();
            ++it
        ) {
            auto &p = *it;
            if (
                p.first->getType() == Value::ValueType::V_STRING &&
                dynamic_cast<StringValue*>(p.first)->getValue() ==
                    v->getValue()
            ) {
                iter->second.erase(it);
                --size_;
                return;
            }
        }
    }
}

Reference*
Table::getFromBoolean(BooleanValue *v)
{
    auto iter = table.find(v->getValue() ? 1 : 0);
    if (iter != table.end())
        for (auto &p : iter->second)
            if (p.first->getType() == Value::ValueType::V_BOOLEAN)
                return &p.second;
    if (iter == table.end())
        iter = table.insert(
            iter, 
            std::make_pair(v->getValue() ? 1 : 0, std::list<Pair>()));
    iter->second.push_back(
        std::make_pair(
            dynamic_cast<Value*>(v),
            getGlobalRuntime()->newNil()));
    return &iter->second.back().second;
}

void
Table::eraseFromBoolean(BooleanValue *v)
{
    auto iter = table.find(v->getValue());
    if (iter != table.end())
        for (
            auto it = iter->second.begin();
            it != iter->second.end();
            ++it
        ) {
            auto &p = *it;
            if (p.first->getType() == Value::ValueType::V_BOOLEAN) {
                iter->second.erase(it);
                --size_;
                return;
            }
        }
}

Reference*
Table::getFromTable(TableValue *v)
{
    auto iter = table.find(v->getID());
    if (iter != table.end())
        for (auto &p : iter->second)
            if (p.first->getType() == Value::ValueType::V_TABLE)
                return &p.second;
    if (iter == table.end())
        iter = table.insert(
            iter, 
            std::make_pair(v->getID(), std::list<Pair>()));
    iter->second.push_back(
        std::make_pair(
            dynamic_cast<Value*>(v),
            getGlobalRuntime()->newNil()));
    return &iter->second.back().second;
}

void
Table::eraseFromTable(TableValue *v)
{
    auto iter = table.find(v->getID());
    if (iter != table.end())
        for (
            auto it = iter->second.begin();
            it != iter->second.end();
            ++it
        ) {
            auto &p = *it;
            if (p.first->getType() == Value::ValueType::V_TABLE) {
                iter->second.erase(it);
                --size_;
                return;
            }
        }
}
