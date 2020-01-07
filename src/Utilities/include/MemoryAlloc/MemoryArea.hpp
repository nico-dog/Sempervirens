//***************************************************
//
// Definition of memory areas
// - HeapArea: is allocated on the heap via a call to general-purpose allocator (e.g. malloc)
// - StackArea: is allocated on the stack (e.g. fixed size array, alloca)
//
//***************************************************
#ifndef MEMORYAREA_HPP
#define MEMORYAREA_HPP
#include <cstdint>

namespace dog::utilities::memoryalloc {
      
  class HeapArea {

    char* _begin;
    std::size_t _size;
    
  public:
    explicit HeapArea(std::size_t size);
    ~HeapArea();
    
    HeapArea(HeapArea const&) = delete;
    HeapArea& operator=(HeapArea const&) = delete;
    HeapArea(HeapArea&&) = delete;
    HeapArea& operator=(HeapArea&&) = delete;

    void* const begin() const { return static_cast<void*>(_begin); }
    std::size_t size() const { return _size; }
  };

  class StackArea {

    char* _begin;
    std::size_t _size;
    
  public:
    StackArea(void* ptr, std::size_t size);
    ~StackArea() = default;
    
    StackArea(StackArea const&) = delete;
    StackArea& operator=(StackArea const&) = delete;
    StackArea(StackArea&&) = delete;
    StackArea& operator=(StackArea&&) = delete;

    void* const begin() const { return static_cast<void*>(_begin); }
    std::size_t size() const { return _size; }
  };
  
}
#endif
