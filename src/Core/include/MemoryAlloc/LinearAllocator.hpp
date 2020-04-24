#ifndef LINEARALLOCATOR_HPP
#define LINEARALLOCATOR_HPP

namespace sempervirens::core::memoryalloc
{
  class LinearAllocator
  {
    char* _begin;
    char* _current;
    char* _end;
    
  public:
    LinearAllocator(void* ptr, std::size_t size);
    ~LinearAllocator() = default;

    void* allocate(std::size_t size, std::size_t alignment, std::size_t offset);
    inline void deallocate(void* ptr, std::size_t size) {};
    //inline void reset() { _current = _begin; }
    inline void reset() { *_current = 0; _current = _begin; *_current = 0xcc; }
    
    inline void* begin() const { return static_cast<void*>(_begin); }
    inline void* current() const { return static_cast<void*>(_current); }
    inline void* end() const { return static_cast<void*>(_end); }

    void dumpMemory();
  };
}
#endif
