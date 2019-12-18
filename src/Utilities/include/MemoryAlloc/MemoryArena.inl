#include <MemoryAlloc/MemoryHelperFcts.hpp>
#include <MemoryAlloc/BoundsCheckingPolicy.hpp>
#include <Logging/Logger.hpp>

#if DOG_BUILD(UNITTESTS)
#include <MemoryAlloc/MemoryAlloc.hpp>
#include <MemoryAlloc/MemoryArea.hpp>
#include <MemoryAlloc/LinearAllocator.hpp>
#include <array>
#include <stdlib.h>
#endif


namespace dog::utilities::memoryalloc {

  template<class AllocationPolicy, class BoundsCheckingPolicy>
  MemoryArena<AllocationPolicy, BoundsCheckingPolicy>::MemoryArena(AllocationPolicy* allocator, std::string description) : _allocator{allocator} {

    DOG_LOGMSG("Memory arena ctor: " << std::move(description)
	       << "\n> .. allocator begin at: " << _allocator->begin());
  }

  template<class AllocationPolicy, class BoundsCheckingPolicy>
  void* MemoryArena<AllocationPolicy, BoundsCheckingPolicy>::allocate(std::size_t size, std::size_t alignment, const char* file, int line) {

    DOG_LOGMSG("original size = " << size << " bytes, with alignment = " << alignment);

    auto newSize = size + 2 * BoundsCheckingPolicy::GUARD_SIZE; 
    auto offset = BoundsCheckingPolicy::GUARD_SIZE; 


    DOG_LOGMSG("new size = " << newSize << " bytes with alignment " << alignment << ", offset = " << offset);
    
    auto ptr = static_cast<char*>(_allocator->allocate(newSize, alignment, offset));

    _boundsChecker.guardFront(ptr);
    _boundsChecker.guardBack(ptr + offset + size);

    DOG_LOGMSG("arena returns " << static_cast<void*>(ptr + offset));
    
    
    return ptr + offset;
  }

  template<class AllocationPolicy, class BoundsCheckingPolicy>
  void MemoryArena<AllocationPolicy, BoundsCheckingPolicy>::deallocate(void* ptr, std::size_t size) {

    _boundsChecker.checkFront(static_cast<char*>(ptr) - BoundsCheckingPolicy::GUARD_SIZE);
    _boundsChecker.checkBack(static_cast<char*>(ptr) + size);
    
    _allocator->deallocate(ptr, size);
  }

  
#if DOG_BUILD(UNITTESTS)
  template<class AllocationPolicy, class BoundsCheckingPolicy>
  void MemoryArena<AllocationPolicy, BoundsCheckingPolicy>::test() {

    auto areaSize = std::size_t{DOG_B(64)};
    
    char* stackArea[areaSize] = {0};
    auto area = StackArea{static_cast<void*>(stackArea), areaSize};
    //auto area = HeapArea{areaSize};
    auto allocator = LinearAllocator{area.begin(), area.size()};

    
    auto arena = MemoryArena<LinearAllocator, BoundsChecker>{&allocator, "Linear arena on stack"};

    struct MyObject {
      int _value;
      MyObject() { DOG_LOGMSG("MyObject default ctor"); }
      explicit MyObject(int val) : _value{val} { DOG_LOGMSG("MyObject ctor"); }
      ~MyObject() { DOG_LOGMSG("MyObject dtor"); }
    };

    struct MyPOD {
      int _value;
    };

    
    Block<MyObject> myBlock = DOG_NEW_ARRAY(MyObject, arena, 2);

    DOG_LOGMSG("First object allocated at " << static_cast<void*>(myBlock._ptr));
    
    allocator.dumpMemory();


    
    MyObject* objects = myBlock._ptr;
    objects[0]._value = 1;
    objects[1]._value = 2;

    Block<MyPOD> myBlock2 = DOG_NEW(MyPOD, arena, 3);

    allocator.dumpMemory();
    

    DOG_DELETE_ARRAY(myBlock, arena);
    DOG_DELETE(myBlock2, arena);

    allocator.reset();
    allocator.dumpMemory();
    

    
  }
#endif
}
