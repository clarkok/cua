#include "gtest/gtest.h"
#include "../../src/runtime/runtime.h"
#include "../../src/runtime/table.h"

using namespace CUA;

TEST(TableTest, NumberValue)
{
    auto table = dynamic_cast<TableValue*>(getGlobalRuntime()->newTable().get());
    auto key = getGlobalRuntime()->newNumber(10);
    auto value = getGlobalRuntime()->newString("test");
    table->getValue()->get(key.get())->reset(value);
    EXPECT_EQ("test", 
        dynamic_cast<StringValue*>(
            table->getValue()->get(key.get())->get())->getValue()
    );
    
    value = getGlobalRuntime()->newString("test2");
    table->getValue()->get(key.get())->reset(value);
    EXPECT_EQ("test2", 
        dynamic_cast<StringValue*>(
            table->getValue()->get(key.get())->get())->getValue()
    );
    
    table->getValue()->erase(key.get());
    EXPECT_EQ(CUA::Value::ValueType::V_NIL,
        table->getValue()->get(key.get())->get()->getType()
    );
}

TEST(TableTest, StringValue)
{
    auto table = dynamic_cast<TableValue*>(getGlobalRuntime()->newTable().get());
    auto key = getGlobalRuntime()->newString("key");
    auto value = getGlobalRuntime()->newString("test");
    table->getValue()->get(key.get())->reset(value);
    EXPECT_EQ("test", 
        dynamic_cast<StringValue*>(
            table->getValue()->get(key.get())->get())->getValue()
    );
    
    value = getGlobalRuntime()->newString("test2");
    table->getValue()->get(key.get())->reset(value);
    EXPECT_EQ("test2", 
        dynamic_cast<StringValue*>(
            table->getValue()->get(key.get())->get())->getValue()
    );
    
    table->getValue()->erase(key.get());
    EXPECT_EQ(CUA::Value::ValueType::V_NIL,
        table->getValue()->get(key.get())->get()->getType()
    );
}

TEST(TableTest, BooleanValue)
{
    auto table = dynamic_cast<TableValue*>(getGlobalRuntime()->newTable().get());
    auto key = getGlobalRuntime()->newBoolean(true);
    auto value = getGlobalRuntime()->newString("test");
    table->getValue()->get(key.get())->reset(value);
    EXPECT_EQ("test", 
        dynamic_cast<StringValue*>(
            table->getValue()->get(key.get())->get())->getValue()
    );
    
    value = getGlobalRuntime()->newString("test2");
    table->getValue()->get(key.get())->reset(value);
    EXPECT_EQ("test2", 
        dynamic_cast<StringValue*>(
            table->getValue()->get(key.get())->get())->getValue()
    );
    
    table->getValue()->erase(key.get());
    EXPECT_EQ(CUA::Value::ValueType::V_NIL,
        table->getValue()->get(key.get())->get()->getType()
    );
}

TEST(TableTest, TableValue)
{
    auto table = dynamic_cast<TableValue*>(getGlobalRuntime()->newTable().get());
    auto key = getGlobalRuntime()->newTable();
    auto value = getGlobalRuntime()->newString("test");
    table->getValue()->get(key.get())->reset(value);
    EXPECT_EQ("test", 
        dynamic_cast<StringValue*>(
            table->getValue()->get(key.get())->get())->getValue()
    );
    
    value = getGlobalRuntime()->newString("test2");
    table->getValue()->get(key.get())->reset(value);
    EXPECT_EQ("test2", 
        dynamic_cast<StringValue*>(
            table->getValue()->get(key.get())->get())->getValue()
    );
    
    table->getValue()->erase(key.get());
    EXPECT_EQ(CUA::Value::ValueType::V_NIL,
        table->getValue()->get(key.get())->get()->getType()
    );
}

TEST(TableTest, Overall)
{
    auto table = dynamic_cast<TableValue*>(getGlobalRuntime()->newTable().get());
    auto number_key = getGlobalRuntime()->newNumber(1);
    auto string_key = getGlobalRuntime()->newString("test");
    auto boolean_key = getGlobalRuntime()->newBoolean(true);
    auto table_key = getGlobalRuntime()->newTable();
    
    auto number_value = getGlobalRuntime()->newString("number");
    table->getValue()->get(number_key.get())->reset(number_value);
    EXPECT_EQ("number", 
        dynamic_cast<StringValue*>(
            table->getValue()->get(number_key.get())->get())->getValue()
    );
    
    auto string_value = getGlobalRuntime()->newString("string");
    table->getValue()->get(string_key.get())->reset(string_value);
    EXPECT_EQ("string", 
        dynamic_cast<StringValue*>(
            table->getValue()->get(string_key.get())->get())->getValue()
    );
    
    auto boolean_value = getGlobalRuntime()->newString("boolean");
    table->getValue()->get(boolean_key.get())->reset(boolean_value);
    EXPECT_EQ("boolean", 
        dynamic_cast<StringValue*>(
            table->getValue()->get(boolean_key.get())->get())->getValue()
    );
    
    auto table_value = getGlobalRuntime()->newString("table");
    table->getValue()->get(table_key.get())->reset(table_value);
    EXPECT_EQ("table", 
        dynamic_cast<StringValue*>(
            table->getValue()->get(table_key.get())->get())->getValue()
    );
}

TEST(TableTest, Iterator)
{
    static const int TEST_NUMBER = 10;
    
    auto table = dynamic_cast<TableValue*>(getGlobalRuntime()->newTable().get());
    
    for (int i = 0; i < TEST_NUMBER; ++i) {
        auto key = getGlobalRuntime()->newNumber(i);
        auto value = getGlobalRuntime()->newNumber(i);
        table->getValue()->get(key.get())->reset(value);
    }
    
    int count = 0;
    for (
        auto iter = table->getValue()->begin();
        !(iter == table->getValue()->end());
        iter = iter.next()
    ) {
        EXPECT_EQ(
            dynamic_cast<NumberValue*>(iter.key())->getValue(),
            dynamic_cast<NumberValue*>(iter.value()->get())->getValue()
        );
        ++count;
    }
    EXPECT_EQ(TEST_NUMBER, count);
}
