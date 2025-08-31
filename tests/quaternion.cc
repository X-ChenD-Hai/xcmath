#include <gtest/gtest.h>

#include <xcmath/xcmath.hpp>
using namespace xcmath;
TEST(Quaternion, Constructors) {
    // 测试标量构造函数
    xcmath::quaternion<double> q1(1.0);
    EXPECT_DOUBLE_EQ(q1.r(), 1.0);
    EXPECT_DOUBLE_EQ(q1.i(), 0.0);
    EXPECT_DOUBLE_EQ(q1.j(), 0.0);
    EXPECT_DOUBLE_EQ(q1.k(), 0.0);

    // 测试轴角构造函数
    xcmath::vec3<double> axis(0, 0, 1);
    double angle = PI / 2;
    xcmath::quaternion<double> q2(axis, angle);
    double expected_r = cos(angle / 2);
    double expected_i = axis.x() * sin(angle / 2);
    double expected_j = axis.y() * sin(angle / 2);
    double expected_k = axis.z() * sin(angle / 2);
    EXPECT_DOUBLE_EQ(q2.r(), expected_r);
    EXPECT_DOUBLE_EQ(q2.i(), expected_i);
    EXPECT_DOUBLE_EQ(q2.j(), expected_j);
    EXPECT_DOUBLE_EQ(q2.k(), expected_k);
}
TEST(Quaternion, Multiplication) {
    xcmath::quaternion<double> q1(1.0, 0.0, 0.0, 0.0);
    xcmath::quaternion<double> q2(0.0, 1.0, 0.0, 0.0);
    xcmath::quaternion<double> result = q1 * q2;
    EXPECT_DOUBLE_EQ(result.r(), 0.0);
    EXPECT_DOUBLE_EQ(result.i(), 1.0);
    EXPECT_DOUBLE_EQ(result.j(), 0.0);
    EXPECT_DOUBLE_EQ(result.k(), 0.0);

    xcmath::quaternion<double> q3(0.0, 0.0, 1.0, 0.0);
    xcmath::quaternion<double> q4(0.0, 0.0, 0.0, 1.0);
    xcmath::quaternion<double> result2 = q3 * q4;
    EXPECT_DOUBLE_EQ(result2.r(), 0.0);
    EXPECT_DOUBLE_EQ(result2.i(), 1.0);
    EXPECT_DOUBLE_EQ(result2.j(), 0.0);
    EXPECT_DOUBLE_EQ(result2.k(), 0.0);
}
TEST(Quaternion, Division) {
    xcmath::quaternion<double> q1(1.0, 0.0, 0.0, 0.0);
    xcmath::quaternion<double> q2(1.0, 0.0, 0.0, 0.0);
    xcmath::quaternion<double> result = q1 / q2;
    EXPECT_DOUBLE_EQ(result.r(), 1.0);
    EXPECT_DOUBLE_EQ(result.i(), 0.0);
    EXPECT_DOUBLE_EQ(result.j(), 0.0);
    EXPECT_DOUBLE_EQ(result.k(), 0.0);

    xcmath::quaternion<double> q3(2.0, 0.0, 0.0, 0.0);
    xcmath::quaternion<double> q4(1.0, 0.0, 0.0, 0.0);
    xcmath::quaternion<double> result2 = q3 / q4;
    EXPECT_DOUBLE_EQ(result2.r(), 2.0);
    EXPECT_DOUBLE_EQ(result2.i(), 0.0);
    EXPECT_DOUBLE_EQ(result2.j(), 0.0);
    EXPECT_DOUBLE_EQ(result2.k(), 0.0);
}
TEST(Quaternion, Norm) {
    xcmath::quaternion<double> q1(1.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(q1.norm(), 1.0);

    xcmath::quaternion<double> q2(1.0, 1.0, 1.0, 1.0);
    EXPECT_DOUBLE_EQ(q2.norm(), 4.0);
}

TEST(Quaternion, Inverse) {
    xcmath::quaternion<double> q1(1.0, 0.0, 0.0, 0.0);
    xcmath::quaternion<double> inverse_q1 = q1.inverse();
    EXPECT_DOUBLE_EQ(inverse_q1.r(), 1.0);
    EXPECT_DOUBLE_EQ(inverse_q1.i(), 0.0);
    EXPECT_DOUBLE_EQ(inverse_q1.j(), 0.0);
    EXPECT_DOUBLE_EQ(inverse_q1.k(), 0.0);

    xcmath::quaternion<double> q2(2.0, 1.0, 1.0, 1.0);
    xcmath::quaternion<double> inverse_q2 = q2.inverse();
    double norm = q2.norm();
    EXPECT_DOUBLE_EQ(inverse_q2.r(), 2.0 / norm);
    EXPECT_DOUBLE_EQ(inverse_q2.i(), -1.0 / norm);
    EXPECT_DOUBLE_EQ(inverse_q2.j(), -1.0 / norm);
    EXPECT_DOUBLE_EQ(inverse_q2.k(), -1.0 / norm);
}

TEST(Quaternion, ToMat) {
    xcmath::quaternion<double> q(0.0, 0.0, 0.0, 1.0);
    xcmath::mat<double, 3, 3> mat = q.to_mat();
    xcmath::mat<double, 3, 3> expected_mat{xcmath::vec3<double>{-1.0, 0.0, 0.0},
                                           xcmath::vec3<double>{0.0, -1.0, 0.0},
                                           xcmath::vec3<double>{0.0, 0.0, 1.0}};
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_DOUBLE_EQ(mat[i][j], expected_mat[i][j]);
        }
    }
}

