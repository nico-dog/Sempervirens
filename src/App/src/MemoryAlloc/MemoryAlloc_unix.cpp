#define MEMORYALLOC_CPP
#include <MemoryAlloc/MemoryAlloc.hpp>
#include <stdlib.h>

namespace dog::app::memoryalloc {

  void* allocate(std::size_t size) {

    return malloc(size);
  }

  void deallocate(void* ptr) {

    free(ptr);
  }
}
