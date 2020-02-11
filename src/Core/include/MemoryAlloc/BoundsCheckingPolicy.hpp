#ifndef BOUNDSCHECKINGPOLICY_HPP
#define BOUNDSCHECKINGPOLICY_HPP
#include <MemoryAlloc/MemoryHelperFcts.hpp>
//#include <cstdint>

namespace sempervirens::core::memoryalloc {

  class VoidBoundsChecker {};
  
  class BoundsChecker {
    
  public:
    static const std::uint32_t GUARD_VALUE = 0xbcbcbcbc;
    static const size_t FRONT_GUARD_SIZE = sizeof(GUARD_VALUE); // 4B of guards
    static const size_t BACK_GUARD_SIZE = sizeof(GUARD_VALUE);  // 4B of guards

    inline void guardFront(void* const ptr) const { Memset(ptr, GUARD_VALUE); }
    inline void guardBack(void* const ptr) const { Memset(ptr, GUARD_VALUE); }
 
    inline void checkFront(void* const ptr) const { Memcheck(ptr, GUARD_VALUE); }
    inline void checkBack(void* const ptr) const { Memcheck(ptr, GUARD_VALUE); }
  };
  
  class ExtendedBoundsChecker {
    
  public:
    static const std::uint32_t GUARD_VALUE = 0xbcbcbcbc;
    static const size_t FRONT_EXTRA_SIZE = 1; // 1B for offset from previous alloc 
    static const size_t BACK_EXTRA_SIZE = 4;  // 4B for size of alloc 
    static const size_t FRONT_GUARD_SIZE = sizeof(GUARD_VALUE) + FRONT_EXTRA_SIZE; 
    static const size_t BACK_GUARD_SIZE = sizeof(GUARD_VALUE) + BACK_EXTRA_SIZE; 
    
    inline void guardFront(void* const ptr, std::uint8_t offset) const {

      Memset(ptr, offset);     
      APtr<std::uint8_t> p{ptr};
      ++p;
      Memset(p.asVoid(), GUARD_VALUE);
    }
    
    inline void guardBack(void* const ptr, std::uint32_t size) const {

      Memset(ptr, size);
      APtr<std::uint32_t> p{ptr};
      ++p;
      Memset(p.asVoid(), GUARD_VALUE);
    }
 
    inline void checkAllGuards(void* end, void* const begin) const {

      void* startAlloc{nullptr};
      APtr<std::uint32_t> p{end};
      do {
	// Check back guard of current allocation and retreive its size.
	Memcheck((--p).asVoid(), GUARD_VALUE);
	auto size = *--p;

	// Check front guard of current allocation and retrieve its offset from the previous allocation.
	APtr<char> fp{p.asVoid()};
	fp -= size + sizeof(GUARD_VALUE);
	Memcheck(fp.asVoid(), GUARD_VALUE);
	auto offset = *--fp;

	// Set pointer to beginning of current allocation.
	fp -= offset;
	startAlloc = fp.asVoid();
	p = startAlloc;
      }
      while(startAlloc != begin);     
    }
  };
    
}
#endif
