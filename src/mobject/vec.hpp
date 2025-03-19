/**
 * @file vec.hpp
 * @brief Header file for vector class template and related utilities
 * @author XCDH
 * @version 1.0
 * @date 2023-10-05
 */

#ifndef VEC_H
#define VEC_H

/**
 * @brief Check if the compiler is MSVC
 *
 */
#ifdef _MSVC_VER
#include <vcruntime_typeinfo.h>
#endif

#include <assert.h>

#include <cmath>
#include <concepts>
#include <cstddef>
#include <type_traits>

#include "../utils/compiling.hpp"
#include "./declaration.hpp"

/**
 * @namespace xcmath
 * @brief Namespace for extended C++ math utilities
 */
namespace xcmath {
/**
 * @brief Concept to check if a type is a vector
 *
 * @tparam T Type to check
 */
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

/**
 * @brief Concept to check if a type is a valid item type for a vector
 *
 * @tparam vec Vector type
 * @tparam _Item Item type to check
 */
template <class vec, class _Item>
concept VecItem = requires {
    Vec<vec>;
    std::convertible_to<typename vec::ItemType, _Item>;
};

/**
 * @brief Compute the size of a pack of vector construct arguments
 *
 * @tparam Args Types of arguments
 */
template <class... Args>
constexpr size_t VecConstructPackSize = ((([]<class Arg = Args>() {
                                             if constexpr (Vec<Arg>) {
                                                 return Arg::length;
                                             } else {
                                                 return 1;
                                             }
                                         })()) +
                                         ...);

template <>
inline constexpr size_t VecConstructPackSize<> = 0;

/**
 * @brief Get the zero item for a type
 *
 * @tparam _Tp Type to get zero item for
 * @return Item of type _Tp initialized to zero
 */
template <class _Tp>
static constexpr auto get_item_zero() {
    if constexpr (Vec<_Tp>) {
        return get_item_zero<typename _Tp::ItemType>();
    } else {
        return _Tp{};
    }
}

/**
 * @brief Vector class template
 *
 * @tparam _Tp Type of elements in the vector
 * @tparam _length Length of the vector
 */
template <typename _Tp, size_t _length>
    requires(_length > 0 && std::is_default_constructible_v<_Tp>)
class vec {
   protected:
    /**
     * @brief Data array of the vector
     */
    _Tp data[_length];

   public:
    /**
     * @brief Type of elements in the vector
     */
    using ItemType = _Tp;

    /**
     * @brief Type of data stored in the vector
     */
    using DataType = decltype(get_item_zero<ItemType>());

    /**
     * @brief Alias for the vector type with a different element type
     *
     * @tparam _T Type of elements for the new vector
     */
    template <class _T>
    using Self = vec<_T, _length>;

    /**
     * @brief Name of the data type
     */
    constexpr static auto datatype = get_type_name<DataType>();

    /**
     * @brief Name of the item type
     */
    constexpr static auto itemtype = get_type_name<ItemType>();

    /**
     * @brief Length of the vector
     */
    constexpr static auto length = _length;

    /**
     * @brief Get pointer to the beginning of the data array
     *
     * @return Pointer to the first element
     */
    constexpr const _Tp* begin() const { return data; }

    /**
     * @brief Get pointer to the end of the data array
     *
     * @return Pointer past the last element
     */
    constexpr const _Tp* end() const { return data + length; }

    /**
     * @brief Access element at specified index
     *
     * @param index Index of the element
     * @return Reference to the element
     */
    constexpr _Tp& operator[](size_t index) { return data[index]; }

    /**
     * @brief Access element at specified index (const version)
     *
     * @param index Index of the element
     * @return Const reference to the element
     */
    constexpr const _Tp& operator[](size_t index) const {
        assert(index < length);
        return data[index];
    }

    /**
     * @brief Default constructor
     */
    constexpr vec()
        requires(std::is_default_constructible_v<_Tp>)
        : data{_Tp{}} {}

