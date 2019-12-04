
namespace dog::utilities::memoryalloc {

  template<typename T>
  struct IsPOD {

    //static const bool value = std::is_pod<T>::value; // deprecated in C++20, considered equivalent to:
    static const bool value = std::conjunction_v<std::is_trivial<T>, std::is_standard_layout<T>>;
  };

  template<typename T>
  inline constexpr bool isPOD = IsPOD<T>::value;
  
  template<typename T, class Arena>
  void Delete(T* object, Arena& arena) {

    object->~T();
    arena.free(object);
  }

  template<typename T, class Arena>
  T* NewArray(Arena& arena, std::size_t N, const char* file, int line) {

    if constexpr (isPOD<T>) return static_cast<T*>(arena.allocate(sizeof(T) * N, file, line));
    else 
    {
      union
      {
	void* as_void;
	std::size_t* as_size_t;
	T* as_T;
      };
 
      as_void = arena.allocate(sizeof(T) * N + sizeof(std::size_t), file, line);
 
      *as_size_t++ = N; // Store number of instances in first size_t bytes
 
      // Construct instances using placement new
      const T* const onePastLast = as_T + N;
      while (as_T < onePastLast)
	new (as_T++) T;
 
      return (as_T - N); // Hand user the pointer to the first instance
    }
  }

  template<typename T, class Arena>
  void DeleteArray(T* ptr, Arena& arena) {

    if constexpr (isPOD<T>) arena.free(ptr);
    else
    {
      union
      {
	std::size_t* as_size_t;
	T* as_T;
      };
 
      as_T = ptr; // User pointer points to first instance...
 
      const std::size_t N = as_size_t[-1]; // ...so go back size_t bytes and grab number of instances
 
      // Call instances' destructor in reverse order, per C++ std
      for (std::size_t i = N; i > 0; --i)
	as_T[i-1].~T();
 
      arena.free(as_size_t - 1);
    }
  }
  
}
