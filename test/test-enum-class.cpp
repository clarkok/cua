#include "gtest/gtest.h"
#include "../src/enum-class.h"

using namespace CUA;

ENUM_CLASS(TestType,
    T_MEMBER1,
    T_MEMBER2,
    T_MEMBER3
);

TEST(EnumClassTest, ToString)
{
    EXPECT_EQ("T_MEMBER1", 
        ERE(TestType)->toString(TestType::T_MEMBER1));
    EXPECT_EQ("T_MEMBER2", 
        ERE(TestType)->toString(TestType::T_MEMBER2));
    EXPECT_EQ("T_MEMBER3", 
        ERE(TestType)->toString(TestType::T_MEMBER3));
}

TEST(EnumClassTest, FromString)
{
    EXPECT_EQ(TestType::T_MEMBER1,
        ERE(TestType)->fromString("T_MEMBER1"));
    EXPECT_EQ(TestType::T_MEMBER2,
        ERE(TestType)->fromString("T_MEMBER2"));
    EXPECT_EQ(TestType::T_MEMBER3,
        ERE(TestType)->fromString("T_MEMBER3"));
}