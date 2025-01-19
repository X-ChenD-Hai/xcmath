// quaternion.hpp
#ifndef XCMATH_QUATERNION_HPP
#define XCMATH_QUATERNION_HPP
#include <type_traits>
#include <cmath>
#include "./vec.hpp"

namespace xcmath {
template <typename _Tp, size_t _rows, size_t _cols>
class mat;
template <typename T>
class quaternion : public vec<T, 4> {
   public:
    using vec<T, 4>::vec;
    using vec<T, 4>::operator[];
    using vec<T, 4>::operator=;
    template <class _T>
    using Self = quaternion<_T>;

    template <class _Tp>
        requires std::is_convertible_v<_Tp, T>
    constexpr quaternion(const _Tp &r) {
        this->data[0] = r;
        this->data[1] = 0;
        this->data[2] = 0;
        this->data[3] = 0;
    }
    template <class _Tp>
        requires std::is_arithmetic_v<_Tp>
    constexpr quaternion(const vec3<_Tp> &axis, const T &angle) {
        T half_angle = angle / 2;
        T s = std::sin(half_angle);
        this->data[0] = std::cos(half_angle);
        this->data[1] = axis.x() * s;
        this->data[2] = axis.y() * s;
        this->data[3] = axis.z() * s;
    }
    constexpr quaternion<T> operator*(const quaternion<T> &other) {
        quaternion<T> res;
        res.r() = r() * other.r() - i() * other.i() - j() * other.j() -
                  k() * other.k();
        res.i() = r() * other.i() + i() * other.r() + j() * other.k() -
                  k() * other.j();
        res.j() = r() * other.j() - i() * other.k() + j() * other.r() +
                  k() * other.i();
        res.k() = r() * other.k() + i() * other.j() - j() * other.i() +
                  k() * other.r();
        return res;
    }
    constexpr quaternion<T> operator/(const quaternion<T> &other) {
        quaternion<T> res;
        T norm = other.norm();
        res.r() = (r() * other.r() + i() * other.i() + j() * other.j() +
                   k() * other.k()) /
                  norm;
        res.i() = (r() * other.i() - i() * other.r() - j() * other.k() +
                   k() * other.j()) /
                  norm;
        res.j() = (r() * other.j() + i() * other.k() - j() * other.r() -
                   k() * other.i()) /
                  norm;
        res.k() = (r() * other.k() - i() * other.j() + j() * other.i() -
                   k() * other.r()) /
                  norm;
        return res;
    }
    constexpr T norm() { return r() * r() + i() * i() + j() * j() + k() * k(); }
    constexpr vec3<T> v() { return vec3<T>{i(), j(), k()}; }

    constexpr quaternion<T> inverse() {
        quaternion<T> res;
        T norm = this->norm();
        res.r() = r() / norm;
        res.i() = -i() / norm;
        res.j() = -j() / norm;
        res.k() = -k() / norm;
        return res;
    }

   public:
    constexpr mat<T, 3, 3> to_mat() const;
    static constexpr quaternion<T> from_mat(const mat<T, 3, 3>& mat);

   public:
    constexpr inline T &r() { return this->data[0]; }
    constexpr inline T &i() { return this->data[1]; }
    constexpr inline T &j() { return this->data[2]; }
    constexpr inline T &k() { return this->data[3]; }
    constexpr inline const T &r() const { return this->data[0]; }
    constexpr inline const T &i() const { return this->data[1]; }
    constexpr inline const T &j() const { return this->data[2]; }
    constexpr inline const T &k() const { return this->data[3]; }
};
template <class _Tp, class _ItemType>
auto operator+(const _Tp &other, const quaternion<_ItemType> &v) {
    quaternion<decltype(_Tp{} + _ItemType{})> res;
    res.r() = other + v.r();
    res.i() = v.i();
    res.j() = v.j();
    res.k() = v.k();
    return res;
}
template <class _Tp, class _ItemType>
auto operator+(const quaternion<_ItemType> &v, const _Tp &other) {
    quaternion<decltype(_Tp{} + _ItemType{})> res;
    res.r() = v.r() + other;
    res.i() = v.i();
    res.j() = v.j();
    res.k() = v.k();
    return res;
}
template <class _Tp, class _ItemType>
auto operator-(const _Tp &other, const quaternion<_ItemType> &v) {
    quaternion<decltype(_Tp{} - _ItemType{})> res;
    res.r() = other - v.r();
    res.i() = -v.i();
    res.j() = -v.j();
    res.k() = -v.k();
    return res;
}
template <class _Tp, class _ItemType>
auto operator-(const quaternion<_ItemType> &v, const _Tp &other) {
    quaternion<decltype(_Tp{} - _ItemType{})> res;
    res.r() = v.r() - other;
    res.i() = v.i();
    res.j() = v.j();
    res.k() = v.k();
    return res;
}

template <typename T>
constexpr mat<T, 3, 3> quaternion<T>::to_mat() const {
    T one{};
    ++one;
    return mat<T, 3, 3>{
        vec<T, 3>{one - 2 * j() * j() - 2 * k() * k(),
                  2 * i() * j() - 2 * r() * k(), 2 * r() * j() + 2 * i() * k()},
        vec<T, 3>{2 * i() * j() + 2 * r() * k(),
                  one - 2 * i() * i() - 2 * k() * k(),
                  2 * j() * k() - 2 * r() * i()},
        vec<T, 3>{2 * r() * j() - 2 * i() * k(), 2 * j() * k() + 2 * r() * i(),
                  one - 2 * i() * i() - 2 * j() * j()},
    };
}

template <typename T>
constexpr quaternion<T> quaternion<T>::from_mat(const mat<T, 3, 3>& mat) {
    quaternion<T> res;
    T tr = mat[0][0] + mat[1][1] + mat[2][2];
    if (tr > 0) {
        T S = std::sqrt(tr + 1) * 2;  // S=4*qw
        res.r() = 0.25 * S;
        res.i() = (mat[2][1] - mat[1][2]) / S;
        res.j() = (mat[0][2] - mat[2][0]) / S;
        res.k() = (mat[1][0] - mat[0][1]) / S;
    } else if ((mat[0][0] > mat[1][1]) && (mat[0][0] > mat[2][2])) {
        T S = std::sqrt(1.0 + mat[0][0] - mat[1][1] - mat[2][2]) * 2;  // S=4*qx
        res.r() = (mat[2][1] - mat[1][2]) / S;
        res.i() = 0.25 * S;
        res.j() = (mat[0][1] + mat[1][0]) / S;
        res.k() = (mat[0][2] + mat[2][0]) / S;
    } else if (mat[1][1] > mat[2][2]) {
        T S = std::sqrt(1.0 + mat[1][1] - mat[0][0] - mat[2][2]) * 2;  // S=4*qy
        res.r() = (mat[0][2] - mat[2][0]) / S;
        res.i() = (mat[0][1] + mat[1][0]) / S;
        res.j() = 0.25 * S;
        res.k() = (mat[1][2] + mat[2][1]) / S;
    } else {
        T S = std::sqrt(1.0 + mat[2][2] - mat[0][0] - mat[1][1]) * 2;  // S=4*qz
        res.r() = (mat[1][0] - mat[0][1]) / S;
        res.i() = (mat[0][2] + mat[2][0]) / S;
        res.j() = (mat[1][2] + mat[2][1]) / S;
        res.k() = 0.25 * S;
    }
    return res;
}

}  // namespace xcmath

#endif  // XCMATH_QUATERNION_HPP