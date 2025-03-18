#ifndef XCMATH_DECLARATION_HPP
#define XCMATH_DECLARATION_HPP
#include <cstddef>
#include <type_traits>
namespace xcmath {
template <typename _Tp, size_t _length>
    requires(_length > 0 && std::is_default_constructible_v<_Tp>)
class vec;
template <typename _Tp, size_t _rows, size_t _cols>
class mat;
template <typename T>
class quaternion;
template <typename T>
class complex;
constexpr long double PI =
    3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;
}  // namespace xcmath

#endif  // XCMATH_DECLARATION_HPP