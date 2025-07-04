
#include <gtest/gtest.h>

// #include <compute/utils/allocator.hpp>
// #include <compute/utils/device.hpp>
// #include <compute/utils/heapdevice.hpp>
#include <compute/utils/tvector.hpp>
#include <cstddef>
// using namespace xcmath::comp;
using namespace xc;

class CustomType1 {
    std::string s;

   public:
    CustomType1(const std::string& s) : s(s) {
        std::cout << "CustomType1: " << this << " " << s
                  << " constructor called" << std::endl;
    }
    CustomType1() {
        std::cout << "CustomType1 " << this << " default constructor called"
                  << std::endl;
    }
    ~CustomType1() {
        std::cout << "CustomType1: " << this << " " << s << " destructor called"
                  << std::endl;
    }
};
class CustomType {
    std::string s;
    CustomType1 t{"sub"};

   public:
    CustomType(const std::string& s) : s(s) {
        std::cout << "CustomType: " << this << " " << s << " constructor called"
                  << std::endl;
    }
    CustomType() {
        std::cout << "CustomType " << this << " default constructor called"
                  << std::endl;
    }
    ~CustomType() {
        std::cout << "CustomType: " << this << " " << s << " destructor called"
                  << std::endl;
    }
};
TEST(MemoryPool, Basic) {}

namespace DeviceTags {
class Singleton;
class RandomAccess;
class SequentialAccess;
class AllowNonTrivialVariables;
}  // namespace DeviceTags

template <class _Device>
concept CDevice = requires(_Device* device) {
    TVector<typename _Device::device_tags>;
    typename _Device::memory_id_t;
    {
        device->allocate(std::declval<size_t>())
    } -> std::same_as<typename _Device::memory_id_t>;
    device->deallocate(std::declval<typename _Device::memory_id_t>());
};

template <class _DTp, size_t _Count, CDevice _Device>
class MetaAllocator {
    template <class, size_t, CDevice, bool>
    friend class Allocator;

   private:
    _Device::memory_id_t __memory_id{};
    MetaAllocator(_Device::memory_id_t memory_id) : __memory_id(memory_id){};

   public:
    constexpr static size_t size = _Count;
};
template <class _DTp, size_t _Count, CDevice _Device,
          bool T = _Device::device_tags::template has<DeviceTags::Singleton>>
class Allocator;

template <class _DTp, size_t _Count, CDevice _Device>
class Allocator<_DTp, _Count, _Device, true>
    : public MetaAllocator<_DTp, _Count, _Device> {
    using MetaAllocator = MetaAllocator<_DTp, _Count, _Device>;

   public:
    Allocator() : MetaAllocator(_Device::allocate(sizeof(_DTp) * _Count)) {}
};
template <class _DTp, size_t _Count, CDevice _Device>
class Allocator<_DTp, _Count, _Device, false>
    : public MetaAllocator<_DTp, _Count, _Device> {
   private:
    using MetaAllocator = MetaAllocator<_DTp, _Count, _Device>;
    _Device* __device{nullptr};

   public:
    constexpr static size_t size = _Count;
    Allocator(_Device* device)
        : MetaAllocator(device->allocate(sizeof(_DTp) * _Count)),
          __device(device) {}
};
class HeapDevice {
   public:
    using device_tags = tvector<DeviceTags::Singleton>;
    using memory_id_t = char*;
    static memory_id_t allocate(size_t size) {
        return static_cast<memory_id_t>(new char[size]);
    }
    static void deallocate(memory_id_t ptr) { delete[] ptr; }
};
TEST(Adapter, Basic) { Allocator<CustomType, 1, HeapDevice> alloc; }