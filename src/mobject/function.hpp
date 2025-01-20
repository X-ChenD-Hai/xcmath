// function.hpp
#ifndef XCMATH_FUNCTION_HPP
#define XCMATH_FUNCTION_HPP
namespace xcmath {
template <typename T>
inline constexpr float radians(T degrees) {
    return degrees * 3.14159265358979323846 / 180.0;
};
template <typename T>
inline constexpr float degrees(T radians) {
    return radians * 180.0 / 3.14159265358979323846;
};
}  // namespace xcmath

#endif