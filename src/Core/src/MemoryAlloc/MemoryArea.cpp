#define MEMORYAREA_CPP
#include <MemoryAlloc/MemoryArea.hpp>
#include <MemoryAlloc/MemoryAlloc.hpp>
#include <Logging/Logger.hpp>

namespace sempervirens::core::memoryalloc {

  HeapArea::HeapArea(std::size_t size) : _begin{static_cast<char*>(sempervirens::core::memoryalloc::allocateHeap(size))}, _size{size} {

    SEMPERVIRENS_MSG("Memory area ctor: size = " << _size
	       << ", begin = " << static_cast<void*>(_begin) << ", end = " << static_cast<void*>(_begin + _size));
  }

  HeapArea::~HeapArea() {

    sempervirens::core::memoryalloc::deallocateHeap(static_cast<void*>(_begin));
  }

  StackArea::StackArea(void* ptr, std::size_t size) : _begin{static_cast<char*>(ptr)}, _size{size} {

    SEMPERVIRENS_MSG("Memory area ctor: size = " << _size
	       << ", begin = " << static_cast<void*>(_begin) << ", end = " << static_cast<void*>(_begin + _size));
  }
}