TEST(Quaternion, FromMat) {
    xcmath::mat<double, 3, 3> mat{xcmath::vec3<double>{-1.0, 0.0, 0.0},
                                  xcmath::vec3<double>{0.0, -1.0, 0.0},
                                  xcmath::vec3<double>{0.0, 0.0, 1.0}};
    xcmath::quaternion<double> q = xcmath::quaternion<double>::from_mat(mat);
    xcmath::quaternion<double> expected_q(0.0, 0.0, 0.0, 1.0);
    EXPECT_DOUBLE_EQ(q.r(), expected_q.r());
    EXPECT_DOUBLE_EQ(q.i(), expected_q.i());
    EXPECT_DOUBLE_EQ(q.j(), expected_q.j());
    EXPECT_DOUBLE_EQ(q.k(), expected_q.k());
}

TEST(Quaternion, ScalarAdditionAndSubtraction) {
    xcmath::quaternion<double> q(1.0, 0.0, 0.0, 0.0);
    auto result = 2.0 + q;
    EXPECT_DOUBLE_EQ(result.r(), 3.0);
    EXPECT_DOUBLE_EQ(result.i(), 0.0);
    EXPECT_DOUBLE_EQ(result.j(), 0.0);
    EXPECT_DOUBLE_EQ(result.k(), 0.0);

    auto result2 = q + 2.0;
    EXPECT_DOUBLE_EQ(result2.r(), 3.0);
    EXPECT_DOUBLE_EQ(result2.i(), 0.0);
    EXPECT_DOUBLE_EQ(result2.j(), 0.0);
    EXPECT_DOUBLE_EQ(result2.k(), 0.0);

    auto result3 = 2.0 - q;
    EXPECT_DOUBLE_EQ(result3.r(), 1.0);
    EXPECT_DOUBLE_EQ(result3.i(), 0.0);
    EXPECT_DOUBLE_EQ(result3.j(), 0.0);
    EXPECT_DOUBLE_EQ(result3.k(), 0.0);

    auto result4 = q - 2.0;
    EXPECT_DOUBLE_EQ(result4.r(), -1.0);
    EXPECT_DOUBLE_EQ(result4.i(), 0.0);
    EXPECT_DOUBLE_EQ(result4.j(), 0.0);
    EXPECT_DOUBLE_EQ(result4.k(), 0.0);
    auto q33 = 1 + 2_qi;
    auto q32 = 2_qi + 2_qk;
}

TEST(Quaternion, ConvertToOtherTypeQuaternion) {
    using namespace xcmath;
    quaternion<float> v1{1, 2, 3, 4};
    auto v2 = (quaternion<double>)v1;

    EXPECT_EQ(v2.r(), 1);
    EXPECT_EQ(v2.i(), 2);
    EXPECT_EQ(v2.j(), 3);
    EXPECT_EQ(v2.k(), 4);
}