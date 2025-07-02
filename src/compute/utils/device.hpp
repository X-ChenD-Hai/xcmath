/**
 * @file device.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2025-07-02
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef XCMATH_DEVICE_HPP
#define XCMATH_DEVICE_HPP
#include <cstddef>
#include <functional>
namespace xcmath::comp {
template <typename _Tp>
struct __CDeviceHelper {
    using mem_id_t = typename _Tp::mem_id_t;
    constexpr static const size_t access_grade = 0;
};
template <typename _Tp>
concept CDevice =
    requires(size_t size, typename _Tp::mem_id_t src,
             typename _Tp::mem_id_t dst, size_t offset, class _OTp) {
        requires(_Tp::access_grade == 0) || requires {
            typename _Tp::mem_id_t;
            { _Tp::access_grade } -> std::same_as<const size_t&>;
            { _Tp::access_by_pointer } -> std::same_as<const bool&>;
            { _Tp::allow_destruct } -> std::same_as<const bool&>;
            requires(_Tp::access_grade < 1) || requires {
                { _Tp::allocate(size) } -> std::same_as<typename _Tp::mem_id_t>;
                _Tp::deallocate(dst);
                _Tp::template copy<__CDeviceHelper<_Tp>>(
                    dst, typename _Tp::mem_id_t{}, size, offset);
            };
            requires(_Tp::access_grade < 2) || requires {
                {
                    _Tp::getItemId(dst, offset)
                } -> std::same_as<typename _Tp::mem_id_t>;
                {
                    _Tp::template getItemValue<_OTp>
                } -> std::same_as<_OTp (&)(typename _Tp::mem_id_t)>;
                {
                    _Tp::setItem
                } -> std::same_as<void (&)(typename _Tp::mem_id_t, void*,
                                           size_t, size_t)>;
            };
            requires(!_Tp::access_by_pointer) || requires {
                {
                    _Tp::template getItemPointer<_OTp>(
                        std::declval<typename _Tp::mem_id_t>())
                } -> std::same_as<_OTp*>;
            };
            requires(!_Tp::allow_destruct) || requires {
                {
                    _Tp::template destruct<_OTp>
                } -> std::same_as<void (&)(typename _Tp::mem_id_t, size_t,
                                           std::function<void(_OTp*)>)>;
            };
            requires(!_Tp::random_visits) || requires {
                typename _Tp::template RandomAccessIterator<_OTp>;
            };
        };
    };

}  // namespace xcmath::comp
#endif  // XCMATH_DEVICE_HPP