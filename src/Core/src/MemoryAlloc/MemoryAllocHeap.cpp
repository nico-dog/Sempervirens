#define MEMORYALLOCHEAP_CPP
#include <MemoryAlloc/MemoryAllocHeap.hpp>

namespace sempervirens::core::memoryalloc
{
  void* allocateHeap(std::size_t size)
  {
    return malloc(size);
  }

  void deallocateHeap(void* ptr)
  {
    free(ptr);
  }

}
