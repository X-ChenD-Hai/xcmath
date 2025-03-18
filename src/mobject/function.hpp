// function.hpp
#ifndef XCMATH_FUNCTION_HPP
#define XCMATH_FUNCTION_HPP
#include <cmath>

#include "./declaration.hpp"

namespace xcmath {
template <typename T>
inline constexpr float radians(T degrees) {
    return degrees * 3.14159265358979323846 / 180.0;
};
template <typename T>
inline constexpr float degrees(T radians) {
    return radians * 180.0 / 3.14159265358979323846;
};
template <class _Tp, size_t _length = 3, size_t _dim = 4>
    requires((_length == 3 || _length == 4) && (_dim == 4 || _dim == 3))
mat<_Tp, _dim, _dim> rotate(const mat<_Tp, _dim, _dim>& m, _Tp angle,
                            const vec<_Tp, _length>& axis) {
    auto _axis = axis.normalize();
    angle = radians(angle);
    _Tp c = std::cos(angle);
    _Tp s = std::sin(angle);
    _Tp t = 1 - c;
    auto res = mat<_Tp, _dim, _dim>::eye();
    res[0][0] = c + t * _axis[0] * _axis[0];
    res[0][1] = t * _axis[0] * _axis[1] - s * _axis[2];
    res[0][2] = t * _axis[0] * _axis[2] + s * _axis[1];

    res[1][0] = t * _axis[0] * _axis[1] + s * _axis[2];
    res[1][1] = c + t * _axis[1] * _axis[1];
    res[1][2] = t * _axis[1] * _axis[2] - s * _axis[0];

    res[2][0] = t * _axis[0] * _axis[2] - s * _axis[1];
    res[2][1] = t * _axis[1] * _axis[2] + s * _axis[0];
    res[2][2] = c + t * _axis[2] * _axis[2];
    return res ^ m;
}
template <class _Tp, size_t _dim = 3>
mat<_Tp, _dim, _dim> rotate(const mat<_Tp, _dim, _dim>& m, _Tp angle) {
    angle = radians(angle);
    auto res = mat<_Tp, _dim, _dim>::eye();
    res[0][0] = std::cos(angle);
    res[0][1] = -std::sin(angle);
    res[1][0] = std::sin(angle);
    res[1][1] = std::cos(angle);
    return res ^ m;
}

template <class _Tp, size_t _dim = 3>
mat<_Tp, _dim, _dim> rotate(const mat<_Tp, _dim, _dim>& m, _Tp angle, _Tp x,
                            _Tp y, _Tp z) {
    return rotate(m, angle, vec<_Tp, 3>(x, y, z));
}

template <class _Tp, size_t _dim = 4>
    requires(_dim == 4 || _dim == 3)
constexpr mat<_Tp, _dim, _dim> translate(const mat<_Tp, _dim, _dim>& m,
                                         const vec<_Tp, _dim - 1>& v) {
    auto res = m;
    res[0][_dim - 1] += v[0];
    res[1][_dim - 1] += v[1];
    if constexpr (_dim == 4) res[2][_dim - 1] += v[2];
    return res;
}
template <class _Tp, size_t _dim = 4>
    requires(_dim == 4 || _dim == 3)
constexpr mat<_Tp, _dim, _dim> translate(const mat<_Tp, _dim, _dim>& m,
                                         const vec<_Tp, _dim>& v) {
    return translate(m, v.template slice<0, _dim - 1>());
}
}  // namespace xcmath

#endif