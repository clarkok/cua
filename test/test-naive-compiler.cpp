#include <iostream>

#include "gtest/gtest.h"
#include "../src/naive-compiler.h"
#include "../src/parse/driver.h"

using namespace CUA;

static char TEST_CODE[] =
    "::label::\n"
    "goto label\n"
    "if (true) then\n"
    "  a = 2;\n"
    "end\n"
    "a = 255 + 2\n"
    "a = b * c\n"
    "a = d + a * b\n"
    "a, b = b, a\n"
    ;
    
TEST(NaiveCompilerTest, Basic)
{
    Driver d(TEST_CODE);
    d.parse();
    
    NaiveCompiler nc;
    d.root->accept(&nc);
    
    for (auto &i : nc.ins_list) {
        std::cout << ERE(InstrumentType)
                        ->toString(i.type) << '\t' 
                  << i.rd << '\t'
                  << i.rs << '\t'
                  << i.rt << std::endl;
    }
}