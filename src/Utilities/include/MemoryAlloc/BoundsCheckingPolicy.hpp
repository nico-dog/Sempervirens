#ifndef BOUNDSCHECKINGPOLICY_HPP
#define BOUNDSCHECKINGPOLICY_HPP
#include <MemoryAlloc/MemoryHelperFcts.hpp>
#include <cstdint>

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
  
  class NoBoundsChecker
  {
  public:
    static const size_t GUARD_SIZE = 0;
 
    inline void guardFront(void* const ptr) const {}
    inline void guardBack(void* const ptr) const {}
 
    inline void checkFront(void* const ptr) const {}
    inline void checkBack(void* const ptr) const {}
  };
}
#endif
