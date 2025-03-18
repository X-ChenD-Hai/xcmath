// complex.hpp
#ifndef XCMATH_COMPLEX_H
#define XCMATH_COMPLEX_H
#include <concepts>
#include <cstdint>
#include <type_traits>

#include "../utils/compiling.hpp"
#include "../utils/concepts.h"

namespace xcmath {

template <typename T>
class complex {
   public:
    T real;
    T imag;
    static constexpr auto Type = get_type_name<T>();

    complex(const T& real, const T& imag) : real(real), imag(imag) {}
    complex(const T& real)
        requires std::is_default_constructible_v<T>
        : complex(real, T{}) {}
    complex()
        requires std::is_default_constructible_v<T>
        : complex(T{}, T{}) {}

    template <typename Vtp2>
        requires std::convertible_to<Vtp2, T>
    complex(const T& real, const Vtp2& imag) : complex(real, T(imag)) {}

    template <typename Vtp1>
        requires std::convertible_to<Vtp1, T>
    complex(const Vtp1& real, const T& imag) : complex(T(real), imag) {}

    complex operator+(const complex& other) const
        requires concepts::Add<T>
    {
        return complex(real + other.real, imag + other.imag);
    }
    complex operator-(const complex& other) const
        requires concepts::Subtract<T>
    {
        return complex(real - other.real, imag - other.imag);
    }
    complex operator-() const
        requires concepts::Minus<T>
    {
        return complex(-real, -imag);
    }
    complex operator*(const complex& other) const
        requires concepts::Muitiply<T>
    {
        return complex(real * other.real - imag * other.imag,
                       real * other.imag + imag * other.real);
    }
    complex operator/(const complex& other) const
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
    complex<T> inv()
        requires concepts::Divide<T>
    {
        auto mod_2 = real * real + imag * imag;
        return complex(real / mod_2, -imag / mod_2);
    }
    template <class V>
        requires std::convertible_to<T, V>
    operator complex<V>() {
        return complex<V>((V)real, (V)imag);
    }
};  // class complex

inline xcmath::complex<long long> operator""_i(unsigned long long x) {
    return xcmath::complex<long long>((long long)0, (long long)x);
};
inline xcmath::complex<long double> operator""_i(long double x) {
    return xcmath::complex<long double>((long double)0, (long double)x);
}

using complex_f128 = complex<long double>;
using complex_f64 = complex<double>;
using complex_f32 = complex<float>;
using complex_f = complex<float>;
using complex_i = complex<int32_t>;
using complex_l = complex<long>;
using complex_ll = complex<long long>;

}  // namespace xcmath

#endif  // XCMATH_COMPLEX_H