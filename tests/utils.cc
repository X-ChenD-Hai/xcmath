#include <gtest/gtest.h>

#include <iostream>
#include <utils/compiling.hpp>

using namespace std;
using namespace xcmath;
TEST(Compiling, get_type_name) {

    EXPECT_STREQ(TypeName<int>, "int");
    EXPECT_STREQ(TypeName<double>, "double");
    EXPECT_STREQ(TypeName<float>, "float");
}