    /**
     * @brief Constructor with initializer list
     *
     * @param arg1 First argument
     * @param args Remaining arguments
     */
    template <class _Tp1, class... _T>
        requires(std::is_convertible_v<_Tp1, _Tp> &&
                 (std::is_convertible_v<_T, _Tp> && ...))
    constexpr vec(const _Tp1& arg1, const _T&... args) {
        size_t i = 0;
        data[0] = arg1;
        ((data[++i] = args), ...);
    }

    /**
     * @brief Constructor with multiple arguments
     *
     * @param args Arguments to initialize the vector
     */
    template <typename... _Args>
        requires((VecConstructPackSize<_Args...> <= _length &&
                  VecConstructPackSize<_Args...> > 1) &&
                 ((VecItem<_Args, ItemType> ||
                   std::is_convertible_v<_Args, ItemType>) &&
                  ...))
    constexpr explicit vec(const _Args&... args) {
        size_t n = 0;
        (([&]<class _Arg>(_Arg _arg) {
             if constexpr (std::is_convertible_v<_Arg, ItemType>)
                 data[n++] = _arg;
             else {
                 for (auto& i : _arg) data[n++] = i;
             }
         }(args)),
         ...);
    }

    /**
     * @brief Constructor with fill value
     *
     * @param fill_value Value to fill the vector with
     */
    template <class T>
        requires(std::is_convertible_v<T, ItemType>)
    constexpr explicit vec(const T& fill_value) {
        for (size_t i = 0; i < length; i++) {
            data[i] = fill_value;
        }
    }

    /**
     * @brief Copy constructor
     *
     * @param other Vector to copy from
     */
    constexpr vec(const vec<_Tp, _length>& other) {
        for (size_t i = 0; i < _length; i++) {
            data[i] = other[i];
        }
    }

    /**
     * @brief Copy assignment operator
     *
     * @param o Vector to copy from
     * @return Reference to this vector
     */
    constexpr vec<_Tp, _length>& operator=(const vec<_Tp, _length>& o) {
        for (size_t i = 0; i < _length; i++) {
            data[i] = o[i];
        }
        return *this;
    }

    /**
     * @brief Move assignment operator
     *
     * @param o Vector to move from
     * @return Reference to this vector
     */
    constexpr vec<_Tp, _length>& operator=(vec<_Tp, _length>&& o) {
        for (size_t i = 0; i < _length; i++) {
            data[i] = o[i];
        }
        return *this;
    }

    /**
     * @brief Move constructor
     *
     * @param o Vector to move from
     */
    constexpr vec(vec<_Tp, _length>&& o) {
        for (size_t i = 0; i < _length; i++) {
            data[i] = o[i];
        }
    }

    /**
     * @brief Slice the vector starting at specified position
     *
     * @tparam _pos Starting position
     * @tparam __length Length of the slice
     * @return Sliced vector
     */
    template <size_t _pos, size_t __length>
        requires(_pos + __length <= _length)
    const vec<_Tp, __length>& slice() const {
        return *(vec<_Tp, __length>*)(data + _pos);
    }

    /**
     * @brief Slice the vector from the beginning
     *
     * @tparam __length Length of the slice
     * @return Sliced vector
     */
    template <size_t __length>
        requires(__length <= _length)
    const vec<_Tp, __length>& slice() const {
        return *(vec<_Tp, __length>*)(data);
    }

    /**
     * @brief Slice the vector starting at specified position (non-const
     * version)
     *
     * @tparam _pos Starting position
     * @tparam __length Length of the slice
     * @return Sliced vector
     */
    template <size_t _pos, size_t __length>
        requires(_pos + __length <= _length)
    vec<_Tp, __length>& slice() {
        return *(vec<_Tp, __length>*)(data + _pos);
    }

    /**
     * @brief Slice the vector from the beginning (non-const version)
     *
     * @tparam __length Length of the slice
     * @return Sliced vector
     */
    template <size_t __length = _length>
        requires(__length <= _length)
    vec<_Tp, __length>& slice() {
        return *(vec<_Tp, __length>*)(data);
    }

