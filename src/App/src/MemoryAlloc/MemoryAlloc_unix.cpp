#define MEMORYALLOC_CPP
#include <MemoryAlloc/MemoryAlloc.hpp>
#include <stdlib.h>
#include <alloca.h>

namespace dog::app::memoryalloc {

  void* allocateHeap(std::size_t size) {

    return malloc(size);
  }

  void deallocateHeap(void* ptr) {

    free(ptr);
  }

}
