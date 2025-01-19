#include "mobject/vec.hpp"

#include <gtest/gtest.h>

#include <xcmath.hpp>

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
