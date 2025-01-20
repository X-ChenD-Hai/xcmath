// vec.hpp
#ifndef VEC_H
#define VEC_H
#include <vcruntime_typeinfo.h>

#include <concepts>
#include <cstddef>
#include <type_traits>

#include "../utils/compiling.hpp"

namespace xcmath {
template <class T>
concept Vec = requires(T a) {
    typename T::DataType;
    typename T::ItemType;
    std::is_same_v<typename T::template Self<typename T::DataType>, T>;
    T::datatype;
    T::itemtype;
    { T::length } -> std::same_as<const size_t&>;
    { a[T::length - 1] } -> std::same_as<typename T::ItemType&>;
};
template <typename _Vec, class _Item>
concept VecItem = requires {
    Vec<_Vec>;
    requires std::convertible_to<typename _Vec::ItemType, _Item> ||
                 std::convertible_to<_Item, typename _Vec::ItemType>;
};
template <class _Tp>
static constexpr auto get_item_zero() {
    if constexpr (Vec<_Tp>) {
        return get_item_zero<typename _Tp::ItemType>();
    } else {
        return _Tp{};
    }
}
template <typename _Tp, size_t _length>
    requires(_length > 0 && std::is_default_constructible_v<_Tp>)
class vec {
   public:
    _Tp data[_length]{_Tp{}};
    using ItemType = _Tp;
    using DataType = decltype(get_item_zero<ItemType>());
    template <class _T>
    using Self = vec<_T, _length>;
    constexpr static auto datatype = get_type_name<DataType>();
    constexpr static auto itemtype = get_type_name<ItemType>();
    constexpr static auto length = _length;
    constexpr const _Tp* begin() const { return data; }
    constexpr const _Tp* end() const { return data + length; }
    _Tp& operator[](size_t index) { return data[index]; }
    const _Tp& operator[](size_t index) const { return data[index]; }

    template <Vec _NTp>
        requires(std::convertible_to<ItemType, typename _NTp::ItemType> &&
                 length == _NTp::length)
    operator _NTp() const {
        _NTp res;
        for (size_t i = 0; i < _length; i++) {
            res[i] = static_cast<_NTp::ItemType>(data[i]);
        }
        return res;
    }
    // constructor
    template <typename... V, size_t _len = _length>
        requires(sizeof...(V) < _len) &&
                ((std::convertible_to<const V&, const _Tp&>) && ...)
    constexpr explicit vec(const _Tp& cur_data, const V&... next_data) {
        data[0] = cur_data;
        size_t idx = 0;
        ([&]() { data[++idx] = next_data; }(), ...);
    }
    template <size_t _n, size_t _len = _length, typename... V>
        requires(_n + sizeof...(V) <= _len) &&
                ((std::convertible_to<V, _Tp>) && ...)
    constexpr explicit vec(const vec<_Tp, _n>& n, V... next_data) {
        for (size_t i = 0; i < _n; i++) {
            data[i] = n[i];
        }
        size_t idx = _n - 1;
        ([&]() { data[++idx] = next_data; }(), ...);
    }
    constexpr explicit vec(const _Tp& fill_data) {
        for (size_t i = 0; i < _length; i++) {
            data[i] = _Tp{fill_data};
        }
    }

