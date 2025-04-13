/**
 * @file quaternion.hpp
 * @brief Header file for quaternion class template and related utilities
 * @author XCDH
 * @version 1.0
 * @date 2023-10-05
 */

#ifndef XCMATH_QUATERNION_HPP
#define XCMATH_QUATERNION_HPP

#include <cmath>
#include <type_traits>

#include "./vec.hpp"

namespace xcmath {
template <typename _Tp, size_t _rows, size_t _cols>
class mat;

/**
 * @brief Quaternion class template
 *
 * @tparam T Type of elements in the quaternion
 */
template <typename _Tp>
class quaternion : public vec<_Tp, 4> {
   public:
    /**
     * @brief Type of elements in the vector
     */
    using ItemType = _Tp;

    /**
     * @brief Type of data stored in the vector
     */
    using DataType = VecInfo<ItemType>::DataType;

    /**
     * @brief Alias for the vector type with a different element type
     *
     * @tparam _T Type of elements for the new vector
     */
    template <class _T>
    using Self = quaternion<_T>;

    /**
     * @brief Name of the data type
     */
    constexpr static auto datatype = TypeName<DataType>;

    /**
     * @brief Name of the item type
     */
    constexpr static auto itemtype = TypeName<ItemType>;

    /**
     * @brief Length of the vector
     */
    constexpr static auto length = 4;

    quaternion() = default;
    quaternion(_Tp r, _Tp i, _Tp j, _Tp k) {
        this->r() = r;
        this->j() = j;
        this->i() = i;
        this->k() = k;
    }

    /**
     * @brief Inherit operator[] from base class
     */
    using vec<_Tp, 4>::operator[];

    /**
     * @brief Inherit assignment operator from base class
     */
    using vec<_Tp, 4>::operator=;

    template <typename _OTp>
        requires(std::is_convertible_v<ItemType, _OTp>)
    constexpr inline operator Self<_OTp>() const {
        Self<_OTp> ret;
        ret.r() = (_OTp)r();
        ret.i() = (_OTp)i();
        ret.j() = (_OTp)j();
        ret.k() = (_OTp)k();
        return ret;
    }

    /**
     * @brief Construct a quaternion from a scalar
     *
     * @tparam _Tp Type of the scalar
     * @param r Scalar value
     */
    template <class _T>
        requires std::is_convertible_v<_T, _Tp>
    constexpr quaternion(const _T &r) {
        this->r() = r;
        this->i() = 0;
        this->j() = 0;
        this->k() = 0;
    }

    /**
     * @brief Construct a quaternion from an axis and angle
     *
     * @tparam _Tp Type of elements in the axis vector
     * @param axis Axis of rotation
     * @param angle Angle of rotation
     */
    template <class _T>
        requires std::is_arithmetic_v<_Tp>
    constexpr quaternion(const vec3<_Tp> &axis, const _T &angle) {
        _T half_angle = angle / 2;
        _T s = std::sin(half_angle);
        this->r() = std::cos(half_angle);
        this->i() = axis.x() * s;
        this->j() = axis.y() * s;
        this->k() = axis.z() * s;
    }

