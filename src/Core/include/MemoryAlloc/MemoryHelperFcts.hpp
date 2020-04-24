#ifndef MEMORYHELPERFCTS_HPP
#define MEMORYHELPERFCTS_HPP

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

namespace sempervirens::core::memoryalloc
{
  template<typename T>
  class APtr
  {
    union
    {
      void* as_void;
      T* as_T;
    };

  public:
    explicit APtr(void* ptr) : as_void{ptr} {};
    explicit APtr(T* ptr) : as_T{ptr} {};
    ~APtr() = default;
    APtr(APtr const&) = default;

    APtr& operator=(APtr const&) = default;
    APtr& operator=(void* ptr) { as_void = ptr; return *this; }
    APtr& operator=(T* ptr) { as_T = ptr; return *this; }
    
    inline APtr& operator++() { ++as_T; return *this; }
    inline APtr operator++(int) { return {as_T++}; }
    inline APtr& operator--() { --as_T; return *this; }
    inline APtr operator--(int) { return {as_T--}; }
    inline APtr& operator+=(std::size_t size) { as_T += size; return *this; }
    inline APtr& operator-=(std::size_t size) { as_T -= size; return *this; }
    inline T* operator+(std::size_t size) const { return as_T + size; }
    inline T* operator-(std::size_t size) const { return as_T - size; }
    inline T operator*() { return *as_T; }
    
    inline void* asVoid() const { return as_void; }
    inline T* asType() const { return as_T; }
  };

  template<typename T>
  inline void Memset(void* const ptr, T value)
  {
    auto as_T = static_cast<T*>(ptr);
    *as_T = value;
  }

  template<typename T>
  inline void Memcheck(void* const ptr, T value)
  {
    auto as_T = static_cast<T*>(ptr);
    assert(*as_T == value);
  }
  
  // Align pointer up to next multiple of alignment
  inline void* alignUp(void* ptr, std::size_t alignment)
  {
    // Need to cast to integral type to perform pointer bitwise op.
    // uintptr_t is an integer type guaranteed to be large enough to store a ptr
    return reinterpret_cast<void*>((reinterpret_cast<std::uintptr_t>(ptr) + alignment - 1) & ~(alignment - 1));
  }

  // Allocation block: ptr + allocated size
  template<typename T>
  struct Block {

    T* _ptr;
    std::size_t _size;
  };

  template<typename T, class Arena, typename... Args>
  Block<T> New(Arena& arena, Args&&... args);

  template<typename T, class Arena>
  void Delete(Block<T> block, Arena& arena);

  template<typename T, class Arena>
  Block<T> NewArray(Arena& arena, const char* file, int line, std::size_t N);
  
  template<typename T, class Arena>
  void DeleteArray(Block<T>, Arena& arena);

#define SEMPERVIRENS_NEW(type, arena, ...) New<type>(arena, __FILENAME__, __LINE__, ##__VA_ARGS__)
#define SEMPERVIRENS_DELETE(block, arena) Delete(block, arena)

#define SEMPERVIRENS_NEW_ARRAY(type, arena, N) NewArray<type>(arena, __FILENAME__, __LINE__, N)
#define SEMPERVIRENS_DELETE_ARRAY(block, arena) DeleteArray(block, arena)

#define SEMPERVIRENS_B(value)  value
#define SEMPERVIRENS_kB(value) SEMPERVIRENS_B(value)  * 1024
#define SEMPERVIRENS_MB(value) SEMPERVIRENS_kB(value) * 1024
#define SEMPERVIRENS_GB(value) SEMPERVIRENS_MB(value) * 1024
}

#include <MemoryAlloc/MemoryHelperFcts.inl>
#endif
