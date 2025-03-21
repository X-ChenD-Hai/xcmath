#include "mobject/vec.hpp"

#include <gtest/gtest.h>

#include <utils/show.hpp>
#include <xcmath.hpp>

#include "gtest/gtest.h"

// Property tests
TEST(Property, DataType) {
    xcmath::vec<float, 3> v1{1, 2, 3};
    xcmath::vec<xcmath::vec<float, 3>, 3> v2{xcmath::vec<float, 3>{1},
                                             xcmath::vec<float, 3>{2},
                                             xcmath::vec<float, 3>{3}};
    EXPECT_STREQ(v1.datatype, "float");
    EXPECT_STREQ(v2.itemtype, "xcmath::vec<float, 3>");
}

TEST(Property, length) {
    xcmath::vec3f v1{1, 2, 3};
    float result = v1.length;
    EXPECT_EQ(result, 3);
}

// Operator tests
TEST(Operator, eq) {
    xcmath::vec3f v1{1, 2, 3};
    xcmath::vec3f v2{1, 1, 3};
    xcmath::vec3b v3{1, 0, 1};

    xcmath::vec3b result = v1 == v2;
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result[i], v3[i]);
    }
}
TEST(Operator, ne) {
    xcmath::vec3f v1{1, 2, 3};
    xcmath::vec3f v2{1, 1, 3};
    xcmath::vec3b v3{0, 1, 0};

    xcmath::vec3b result = v1 != v2;
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result[i], v3[i]);
    }
}
TEST(Operator, lt) {
    xcmath::vec3f v1{1, 2, 3};
    xcmath::vec3f v2{1, 4, 3};
    xcmath::vec3b v3{0, 1, 0};

    xcmath::vec3b result = v1 < v2;
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result[i], v3[i]);
    }
}
TEST(Operator, gt) {
    xcmath::vec3f v1{1, 2, 3};
    xcmath::vec3f v2{2, 1, 3};
    xcmath::vec3b v3{0, 1, 0};

    xcmath::vec3b result = v1 > v2;
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result[i], v3[i]);
    }
}
TEST(Operator, le) {
    xcmath::vec3f v1{1, 2, 4};
    xcmath::vec3f v2{1, 1, 3};
    xcmath::vec3b v3{1, 0, 0};
    xcmath::vec3b result = v1 <= v2;
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result[i], v3[i]);
    }
}
TEST(Operator, ge) {
    xcmath::vec3f v1{1, 2, 3};
    xcmath::vec3f v2{1, 1, 3};
    xcmath::vec3b v3{1, 1, 1};

    xcmath::vec3b result = v1 >= v2;
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result[i], v3[i]);
    }
}
TEST(Operator, Addition) {
    xcmath::vec3f v1{1, 2, 3};
    xcmath::vec3f v2{4, 5, 6};
    xcmath::vec3f v3{5, 7, 9};

    xcmath::vec3f result = v1 + v2;
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result[i], v3[i]);
    }
}
TEST(Operator, Subtraction) {
    xcmath::vec3f v1{1, 2, 3};
    xcmath::vec3f v2{4, 5, 6};
    xcmath::vec3f v3{-3, -3, -3};

    xcmath::vec3f result = v1 - v2;
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result[i], v3[i]);
    }
}
TEST(Operator, Multiplication) {
    xcmath::vec3f v1{1, 2, 3};
    xcmath::vec3f v2{4, 5, 6};
    xcmath::vec3f v3{4, 10, 18};

    xcmath::vec3f result = v1 * v2;
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result[i], v3[i]);
    }
}
TEST(Operator, Division) {
    xcmath::vec3f v1{1, 2, 3};
    xcmath::vec3f v2{4, 5, 6};
    xcmath::vec3f v3{0.25, 0.4, 0.5};

    xcmath::vec3f result = v1 / v2;
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result[i], v3[i]);
    }
}
TEST(Operator, UnaryMinus) {
    xcmath::vec3f v1{1, 2, 3};
    xcmath::vec3f v2{-1, -2, -3};

    xcmath::vec3f result = -v1;
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result[i], v2[i]);
    }
}
TEST(Operator, UnaryPlus) {
    xcmath::vec3f v1{1, 2, 3};
    xcmath::vec3f v2{1, 2, 3};

    xcmath::vec3f result = +v1;
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result[i], v2[i]);
    }
}

