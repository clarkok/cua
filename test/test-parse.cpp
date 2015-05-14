#include "gtest/gtest.h"
#include "../../src/parse/driver.h"
#include "../../src/exception.h"

#include "../src/visitor.h"

using namespace CUA;

TEST(ParseTest, Basic)
{
    static const char TEST_CODE[] = 
        "a = 1\n"
        "b = \"string\"\n"
        ";\n"
        "a = a + b\n"
        "b = a + b * c\n"
        "c = a + b * (c + d)\n"
        "::label::\n"
        "d = -a + +b\n"
        "e = a and b\n"
        "a, b = b, a\n"
        "a[e] = a[d]\n"
        ;

    try {
        Driver d(TEST_CODE);
        d.parse();
    }
    catch (const CUA::Exception &e) {
        EXPECT_EQ("", e.toString());
    };
}
