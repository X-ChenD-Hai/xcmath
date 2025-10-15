/**
 * @file vec.hpp
 * @brief N-dimensional mathematical vector implementation with template
 * metaprogramming support
 * @author XCDH
 * @version 2.1
 * @date 2023-10-05
 *
 * Provides a type-safe, dimension-aware vector implementation supporting:
 * - Basic linear algebra operations
 * - Component-wise operations
 * - Template meta-programming for dimension and type checking
 * - Cross/dot products and vector normalization
 * - Swizzling operations and slice views
 */
#pragma once
#ifndef VEC_H
#define VEC_H

/**
 * @brief Compiler-specific type information handling for MSVC
 * @details Provides workarounds for MSVC's type system differences
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
 * @brief Namespace for extended mathematical utilities
 * @details Contains vector implementations, algebraic structures,
 *          and related meta-programming utilities
 */
namespace xcmath {
template <typename _Tp, size_t _length>
    requires(_length > 0 && std::is_default_constructible_v<_Tp>)
class vec;
/**
 * @brief Type requirement concept for vector types
 * @tparam T Type to validate as a vector
 * @note - Must have nested DataType and ItemType typedefs
 *          - Must have static dimension and length constants
 *          - Must support element access via operator[]
 */
template <class T>
concept Vec = requires(T a) {
    typename T::DataType;
    typename T::ItemType;
    std::is_same_v<typename T::template Self<typename T::DataType>, T>;
    T::datatype;
    T::itemtype;
    { T::dim } -> std::same_as<const size_t&>;
    { T::length } -> std::same_as<const size_t&>;
    { a[T::length - 1] } -> std::same_as<typename T::ItemType&>;
};

/**
 * @brief Concept for valid vector component types
 * @tparam vec Vector type to check
 * @tparam _Item Candidate component type
 * Notw:
 * - vec must satisfy Vec concept
 *          - _Item must be convertible to vector's ItemType
 */
template <class vec, class _Item>
concept VecItem = requires {
    requires(Vec<vec>);
    requires(std::convertible_to<typename vec::ItemType, _Item>);
};
/**
 * @brief Metafunction computing total size of vector constructor arguments
 * @tparam Args Variadic argument types (vectors and/or scalars)
 * @return Total number of elements when expanded (recursively counts vector
 * elements)
 */
template <class Arg, class... Args>
constexpr size_t VecConstructPackSize =
    VecConstructPackSize<Arg> + VecConstructPackSize<Args...>;
/**
 * @brief Metafunction computing total size of vector constructor arguments
 *
 * @tparam Arg
 */
template <class Arg>
inline constexpr size_t VecConstructPackSize<Arg> = []() -> size_t {
    if constexpr (Vec<Arg>)
        return Arg::length;
    else
        return 1;
}();
/**
 * @brief
 *
 * @tparam _Tp
 *
 *
 */
template <class _Tp>
struct VecInfo {
#ifdef _MSVC_VER
    static constexpr size_t Dim = []() -> size_t {
        if constexpr (Vec<_Tp>) return VecInfo<_Tp::ItemType>::Dim + 1;
        return 0;
    }();
    static constexpr auto Zero = []() {
        if constexpr (Vec<_Tp>)
            return VecInfo<_Tp::ItemType>::Zero;
        else
            return _Tp{};
    }();
    using DataType = decltype(Zero);
#else

    static constexpr size_t dim = []() -> size_t {
        if constexpr (Vec<_Tp>) return VecInfo<typename _Tp::ItemType>::dim + 1;
        return 0;
    }();