TEST(Operator, slice) {
    xcmath::vec3f v1{1, 2, 3};
    xcmath::vec3f v2{4, 5, 6};
    xcmath::vec3f v3{5, 7, 9};

    xcmath::vec2f result = v1.slice<0, 2>();
    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(result[i], v1[i]);
    }
    result = v1.slice<2>();
    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(result[i], v1[i]);
    }

    result = v2.slice<1, 2>();
    for (int i = 1; i < 2; i++) {
        EXPECT_EQ(result[i - 1], v2[i]);
    }

    auto result2 = v3.slice<0, 3>();
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result2[i], v3[i]);
    }

    auto result3 = v1.slice();
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result3[i], v1[i]);
    }
}
// Method tests
TEST(Method, dot) {
    xcmath::vec3f v1{1, 2, 3};
    xcmath::vec3f v2{4, 5, 6};
    float result = v1.dot(v2);
    EXPECT_EQ(result, 32);
}
TEST(Method, cross) {
    xcmath::vec3f v1{1, 2, 3};
    xcmath::vec3f v2{4, 5, 6};
    xcmath::vec3f result = v1.cross(v2);
    xcmath::vec3f expected{-3, 6, -3};

    EXPECT_FLOAT_EQ(result[0], expected[0]);
}
TEST(Method, mod) {
    xcmath::vec3f v1{1, 2, 3};
    float result = v1.mod();
    EXPECT_FLOAT_EQ(result, 3.7416573867739413);
}
TEST(Method, distance) {
    xcmath::vec3f v1{1, 2, 3};
    xcmath::vec3f v2{4, 5, 6};
    float result = v1.distance(v2);
    EXPECT_FLOAT_EQ(result, 5.196152422706632);
}
TEST(Method, normalize) {
    xcmath::vec3f v1{1, 2, 3};
    xcmath::vec3f result = v1.normalize();
    xcmath::vec3f expected{0.2672612419124244, 0.5345224838248488,
                           0.8017837257372732};

    for (int i = 0; i < 3; i++) {
        EXPECT_FLOAT_EQ(result[i], expected[i]);
    }
}
TEST(Method, angle) {
    xcmath::vec3f v1{1, 0, 0};
    xcmath::vec3f v2{0, 1, 0};
    float result = v1.angle(v2);
    EXPECT_FLOAT_EQ(result, 1.5707963267948966);
}

TEST(Method, any) {
    xcmath::vec3b v1{1, 0, 1};
    bool result = v1.any();
    EXPECT_EQ(result, true);

    xcmath::vec3b v2{0, 0, 0};
    result = v2.any();
    EXPECT_EQ(result, false);

    xcmath::vec<xcmath::vec3b, 3> v3{v1, v2, v1};
    result = v3.any();
    EXPECT_EQ(result, true);

    xcmath::vec<xcmath::vec3b, 3> v4{v2, v2, v2};
    result = v4.any();
    EXPECT_EQ(result, false);
}
TEST(Method, every) {
    xcmath::vec3b v1{1, 1, 1};
    bool result = v1.every();
    EXPECT_EQ(result, true);

    xcmath::vec3b v2{0, 1, 1};
    result = v2.every();
    EXPECT_EQ(result, false);

    xcmath::vec<xcmath::vec3b, 3> v3{v1, v2, v1};
    result = v3.every();
    EXPECT_EQ(result, false);

    xcmath::vec<xcmath::vec3b, 3> v4{v1, v1, v1};
    result = v4.every();
    EXPECT_EQ(result, true);
}

TEST(Method, ConvertToOtherTypeVec) {
    using namespace xcmath;
    vec3f v1{1, 2, 3};
    vec3d v2 = (vec3d)v1;

    EXPECT_EQ(v2.x(), 1);
    EXPECT_EQ(v2.y(), 2);
    EXPECT_EQ(v2.z(), 3);
}
template <typename T = float>
class Point final : public xcmath::vec2<T> {
    using vec2 = xcmath::vec2<T>;

   public:
    Point(T x = T{}, T y = T{}) : xcmath::vec2<T>(x, y) {}
    Point(const vec2& data) : xcmath::vec2<T>(data) {}
    Point(const Point& o) : vec2((vec2)o) {}
    T x() const { return xcmath::vec2f::x(); }
    T y() const { return xcmath::vec2f::y(); }
    void setX(T x) { xcmath::vec2f::x() = x; }
    void setY(T y) { xcmath::vec2f::y() = y; }
    const std::array<T, 2>& array() const { return *((std::array<T, 2>*)this); }
    operator const vec2&() const { return *(xcmath::vec2<T>*)this; }
};
TEST(Method, EqualOoperator) {
    using namespace xcmath;
    // Point v1{1, 2};
    // Point v2{1, 2};
    // v2 = xcmath::vec2{1, 2};
    // v2 = v1 + v2;
    // v2 = (v1 + v1);
    //    auto  s =  VecInfo<vec3b>::dim;
    // s =  VecInfo<vec3<vec3b>>::dim;
    auto s = VecInfo<vec3<vec3<vec3b>>>::Dim;
    auto s1 = VecInfo<vec3<vec3<vec4d>>>::Zero;
}
