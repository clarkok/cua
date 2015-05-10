#include "gtest/gtest.h"

#include "../src/runtime/runtime.h"
#include "../src/casting.h"

using namespace CUA;

TEST(CastingTest, FromValueNil)
{
    auto nil_value = getGlobalRuntime()->newNil().get();
    
    EXPECT_EQ(0, from_value<std::int64_t>(nil_value));
    EXPECT_EQ("nil", from_value<std::string>(nil_value));
    EXPECT_EQ(false, from_value<bool>(nil_value));
}

TEST(CastingTest, FromValueNumber)
{
    auto number_value = getGlobalRuntime()->newNumber(10).get();
    
    EXPECT_EQ(10, from_value<std::int64_t>(number_value));
    EXPECT_EQ("10", from_value<std::string>(number_value));
    EXPECT_EQ(true, from_value<bool>(number_value));
    
    number_value = getGlobalRuntime()->newNumber(0).get();
    
    EXPECT_EQ(0, from_value<std::int64_t>(number_value));
    EXPECT_EQ("0", from_value<std::string>(number_value));
    EXPECT_EQ(false, from_value<bool>(number_value));
}

TEST(CastingTest, FromValueString)
{
    auto string_value = getGlobalRuntime()->newString("10010").get();
    
    EXPECT_EQ(10010, from_value<std::int64_t>(string_value));
    EXPECT_EQ("10010", from_value<std::string>(string_value));
    EXPECT_EQ(true, from_value<bool>(string_value));
    
    string_value = getGlobalRuntime()->newString("10 ").get();
    
    EXPECT_EQ(10, from_value<std::int64_t>(string_value));
    EXPECT_EQ("10 ", from_value<std::string>(string_value));
    EXPECT_EQ(true, from_value<bool>(string_value));
    
    string_value = getGlobalRuntime()->newString("w10").get();
    
    EXPECT_EQ(0, from_value<std::int64_t>(string_value));
    EXPECT_EQ("w10", from_value<std::string>(string_value));
    EXPECT_EQ(true, from_value<bool>(string_value));
    
    string_value = getGlobalRuntime()->newString("").get();
    
    EXPECT_EQ(0, from_value<std::int64_t>(string_value));
    EXPECT_EQ("", from_value<std::string>(string_value));
    EXPECT_EQ(false, from_value<bool>(string_value));
}

TEST(CastingTest, ToRef)
{
    EXPECT_EQ(
        10,
        from_ref<std::int64_t>(to_ref<std::int64_t>(10))
    );
    EXPECT_EQ(
        "test",
        from_ref<std::string>(to_ref<std::string>("test"))
    );
    EXPECT_EQ(
        true,
        from_ref<bool>(to_ref<bool>(true))
    );
}