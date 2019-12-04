//***************************************************
//
// Definition of helper functions
// Following implementation from Molecular Matters (https://blog.molecular-matters.com/2011/07/07/memory-system-part-2/)

// - DOG_NEW: calls the new op. with placement syntax -> calls void* operator new(size_t bytes, void* ptr)
//            which does not allocate but returns pointer provided by arena after constructing 'type' at that location
//            Final 'type' in macro expansion allows to pass ctor arguments
// - DOG_DELETE: calls the Delete function
// - DOG_NEW_ARRAY/DOG_DELETE_ARRAY: call resp. NewArray and DeleteArray functions.
//                                   Both are optimized for POD vs non-POD types (i.e., no ctor/dtor calls for POD types)
//
//***************************************************
#ifndef MEMORYHELPERFCTS_HPP
#define MEMORYHELPERFCTS_HPP
#include <Misc/Misc.hpp>
#include <type_traits>


namespace dog::utilities::memoryalloc {
  
  template<typename T, class Arena>
  void Delete(T* type, Arena& arena);

  template <typename T, class Arena>
  T* NewArray(Arena& arena, std::size_t N, const char* file, int line);

  template <typename T, class Arena>
  void DeleteArray(T* ptr, Arena& arena);
  
#define DOG_NEW(type, arena) new (arena.allocate(std::sizeof(type), std::alignment_of_v<type>, __FILENAME__, __LINE__)) type
#define DOG_DELETE(object, arena) Delete(object, arena)

#define DOG_NEW_ARRAY(type, N, arena) NewArray<type>(arena, N, __FILENAME__, __LINE__)
#define DOG_DELETE_ARRAY(object, arena) DeleteArray(object, arena)

#define DOG_kB(value) value * 1024
#define DOG_MB(value) DOG_kB(value) * 1024
#define DOG_GB(value) DOG_MB(value) * 1024

  // size conversion operators
  //constexpr std::size_t kB = 1024;
  //constexpr std::size_t operator""_kB (unsigned long long v) { return std::size_t{v * kB}; }
  //constexpr std::size_t operator""_MB (unsigned long long v) { return v * kB * kB; }
  //constexpr std::size_t operator""_GB (unsigned long long v) { return v * kB * kB * kB; }
}

#include <MemoryAlloc/MemoryHelperFcts.inl>
#endif
