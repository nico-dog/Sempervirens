#ifndef BOUNDSCHECKINGPOLICY_HPP
#define BOUNDSCHECKINGPOLICY_HPP
#include <MemoryAlloc/MemoryHelperFcts.hpp>
#include <cstdint>
#include <cstring>

namespace dog::utilities::memoryalloc {

  class BoundsChecker
  {
    std::uint8_t _val{0xbc};
    
  public:
    static const size_t GUARD_SIZE = 6;
 
    inline void guardFront(void* const ptr) const { Memset(ptr, _val, GUARD_SIZE); }
    inline void guardBack(void* const ptr) const { Memset(ptr, _val, GUARD_SIZE); }
 
    inline void checkFront(void* const ptr) const { Memcheck(ptr, _val, GUARD_SIZE); }
    inline void checkBack(void* const ptr) const { Memcheck(ptr, _val, GUARD_SIZE); }
  };
  
  class VoidBoundsChecker
  {
  public:
    static const size_t SIZE_GUARD = 0;
 
    inline void guardFront(void*) const {}
    inline void guardBack(void*) const {}
 
    inline void checkFront(const void*) const {}
    inline void checkBack(const void*) const {}
  };
}
#endif
