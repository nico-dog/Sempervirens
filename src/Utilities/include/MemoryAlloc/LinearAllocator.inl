#ifndef LINEARALLOCATOR_INL
#define LINEARALLOCATOR_INL
#include <Logging/Logger.hpp>

namespace dog::utilities::memoryalloc {


  template <typename AreaPolicy>
  LinearAllocator::LinearAllocator(AreaPolicy area) :
    _begin{static_cast<char*>(area.begin())}, _current{_begin}, _end{static_cast<char*>(area.end())} {

      DOG_LOGMSG("LinearAllocator ctor: begin = " << area.begin() << ", current = " << current() << ", end = " << area.end());
  }
}
#endif
