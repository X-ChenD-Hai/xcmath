/**
 * @file heapdevice.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2025-07-02
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef XCMATH_HEAPDEVICE_HPP
#define XCMATH_HEAPDEVICE_HPP
#include <cstring>

#include "./device.hpp"
namespace xcmath::comp {

class HeapDevice {
   public:
    using mem_id_t = void*;
    constexpr static const size_t access_grade = 2;
    constexpr static const bool access_by_pointer = 1;
    constexpr static const bool allow_destruct = 1;
    constexpr static const bool random_visits = 1;
    constexpr static const bool sequential_visits = 0;
    template <typename _Tp>
    class RandomAccessIterator {
       private:
        _Tp* ptr;

       public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = _Tp;
        using difference_type = ptrdiff_t;
        using pointer = _Tp*;

        RandomAccessIterator(mem_id_t ptr) : ptr(ptr) {}
        ~RandomAccessIterator() = default;

        _Tp& operator*() const { return *ptr; }
        _Tp* operator->() const { return ptr; }

        RandomAccessIterator& operator++() {
            ++ptr;
            return *this;
        }
        RandomAccessIterator operator++(int) {
            RandomAccessIterator tmp = *this;
            ++ptr;
            return tmp;
        }
        RandomAccessIterator& operator--() {
            --ptr;
            return *this;
        }
        RandomAccessIterator operator--(int) {
            RandomAccessIterator tmp = *this;
            --ptr;
            return tmp;
        }
        RandomAccessIterator& operator+=(difference_type n) {
            ptr += n;
            return *this;
        }
        RandomAccessIterator& operator-=(difference_type n) {
            ptr -= n;
            return *this;
        }
        RandomAccessIterator operator+(difference_type n) const {
            return RandomAccessIterator(ptr + n);
        }
        RandomAccessIterator operator-(difference_type n) const {
            return RandomAccessIterator(ptr - n);
        }
        difference_type operator-(RandomAccessIterator other) const {
            return ptr - other.ptr;
        }
        bool operator==(RandomAccessIterator other) const {
            return ptr == other.ptr;
        }
        bool operator!=(RandomAccessIterator other) const {
            return ptr != other.ptr;
        }
        bool operator<(RandomAccessIterator other) const {
            return ptr < other.ptr;
        }
        bool operator<=(RandomAccessIterator other) const {
            return ptr <= other.ptr;
        }
        bool operator>(RandomAccessIterator other) const {
            return ptr > other.ptr;
        }
        bool operator>=(RandomAccessIterator other) const {
            return ptr >= other.ptr;
        }
    };

    static mem_id_t allocate(size_t size) { return malloc(size); }
    static void deallocate(mem_id_t ptr) { free(ptr); }
    template <CDevice _Tp>
    static void fill(mem_id_t dst, const _Tp val, size_t size) {}
    template <CDevice _Tp>
    static void copy(mem_id_t dst, _Tp::mem_id_t src, size_t size,
                     size_t offset = 0) {
        static_assert(false, "Not implemented for this device");
    }
    static mem_id_t getItemId(mem_id_t ptr, size_t offset = 0) {
        return (static_cast<char*>(ptr) + offset);
    }
    template <class Vtp>
    static Vtp getItemValue(mem_id_t ptr) {
        return *static_cast<Vtp*>(ptr);
    }
    template <typename _Tp>
    static void destruct(mem_id_t ptr, size_t size,
                         std::function<void(_Tp*)> deleter) {
        auto ptr_ = static_cast<_Tp*>(ptr);
        for (size_t i = 0; i < size; i++) deleter(&ptr_[i]);
    }
    template <typename _Tp>
    static _Tp* getItemPointer(mem_id_t ptr) {
        return static_cast<_Tp*>(ptr);
    }
    static void setItem(mem_id_t ptr, void* item, size_t item_size,
                        size_t offset = 0) {
        memcpy(static_cast<char*>(ptr) + offset, item, item_size);
    }
    template <>
    void copy<HeapDevice>(mem_id_t dst, mem_id_t src, size_t size,
                          size_t offset) {
        memcpy(static_cast<char*>(dst) + offset,
               static_cast<char*>(src) + offset, size);
    }
};

}  // namespace xcmath::comp

#endif  // XCMATH_HEAPDEVICE_HPP