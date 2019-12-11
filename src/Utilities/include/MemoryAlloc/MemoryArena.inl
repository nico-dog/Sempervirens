#include <MemoryAlloc/MemoryHelperFcts.hpp>
#include <MemoryAlloc/BoundsChecking.hpp>
#include <Logging/Logger.hpp>

#if DOG_BUILD(UNITTESTS)
#include <MemoryAlloc/MemoryArea.hpp>
#include <MemoryAlloc/LinearAllocator.hpp>
#include <array>
#endif


namespace dog::utilities::memoryalloc {

  template <class AllocationPolicy, class BoundsCheckingPolicy>
  MemoryArena<AllocationPolicy, BoundsCheckingPolicy>::MemoryArena(AllocationPolicy* allocator, std::string description) : _allocator{allocator} {

    DOG_LOGMSG("Memory arena ctor: " << std::move(description)
	       << "\n> .. allocator begin at: " << _allocator->begin());
  }

  template <class AllocationPolicy, class BoundsCheckingPolicy>
  void* MemoryArena<AllocationPolicy, BoundsCheckingPolicy>::allocate(std::size_t size, std::size_t alignment, const char* file, int line) {

    DOG_LOGMSG("original size = " << size << " bytes, with alignment = " << alignment);

    auto newSize = size + 2 * BoundsCheckingPolicy::SIZE_GUARD; //stuff like bounds checking policy guards
    auto offset = BoundsCheckingPolicy::SIZE_GUARD; //stuff like bounds checking policy guards, would also need to store the allocation size (?)


    DOG_LOGMSG("new size = " << newSize << " bytes with alignment " << alignment << ", offset = " << offset);
    
    auto ptr = static_cast<char*>(_allocator->allocate(newSize, alignment, offset));

    DOG_LOGMSG("arena returns " << static_cast<void*>(ptr + offset));
    
    
    return ptr + offset;
  }

  template <class AllocationPolicy, class BoundsCheckingPolicy>
  void MemoryArena<AllocationPolicy, BoundsCheckingPolicy>::deallocate(void* ptr) {

    _allocator->deallocate(ptr);
  }

  
#if DOG_BUILD(UNITTESTS)
  template <class AllocationPolicy, class BoundsCheckingPolicy>
  void MemoryArena<AllocationPolicy, BoundsCheckingPolicy>::test() {

    //auto block = std::array<char, DOG_kB(1)>{};
    auto block = std::array<char, DOG_B(64)>{};
    auto area = StackArea{static_cast<void*>(block.data()), block.size()};
    auto allocator = LinearAllocator{area};
    auto arena = MemoryArena<LinearAllocator, BoundsChecker>{&allocator, "linear arena on stack"};

    struct MyObject {
      int _value;
      MyObject() { DOG_LOGMSG("MyObject default ctor"); }
      explicit MyObject(int val) : _value{val} { DOG_LOGMSG("MyObject ctor"); }
      ~MyObject() { _value = 0; DOG_LOGMSG("MyObject dtor"); }
    };

    struct MyPOD {
      int _value;
    };

  

    Block<MyObject> myBlock = DOG_NEW_ARRAY(MyObject, 2, arena);
    DOG_LOGMSG("First object allocated at " << static_cast<void*>(myBlock._ptr));
    
    allocator.dumpMemory();

    MyObject* objects = myBlock._ptr;
    objects[0]._value = 1;
    objects[1]._value = 2;

    Block<MyObject> myBlock2 = DOG_NEW(MyObject, arena, 3);

    allocator.dumpMemory();
    

    DOG_DELETE_ARRAY(myBlock, arena);
    DOG_DELETE(myBlock2, arena);

    allocator.dumpMemory();
    
  }
#endif
}
