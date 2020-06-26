#define LINEARALLOCATOR_CPP
#include <MemoryAlloc/LinearAllocator.hpp>
#include <MemoryAlloc/MemoryHelperFcns.hpp>
#include <Logging/Logger.hpp>

namespace sempervirens::memoryalloc
{
  LinearAllocator::LinearAllocator(void* ptr, std::size_t size) :
    _begin{static_cast<char*>(ptr)}, _current{_begin}, _end{_begin + size} {}  


  void* LinearAllocator::allocate(std::size_t size, std::size_t alignment, std::size_t offset)
  {
    APtr<char> p{_current};
    
    SEMPERVIRENS_MSG("current ptr = " << p.asVoid());

    // Offset pointer first, align it, and offset it back
    p += offset;    
    p = alignUp(p.asVoid(), alignment);
    SEMPERVIRENS_MSG("aligned ptr = " << p.asVoid());
    p -= offset;

    SEMPERVIRENS_MSG("current ptr after alignment + offset = " << p.asVoid());
	       
    auto nLostBytes = p.asType() - _current;
    SEMPERVIRENS_MSG("number of bytes lost: " << nLostBytes);
    for (auto i = 0; i < nLostBytes; ++i) *_current++ = 0xcd;	       


    _current += offset;
    for (auto i = std::size_t{0}; i < size - 2 * offset; ++i) *_current++ = 0xab;
    _current += offset;

    //_current += (as_char - _current) + size;
    
    SEMPERVIRENS_MSG("current ptr after allocation = " << static_cast<void*>(_current));
    
    assert(!(_current > _end));

    *_current = 0xcc;

    return p.asVoid();
    //    return as_void;
  }

  void LinearAllocator::dumpMemory()
  {
    std::stringstream s{};
    auto ptr = _begin;
    auto nBytes = _end - _begin;

    SEMPERVIRENS_MSG("Memory dump: nBytes = " << nBytes);

    auto delimiters = std::array<char, 2>{' ', ':'};
    for (auto i = 1; i < nBytes + 1; ++i)
    {
      if (!((i - 1) & 15)) s << static_cast<void*>(ptr) << "  ";

      s << std::setw(2) << std::setfill('0') << std::hex << +static_cast<std::uint8_t>(*ptr++) << delimiters[(i & 3) > 0];

      if (!(i & 15) || i == nBytes)
      {
	SEMPERVIRENS_MSG(s.str());
	std::stringstream().swap(s);
      }
    }
  }

}
