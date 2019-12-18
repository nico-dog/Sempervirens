#define LINEARALLOCATOR_CPP
#include <MemoryAlloc/LinearAllocator.hpp>
#include <MemoryAlloc/MemoryHelperFcts.hpp>
#include <Logging/Logger.hpp>
#include <iomanip>
#include <sstream>

namespace dog::utilities::memoryalloc {

  LinearAllocator::LinearAllocator(void* ptr, std::size_t size) :
    _begin{static_cast<char*>(ptr)}, _current{_begin}, _end{_begin + size} {}  


  void* LinearAllocator::allocate(std::size_t size, std::size_t alignment, std::size_t offset) {

    DOG_LOGMSG("current ptr = " << static_cast<void*>(_current));
    auto prev = _current;
    
    auto alignedPtr = alignUp(_current + offset, alignment);

    DOG_LOGMSG("aligned ptr = " << static_cast<void*>(alignedPtr));
    
    // Offset pointer first, align it, and offset it back
    _current = static_cast<char*>(alignedPtr) - offset;

    DOG_LOGMSG("current ptr after alignment + offset = " << static_cast<void*>(_current));

    auto nLostBytes = _current - prev;
    DOG_LOGMSG("number of bytes lost: " <<nLostBytes);
    for (auto i = 0; i < nLostBytes; ++i) *prev++ = 0xcd;

    
    void* usrPtr = _current;

    //for (auto i = std::size_t{0}; i < offset; ++i) *prev++ = 0xef;
    prev += offset;
    for (auto i = std::size_t{0}; i < size - 2 * offset; ++i) *prev++ = 0xab;
    //for (auto i = std::size_t{0}; i < offset; ++i) *prev++ = 0xef;


    
    _current += size;

    DOG_LOGMSG("current ptr after allocation = " << static_cast<void*>(_current));
    
    if (_current >= _end) return nullptr;

    *_current = 0xcc;
 
    return usrPtr;
  }

  void LinearAllocator::dumpMemory() {

    DOG_LOGMSG("Memory dump:");

    std::stringstream s{};
    auto ptr = _begin;
    auto nBytes = _end - _begin;

    auto delimiters = std::array<char, 2>{' ', ':'};
    for (auto i = 1; i < nBytes + 1; ++i)
    {
      if (!((i - 1) & 15)) s << static_cast<void*>(ptr) << "  ";

      s << std::setw(2) << std::setfill('0') << std::hex << +static_cast<std::uint8_t>(*ptr++) << delimiters[(i & 3) > 0];

      if (!(i & 15))
      {
	DOG_LOGMSG(s.str());
	std::stringstream().swap(s);
      }
    }
  }

}