    /**
     * @brief Get the item at index 0
     *
     * @return Reference to the item
     */
    constexpr _Tp& x()
        requires(_length < 5)
    {
        return this->data[0];
    }

    /**
     * @brief Get the item at index 1
     *
     * @return Reference to the item
     */
    constexpr _Tp& y()
        requires(_length < 5 && _length > 1)
    {
        return this->data[1];
    }

    /**
     * @brief Get the item at index 2
     *
     * @return Reference to the item
     */
    constexpr _Tp& z()
        requires(_length < 5 && _length > 2)
    {
        return this->data[2];
    }

    /**
     * @brief Get the item at index 3
     *
     * @return Reference to the item
     */
    constexpr _Tp& w()
        requires(_length < 5 && _length > 3)
    {
        return this->data[3];
    }

    /**
     * @brief Get the item at index 0 (const version)
     *
     * @return Const reference to the item
     */
    constexpr const _Tp& x() const
        requires(_length < 5)
    {
        return this->data[0];
    }

    /**
     * @brief Get the item at index 1 (const version)
     *
     * @return Const reference to the item
     */
    constexpr const _Tp& y() const
        requires(_length < 5 && _length > 1)
    {
        return this->data[1];
    }

    /**
     * @brief Get the item at index 2 (const version)
     *
     * @return Const reference to the item
     */
    constexpr const _Tp& z() const
        requires(_length < 5 && _length > 2)
    {
        return this->data[2];
    }

    /**
     * @brief Get the item at index 3 (const version)
     *
     * @return Const reference to the item
     */
    constexpr const _Tp& w() const
        requires(_length < 5 && _length > 3)
    {
        return this->data[3];
    }

    /**
     * @brief Compute cross product with another vector
     *
     * @param other Vector to compute cross product with
     * @return Resulting vector
     */
    constexpr vec<_Tp, _length> cross(const vec<_Tp, _length>& other) const {
        vec<_Tp, _length> res;
        res[0] = data[1] * other[2] - data[2] * other[1];
        res[1] = data[2] * other[0] - data[0] * other[2];
        res[2] = data[0] * other[1] - data[1] * other[0];
        return res;
    }

    /**
     * @brief Compute dot product with another vector
     *
     * @param other Vector to compute dot product with
     * @return Resulting value
     */
    constexpr _Tp dot(const vec<_Tp, _length>& other) const {
        _Tp res = _Tp{};
        for (size_t i = 0; i < _length; i++) {
            res += data[i] * other[i];
        }
        return res;
    }

    /**
     * @brief Normalize the vector
     *
     * @return Normalized vector
     */
    constexpr vec<_Tp, _length> normalize() const {
        vec<_Tp, _length> res;
        auto disten = distance({});
        for (size_t i = 0; i < _length; i++) {
            res[i] = data[i] / disten;
        }
        return res;
    }

    /**
     * @brief Compute distance to another vector
     *
     * @param other Vector to compute distance to
     * @return Distance value
     */
    constexpr _Tp distance(const vec<_Tp, _length>& other) const {
        _Tp res = _Tp{};
        for (size_t i = 0; i < _length; i++) {
            res += (data[i] - other[i]) * (data[i] - other[i]);
        }
        return std::sqrt(res);
    }

    /**
     * @brief Compute modulus of the vector
     *
     * @return Modulus value
     */
    constexpr _Tp mod() const {
        _Tp res = _Tp{};
        for (size_t i = 0; i < _length; i++) {
            res += data[i] * data[i];
        }
        return sqrt(res);
    }

    /**
     * @brief Compute angle with another vector
     *
     * @param other Vector to compute angle with
     * @return Angle value
     */
    constexpr _Tp angle(const vec<_Tp, _length>& other) const {
        _Tp cos_theta = dot(other) / (mod() * other.mod());
        return std::acos(cos_theta);
    }

