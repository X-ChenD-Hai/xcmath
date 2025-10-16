#include <gtest/gtest.h>
#include <xcmath/symbolsystem/monomial.h>
#include <xcmath/symbolsystem/symbol.h>

using namespace xcmath;
using namespace std;

TEST(SymbolTest, test1) {
    // Symbol x("x");
    // auto y = ((Monomial)x)*x;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}