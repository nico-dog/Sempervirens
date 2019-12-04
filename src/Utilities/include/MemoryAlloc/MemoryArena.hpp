//***************************************************
//
// Definition of memory arena
// Following implementation from Molecular Matters (https://blog.molecular-matters.com/2011/07/07/memory-system-part-5/)
//
// 
//
//***************************************************
#ifndef MEMORYARENA_HPP
#define MEMORYARENA_HPP
#include <Build/Build.hpp>
#include <string>

namespace dog::utilities::memoryalloc {

  //template <class AllocationPolicy, class ThreadPolicy, class BoundsCheckingPolicy, class MemoryTrackingPolicy, class MemoryTaggingPolicy>
  template <class AllocationPolicy>
  class MemoryArena
  {
    AllocationPolicy* _allocator;
    //ThreadPolicy _threadGuard;
    //BoundsCheckingPolicy _boundsChecker;
    //MemoryTrackingPolicy _memoryTracker;
    //MemoryTaggingPolicy _memoryTagger;
    
  public:
    MemoryArena(AllocationPolicy* allocator, std::string description);
    ~MemoryArena() = default;
    
    //void* allocate(size_t size, size_t alignment, const SourceInfo& sourceInfo);
    void* allocate(std::size_t size, std::size_t alignment, const char* file, int line);
    void deallocate(void* ptr);

#if DOG_BUILD(UNITTESTS)
    void static test();
#endif    
  };

}
#include <MemoryAlloc/MemoryArena.inl>
#endif
