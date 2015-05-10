#include "gtest/gtest.h"
#include "../../src/runtime/scope.h"

using namespace CUA;

TEST(ScopeTest, Basic)
{
    Scope *uut = new Scope(nullptr);
    
    auto ref = getGlobalRuntime()->newString("test");
    uut->registerReference("test", ref);
    
    EXPECT_EQ(
        "test", 
        dynamic_cast<StringValue*>(
            uut->getReferenceByName("test").get()
        )->getValue()
    );
}

TEST(ScopeTest, Lookup)
{
    Scope *base = new Scope(nullptr);
    Scope *child = base->createChildScope();
    
    auto ref = getGlobalRuntime()->newString("base");
    base->registerReference("base", ref);
    
    ref = getGlobalRuntime()->newString("child");
    child->registerReference("child", ref);
    
    EXPECT_EQ(
        "base",
        dynamic_cast<StringValue*>(
            child->getReferenceByName("base").get()
        )->getValue()
    );
    
    EXPECT_EQ(
        "child",
        dynamic_cast<StringValue*>(
            child->getReferenceByName("child").get()
        )->getValue()
    );
}