    /**
     * @brief Check if any element satisfies a condition
     *
     * @return True if any element satisfies the condition, false otherwise
     */
    constexpr bool any() const
        requires(std::is_convertible_v<DataType, bool>)
    {
        if constexpr (std::is_convertible_v<ItemType, bool>) {
            for (size_t i = 0; i < _length; i++)
                if (data[i]) {
                    return true;
                }
            return false;
        } else if constexpr (Vec<ItemType>) {
            for (size_t i = 0; i < _length; i++) {
                if (data[i].any()) {
                    return true;
                }
            }
            return false;
        }
    }

    /**
     * @brief Check if all elements satisfy a condition
     *
     * @return True if all elements satisfy the condition, false otherwise
     */
    constexpr bool every() const
        requires(std::is_convertible_v<DataType, bool>)
    {
        if constexpr (std::is_convertible_v<ItemType, bool>) {
            for (size_t i = 0; i < _length; i++)
                if (!data[i]) {
                    return false;
                }
            return true;
        } else if constexpr (Vec<ItemType>) {
            for (size_t i = 0; i < _length; i++) {
                if (!data[i].every()) {
                    return false;
                }
            }
            return true;
        }
    }

    /**
     * @brief Check if all elements satisfy a condition (alias for every())
     *
     * @return True if all elements satisfy the condition, false otherwise
     */
    constexpr inline bool all() const
        requires(std::is_convertible_v<DataType, bool>)
    {
        return every();
    }

    template <typename _OTp>
        requires(std::is_convertible_v<ItemType, _OTp>)
    constexpr inline operator Self<_OTp>() const {
        Self<_OTp> ret;
        for (size_t i = 0; i < _length; i++)
            ret[i] = static_cast<_OTp>(data(i));
        return ret;
    }

    /**
     * @brief Unary negation operator
     *
     * @return Negated vector
     */
    auto operator-() const {
        Self<decltype(-data[0])> res;
        for (size_t i = 0; i < _length; i++) {
            res[i] = -data[i];
        }
        return res;
    }

    /**
     * @brief Unary plus operator
     *
     * @return Vector with elements unchanged
     */
    auto operator+() const {
        Self<decltype(+data[0])> res;
        for (size_t i = 0; i < _length; i++) {
            res[i] = +data[i];
        }
        return res;
    }

    /**
     * @brief Pre-decrement operator
     *
     * @return Copy of the vector before decrement
     */
    auto operator--() {
        auto tmp = *this;
        for (size_t i = 0; i < _length; i++) {
            data[i]--;
        }
        return tmp;
    }

    /**
     * @brief Post-decrement operator
     *
     * @return Reference to the decremented vector
     */
    auto& operator--(int) {
        for (size_t i = 0; i < _length; i++) {
            --data[i];
        }
        return *this;
    }

    /**
     * @brief Pre-increment operator
     *
     * @return Copy of the vector before increment
     */
    auto operator++() {
        auto tmp = *this;
        for (size_t i = 0; i < _length; i++) {
            data[i]++;
        }
        return tmp;
    }

