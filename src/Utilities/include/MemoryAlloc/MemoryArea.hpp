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
    char* _end;
    std::size_t _size;

  public:
    explicit HeapArea(std::size_t size);
    ~HeapArea();

    HeapArea(HeapArea const&) = default;
    HeapArea& operator=(HeapArea const&) = default;
    HeapArea(HeapArea&&) = delete;
    HeapArea& operator=(HeapArea&&) = delete;
 
    void* begin() const { return _begin; }
    void* end() const { return _end; }
    std::size_t size() const { return _size; }
  };
    
  class StackArea {

    char* _begin;
    std::size_t _size;
    
  public:
    StackArea(void* begin, std::size_t size);
    
    StackArea(StackArea const&) = default;
    StackArea& operator=(StackArea const&) = default;
    StackArea(StackArea&&) noexcept = default;
    StackArea& operator=(StackArea&&) noexcept = default;

    void* begin() { return _begin; }
    void* end() { return _begin + _size; }
    std::size_t size() { return _size; }
  };
}
#endif
