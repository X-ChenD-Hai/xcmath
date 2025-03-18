// show.hpp
#ifndef SHOW_H
#define SHOW_H
#include <iostream>

#include "../mobject/declaration.hpp"
#include "./concepts.h"  // IWYU pragma: keep


namespace xcmath {
namespace concepts {
template <typename T>
concept OstreamOverwrite = requires(T a) {
    { std::cout << a } -> std::same_as<std::ostream&>;
};
}  // namespace concepts

template <typename T>
    requires concepts::OstreamOverwrite<T> || requires(T x) {
        { x.to_string() } -> std::same_as<std::string>;
    }
std::ostream& operator<<(std::ostream& os, const complex<T>& c) {
    if constexpr (std::is_arithmetic_v<T>)
        os << c.real << (c.imag >= 0 ? " + " : " - ") << "j" << abs(c.imag);
    else if constexpr (concepts::OstreamOverwrite<T>)
        os << c.real << " + " << "j(" << c.imag << ")";
    else
        os << c.real.to_string() << " + j(" << c.imag.to_string() << ")";
    return os;
}
template <typename T, size_t _rows, size_t _cols>
    requires concepts::OstreamOverwrite<T> || requires(T x) {
        { x.to_string() } -> std::same_as<std::string>;
    }
std::ostream& operator<<(std::ostream& os, const mat<T, _rows, _cols>& m) {
    size_t i = 0;
    if constexpr (std::is_arithmetic_v<T> || concepts::OstreamOverwrite<T>) {
        os << "[";
        for (auto& r : m) {
            if (i) os << " ";
            os << r;
            os << (++i < _rows ? ",\n" : "");
        }
        os << "]";
    } else {
        os << "[";
        for (auto& r : m) {
            if (i) os << " ";
            os << r;
            os << (++i < _rows ? ",\n" : "");
        }
        os << "]";
    };
    return os;
}
template <typename T, size_t _size>
    requires concepts::OstreamOverwrite<T> || requires(T x) {
        { x.to_string() } -> std::same_as<std::string>;
    }
std::ostream& operator<<(std::ostream& os, const vec<T, _size>& v) {
    size_t i = 0;
    if constexpr (std::is_arithmetic_v<T> || concepts::OstreamOverwrite<T>) {
        os << "[";
        for (auto& c : v) {
            os << c << (++i < _size ? ", " : "");
        }
        os << "]";
    } else {
        os << "[";
        for (auto& c : v) {
            os << c.to_string() << (++i < _size ? ", " : "");
        }
        os << "]";
    }
    return os;
}

template <typename T>
    requires concepts::OstreamOverwrite<T> || requires(T x) {
        { x.to_string() } -> std::same_as<std::string>;
    }
std::ostream& operator<<(std::ostream& os, const quaternion<T>& q) {
    if constexpr (std::is_arithmetic_v<T> || concepts::OstreamOverwrite<T>) {
        constexpr auto fn = [](T x) { return x >= 0 ? " + " : " - "; };
        os << q.r() << fn(q.i()) << abs(q.i()) << "i" << fn(q.j()) << abs(q.j())
           << "j" << fn(q.k()) << abs(q.k()) << "k";
    } else {
        os << q.r().to_string() << " + " << q.i().to_string() << "i + "
           << q.j().to_string() << "j + " << q.k().to_string() << "k";
    }
    return os;
}

}  // namespace xcmath
#endif  // SHOW_H