    /**
     * @brief Post-increment operator
     *
     * @return Reference to the incremented vector
     */
    auto& operator++(int) {
        for (size_t i = 0; i < _length; i++) {
            --data[i];
        }
        return *this;
    }

#define __VEC_OP_VEC_ON_EQ_LENGTH(op)             \
    template <class _OTp>                         \
    auto operator op(const Self<_OTp>& o) const { \
        Self<decltype(data[0] op o.data[0])> res; \
        for (size_t i = 0; i < _length; i++) {    \
            res[i] = data[i] op o.data[i];        \
        }                                         \
        return res;                               \
    }
    __VEC_OP_VEC_ON_EQ_LENGTH(+)
    __VEC_OP_VEC_ON_EQ_LENGTH(-)
    __VEC_OP_VEC_ON_EQ_LENGTH(*)
    __VEC_OP_VEC_ON_EQ_LENGTH(/)
    __VEC_OP_VEC_ON_EQ_LENGTH(%)
    __VEC_OP_VEC_ON_EQ_LENGTH(&)
    __VEC_OP_VEC_ON_EQ_LENGTH(|)
    __VEC_OP_VEC_ON_EQ_LENGTH(^)
    __VEC_OP_VEC_ON_EQ_LENGTH(==)
    __VEC_OP_VEC_ON_EQ_LENGTH(!=)
    __VEC_OP_VEC_ON_EQ_LENGTH(>)
    __VEC_OP_VEC_ON_EQ_LENGTH(<)
    __VEC_OP_VEC_ON_EQ_LENGTH(>=)
    __VEC_OP_VEC_ON_EQ_LENGTH(<=)
#undef __VEC_OP_VEC_ON_EQ_LENGTH

#define __VEC_OP_ITEM_ON_OP_ABLE(op)                   \
    template <class _OTp>                              \
        requires(!std::is_same_v<Self<_Tp>, _OTp>)     \
    inline constexpr auto operator op(const _OTp& o) { \
        Self<decltype(data[0] op o)> res;              \
        for (size_t i = 0; i < _length; i++) {         \
            res[i] = data[i] op o;                     \
        }                                              \
        return res;                                    \
    }
    __VEC_OP_ITEM_ON_OP_ABLE(+)
    __VEC_OP_ITEM_ON_OP_ABLE(-)
    __VEC_OP_ITEM_ON_OP_ABLE(*)
    __VEC_OP_ITEM_ON_OP_ABLE(/)
    __VEC_OP_ITEM_ON_OP_ABLE(%)
    __VEC_OP_ITEM_ON_OP_ABLE(&)
    __VEC_OP_ITEM_ON_OP_ABLE(|)
    __VEC_OP_ITEM_ON_OP_ABLE(^)
    __VEC_OP_ITEM_ON_OP_ABLE(==)
    __VEC_OP_ITEM_ON_OP_ABLE(!=)
    __VEC_OP_ITEM_ON_OP_ABLE(>)
    __VEC_OP_ITEM_ON_OP_ABLE(<)
    __VEC_OP_ITEM_ON_OP_ABLE(>=)
    __VEC_OP_ITEM_ON_OP_ABLE(<=)
#undef __VEC_OP_ITEM_ON_OP_ABLE
};

#define __ITEM_OP_VEC_ON_OP_ENABLE(op)                                   \
    template <class _OTp, Vec _Tp>                                       \
        requires(!std::is_same_v<_Tp, _OTp>)                             \
    inline constexpr auto operator op(const _OTp& other, const _Tp& o) { \
        typename _Tp::template Self<decltype(other op o[0])> res;        \
        for (size_t i = 0; i < _Tp::length; i++) res[i] = other[i] + o;  \
        return res;                                                      \
    }
__ITEM_OP_VEC_ON_OP_ENABLE(+)
__ITEM_OP_VEC_ON_OP_ENABLE(-)
__ITEM_OP_VEC_ON_OP_ENABLE(*)
__ITEM_OP_VEC_ON_OP_ENABLE(/)
__ITEM_OP_VEC_ON_OP_ENABLE(%)
__ITEM_OP_VEC_ON_OP_ENABLE(&)
__ITEM_OP_VEC_ON_OP_ENABLE(|)
__ITEM_OP_VEC_ON_OP_ENABLE(^)
__ITEM_OP_VEC_ON_OP_ENABLE(==)
__ITEM_OP_VEC_ON_OP_ENABLE(!=)
__ITEM_OP_VEC_ON_OP_ENABLE(>)
__ITEM_OP_VEC_ON_OP_ENABLE(<)
__ITEM_OP_VEC_ON_OP_ENABLE(>=)
__ITEM_OP_VEC_ON_OP_ENABLE(<=)
#undef __ITEM_OP_VEC_ON_OP_ENABLE
}  // namespace xcmath
#endif  // VEC_H