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

TEST(VMTest, GotoLabel)
{
    const char TEST_CODE[] =
        "a = 1\n"
        "goto label_not_set\n"
        "a = 2\n"
        "::label_not_set::\n"
    ;
    Driver d(TEST_CODE);
    d.parse();
    NaiveCompiler nc;
    auto inss = nc.compile(d.root);
    NaiveVM nvm;
    nvm.run(inss);
    EXPECT_EQ(1,
        from_ref<std::int64_t>(
            *nvm.current_scope->getReferenceByName("a")));
}

TEST(VMTest, IfStmt)
{
    const char TEST_CODE[] =
        "a = 1\n"
        "if (true) then\n"
        "  a = 2;\n"
        "end\n"
        "b = 1\n"
        "if (false) then\n"
        "  b = 2\n"
        "else\n"
        "  b = 3\n"
        "end\n"
    ;
    NaiveVM nvm;
    try {
        Driver d(TEST_CODE);
        d.parse();
        NaiveCompiler nc;
        auto inss = nc.compile(d.root);
        nvm.run(inss);
        EXPECT_EQ(2,
            from_ref<std::int64_t>(
                *nvm.current_scope->getReferenceByName("a")));
        EXPECT_EQ(3,
            from_ref<std::int64_t>(
                *nvm.current_scope->getReferenceByName("b")));
    }
    catch (const Exception &e) {
        EXPECT_EQ("", e.toString());
    }
}

TEST(VMTest, ConditionalExpr)
{
    const char TEST_CODE[] =
        "a = true\n"
        "b = false\n"
        "if (a or b) then\n"
        "  c = 1\n"
        "else\n"
        "  c = 2\n"
        "end\n"
        "if (a and b) then\n"
        "  d = 1\n"
        "else\n"
        "  d = 2\n"
        "end\n"
    ;
    NaiveVM nvm;
    try {
        Driver d(TEST_CODE);
        d.parse();
        NaiveCompiler nc;
        auto inss = nc.compile(d.root);
        nvm.run(inss);
        EXPECT_EQ(1,
            from_ref<std::int64_t>(
                *nvm.current_scope->getReferenceByName("c")));
        EXPECT_EQ(2,
            from_ref<std::int64_t>(
                *nvm.current_scope->getReferenceByName("d")));
    }
    catch (const Exception &e) {
        EXPECT_EQ("", e.toString());
    }
}

TEST(VMTest, SimLoopWithIfAndGoto)
{
    const char TEST_CODE[] =
        "COUNT = 10000\n"
        "a = 0\n"
        "::loop_start::\n"
        "if a == COUNT then\n"
        "    goto loop_end\n"
        "end\n"
        "a = a + 1\n"
        "goto loop_start\n"
        "::loop_end::\n"
    ;
    NaiveVM nvm;
    try {
        Driver d(TEST_CODE);
        d.parse();
        NaiveCompiler nc;
        auto inss = nc.compile(d.root);
        nvm.run(inss);
        EXPECT_EQ(10000,
            from_ref<std::int64_t>(
                *nvm.current_scope->getReferenceByName("a")));
    }
    catch (const Exception &e) {
        EXPECT_EQ("", e.toString());
    }
}