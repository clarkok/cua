#include "gtest/gtest.h"
#include "../src/parse/driver.h"
#include "../src/naive-compiler.h"
#include "../src/vm.h"
#include "../src/casting.h"

using namespace CUA;

TEST(VMTest, Basic)
{
    const char TEST_ADD[] = "a = 1 + 2";
    const char TEST_SUB[] = "a = 1 - 2";
    const char TEST_MUL[] = "a = 2 * 3";
    const char TEST_DIV[] = "a = 4 / 2";
    const char TEST_MOD[] = "a = 3 % 2";
    
    Driver d(TEST_ADD);
    d.parse();
    
    NaiveCompiler nc;
    auto inss = nc.compile(d.root);
    NaiveVM nvm;
    nvm.run(inss);
    EXPECT_EQ(3,
        from_ref<std::int64_t>(
            *nvm.current_scope->getReferenceByName("a")));
            
    d = Driver(TEST_SUB);
    d.parse();
    inss = nc.compile(d.root);
    nvm.run(inss);
    EXPECT_EQ(-1,
        from_ref<std::int64_t>(
            *nvm.current_scope->getReferenceByName("a")));
            
    d = Driver(TEST_MUL);
    d.parse();
    inss = nc.compile(d.root);
    nvm.run(inss);
    EXPECT_EQ(6,
        from_ref<std::int64_t>(
            *nvm.current_scope->getReferenceByName("a")));
            
    d = Driver(TEST_DIV);
    d.parse();
    inss = nc.compile(d.root);
    nvm.run(inss);
    EXPECT_EQ(2,
        from_ref<std::int64_t>(
            *nvm.current_scope->getReferenceByName("a")));
            
    d = Driver(TEST_MOD);
    d.parse();
    inss = nc.compile(d.root);
    nvm.run(inss);
    EXPECT_EQ(1,
        from_ref<std::int64_t>(
            *nvm.current_scope->getReferenceByName("a")));
}

TEST(VMTest, ComplexExpr)
{
    const char TEST_CODE[] = "a = (1 + 2) * 3 / 4 % 3";
    Driver d(TEST_CODE);
    d.parse();
    NaiveCompiler nc;
    auto inss = nc.compile(d.root);
    NaiveVM nvm;
    nvm.run(inss);
    EXPECT_EQ(2,
        from_ref<std::int64_t>(
            *nvm.current_scope->getReferenceByName("a")));
}

TEST(VMTest, VarInExpr)
{
    const char TEST_CODE[] =
        "a = 1\n"
        "b = 2\n"
        "a, b = b, a\n"
    ;
    Driver d(TEST_CODE);
    d.parse();
    NaiveCompiler nc;
    auto inss = nc.compile(d.root);
    NaiveVM nvm;
    nvm.run(inss);
    EXPECT_EQ(2,
        from_ref<std::int64_t>(
            *nvm.current_scope->getReferenceByName("a")));
    EXPECT_EQ(1,
        from_ref<std::int64_t>(
            *nvm.current_scope->getReferenceByName("b")));
}