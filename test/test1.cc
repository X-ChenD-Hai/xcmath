#include <cmath>  // IWYU pragma: keep
#include <iostream>

#include "xcmath.hpp"
#include "mobject/vec.hpp"

using namespace std;

int main() {
    using namespace std;
    using namespace xcmath;
    auto x = vec3<int>(1, 2, 3);
    auto x2 = vec2<int>(1, 2);
    auto x3 = vec3<int>(x2, 3);
    quaternion<int> q(1, 2, 3, 4);
    auto m = mat<int, 3, 2>{vec2<int>(1, 2), vec2<int>{3, 4}, vec2<int>{5, 6}};

    return 0;
}