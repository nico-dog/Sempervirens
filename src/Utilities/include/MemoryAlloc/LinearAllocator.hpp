//***************************************************
//
// Definition of LinearAllocator
// The linear allocator's ctor takes an AreaPolicy (either stack or heap area) as argument.
// The allocator holds at internal ptr for the position in the area.
// The allocator cannot deallocate individual allocation but simply reset the internal ptr to the beginning of the area.
//
// Following implementation from:
// https://blog.molecular-matters.com/2012/08/14/memory-allocation-strategies-a-linear-allocator/
//
//***************************************************
#ifndef LINEARALLOCATOR_HPP
#define LINEARALLOCATOR_HPP
#include <cstddef>

namespace dog::utilities::memoryalloc {

  class LinearAllocator {

    char* _begin;
    char* _current;
    char* _end;
    
  public:
    template <typename AreaPolicy>
    LinearAllocator(AreaPolicy area);

    ~LinearAllocator() = default;

    void* allocate(std::size_t size, std::size_t alignment, std::size_t offset);
    inline void deallocate(void* ptr) const {}
    inline void reset() { _current = _begin; *_current = 0xcc; }
    
    inline void* begin() const { return _begin; }
    inline void* current() const { return _current; }
    inline void* end() const { return _end; }

    void dumpMemory();
  };
}
#include <MemoryAlloc/LinearAllocator.inl>
#endif