    static constexpr auto Zero = []() {
        if constexpr (Vec<_Tp>)
            return VecInfo<typename _Tp::ItemType>::Zero;
        else
            return _Tp{};
    }();
    using DataType = decltype([]() {
        if constexpr (Vec<_Tp>)
            return VecInfo<typename _Tp::ItemType>::Zero;
        else
            return _Tp{};
    }());

#endif
    template <class _Sl, class... _Sls>
    static constexpr auto SubVecZero = []() constexpr {
        if constexpr (sizeof...(_Sls))
            return int{};
        else
            return std::declval<float>();
    }();
    template <class _Sl, class... _Sls>
    using SubVec = decltype(SubVecZero<_Sl, _Sls...>);
};
/**
 * @brief Metaclassfor constructing a vector from a pack of arguments
 * @tparam T Type of vector components
 * @tparam len Length of the vector
 * @tparam lens Lengths of sub-vectors (if any)
 */
template <class T, size_t len, size_t... lens>
struct __batchHelper {
    /**
     * @brief Type of the vector constructed from the arguments
     *
     */
    using Type = vec<typename __batchHelper<T, lens...>::Type, len>;
};
/**
 * @brief Metaclass for constructing a vector from a pack of arguments
 *
 * @tparam T Type of vector components
 * @tparam len Length of the vector
 */
template <class T, size_t len>
struct __batchHelper<T, len> {
    /**
     * @brief
     *
     */
    using Type = vec<T, len>;
};

/**
 * @brief Metafunction for constructing a vector from a pack of arguments
 *
 * @tparam T
 * @tparam lens
 */
template <class T, size_t... lens>
using batch = __batchHelper<T, lens...>::Type;
/**
 * @brief N-dimensional mathematical vector template
 * @tparam _Tp Arithmetic type of vector components
 * @tparam _length Dimension of the vector (1-4 for swizzle operations)
 * Notw:
 * _Tp must be default constructible and support basic arithmetic
 * operations
 *
 * Provides:
 * - Component-wise operations
 * - Vector space operations (addition, scaling, etc.)
 * - Geometric operations (dot/cross products, normalization)
 * - Type-safe dimensional operations through template metaprogramming
 */
template <typename _Tp, size_t _length>
    requires(_length > 0 && std::is_default_constructible_v<_Tp>)
class vec {
   protected:
    /**
     * @brief Component storage array
     * @details Contiguous memory storage following standard vector layout
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
    using DataType = typename VecInfo<ItemType>::DataType;
    static constexpr size_t dim = VecInfo<ItemType>::dim + 1;

    /**
     * @brief Metafunction for type transformation
     * @tparam _T New component type
     * @returns Vector type with specified component type and same dimension
     */

    template <class __Tp, size_t __len, size_t... __lens>
    struct __subVecHelper {};

    template <size_t __len, size_t... __lens>
    struct __subVecHelper<size_t, __len, __lens...> {
        using Type = vec<typename ItemType::template SubVec<__lens...>, __len>;
    };
    template <size_t __len>
    struct __subVecHelper<size_t, __len> {
        using Type = vec<ItemType, __len>;
    };

    template <size_t __len, size_t... __lens>
    using SubVec = __subVecHelper<size_t, __len, __lens...>::Type;

    // template <size_t __len>
    // using SubVec<__len> = vec<ItemType, __len>;

    template <class _T>
    using Self = vec<_T, _length>;

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
    constexpr static auto length = _length;

    /**
     * @brief Construct a zero-initialized vector
     * Notw:
     * _Tp must be default constructible
     */
    constexpr vec()
        requires(std::is_default_constructible_v<_Tp>)
        : data{_Tp{}} {}

    /**
     * @brief Construct from component values
     * @param arg1 First component value
     * @param args Remaining component values
     * @tparam _Tp1 Type of first component (must be convertible to _Tp)
     * @tparam _T Types of remaining components (must be convertible to _Tp)
     * Notw:
     * All arguments must be convertible to component type _Tp
     * @throws std::out_of_range if too many arguments provided
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
     * @brief Construct from mixed scalars and vectors
     * @param args Component initializers (scalars or vectors to flatten)
     * @tparam _Args Variadic argument types
     * Notw:
     * Total elements from args must exactly match vector length
     *           Each argument must be convertible to _Tp or be a vector of _Tp
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
     * @brief Uniform value constructor
     * @param fill_value Value to initialize all components
     * @tparam T Type of fill value (must be convertible to _Tp)
     */
    template <class T>
        requires(std::is_convertible_v<T, ItemType>)
    constexpr explicit vec(const T& fill_value) {
        for (size_t i = 0; i < length; i++) {
            data[i] = fill_value;
        }
    }