    /**
     * @brief Quaternion multiplication operator
     *
     * @param other Quaternion to multiply with
     * @return Resulting quaternion
     */
    constexpr quaternion<_Tp> operator*(const quaternion<_Tp> &other) const {
        quaternion<_Tp> res;
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

    /**
     * @brief Quaternion division operator
     *
     * @param other Quaternion to divide by
     * @return Resulting quaternion
     */
    constexpr quaternion<_Tp> operator/(const quaternion<_Tp> &other) const {
        quaternion<_Tp> res;
        _Tp norm = other.norm();
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

    /**
     * @brief Compute norm of the quaternion
     *
     * @return Norm value
     */
    constexpr _Tp norm() const {
        return r() * r() + i() * i() + j() * j() + k() * k();
    }

    /**
     * @brief Get vector part of the quaternion
     *
     * @return Vector part as vec3<_Tp>
     */
    constexpr vec3<_Tp> v() { return vec3<_Tp>{i(), j(), k()}; }

    /**
     * @brief Compute inverse of the quaternion
     *
     * @return Inverse quaternion
     */
    constexpr quaternion<_Tp> inverse() {
        quaternion<_Tp> res;
        _Tp norm = this->norm();
        res.r() = r() / norm;
        res.i() = -i() / norm;
        res.j() = -j() / norm;
        res.k() = -k() / norm;
        return res;
    }

   public:
    /**
     * @brief Convert quaternion to rotation matrix
     *
     * @return Rotation matrix
     */
    constexpr mat<_Tp, 3, 3> to_mat() const;

    /**
     * @brief Create quaternion from rotation matrix
     *
     * @param mat Rotation matrix
     * @return Quaternion
     */
    static constexpr quaternion<_Tp> from_mat(const mat<_Tp, 3, 3> &mat);

   public:
    /**
     * @brief Get scalar part of the quaternion
     *
     * @return Scalar part
     */
    constexpr inline _Tp &r() { return this->data[3]; }

    /**
     * @brief Get i-component of the quaternion
     *
     * @return i-component
     */
    constexpr inline _Tp &i() { return this->data[0]; }

    /**
     * @brief Get j-component of the quaternion
     *
     * @return j-component
     */
    constexpr inline _Tp &j() { return this->data[1]; }

    /**
     * @brief Get k-component of the quaternion
     *
     * @return k-component
     */
    constexpr inline _Tp &k() { return this->data[2]; }

    /**
     * @brief Get scalar part of the quaternion (const version)
     *
     * @return Scalar part
     */
    constexpr inline const _Tp &r() const { return this->data[3]; }

    /**
     * @brief Get i-component of the quaternion (const version)
     *
     * @return i-component
     */
    constexpr inline const _Tp &i() const { return this->data[0]; }

    /**
     * @brief Get j-component of the quaternion (const version)
     *
     * @return j-component
     */
    constexpr inline const _Tp &j() const { return this->data[1]; }

    /**
     * @brief Get k-component of the quaternion (const version)
     *
     * @return k-component
     */
    constexpr inline const _Tp &k() const { return this->data[2]; }

    /**
     * @brief Quaternion addition operator with scalar on the right
     *
     * @tparam _ItemType Type of elements in the quaternion
     * @param v Quaternion to add
     * @param other Scalar value
     * @return Resulting quaternion
     */
    template <class _ItemType>
        requires(!std::is_same_v<_ItemType, Self<_Tp>>)
    auto operator+(const _ItemType &other) {
        quaternion<decltype(r() + other)> res;
        res.r() = r() + other;
        res.i() = i();
        res.j() = j();
        res.k() = k();
        return res;
    }

    /**
     * @brief Quaternion subtraction operator with scalar on the right
     *
     * @tparam _ItemType Type of elements in the quaternion
     * @param v Quaternion to subtract
     * @param other Scalar value
     * @return Resulting quaternion
     */
    template <class _ItemType>
        requires(!std::is_same_v<_ItemType, Self<_Tp>>)
    auto operator-(const _ItemType &other) {
        quaternion<decltype(r() + other)> res;
        res.r() = r() - other;
        res.i() = i();
        res.j() = j();
        res.k() = k();
        return res;
    }
    template <class _ItemType>
    auto operator-(const Self<_ItemType> &other) {
        Self<decltype(r() + other.r())> res;
        res.r() = r() - other.r();
        res.i() = i() - other.i();
        res.j() = j() - other.j();
        res.k() = k() - other.k();
        return res;
    }
    template <class _ItemType>
    auto operator+(const Self<_ItemType> &other) {
        Self<decltype(r() - other.r())> res;
        res.r() = r() + other.r();
        res.i() = i() + other.i();
        res.j() = j() + other.j();
        res.k() = k() + other.k();
        return res;
    }
};

/**
 * @brief Quaternion addition operator with scalar on the left
 *
 * @tparam _Tp Type of the scalar
 * @tparam _ItemType Type of elements in the quaternion
 * @param other Scalar value
 * @param v Quaternion to add to
 * @return Resulting quaternion
 */
template <class _Tp, class _ItemType>
    requires(!std::is_same_v<_Tp, quaternion<_ItemType>>)
auto operator+(const _Tp &other, const quaternion<_ItemType> &v) {
    quaternion<decltype(_Tp{} + _ItemType{})> res;
    res.r() = other + v.r();
    res.i() = v.i();
    res.j() = v.j();
    res.k() = v.k();
    return res;
}

/**
 * @brief Quaternion subtraction operator with scalar on the left
 *
 * @tparam _Tp Type of the scalar
 * @tparam _ItemType Type of elements in the quaternion
 * @param other Scalar value
 * @param v Quaternion to subtract from
 * @return Resulting quaternion
 */
template <class _Tp, class _ItemType>
    requires(!std::is_same_v<_Tp, quaternion<_ItemType>>)
auto operator-(const _Tp &other, const quaternion<_ItemType> &v) {
    quaternion<decltype(_Tp{} - _ItemType{})> res;
    res.r() = other - v.r();
    res.i() = -v.i();
    res.j() = -v.j();
    res.k() = -v.k();
    return res;
}

/**
 * @brief Convert quaternion to rotation matrix
 *
 * @tparam T Type of elements in the quaternion
 * @return Rotation matrix
 */
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

/**
 * @brief Create quaternion from rotation matrix
 *
 * @tparam T Type of elements in the quaternion
 * @param mat Rotation matrix
 * @return Quaternion
 */
template <typename T>
constexpr quaternion<T> quaternion<T>::from_mat(const mat<T, 3, 3> &mat) {
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
constexpr inline quaternion<int> operator""_qi(unsigned long long i) {
    auto res = quaternion<int>(0);
    res.i() = i;
    return res;
}
constexpr inline quaternion<int> operator""_qj(unsigned long long j) {
    auto res = quaternion<int>(0);
    res.j() = j;
    return res;
}
constexpr inline quaternion<int> operator""_qk(unsigned long long k) {
    auto res = quaternion<int>(0);
    res.k() = k;
    return res;
}

constexpr inline quaternion<float> operator""_qi(long double i) {
    auto res = quaternion<float>(0);
    res.i() = i;
    return res;
}
constexpr inline quaternion<float> operator""_qj(long double j) {
    auto res = quaternion<float>(0);
    res.j() = j;
    return res;
}
constexpr inline quaternion<float> operator""_qk(long double k) {
    auto res = quaternion<float>(0);
    res.k() = k;
    return res;
}

}  // namespace xcmath

#endif  // XCMATH_QUATERNION_HPP