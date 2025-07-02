/**
 * @file allocator.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2025-07-02
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef XCMATH_ALLOCATOR_HPP
#define XCMATH_ALLOCATOR_HPP
#include "./device.hpp"
namespace xcmath::comp {
class HeapDevice;
template <typename _Tp, size_t _Count = 1, CDevice _Device = HeapDevice>
class Allocator {
   public:
    using value_type = _Tp;
    constexpr static size_t size = _Count;
    _Device::mem_id_t __data{};
    Allocator() {
        if constexpr (_Device::access_grade) {
            __data = _Device::allocate(_Count * sizeof(_Tp));
            if constexpr (_Device::access_by_pointer)
                new (_Device::template getItemPointer<void>(__data)) _Tp[size];
            else {
                if constexpr (_Count * sizeof(_Tp) < 1024 * 1024) {
                    auto data = std::array<_Tp, _Count>{};
                    _Device::template copy<HeapDevice>(
                        __data, (void*)data.data(), _Count * sizeof(_Tp), 0);
                } else {
                    auto data = std::vector<_Tp>(_Count);
                    _Device::template copy<HeapDevice>(
                        __data, (void*)data.data(), _Count * sizeof(_Tp), 0);
                }
            }
        }
    }
    ~Allocator() {
        if constexpr (_Device::access_grade) {
            if constexpr (_Device::allow_destruct &&
                          !std::is_trivially_destructible_v<value_type>)
                _Device::template destruct<value_type>(
                    __data, _Count, [](value_type* p) { p->~value_type(); });
            _Device::deallocate(__data);
        }
    }
    bool isVaild() const { return (__data != typename _Device::mem_id_t{}); }
    _Tp& operator[](size_t i)
        requires(_Device::access_grade >= 2 && _Device::access_by_pointer)
    {
        return *_Device::template getItemPointer<value_type>(
            (_Device::getItemId(__data, i * sizeof(_Tp))));
    }
    _Tp& operator[](size_t i) const
        requires(_Device::access_grade >= 2 && _Device::access_by_pointer)
    {
        return *_Device::template getItemPointer<value_type>(
            _Device::getItemId(__data, i * sizeof(_Tp)));
    }
};
}  // namespace xcmath::comp
#endif  // XCMATH_ALLOCATOR_HPP