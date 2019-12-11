#ifndef BOUNDSCHECKING_HPP
#define BOUNDSCHECKING_HPP

namespace dog::utilities::memoryalloc {

  class BoundsChecker
  {
    //char _value{std::uint8_t{0xbc}};
    
  public:
    static const size_t SIZE_GUARD = 6;
 
    inline void GuardFront(void* ptr) const {}
    inline void GuardBack(void* ptr) const {}
 
    inline void CheckFront(const void* ptr) const {}
    inline void CheckBack(const void* ptr) const {}
  };
  
  class VoidBoundsChecker
  {
  public:
    static const size_t SIZE_GUARD = 0;
 
    inline void GuardFront(void*) const {}
    inline void GuardBack(void*) const {}
 
    inline void CheckFront(const void*) const {}
    inline void CheckBack(const void*) const {}
  };
}
#endif
