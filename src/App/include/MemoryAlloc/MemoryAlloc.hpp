//***************************************************
//
// Definition of memoryalloc namespace:
// The namespace provides a platform-indepedent interface for general-purpose memory allocation
// Different implementations are provided for different platforms.
//
//***************************************************
#ifndef MEMORYALLOC_HPP
#define MEMORYALLOC_HPP
#include <cstddef>

namespace dog::app::memoryalloc {

  void* allocate(std::size_t size);
  void deallocate(void* ptr);
}
#endif