    constexpr vec(const vec<_Tp, _length>& other)
        requires(std::is_trivially_copy_constructible_v<_Tp>)
    = default;

    /**
     * @brief Copy constructor
     * @param other Vector to copy
     * @note Performs deep copy of all components
     */
    constexpr vec(const vec<_Tp, _length>& other) {
        for (size_t i = 0; i < _length; i++) {
            data[i] = other[i];
        }
    }

    constexpr vec(vec<_Tp, _length>&& o)
        requires(std::is_trivially_move_constructible_v<_Tp>)
    = default;
    /**
     * @brief Move constructor
     * @param o Vector to move from
     * @note Component values are moved if _Tp supports move semantics,
     *       otherwise copies are performed
     */
    constexpr vec(vec<_Tp, _length>&& o) {
        for (size_t i = 0; i < _length; i++) {
            data[i] = o[i];
        }
    }

    constexpr vec(const std::initializer_list<ItemType>& list) {
        size_t i = 0;
        for (auto it : list) {
            assert(i < _length);
            data[i++] = it;
        }
    }

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

    constexpr vec<_Tp, _length>& operator=(const vec<_Tp, _length>& other)
        requires(std::is_trivially_copy_assignable_v<_Tp>)
    = default;
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
    constexpr vec<_Tp, _length>& operator=(vec<_Tp, _length>&& other)
        requires(std::is_trivially_move_assignable_v<_Tp>)
    = default;

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
     * @brief qualified operator() for slicing and swizzling
     * @tparam idx Indices of the elements to select (0-3 for swizzling, 0-n for
     * slicing)
     * @return Subvector or scalar value
     */
    template <size_t... idx, class... _Ss>
        requires(sizeof...(_Ss) < dim)
    constexpr SubVec<sizeof...(idx), (_Ss::length, ...)> operator()(
        Slice<idx...>, _Ss... ns) const {
        return {(data[idx](ns...))...};
    }

