/**
 * @file declaration.hpp
 * @brief Declaration of vector, matrix, quaternion, and complex classes
 * @author XCDH
 * @version 1.0
 * @date 2023-10-05
 */

#ifndef XCMATH_DECLARATION_HPP
#define XCMATH_DECLARATION_HPP

#include <cstddef>
#include <type_traits>

namespace xcmath {
/**
 * @brief Vector class template
 *
 * @tparam _Tp Type of elements in the vector
 * @tparam _length Length of the vector
 */
template <typename _Tp, size_t _length>
    requires(_length > 0 && std::is_default_constructible_v<_Tp>)
class vec;

/**
 * @brief Matrix class template
 *
 * @tparam _Tp Type of elements in the matrix
 * @tparam _rows Number of rows
 * @tparam _cols Number of columns
 */
template <typename _Tp, size_t _rows, size_t _cols>
class mat;

/**
 * @brief Quaternion class template
 *
 * @tparam T Type of elements in the quaternion
 */
template <typename T>
class quaternion;

/**
 * @brief Complex number class template
 *
 * @tparam T Type of elements in the complex number
 */
template <typename T>
class complex;

/**
 * @brief Deduction guide for vec class template
 *
 * @tparam _Tp1 Type of the first element
 * @tparam _Tp Types of remaining elements
 * @return vec object with elements of type _Tp1 and length sizeof...(_Tp) + 1
 */
template <class _Tp1, class... _Tp>
vec(const _Tp1&, const _Tp...) -> vec<_Tp1, sizeof...(_Tp) + 1>;

// vector type aliases
/**
 * @brief Alias for vec<T, 2>
 *
 * @tparam T Type of elements
 */
template <typename T>
using vec2 = vec<T, 2>;

/**
 * @brief Alias for vec<T, 3>
 *
 * @tparam T Type of elements
 */
template <typename T>
using vec3 = vec<T, 3>;

/**
 * @brief Alias for vec<T, 4>
 *
 * @tparam T Type of elements
 */
template <typename T>
using vec4 = vec<T, 4>;

/**
 * @brief Alias for vec<float, _len>
 *
 * @tparam _len Length of the vector
 */
template <size_t _len>
using vecf = vec<float, _len>;

/**
 * @brief Alias for vec<double, _len>
 *
 * @tparam _len Length of the vector
 */
template <size_t _len>
using vecd = vec<double, _len>;

/**
 * @brief Alias for vec<int, _len>
 *
 * @tparam _len Length of the vector
 */
template <size_t _len>
using veci = vec<int, _len>;

/**
 * @brief Alias for vec<unsigned int, _len>
 *
 * @tparam _len Length of the vector
 */
template <size_t _len>
using vecui = vec<unsigned int, _len>;

/**
 * @brief Alias for vec<long, _len>
 *
 * @tparam _len Length of the vector
 */
template <size_t _len>
using vecl = vec<long, _len>;

/**
 * @brief Alias for vec<unsigned long, _len>
 *
 * @tparam _len Length of the vector
 */
template <size_t _len>
using vecul = vec<unsigned long, _len>;

/**
 * @brief Alias for vec<long long, _len>
 *
 * @tparam _len Length of the vector
 */
template <size_t _len>
using vecll = vec<long long, _len>;

/**
 * @brief Alias for vec<unsigned long long, _len>
 *
 * @tparam _len Length of the vector
 */
template <size_t _len>
using vecull = vec<unsigned long long, _len>;

/**
 * @brief Alias for vec<bool, _len>
 *
 * @tparam _len Length of the vector
 */
template <size_t _len>
using vecb = vec<bool, _len>;

// specific vector type aliases
using vec2f = vec2<float>;
using vec3f = vec3<float>;
using vec4f = vec4<float>;
using vec2d = vec2<double>;
using vec3d = vec3<double>;
using vec4d = vec4<double>;
using vec2i = vec2<int>;
using vec3i = vec3<int>;
using vec4i = vec4<int>;
using vec2ui = vec2<unsigned int>;
using vec3ui = vec3<unsigned int>;
using vec4ui = vec4<unsigned int>;
using vec2l = vec2<long>;
using vec3l = vec3<long>;
using vec4l = vec4<long>;
using vec2ul = vec2<unsigned long>;
using vec3ul = vec3<unsigned long>;
using vec4ul = vec4<unsigned long>;
using vec2ll = vec2<long long>;
using vec3ll = vec3<long long>;
using vec4ll = vec4<long long>;
using vec2ull = vec2<unsigned long long>;
using vec3ull = vec3<unsigned long long>;
using vec4ull = vec4<unsigned long long>;
using vec2b = vec2<bool>;
using vec3b = vec3<bool>;
using vec4b = vec4<bool>;

// matrix type aliases
/**
 * @brief Alias for mat<_Tp, 1, 2>
 *
 * @tparam _Tp Type of elements
 */
template <class _Tp>
using mat1x2 = mat<_Tp, 1, 2>;

/**
 * @brief Alias for mat<_Tp, 1, 3>
 *
 * @tparam _Tp Type of elements
 */
template <class _Tp>
using mat1x3 = mat<_Tp, 1, 3>;

/**
 * @brief Alias for mat<_Tp, 1, 4>
 *
 * @tparam _Tp Type of elements
 */
template <class _Tp>
using mat1x4 = mat<_Tp, 1, 4>;

/**
 * @brief Alias for mat<_Tp, 2, 1>
 *
 * @tparam _Tp Type of elements
 */
template <class _Tp>
using mat2x1 = mat<_Tp, 2, 1>;

/**
 * @brief Alias for mat<_Tp, 2, 2>
 *
 * @tparam _Tp Type of elements
 */
template <class _Tp>
using mat2x2 = mat<_Tp, 2, 2>;

/**
 * @brief Alias for mat<_Tp, 2, 3>
 *
 * @tparam _Tp Type of elements
 */
template <class _Tp>
using mat2x3 = mat<_Tp, 2, 3>;

/**
 * @brief Alias for mat<_Tp, 2, 4>
 *
 * @tparam _Tp Type of elements
 */
template <class _Tp>
using mat2x4 = mat<_Tp, 2, 4>;

/**
 * @brief Alias for mat<_Tp, 3, 1>
 *
 * @tparam _Tp Type of elements
 */
template <class _Tp>
using mat3x1 = mat<_Tp, 3, 1>;

/**
 * @brief Alias for mat<_Tp, 3, 2>
 *
 * @tparam _Tp Type of elements
 */
template <class _Tp>
using mat3x2 = mat<_Tp, 3, 2>;

/**
 * @brief Alias for mat<_Tp, 3, 3>
 *
 * @tparam _Tp Type of elements
 */
template <class _Tp>
using mat3x3 = mat<_Tp, 3, 3>;

/**
 * @brief Alias for mat<_Tp, 3, 4>
 *
 * @tparam _Tp Type of elements
 */
template <class _Tp>
using mat3x4 = mat<_Tp, 3, 4>;

/**
 * @brief Alias for mat<_Tp, 4, 1>
 *
 * @tparam _Tp Type of elements
 */
template <class _Tp>
using mat4x1 = mat<_Tp, 4, 1>;

/**
 * @brief Alias for mat<_Tp, 4, 2>
 *
 * @tparam _Tp Type of elements
 */
template <class _Tp>
using mat4x2 = mat<_Tp, 4, 2>;

/**
 * @brief Alias for mat<_Tp, 4, 3>
 *
 * @tparam _Tp Type of elements
 */
template <class _Tp>
using mat4x3 = mat<_Tp, 4, 3>;

/**
 * @brief Alias for mat<_Tp, 4, 4>
 *
 * @tparam _Tp Type of elements
 */
template <class _Tp>
using mat4x4 = mat<_Tp, 4, 4>;

/**
 * @brief Alias for mat3x3<_Tp>
 *
 * @tparam _Tp Type of elements
 */
template <class _Tp>
using mat3 = mat3x3<_Tp>;

/**
 * @brief Alias for mat4x4<_Tp>
 *
 * @tparam _Tp Type of elements
 */
template <class _Tp>
using mat4 = mat4x4<_Tp>;

// specific matrix type aliases
using mat1x2f = mat1x2<float>;
using mat1x3f = mat1x3<float>;
using mat1x4f = mat1x4<float>;
using mat2x1f = mat2x1<float>;
using mat2x2f = mat2x2<float>;
using mat2x3f = mat2x3<float>;
using mat2x4f = mat2x4<float>;
using mat3x1f = mat3x1<float>;
using mat3x2f = mat3x2<float>;
using mat3x3f = mat3x3<float>;
using mat3x4f = mat3x4<float>;
using mat4x1f = mat4x1<float>;
using mat4x2f = mat4x2<float>;
using mat4x3f = mat4x3<float>;
using mat4x4f = mat4x4<float>;

using mat1x2d = mat1x2<double>;
using mat1x3d = mat1x3<double>;
using mat1x4d = mat1x4<double>;
using mat2x1d = mat2x1<double>;
using mat2x2d = mat2x2<double>;
using mat2x3d = mat2x3<double>;
using mat2x4d = mat2x4<double>;
using mat3x1d = mat3x1<double>;
using mat3x2d = mat3x2<double>;
using mat3x3d = mat3x3<double>;
using mat3x4d = mat3x4<double>;
using mat4x1d = mat4x1<double>;
using mat4x2d = mat4x2<double>;
using mat4x3d = mat4x3<double>;
using mat4x4d = mat4x4<double>;

using mat1x2i = mat1x2<int>;
using mat1x3i = mat1x3<int>;
using mat1x4i = mat1x4<int>;
using mat2x1i = mat2x1<int>;
using mat2x2i = mat2x2<int>;
using mat2x3i = mat2x3<int>;
using mat2x4i = mat2x4<int>;
using mat3x1i = mat3x1<int>;
using mat3x2i = mat3x2<int>;
using mat3x3i = mat3x3<int>;
using mat3x4i = mat3x4<int>;
using mat4x1i = mat4x1<int>;
using mat4x2i = mat4x2<int>;
using mat4x3i = mat4x3<int>;
using mat4x4i = mat4x4<int>;

using mat1x2l = mat1x2<long>;
using mat1x3l = mat1x3<long>;
using mat1x4l = mat1x4<long>;
using mat2x1l = mat2x1<long>;
using mat2x2l = mat2x2<long>;
using mat2x3l = mat2x3<long>;
using mat2x4l = mat2x4<long>;
using mat3x1l = mat3x1<long>;
using mat3x2l = mat3x2<long>;
using mat3x3l = mat3x3<long>;
using mat3x4l = mat3x4<long>;
using mat4x1l = mat4x1<long>;
using mat4x2l = mat4x2<long>;
using mat4x3l = mat4x3<long>;
using mat4x4l = mat4x4<long>;

using mat1x2ul = mat1x2<unsigned long>;
using mat1x3ul = mat1x3<unsigned long>;
using mat1x4ul = mat1x4<unsigned long>;
using mat2x1ul = mat2x1<unsigned long>;
using mat2x2ul = mat2x2<unsigned long>;
using mat2x3ul = mat2x3<unsigned long>;
using mat2x4ul = mat2x4<unsigned long>;
using mat3x1ul = mat3x1<unsigned long>;
using mat3x2ul = mat3x2<unsigned long>;
using mat3x3ul = mat3x3<unsigned long>;
using mat3x4ul = mat3x4<unsigned long>;
using mat4x1ul = mat4x1<unsigned long>;
using mat4x2ul = mat4x2<unsigned long>;
using mat4x3ul = mat4x3<unsigned long>;
using mat4x4ul = mat4x4<unsigned long>;

using mat1x2b = mat1x2<bool>;
using mat1x3b = mat1x3<bool>;
using mat1x4b = mat1x4<bool>;
using mat2x1b = mat2x1<bool>;
using mat2x2b = mat2x2<bool>;
using mat2x3b = mat2x3<bool>;
using mat2x4b = mat2x4<bool>;
using mat3x1b = mat3x1<bool>;
using mat3x2b = mat3x2<bool>;
using mat3x3b = mat3x3<bool>;
using mat3x4b = mat3x4<bool>;
using mat4x1b = mat4x1<bool>;
using mat4x2b = mat4x2<bool>;
using mat4x3b = mat4x3<bool>;
using mat4x4b = mat4x4<bool>;

using mat2f = mat2x2f;
using mat3f = mat3x3f;
using mat4f = mat4x4f;
using mat2d = mat2x2d;
using mat3d = mat3x3d;
using mat4d = mat4x4d;
using mat2i = mat2x2i;
using mat3i = mat3x3i;
using mat4i = mat4x4i;
using mat2l = mat2x2l;
using mat3l = mat3x3l;
using mat4l = mat4x4l;
using mat2ul = mat2x2ul;
using mat3ul = mat3x3ul;
using mat4ul = mat4x4ul;
using mat2b = mat2x2b;
using mat3b = mat3x3b;
using mat4b = mat4x4b;

// constants
/**
 * @brief Pi constant
 */
constexpr long double PI =
    3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

}  // namespace xcmath

#endif  // XCMATH_DECLARATION_HPP