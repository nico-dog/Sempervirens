//***************************************************
//
// Definition of memory arena
// Following implementation from Molecular Matters (https://blog.molecular-matters.com/2011/07/07/memory-system-part-5/)
// The arena forwards allocation calls to the allocator it points to, while taking care of:
// - bounds checking
// - memory tracking
// - memory tagging
// - concurrent access to allocator
// The allocator is initialized beforehand for a given memory area (stack or heap).
//
//***************************************************
#ifndef MEMORYARENA_HPP
#define MEMORYARENA_HPP
#include <Macros/Build.hpp>
//#include <string>

namespace sempervirens::core::memoryalloc {

  //template <class AllocationPolicy, class ThreadPolicy, class BoundsCheckingPolicy, class MemoryTrackingPolicy, class MemoryTaggingPolicy>
  template<class AllocationPolicy, class BoundsCheckingPolicy>
  class MemoryArena {

    AllocationPolicy* _allocator;
    //ThreadPolicy _threadGuard;
    BoundsCheckingPolicy _boundsChecker;
    //MemoryTrackingPolicy _memoryTracker;
    //MemoryTaggingPolicy _memoryTagger;
    
  public:
    MemoryArena(AllocationPolicy* allocator, std::string description);
    ~MemoryArena() = default;

    MemoryArena(MemoryArena const&) = delete;
    MemoryArena& operator=(MemoryArena const&) = delete;
    MemoryArena(MemoryArena&&) = delete;
    MemoryArena& operator=(MemoryArena&&) = delete;
    
    void* allocate(std::size_t size, std::size_t alignment, const char* file, int line);
    void deallocate(void* ptr, std::size_t size);

#if SEMPERVIRENS_BUILD(UNITTESTING)
    void static test();
#endif    
  };

}
#include <MemoryAlloc/MemoryArena.inl>
#endif
