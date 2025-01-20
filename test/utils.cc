#include <gtest/gtest.h>
#include <utils/compiling.hpp>
using namespace std;
using namespace xcmath;
TEST(Compiling, get_type_name) {
    EXPECT_STREQ(get_type_name<int>(), "int");
    EXPECT_STREQ(get_type_name<double>(), "double");
    EXPECT_STREQ(get_type_name<float>(), "float");
}