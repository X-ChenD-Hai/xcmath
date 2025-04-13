#include <gtest/gtest.h>
#include <symbolsystem/symbol.h>
using namespace xcmath;
TEST(SymbolTest, test1) {
    EXPECT_EQ(1, 1);
    symbol x("123");
}
