#include <gtest/gtest.h>
#include <symbolsystem/symbol.h>
#include <symbolsystem/monomial.h>

#include <iostream>
using namespace xcmath;
using namespace std;

TEST(SymbolTest, test1) {
    Symbol x("x");
    auto y = ((Monomial)x)*x;
}
