#include <gtest/gtest.h>

#include <xcmath/xcmath.hpp>

using namespace xcmath;

TEST(Function, RadiansAndDegrees) {
    // 测试 radians 函数
    EXPECT_DOUBLE_EQ(xcmath::radians(180.0), xcmath::PI);
    EXPECT_DOUBLE_EQ(xcmath::radians(90.0), xcmath::PI / 2.0);
    EXPECT_DOUBLE_EQ(xcmath::radians(0.0), 0.0);

    // 测试 degrees 函数
    EXPECT_DOUBLE_EQ(xcmath::degrees(xcmath::PI), 180.0);
    EXPECT_DOUBLE_EQ(xcmath::degrees(xcmath::PI / 2.0), 90.0);
    EXPECT_DOUBLE_EQ(xcmath::degrees(0.0), 0.0);
}

TEST(Function, Rotate) {
    // 测试 2D 旋转矩阵
    xcmath::mat<float, 3, 3> m = xcmath::mat<float, 3, 3>::eye();
    xcmath::mat<float, 3, 3> rotated = xcmath::rotate(m, 90.0f);
    xcmath::mat<float, 3, 3> expected{{cos(xcmath::radians(90.f)), -1.0f, 0.0f},
                                      {1.0f, cos(xcmath::radians(90.0f)), 0.0f},
                                      {0.0f, 0.0f, 1.0f}};
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_FLOAT_EQ(rotated[i][j], expected[i][j]);
        }
    }

    // 测试 3D 旋转矩阵
    xcmath::mat<float, 4, 4> m3d = xcmath::mat<float, 4, 4>::eye();
    xcmath::vec3<float> axis(0.0f, 0.0f, 1.0f);
    xcmath::mat<float, 4, 4> rotated3d = xcmath::rotate(m3d, 90.0f, axis);
    xcmath::mat<float, 4, 4> expected3d{
        {cos(xcmath::radians(90.0f)), -1.0f, 0.0f, 0.0f},
        {1.0f, cos(xcmath::radians(90.0f)), 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}};
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            EXPECT_FLOAT_EQ(rotated3d[i][j], expected3d[i][j]);
        }
    }
}

TEST(Function, Translate) {
    xcmath::mat<float, 4, 4> m = xcmath::mat<float, 4, 4>::eye();
    xcmath::vec3<float> v(1.0f, 2.0f, 3.0f);
    xcmath::mat<float, 4, 4> translated = xcmath::translate(m, v);
    xcmath::mat<float, 4, 4> expected{{1, 0, 0, 1},  //
                                      {0, 1, 0, 2},
                                      {0, 0, 1, 3},
                                      {0, 0, 0, 1}};
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            EXPECT_FLOAT_EQ(translated[i][j], expected[i][j]);
        }
    }
    auto m1 = xcmath::mat3f::eye();
    const xcmath::vec3f v1(1.0f, 2.0f);
    auto translated1 = xcmath::translate(m, v);
    xcmath::mat3f expected1{{1, 0, 1},  //
                            {0, 1, 2},
                            {0, 0, 1}};
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_FLOAT_EQ(translated[i][j], expected[i][j]);
        }
    }
}

TEST(Function, Scale) {
    xcmath::mat<float, 4, 4> m = xcmath::mat<float, 4, 4>::eye();
    xcmath::vec3<float> v(2.0f, 3.0f, 4.0f);
    xcmath::mat<float, 4, 4> scaled = xcmath::scale(m, v);
    xcmath::mat<float, 4, 4> expected{{2, 0, 0, 0},  //
                                      {0, 3, 0, 0},
                                      {0, 0, 4, 0},
                                      {0, 0, 0, 1}};
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            EXPECT_FLOAT_EQ(scaled[i][j], expected[i][j]);
        }
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}