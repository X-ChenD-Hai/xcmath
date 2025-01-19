// mathconcepts.h
#ifndef MATHCONCEPTS_H
#define MATHCONCEPTS_H
#include <concepts>

namespace xcmath {
namespace concepts {
template <typename _Tp1, typename _Tp2 = _Tp1, typename _RTp = _Tp1>
concept Add = requires(_Tp1 a, _Tp2 b) {
    { a + b } -> std::same_as<_RTp>;
};
template <typename _Tp1, typename _Tp2 = _Tp1, typename _RTp = _Tp1>
concept Subtract = requires(_Tp1 a, _Tp2 b) {
    { a - b } -> std::same_as<_RTp>;
};
template <typename _Tp1, typename _Tp2 = _Tp1, typename _RTp = _Tp1>
concept Muitiply = requires(_Tp1 a, _Tp2 b) {
    { a* b } -> std::same_as<_RTp>;
};
template <typename _Tp1, typename _Tp2 = _Tp1, typename _RTp = _Tp1>
concept Divide = requires(_Tp1 a, _Tp2 b) {
    { a / b } -> std::same_as<_RTp>;
};
template <typename _Tp1, typename _RTp = _Tp1>
concept Minus = requires(_Tp1 a) {
    { -a } -> std::same_as<_RTp>;
};
template <typename _Tp1, typename _RTp = _Tp1>
concept Sqrt = requires(_Tp1 x) {
    { sqrt(x) } -> std::same_as<_RTp>;
};
template <typename Tp1, typename Tp2>
concept lt = requires(Tp1 a, Tp2 b) {
    { a < b } -> std::same_as<bool>;
};
template <typename Tp1, typename Tp2>
concept le = requires(Tp1 a, Tp2 b) {
    { a <= b } -> std::same_as<bool>;
};
template <typename Tp1, typename Tp2>
concept gt = requires(Tp1 a, Tp2 b) {
    { a > b } -> std::same_as<bool>;
};
template <typename Tp1, typename Tp2>
concept ge = requires(Tp1 a, Tp2 b) {
    { a > b } -> std::same_as<bool>;
};
template <typename Tp1, typename Tp2>
concept eq = requires(Tp1 a, Tp2 b) {
    { a == b } -> std::same_as<bool>;
};
template <typename Tp1, typename Tp2>
concept ne = requires(Tp1 a, Tp2 b) {
    { a != b } -> std::same_as<bool>;
};
template <typename Tp1, typename Tp2>
concept lg = requires(Tp1 a, Tp2 b) {
    { a <= b } -> std::same_as<bool>;
};
template <typename Tp1, typename Tp2>
concept Compare = requires(Tp1 a, Tp2 b) {
    { a < b } -> std::same_as<bool>;
    { a <= b } -> std::same_as<bool>;
    { a > b } -> std::same_as<bool>;
    { a >= b } -> std::same_as<bool>;
    { a == b } -> std::same_as<bool>;
    { a != b } -> std::same_as<bool>;
};

};  // namespace concepts

}  // namespace math

#endif  // MATHCONCEPTS_H