    /**
     * @brief qualified operator() for slicing and swizzling (const version)
     * @tparam idx Indices of the elements to select (0-3 for swizzling, 0-n for
     * slicing)
     * @return Subvector or scalar value
     */
    template <size_t... idx>
    constexpr vec<ItemType, sizeof...(idx)> operator()(Slice<idx...> s) const {
        return {data[idx]...};
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
     * @brief Compute 3D cross product
     * @param other Right-hand operand vector
     * @return vec<_Tp,3> Resulting perpendicular vector
     * Notw:
     * _length == 3 (enabled via SFINAE)
     * @note Implements the right-hand rule: cross(a, b) = |i j k|
     *                                               |aₓ aᵧ a_z|
     *                                               |bₓ bᵧ b_z|
     */
    constexpr vec<_Tp, _length> cross(const vec<_Tp, _length>& other) const {
        vec<_Tp, _length> res;
        res[0] = data[1] * other[2] - data[2] * other[1];
        res[1] = data[2] * other[0] - data[0] * other[2];
        res[2] = data[0] * other[1] - data[1] * other[0];
        return res;
    }

    /**
     * @brief Compute Euclidean inner product
     * @param other Right-hand operand vector
     * @return _Tp Scalar result of Σ(a_i * b_i)
     * @note For vectors u, v: u·v = |u||v|cosθ
     */
    constexpr _Tp dot(const vec<_Tp, _length>& other) const {
        _Tp res = _Tp{};
        for (size_t i = 0; i < _length; i++) {
            res += data[i] * other[i];
        }
        return res;
    }

    /**
     * @brief Create unit vector in same direction
     * @return vec<_Tp,_length> Scaled vector with magnitude 1
     * @throws std::domain_error if modulus is zero
     * @note Normalization formula: û = u / ||u||
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
     * @brief Calculate Euclidean norm (magnitude)
     * @return _Tp ||v|| = √(Σv_i²)
     * @note Directly computes sqrt(dot(*this))
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
     * @brief Check universal quantification of components
     * @return bool True if all elements evaluate to true
     * Notw:
     * DataType must be contextually convertible to bool
     * @note This is an alias for every()
     * @see every()
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
     * @brief Component-wise additive inverse
     * @return vec<decltype(-_Tp{}),_length> New vector with -v_i components
     * @note Equivalent to vector scaling by -1
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

/**
 * @def __VEC_OP_VEC_ON_EQ_LENGTH
 * @brief Macro generating component-wise vector operations
 * @param op Operator to apply (+, -, *, /, etc.)
 * @note Requires both vectors to have same dimensionality.
 *       Creates new vector with operator applied to each component pair.
 */
#define __VEC_OP_VEC_ON_EQ_LENGTH(op)          \
    template <class _OTp>                      \
        requires(dim == VecInfo<_OTp>::dim)    \
    auto operator op(const _OTp& o) const {    \
        Self<decltype(data[0] op o[0])> res;   \
        for (size_t i = 0; i < _length; i++) { \
            res[i] = data[i] op o[i];          \
        }                                      \
        return res;                            \
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

/**
 * @def __VEC_OP_ITEM_ON_OP_ABLE
 * @brief Macro generating vector-scalar operations
 * @param op Operator to apply (+, -, *, /, etc.)
 * @note Applies operator to each component with scalar
 *       Allows mixed-type operations through decltype deduction
 */
#define __VEC_OP_ITEM_ON_OP_ABLE(op)                                       \
    template <class _OTp>                                                  \
        requires(VecInfo<_OTp>::dim == 0 || dim == VecInfo<_OTp>::dim + 1) \
    inline constexpr auto operator op(const _OTp& o) {                     \
        Self<decltype(data[0] op o)> res;                                  \
        for (size_t i = 0; i < _length; i++) {                             \
            res[i] = data[i] op o;                                         \
        }                                                                  \
        return res;                                                        \
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
        requires(VecInfo<_OTp>::dim == 0 ||                              \
                 (VecInfo<_OTp>::dim == _Tp::dim - 1))                   \
    inline constexpr auto operator op(const _OTp& other, const _Tp& o) { \
        typename _Tp::template Self<decltype(other op o[0])> res;        \
        for (size_t i = 0; i < _Tp::length; i++) res[i] = other op o[i]; \
        return res;                                                      \
    }

__ITEM_OP_VEC_ON_OP_ENABLE(+)
__ITEM_OP_VEC_ON_OP_ENABLE(-)
__ITEM_OP_VEC_ON_OP_ENABLE(*)
__ITEM_OP_VEC_ON_OP_ENABLE(/)
__ITEM_OP_VEC_ON_OP_ENABLE(%)
__ITEM_OP_VEC_ON_OP_ENABLE(&)
__ITEM_OP_VEC_ON_OP_ENABLE(|)
__ITEM_OP_VEC_ON_OP_ENABLE(^) __ITEM_OP_VEC_ON_OP_ENABLE(==)
    __ITEM_OP_VEC_ON_OP_ENABLE(!=) __ITEM_OP_VEC_ON_OP_ENABLE(>)
        __ITEM_OP_VEC_ON_OP_ENABLE(<) __ITEM_OP_VEC_ON_OP_ENABLE(>=)
            __ITEM_OP_VEC_ON_OP_ENABLE(<=)
#undef __ITEM_OP_VEC_ON_OP_ENABLE
}  // namespace xcmath
#endif  // VEC_H
