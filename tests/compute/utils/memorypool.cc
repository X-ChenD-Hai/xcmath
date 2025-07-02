
#include <gtest/gtest.h>

#include <compute/utils/allocator.hpp>
#include <compute/utils/device.hpp>
#include <compute/utils/heapdevice.hpp>
#include <cstddef>
using namespace xcmath::comp;
class HeapPoolDevice {
   public:
    constexpr static const size_t access_grade = 0;
    constexpr static const bool access_by_pointer = 1;
    constexpr static const bool allow_destruct = 1;
    constexpr static const bool random_visits = 1;
    constexpr static const bool sequential_visits = 0;

   private:
   public:
    struct Block {
        void* ptr;
        size_t size;
    };
    struct mem_id_t {
        HeapPoolDevice* pool;
        size_t offset;
    };
};

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
TEST(MemoryPool, Basic) {
    auto pool = Allocator<CustomType, 1, HeapPoolDevice>();
    for (int i = 0; i < pool.size; i++) {
        // pool[i] = CustomType("test" + std::to_string(i));
    }
}
