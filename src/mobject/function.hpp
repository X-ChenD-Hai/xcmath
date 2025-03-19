/**
 * @file function.hpp
 * @brief Header file for mathematical functions
 * @author XCDH
 * @version 1.0
 * @date 2023-10-05
 */

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
inline constexpr float radians(T degrees) {
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
inline constexpr float degrees(T radians) {
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

/**
 * @brief Apply rotation for 2D transform or rotation matrix around an axis
 *
 * @tparam _Tp Type of elements
 * @tparam _dim Dimension of the matrix (3 or 4)
 * @param m Input matrix to apply rotation
 * @param angle Rotation angle in degrees
 * @return Rotated matrix
 */
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
template <class _Tp, size_t _dim = 3>
mat<_Tp, _dim, _dim> rotate(const mat<_Tp, _dim, _dim>& m, _Tp angle, _Tp x,
                            _Tp y, _Tp z) {
    return rotate(m, angle, vec<_Tp, 3>(x, y, z));
}

/**
 * @brief Apply translation for matrix
 *
 * @tparam _Tp Type of elements
 * @tparam _dim Dimension of the matrix (3 or 4)
 * @param m Input matrix to apply translation
 * @param v Translation vector
 * @return Translated matrix
 */
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

/**
 * @brief Apply translation for matrix using a homogenous vector
 *
 * @tparam _Tp Type of elements
 * @tparam _dim Dimension of the matrix (3 or 4)
 * @param m Input matrix to apply translation
 * @param v Translation vector
 * @return Translated matrix
 */
template <class _Tp, size_t _dim = 4>
    requires(_dim == 4 || _dim == 3)
constexpr mat<_Tp, _dim, _dim> translate(const mat<_Tp, _dim, _dim>& m,
                                         const vec<_Tp, _dim>& v) {
    return translate(m, v.template slice<_dim - 1>());
}
}  // namespace xcmath

#endif