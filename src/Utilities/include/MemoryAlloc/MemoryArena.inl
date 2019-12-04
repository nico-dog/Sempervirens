#include <Logging/Logger.hpp>

#if DOG_BUILD(UNITTESTS)
#include <MemoryAlloc/MemoryArea.hpp>
#include <MemoryAlloc/LinearAllocator.hpp>
#include <MemoryAlloc/MemoryHelperFcts.hpp>
#include <Logging/Logger.hpp>
#include <array>
#endif


namespace dog::utilities::memoryalloc {

  template <class AllocationPolicy>
  MemoryArena<AllocationPolicy>::MemoryArena(AllocationPolicy* allocator, std::string description) : _allocator{allocator} {

    DOG_LOGMSG("Memory arena ctor: " << std::move(description)
	       << "\n> .. allocator begin at: " << _allocator->begin());
  }


  template <class AllocationPolicy>
  void* MemoryArena<AllocationPolicy>::allocate(std::size_t size, std::size_t alignment, const char* file, int line) {

    DOG_LOGMSG("allocating " << size << " bytes with alignment " << alignment);
    return nullptr;
  }

  template <class AllocationPolicy>
  void MemoryArena<AllocationPolicy>::deallocate(void* ptr) {

  }

  
#if DOG_BUILD(UNITTESTS)
  template <class AllocationPolicy>
  void MemoryArena<AllocationPolicy>::test() {

    auto block = std::array<char, DOG_kB(1)>{};
    DOG_LOGMSG("Creating block on stack, start = " << static_cast<void*>(block.data()));

    auto area = StackArea{static_cast<void*>(block.data()), block.size()};
    auto allocator = LinearAllocator{area};
    auto arena = MemoryArena{&allocator, "linear arena on stack"};

    struct MyObject {
      int _value;
    };

    DOG_NEW(MyObject, arena)(1);
    
  }
#endif
}
