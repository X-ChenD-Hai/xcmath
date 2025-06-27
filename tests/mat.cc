#include <gtest/gtest.h>

#include <xcmath.hpp>

TEST(Method, construct_with_vec) {
    xcmath::batch<float, 3, 3> v1{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    xcmath::mat3f m1{v1};
    EXPECT_EQ(m1[0][0], 1.0f);
    EXPECT_EQ(m1[0][1], 2.0f);
    EXPECT_EQ(m1[0][2], 3.0f);
    EXPECT_EQ(m1[1][0], 4.0f);
    EXPECT_EQ(m1[1][1], 5.0f);
    EXPECT_EQ(m1[1][2], 6.0f);
    EXPECT_EQ(m1[2][0], 7.0f);
    EXPECT_EQ(m1[2][1], 8.0f);
    EXPECT_EQ(m1[2][2], 9.0f);
    m1 = v1;
    EXPECT_EQ(m1[0][0], 1.0f);
    EXPECT_EQ(m1[0][1], 2.0f);
    EXPECT_EQ(m1[0][2], 3.0f);
    EXPECT_EQ(m1[1][0], 4.0f);
    EXPECT_EQ(m1[1][1], 5.0f);
    EXPECT_EQ(m1[1][2], 6.0f);
    EXPECT_EQ(m1[2][0], 7.0f);
    EXPECT_EQ(m1[2][1], 8.0f);
    EXPECT_EQ(m1[2][2], 9.0f);
}
TEST(Method, det__1x1) {
    xcmath::mat<float, 1, 1> mat1x1;
    mat1x1[0][0] = 5.0f;
    EXPECT_FLOAT_EQ(mat1x1.det(), 5.0f);
}

TEST(Method, det__2x2) {
    xcmath::mat<float, 2, 2> mat2x2;
    mat2x2[0][0] = 1.0f;
    mat2x2[0][1] = 2.0f;
    mat2x2[1][0] = 3.0f;
    mat2x2[1][1] = 4.0f;
    EXPECT_FLOAT_EQ(mat2x2.det(), -2.0f);
}

TEST(Method, det__3x3) {
    xcmath::mat<float, 3, 3> mat3x3;
    mat3x3[0][0] = 1.0f;
    mat3x3[0][1] = 2.0f;
    mat3x3[0][2] = 3.0f;
    mat3x3[1][0] = 0.0f;
    mat3x3[1][1] = 4.0f;
    mat3x3[1][2] = 5.0f;
    mat3x3[2][0] = 1.0f;
    mat3x3[2][1] = 0.0f;
    mat3x3[2][2] = 6.0f;
    EXPECT_FLOAT_EQ(mat3x3.det(), 22.0f);
}

TEST(Method, det__4x4) {
    xcmath::mat<float, 4, 4> mat4x4;
    mat4x4[0][0] = 1.0f;
    mat4x4[0][1] = 0.0f;
    mat4x4[0][2] = 2.0f;
    mat4x4[0][3] = -1.0f;
    mat4x4[1][0] = 3.0f;
    mat4x4[1][1] = 0.0f;
    mat4x4[1][2] = 0.0f;
    mat4x4[1][3] = 5.0f;
    mat4x4[2][0] = 2.0f;
    mat4x4[2][1] = 1.0f;
    mat4x4[2][2] = 4.0f;
    mat4x4[2][3] = -3.0f;
    mat4x4[3][0] = 1.0f;
    mat4x4[3][1] = 0.0f;
    mat4x4[3][2] = -1.0f;
    mat4x4[3][3] = 6.0f;
    EXPECT_FLOAT_EQ(mat4x4.det(), 18.0f);
}

TEST(Method, det__IdentityMatrix_2x2) {
    xcmath::mat<float, 2, 2> identity = xcmath::mat<float, 2, 2>::eye();
    EXPECT_FLOAT_EQ(identity.det(), 1.0f);
}

TEST(Method, det__IdentityMatrix_3x3) {
    xcmath::mat<float, 3, 3> identity = xcmath::mat<float, 3, 3>::eye();
    EXPECT_FLOAT_EQ(identity.det(), 1.0f);
}

TEST(Method, det__IdentityMatrix_4x4) {
    xcmath::mat<float, 4, 4> identity = xcmath::mat<float, 4, 4>::eye();
    EXPECT_FLOAT_EQ(identity.det(), 1.0f);
}

TEST(Method, det__OnesMatrix_2x2) {
    xcmath::mat<float, 2, 2> ones = xcmath::mat<float, 2, 2>::ones();
    EXPECT_FLOAT_EQ(ones.det(), 0.0f);
}

TEST(Method, det__OnesMatrix_3x3) {
    xcmath::mat<float, 3, 3> ones = xcmath::mat<float, 3, 3>::ones();
    EXPECT_FLOAT_EQ(ones.det(), 0.0f);
}

TEST(Method, det__OnesMatrix_4x4) {
    xcmath::mat<float, 4, 4> ones = xcmath::mat<float, 4, 4>::ones();
    EXPECT_FLOAT_EQ(ones.det(), 0.0f);
}

TEST(Method, det__SingularMatrix) {
    xcmath::mat<float, 2, 2> singular;
    singular[0][0] = 1.0f;
    singular[0][1] = 2.0f;
    singular[1][0] = 2.0f;
    singular[1][1] = 4.0f;
    EXPECT_FLOAT_EQ(singular.det(), 0.0f);
}

TEST(Method, nat_muti_vec) {
    using namespace xcmath;
    xcmath::mat<float, 2, 2> mat1;
    mat1[0][0] = 1.0f;
    mat1[0][1] = 2.0f;
    mat1[1][0] = 3.0f;
    mat1[1][1] = 4.0f;
    xcmath::vec<float, 2> vec1;
    vec1[0] = 5.0f;
    vec1[1] = 6.0f;
    // // auto res = mat1 ^ vec1;
    // auto result = vec{17.0f, 39.0f};
    // auto result2 = vec{12.0f, 39.0f};
    // EXPECT_TRUE((res == result).all());
    // EXPECT_FALSE((res == result2).all());
}
