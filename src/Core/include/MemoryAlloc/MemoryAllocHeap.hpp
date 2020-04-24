#ifndef MEMORYALLOCHEAP_HPP
#define MEMORYALLOCHEAP_HPP

namespace sempervirens::core::memoryalloc
{
  void* allocateHeap(std::size_t size);
  void deallocateHeap(void* ptr);
}
#endif
