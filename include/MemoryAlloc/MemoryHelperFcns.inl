//#include <utility>

namespace sempervirens::memoryalloc
{
  // Define POD type for optimizations
  // std::is_pod<T>::value was deprecated in C++20, considered equivalent to what is implemented below
  template<typename T>
  struct IsPOD
  {
    static const bool value = std::conjunction_v<std::is_trivial<T>, std::is_standard_layout<T>>;
  };
  template<typename T>
  inline constexpr bool isPOD = IsPOD<T>::value;

  
  template<typename T, class Arena, typename... Args>
  Block<T> New(Arena& arena, const char* file, int line, Args&&... args)
  {
    void* ptr = arena.allocate(sizeof(T), std::alignment_of_v<T>, file, line);
    
    if constexpr (isPOD<T>) return {static_cast<T*>(new (ptr) T{std::forward<Args>(args)...}), sizeof(T)};
    else return {static_cast<T*>(new (ptr) T(std::forward<Args>(args)...)), sizeof(T)};
  }
  
  
  template<typename T, class Arena>
  void Delete(Block<T> block, Arena& arena)
  {
    if constexpr (!isPOD<T>) block._ptr->~T();
    arena.deallocate(block._ptr, block._size);
  }

  
  template<typename T, class Arena>
  Block<T> NewArray(Arena& arena, const char* file, int line, std::size_t N)
  {  
    if constexpr (isPOD<T>) return {static_cast<T*>(arena.allocate(sizeof(T) * N, std::alignment_of_v<T>, file, line)), sizeof(T) * N};
    else 
    {
      union
      {
	void* as_void;
	T* as_T;
      };
 
      as_void = arena.allocate(sizeof(T) * N, std::alignment_of_v<T>, file, line);
 
      // Construct instances using placement new
      const T* const onePastLast = as_T + N;
      while (as_T < onePastLast)
	new (as_T++) T;
 
      return {(as_T - N), sizeof(T) * N}; // Return pointer to the first instance
    }
  }

  
  template<typename T, class Arena>
  void DeleteArray(Block<T> block, Arena& arena)
  {
    if constexpr (isPOD<T>) arena.dealocate(block._ptr, block._size);
    else
    {
      auto as_T = block._ptr; // User pointer points to first instance...
 
      // Call instances' destructor in reverse order, per C++ std
      auto N = block._size / sizeof(T);
      
      for (std::size_t i = N; i > 0; --i)
	as_T[i-1].~T();
 
      arena.deallocate(block._ptr, block._size);
    }
  }
  
}