    constexpr vec(const vec<_Tp, _length>& other) {
        for (size_t i = 0; i < _length; i++) {
            data[i] = other[i];
        }
    }
    constexpr vec() {}
    // computional methods
    vec<_Tp, _length> cross(const vec<_Tp, _length>& other) const {
        vec<_Tp, _length> res;
        res[0] = data[1] * other[2] - data[2] * other[1];
        res[1] = data[2] * other[0] - data[0] * other[2];
        res[2] = data[0] * other[1] - data[1] * other[0];
        return res;
    }
    _Tp dot(const vec<_Tp, _length>& other) const {
        _Tp res = _Tp{};
        for (size_t i = 0; i < _length; i++) {
            res += data[i] * other[i];
        }
        return res;
    }
    vec<_Tp, _length> normalize() const {
        vec<_Tp, _length> res;
        auto disten = distance({});
        for (size_t i = 0; i < _length; i++) {
            res[i] = data[i] / disten;
        }
        return res;
    }
    _Tp distance(const vec<_Tp, _length>& other) const {
        _Tp res = _Tp{};
        for (size_t i = 0; i < _length; i++) {
            res += (data[i] - other[i]) * (data[i] - other[i]);
        }
        return sqrt(res);
    }
    _Tp mod() const {
        _Tp res = _Tp{};
        for (size_t i = 0; i < _length; i++) {
            res += data[i] * data[i];
        }
        return sqrt(res);
    }
    _Tp angle(const vec<_Tp, _length>& other) const {
        _Tp cos_theta = dot(other) / (mod() * other.mod());
        return acos(cos_theta);
    }
};

template <typename T>
class vec4 : public vec<T, 4> {
   public:
    using vec<T, 4>::vec;
    T& w() { return this->data[0]; }
    T& x() { return this->data[1]; }
    T& y() { return this->data[2]; }
    T& z() { return this->data[3]; }
    const T& w() const { return this->data[0]; }
    const T& x() const { return this->data[1]; }
    const T& y() const { return this->data[2]; }
    const T& z() const { return this->data[3]; }
};
template <typename T>
class vec3 : public vec<T, 3> {
   public:
    using vec<T, 3>::vec;
    T& x() { return this->data[0]; }
    T& y() { return this->data[1]; }
    T& z() { return this->data[2]; }
    const T& x() const { return this->data[0]; }
    const T& y() const { return this->data[1]; }
    const T& z() const { return this->data[2]; }
};
template <typename T>
class vec2 : public vec<T, 2> {
   public:
    using vec<T, 2>::vec;
    T& x() { return this->data[0]; }
    T& y() { return this->data[1]; }
    const T& x() const { return this->data[0]; }
    const T& y() const { return this->data[1]; }
};

template <Vec _Tp>
inline auto operator+(const _Tp& self) {
    return self;
}
template <Vec _Tp>
inline auto operator-(const _Tp& self) {
    _Tp res;
    for (size_t i = 0; i < _Tp::length; i++) {
        res[i] = -self[i];
    }
    return res;
}

template <Vec _Tp1, Vec _Tp2>
    requires(_Tp1::length == _Tp2::length)
inline auto operator+(const _Tp1& self, const _Tp2& other) {
    typename _Tp1::template Self<decltype(typename _Tp1::DataType{} +
                                          typename _Tp2::DataType{})>
        res;
    for (size_t i = 0; i < _Tp1::length; i++) {
        res[i] = self[i] + other[i];
    }
    return res;
}
template <Vec _Tp, class _RTp>
inline auto operator-(const _Tp& self) {
    typename _Tp::template Self<decltype(-typename _Tp::DataType{})> res;
    for (size_t i = 0; i < _Tp::length; i++) {
        res[i] = -self[i];
    }
    return res;
}
template <Vec _Tp1, Vec _Tp2>
    requires(_Tp1::length == _Tp2::length)
inline auto operator-(const _Tp1& self, const _Tp2& other) {
    typename _Tp1::template Self<decltype(typename _Tp1::DataType{} -
                                          typename _Tp2::DataType{})>
        res;
    for (size_t i = 0; i < _Tp1::length; i++) {
        res[i] = self[i] - other[i];
    }
    return res;
}
template <Vec _Tp1, Vec _Tp2>
    requires(_Tp1::length == _Tp2::length)
inline auto operator*(const _Tp1& self, const _Tp2& other) {
    typename _Tp1::template Self<decltype(typename _Tp1::DataType{} *
                                          typename _Tp2::DataType{})>
        res;
    for (size_t i = 0; i < _Tp1::length; i++) {
        res[i] = self[i] * other[i];
    }
    return res;
}
template <Vec _Tp1, Vec _Tp2>
    requires(_Tp1::length == _Tp2::length)
inline auto operator/(const _Tp1& self, const _Tp2& other) {
    typename _Tp1::template Self<decltype(typename _Tp1::DataType{} /
                                          typename _Tp2::DataType{})>
        res;
    for (size_t i = 0; i < _Tp1::length; i++) {
        res[i] = self[i] / other[i];
    }
    return res;
}

template <Vec _Tp1, Vec _Tp2>
    requires(_Tp1::length == _Tp2::length)
inline vec<bool, _Tp1::length> operator>(const _Tp1& self, const _Tp2& other) {
    vec<bool, _Tp1::length> res;
    for (size_t i = 0; i < _Tp1::length; i++) {
        res[i] = self[i] > other[i];
    }
    return res;
}
template <Vec _Tp1, Vec _Tp2>
    requires(_Tp1::length == _Tp2::length)
inline vec<bool, _Tp1::length> operator<(const _Tp1& self, const _Tp2& other) {
    vec<bool, _Tp1::length> res;
    for (size_t i = 0; i < _Tp1::length; i++) {
        res[i] = self[i] < other[i];
    }
    return res;
}
template <Vec _Tp1, Vec _Tp2>
    requires(_Tp1::length == _Tp2::length)
inline vec<bool, _Tp1::length> operator>=(const _Tp1& self, const _Tp2& other) {
    vec<bool, _Tp1::length> res;
    for (size_t i = 0; i < _Tp1::length; i++) {
        res[i] = self[i] >= other[i];
    }
    return res;
}
template <Vec _Tp1, Vec _Tp2>
    requires(_Tp1::length == _Tp2::length)
inline vec<bool, _Tp1::length> operator<=(const _Tp1& self, const _Tp2& other) {
    vec<bool, _Tp1::length> res;
    for (size_t i = 0; i < _Tp1::length; i++) {
        res[i] = self[i] <= other[i];
    }
    return res;
}
template <Vec _Tp1, Vec _Tp2>
    requires(_Tp1::length == _Tp2::length)
inline vec<bool, _Tp1::length> operator==(const _Tp1& self, const _Tp2& other) {
    vec<bool, _Tp1::length> res;
    for (size_t i = 0; i < _Tp1::length; i++) {
        res[i] = self[i] == other[i];
    }
    return res;
}
template <Vec _Tp1, Vec _Tp2>
    requires(_Tp1::length == _Tp2::length)
inline vec<bool, _Tp1::length> operator!=(const _Tp1& self, const _Tp2& other) {
    vec<bool, _Tp1::length> res;
    for (size_t i = 0; i < _Tp1::length; i++) {
        res[i] = self[i] != other[i];
    }
    return res;
}

template <Vec _Tp, class _ItemType>
inline auto operator+(const _Tp& self, const _ItemType& other) {
    typename _Tp::template Self<decltype(typename _Tp::DataType{} +
                                         _ItemType{})>
        res;
    for (size_t i = 0; i < _Tp::length; i++) {
        res[i] = self[i] + other;
    }
    return res;
}
template <Vec _Tp, class _ItemType>
inline auto operator-(const _Tp& self, const _ItemType& other) {
    typename _Tp::template Self<decltype(typename _Tp::DataType{} -
                                         _ItemType{})>
        res;
    for (size_t i = 0; i < _Tp::length; i++) {
        res[i] = self[i] - other;
    }
    return res;
}
template <Vec _Tp, class _ItemType>
inline auto operator*(const _Tp& self, const _ItemType& other) {
    typename _Tp::template Self<decltype(typename _Tp::DataType{} *
                                         _ItemType{})>
        res;
    for (size_t i = 0; i < _Tp::length; i++) {
        res[i] = self[i] * other;
    }
    return res;
}
template <Vec _Tp, class _ItemType>
inline auto operator/(const _Tp& self, const _ItemType& other) {
    typename _Tp::template Self<decltype(typename _Tp::DataType{} /
                                         _ItemType{})>
        res;
    for (size_t i = 0; i < _Tp::length; i++) {
        res[i] = self[i] / other;
    }
    return res;
}

template <Vec _Tp, class _ItemType>
    requires(VecItem<_Tp, _ItemType>)
inline auto operator+(const _ItemType& other, const _Tp& v) {
    typename _Tp::template Self<decltype(_ItemType{} +
                                         (typename _Tp::DataType{}))>
        res;
    for (size_t i = 0; i < _Tp::length; i++) {
        res[i] = other + v[i];
    }
    return res;
}
template <Vec _Tp, class _ItemType>
    requires(VecItem<_Tp, _ItemType>)
inline auto operator-(const _ItemType& other, const _Tp& self) {
    typename _Tp::template Self<decltype(typename _Tp::DataType{} -
                                         _ItemType{})>
        res;
    for (size_t i = 0; i < _Tp::length; i++) {
        res[i] = other - self[i];
    }
    return res;
}

template <Vec _Tp, class _ItemType>
    requires(VecItem<_Tp, _ItemType>)
inline auto operator*(const _ItemType& other, const _Tp& v) {
    typename _Tp::template Self<decltype(_ItemType{} *
                                         typename _Tp::DataType{})>
        res;
    for (size_t i = 0; i < _Tp::length; i++) {
        res[i] = other * v[i];
    }
    return res;
}
template <Vec _Tp, class _ItemType>
    requires(VecItem<_Tp, _ItemType>)
inline auto operator/(const _ItemType& other, const _Tp& v) {
    typename _Tp::template Self<decltype(typename _Tp::DataType{} /
                                         _ItemType{})>
        res;
    for (size_t i = 0; i < _Tp::length; i++) {
        res[i] = other / v[i];
    }
    return res;
}

template <Vec _Tp>
_Tp& operator++(const _Tp& v) {
    for (size_t i = 0; i < _Tp::length; i++) {
        ++v[i];
    }
    return v;
}
template <Vec _Tp>
_Tp& operator--(const _Tp& v) {
    for (size_t i = 0; i < _Tp::length; i++) {
        --v[i];
    }
    return v;
}

template <Vec _Tp>
_Tp operator++(const _Tp& v, int) {
    _Tp res = v;
    for (size_t i = 0; i < _Tp::length; i++) {
        ++res[i];
    }
    return res;
}
template <Vec _Tp>
_Tp operator--(const _Tp& v, int) {
    _Tp res = v;
    for (size_t i = 0; i < _Tp::length; i++) {
        --res[i];
    }
}
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

};  // namespace xcmath
#endif  // VEC_H