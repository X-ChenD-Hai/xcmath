/**
 * @file function.hpp
 * @brief Header file for mathematical functions
 * @author XCDH
 * @version 1.0
 * @date 2023-10-05
 */
#pragma once
#ifndef XCMATH_FUNCTION_HPP
#define XCMATH_FUNCTION_HPP

#include <cmath>

#include "./declaration.hpp"

namespace xcmath {
/**
 * @brief Convert degrees to radians
 *
 * @tparam T Type of degrees
 * @param degrees Degrees to convert
 * @return Equivalent radians value
 */
template <typename T>
inline constexpr T radians(T degrees) {
    return degrees * PI / 180.0;
};

/**
 * @brief Convert radians to degrees
 *
 * @tparam T Type of radians
 * @param radians Radians to convert
 * @return Equivalent degrees value
 */
template <typename T>
inline constexpr T degrees(T radians) {
    return radians * 180.0 / PI;
};

/**
 * @brief Apply rotation for transform or rotation matrix around an axis
 *
 * @tparam _Tp Type of elements
 * @tparam _length Length of the axis vector (3 or 4)
 * @tparam _dim Dimension of the matrix (3 or 4)
 * @param m Input matrix to apply rotation
 * @param angle Rotation angle in degrees
 * @param axis Rotation axis vector
 * @return Rotated matrix
 */
template <class _Tp, size_t _length = 3, size_t _dim = 4>
    requires((_length == 3 || _length == 4) && (_dim == 4 || _dim == 3))
mat<_Tp, _dim, _dim> rotate(const mat<_Tp, _dim, _dim>& m, _Tp angle,
                            const vec<_Tp, _length>& axis) {
    auto _axis = axis.normalize();
    auto res = mat<_Tp, _dim, _dim>::eye();
    angle = radians(angle);
    _Tp c = std::cos(angle);
    _Tp s = std::sin(angle);
    _Tp t = 1 - c;
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

/**
 * @brief Apply rotation for 2D transform or rotation matrix around an axis
 *
 * @tparam _Tp Type of elements
 * @tparam _dim Dimension of the matrix (3 or 4)
 * @param m Input matrix to apply rotation
 * @param angle Rotation angle in degrees
 * @return Rotated matrix
 */
template <class _Tp, class _MTp = _Tp, size_t _dim = 3>
    requires(std::is_floating_point_v<_Tp> && (_dim == 3 || _dim == 4))
mat<_MTp, _dim, _dim> rotate(const mat<_MTp, _dim, _dim>& m, _Tp angle) {
    auto res = mat<_Tp, _dim, _dim>::eye();
    angle = radians(angle);
    res[1][1] = res[0][0] = std::cos(angle);
    res[0][1] = -(res[1][0] = std::sin(angle));
    return res ^ m;
}

/**
 * @brief Apply rotation for matrix around an axis specified by coordinates
 *
 * @tparam _Tp Type of elements
 * @tparam _dim Dimension of the matrix (3 or 4)
 * @param m Input matrix to apply rotation
 * @param angle Rotation angle in degrees
 * @param x X-coordinate of rotation axis
 * @param y Y-coordinate of rotation axis
 * @param z Z-coordinate of rotation axis
 * @return Rotated matrix
 */
template <class _Tp, class _ATp = _Tp, size_t _dim = 3>
    requires(std::is_floating_point_v<_Tp> && std::is_floating_point_v<_ATp>)
mat<_Tp, _dim, _dim> rotate(const mat<_Tp, _dim, _dim>& m, _ATp angle, _Tp x,
                            _Tp y, _Tp z) {
    return rotate(m, angle, vec<_Tp, 3>(x, y, z));
}

/**
 * @brief Apply translation for matrix
 *
 * @tparam _Tp Type of elements
 * @tparam _len Dimension of the matrix (3 or 4)
 * @param m Input matrix to apply translation
 * @param v Translation vector
 * @return Translated matrix
 */
template <class _Tp, size_t _len = 4, size_t _vlen = 3>
    requires((_len == 4 || _len == 3) && _vlen == _len - 1)
constexpr mat<_Tp, _len, _len> translate(const mat<_Tp, _len, _len>& m,
                                         const vec<_Tp, _vlen>& v) {
    auto res = m;
    res[0][_vlen] += v[0];
    res[1][_vlen] += v[1];
    if constexpr (_len == 4) res[2][_vlen] += v[2];
    return res;
}

/**
 * @brief Apply translation for matrix using a homogenous vector
 *
 * @tparam _Tp Type of elements
 * @tparam _len Dimension of the matrix (3 or 4)
 * @param m Input matrix to apply translation
 * @param v Translation vector
 * @return Translated matrix
 */
template <class _Tp, size_t _len = 4>
    requires(_len == 4 || _len == 3)
constexpr mat<_Tp, _len, _len> translate(const mat<_Tp, _len, _len>& m,
                                         const vec<_Tp, _len>& v) {
    return translate(m, v(slice_to<_len - 1>));
}

/**
 * @brief Apply translation to a matrix
 *
 * @param m Input matrix to apply translation
 * @param v Translation vector
 * @return Translated matrix
 */
template <class _Tp, class _ATp = _Tp, size_t _dim = 4>
    requires(std::is_floating_point_v<_Tp> && std::is_floating_point_v<_ATp> &&
             (_dim == 4 || _dim == 3))
constexpr mat<_Tp, _dim, _dim> scale(const mat<_Tp, _dim, _dim>& m,
                                     const vec<_ATp, _dim - 1>& v) {
    auto res = mat<_Tp, _dim, _dim>::eye();
    res[0][0] *= v[0];
    res[1][1] *= v[1];
    if constexpr (_dim == 4) res[2][2] *= v[2];
    return res ^ m;
}
/**
 * @brief Scale a matrix by a vector
 * @tparam _Tp The type of the matrix
 * @tparam _STp The type of the vector
 *
 * @param m The matrix to scale
 * @param v The vector to scale by
 * @return The scaled matrix
 */

template <class _Tp, class _STp, size_t _dim = 4>
    requires(std::is_arithmetic_v<_STp> && (_dim == 4 || _dim == 3))
constexpr mat<_Tp, _dim, _dim> scale(const mat<_Tp, _dim, _dim>& m,
                                     const _STp s) {
    return scale(m, vec<_Tp, _dim - 1>(s));
}

}  // namespace xcmath

#endif