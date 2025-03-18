#include <gtest/gtest.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <xcmath.hpp>
//
#include <utils/show.hpp>
#define DEBUG std::cout
#define END std::endl
#define DEBUG_S(x) << #x " "
#define DEBUG_SV(x) << #x ": " << x << " "
#define DEBUG_NV(n, x) << #n ": " << x << " "
#define DEBUG_V(n, x) << x << " "

TEST(Function, Function) {
    using namespace xcmath;
    constexpr auto a = mat3f::eye();
    auto s = xcmath::rotate(a, 90.0f, vec3f{1.0f, 0.0f, 0.0f});
    DEBUG DEBUG_NV(s, s);
}

TEST(Function, muti) {
    using namespace xcmath;
    auto m = mat3f::eye();
    m = rotate(m, 90.0f);
    m = translate(m, vecf<2>{1.0f, 1.0f});
    auto v = vec3f(1.f);
    // v[2] = 0;
    DEBUG << (v) << END;
    DEBUG << (m) << END;
    DEBUG << (m ^ v) << END;
}