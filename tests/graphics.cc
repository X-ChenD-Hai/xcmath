#include <gtest/gtest.h>

#include <cstddef>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <xcmath/xcmath.hpp>
//
#include <xcmath/utils/show.hpp>

#include "gtest/gtest.h"

xcmath::mat4f projection(float fov, float aspect, float near_, float far_) {
    if (fov == 0.0f || aspect == 0.0f || near_ == 0.0f || far_ == 0.0f ||
        near_ >= far_) {
        // throw std::runtime_error("Invalid camera parameters");
    }
    xcmath::mat4f projectionMatrix{};
    float f = 1.0f / tan(fov / 2.0f);
    projectionMatrix[0][0] = f / aspect;
    projectionMatrix[1][1] = f;
    projectionMatrix[2][2] = (far_ + near_) / (near_ - far_);
    projectionMatrix[3][2] = 2.0f * far_ * near_ / (near_ - far_);
    projectionMatrix[2][3] = -1.0f;

    return projectionMatrix;
}
xcmath::mat4f lookAt(const xcmath::vec3f &position, const xcmath::vec3f &target,
                     const xcmath::vec3f &up) {
    if ((position == target).every()) {
        // throw std::runtime_error("Position and target are the same");
    }
    xcmath::vec3f forward = (target - position).normalize();
    if (std::abs(forward.dot(up)) >=
        0.9999f) {  // 使用一个阈值来判断是否接近平行
        // throw std::runtime_error("Forward and up vectors are parallel");
    }
    xcmath::vec3f side = forward.cross(up).normalize();
    xcmath::vec3f upward = side.cross(forward).normalize();

    // 修正视图矩阵的第四行
    xcmath::mat4f viewMatrix{
        xcmath::vec4f(side.x(), upward.x(), -forward.x(), 0.0f),
        xcmath::vec4f(side.y(), upward.y(), -forward.y(), 0.0f),
        xcmath::vec4f(side.z(), upward.z(), -forward.z(), 0.0f),
        xcmath::vec4f(-position.x(), -position.y(), -position.z(), 1.0f)};

    // 使用一个小的阈值来检查行列式
    const float epsilon = 1e-6f;
    if (std::abs(viewMatrix.det()) < epsilon) {
        // throw std::runtime_error("Invalid camera parameters");
    }

    return viewMatrix;
}

TEST(GraphicsTest, Projection) {
    xcmath::mat4f projectionMatrix =
        projection(xcmath::radians(55.0f), 1.321, 0.1f, 1000.0f);
    glm::mat4 glmProjectionMatrix =
        glm::perspective(glm::radians(55.0f), 1.321f, 0.1f, 1000.0f);
    std::cout << projectionMatrix << std::endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << glmProjectionMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    for (size_t i; i < 16; i++) {
        EXPECT_FLOAT_EQ(((&projectionMatrix[0][0]))[i],
                        (&glmProjectionMatrix[0][0])[i]);
    }
}

TEST(GraphicsTest, LookAt) {
    xcmath::mat4f viewMatrix =
        lookAt(xcmath::vec3f(0.0f, 0.0f, 3.0f), xcmath::vec3f(0.0f, 0.0f, 1.0f),
               xcmath::vec3f(0.0f, 1.0f, 0.0f));
    glm::mat4 glmViewMatrix =
        glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 1.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f));

    std::cout << viewMatrix << std::endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << glmViewMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}