#include <cmath>  // IWYU pragma: keep
#include <cstddef>
#include <iostream>

#include "math.hpp"
#include "mobject/complex.hpp"
#include "mobject/vec.hpp"
#include "utils/show.hpp"

using namespace std;

int main() {
    using namespace std;
    using namespace math;
    auto x = vec3<int>(1, 2, 3);
    auto x2 = vec2<int>(1, 2);
    auto x3 = vec3<int>(x2, 3);
    mat<int, 3, 3> m(x, vec<int, 3>{1}, x3);
    quaternion<int> q(1, 2, 3, 4);
    cout << m << endl;
    cout << x3 << endl;
    return 0;
}