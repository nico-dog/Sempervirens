#define MEMORYAREA_CPP
#include <MemoryAlloc/MemoryArea.hpp>
#include <MemoryAlloc/MemoryAlloc.hpp>
#include <Logging/Logger.hpp>

namespace dog::utilities::memoryalloc {

  HeapArea::HeapArea(std::size_t size) {

    _begin = static_cast<char*>(dog::app::memoryalloc::allocate(size));
    _end = _begin + size;
    _size = size;

    DOG_LOGMSG("HeapArea ctor: size = " << _size
	       << ", start = " << static_cast<void*>(_begin)
	       << ", end = " << static_cast<void*>(_end));
  }

  HeapArea::~HeapArea() {

    dog::app::memoryalloc::deallocate(_begin);
  }

  StackArea::StackArea(void* begin, std::size_t size) : _begin{static_cast<char*>(begin)}, _size{size} {

    DOG_LOGMSG("StaticArea ctor: size = " << _size
	       << ", begin = " << static_cast<void*>(_begin) << ", end = " << static_cast<void*>(_begin + _size));
  }
}
