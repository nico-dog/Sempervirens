//***************************************************
//
// Definition of LinearAllocator
//
//
//***************************************************
#ifndef LINEARALLOCATOR_HPP
#define LINEARALLOCATOR_HPP

namespace dog::utilities::memoryalloc {

  class LinearAllocator {

    char* _begin;
    char* _end;
    char* _current;
    
  public:
    template <typename AreaPolicy>
    LinearAllocator(AreaPolicy area);

    ~LinearAllocator() = default;

    void* begin() const { return _begin; }
    void* end() const { return _end; }
  };
}
#include <MemoryAlloc/LinearAllocator.inl>
#endif
