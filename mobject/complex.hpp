// complex.hpp
#ifndef XCMATH_COMPLEX_H
#define XCMATH_COMPLEX_H
#include <concepts>
#include <cstdint>
#include <type_traits>

#include "../utils/concepts.h"
#include "../utils/compiling.hpp"

namespace xcmath {

template <typename T = double>
class Complex {
   public:
    T real;
    T imag;
    static constexpr auto Type = get_type_name<T>();

    Complex(const T& real, const T& imag) : real(real), imag(imag) {}
    Complex(const T& real)
        requires std::is_default_constructible_v<T>
        : Complex(real, T{}) {}
    Complex()
        requires std::is_default_constructible_v<T>
        : Complex(T{}, T{}) {}

    template <typename Vtp2>
        requires std::convertible_to<Vtp2, T>
    Complex(const T& real, const Vtp2& imag) : Complex(real, T(imag)) {}

    template <typename Vtp1>
        requires std::convertible_to<Vtp1, T>
    Complex(const Vtp1& real, const T& imag) : Complex(T(real), imag) {}

    Complex operator+(const Complex& other) const
        requires concepts::Add<T>
    {
        return Complex(real + other.real, imag + other.imag);
    }
    Complex operator-(const Complex& other) const
        requires concepts::Subtract<T>
    {
        return Complex(real - other.real, imag - other.imag);
    }
    Complex operator-() const
        requires concepts::Minus<T>
    {
        return Complex(-real, -imag);
    }
    Complex operator*(const Complex& other) const
        requires concepts::Muitiply<T>
    {
        return Complex(real * other.real - imag * other.imag,
                       real * other.imag + imag * other.real);
    }
    Complex operator/(const Complex& other) const
        requires concepts::Divide<T>
    {
        return *this * other.inv();
    }
    template <typename Res = double>
    Res mod()
        requires concepts::Sqrt<T>
    {
        return sqrt(real * real + imag * imag);
    }
    Complex<T> inv()
        requires concepts::Divide<T>
    {
        auto mod_2 = real * real + imag * imag;
        return Complex(real / mod_2, -imag / mod_2);
    }
    template <class V>
        requires std::convertible_to<T, V>
    operator Complex<V>() {
        return Complex<V>((V)real, (V)imag);
    }
};  // class Complex

inline xcmath::Complex<long long> operator"" _i(unsigned long long x) {
    return xcmath::Complex<long long>((long long)0, (long long)x);
};
inline xcmath::Complex<long double> operator"" _i(long double x) {
    return xcmath::Complex<long double>((long double)0, (long double)x);
}

using Complex_f128 = Complex<long double>;
using Complex_f64 = Complex<double>;
using Complex_f32 = Complex<float>;
using Complex_f = Complex<float>;
using Complex_i = Complex<int32_t>;
using Complex_l = Complex<long>;
using Complex_ll = Complex<long long>;

}  // namespace xcmath

#endif  // XCMATH_COMPLEX_H