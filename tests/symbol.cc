#include <gtest/gtest.h>
#include <symbolsystem/expression.h>
#include <symbolsystem/symbol.h>

#include <iostream>
using namespace xcmath;
using namespace std;

TEST(SymbolTest, test1) {
    EXPECT_EQ(1, 1);
    Symbol x("x");
    auto y = (x + x);
    // auto z = y + x;
}
