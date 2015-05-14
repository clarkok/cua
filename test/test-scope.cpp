#include "gtest/gtest.h"
#include "../../src/runtime/scope.h"

using namespace CUA;

TEST(ScopeTest, Basic)
{
    Scope *uut = new Scope(nullptr);
    
    auto ref = getGlobalRuntime()->newString("test");
    uut->getReferenceByName("test")->reset(ref);
    
    EXPECT_EQ(
        "test", 
        dynamic_cast<StringValue*>(
            uut->getReferenceByName("test")->get()
        )->getValue()
    );
}

TEST(ScopeTest, Lookup)
{
    Scope *base = new Scope(nullptr);
    Scope *child = base->createChildScope();
    
    auto ref = getGlobalRuntime()->newString("base");
    base->getReferenceByName("base")->reset(ref);
    
    ref = getGlobalRuntime()->newString("child");
    child->getReferenceByName("child")->reset(ref);
    
    EXPECT_EQ(
        "base",
        dynamic_cast<StringValue*>(
            child->getReferenceByName("base")->get()
        )->getValue()
    );
    
    EXPECT_EQ(
        "child",
        dynamic_cast<StringValue*>(
            child->getReferenceByName("child")->get()
        )->getValue()
    );
}

TEST(ScopeTest, LocalVarible)
{
    Scope *base = new Scope(nullptr);
    Scope *child = base->createChildScope();
    
    auto ref = getGlobalRuntime()->newString("base");
    base->getReferenceByName(
        Config::SCOPE_LOCAL_PREFIX + std::string("local"))->reset(ref);
        
    ref = getGlobalRuntime()->newString("child");
    child->getReferenceByName(
        Config::SCOPE_LOCAL_PREFIX + std::string("local"))->reset(ref);
    
    EXPECT_EQ(
        "base",
        dynamic_cast<StringValue*>(
            base->getReferenceByName(
                Config::SCOPE_LOCAL_PREFIX + std::string("local"))
                    ->get()
        )->getValue()
    );
    
    EXPECT_EQ(
        "child",
        dynamic_cast<StringValue*>(
            child->getReferenceByName(
                Config::SCOPE_LOCAL_PREFIX + std::string("local"))
                    ->get()
        )->getValue()
    );
}