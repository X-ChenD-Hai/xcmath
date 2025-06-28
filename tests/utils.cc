#include <gtest/gtest.h>

#include <utils/compiling.hpp>
#include <utils/types.hpp>

using namespace std;
using namespace xcmath;
TEST(Compiling, get_type_name) {
    EXPECT_STREQ(TypeName<int>, "int");
    EXPECT_STREQ(TypeName<double>, "double");
    EXPECT_STREQ(TypeName<float>, "float");
}

TEST(Compiling, tvector) {
    using integer = tvector<char, short, int, long, long long>;
    using floating = tvector<long double, double, float>;
    using number = integer::concat<floating>::push_back<bool>;
    using int1 = integer::pop_back;
    using int2 = integer::pop_front;
    using int43 = integer::remove_all<>;
    using int44 = integer::remove_all<int, short>;
    using int45 = integer::remove_all_from_list<tvector<>>;
    using int46 = integer::remove_all_from_list<tvector<int>>;
    using int47 = integer::remove_all_from_list<tvector<int, long>>;
    using t1 = tvector<int, double, float>::remove<0>;
    using t2 = tvector<int, double, float>::slice<0, 2>;
    EXPECT_FALSE(tvector<>::has<int>);
    EXPECT_FALSE(tvector<>::has<double>);
    EXPECT_EQ(tvector<int>::size, 1);
    EXPECT_EQ((tvector<int, double>::size), 2);
    EXPECT_EQ((tvector<int, double, float>::size), 3);
    EXPECT_EQ(t1::size, 2);
    EXPECT_EQ(t2::size, 2);
}