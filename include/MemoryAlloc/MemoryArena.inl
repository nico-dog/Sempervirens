#include <MemoryAlloc/MemoryHelperFcns.hpp>
#include <MemoryAlloc/BoundsCheckingPolicy.hpp>
#include <Logging/Logger.hpp>

#if SEMPERVIRENS_BUILD(UNITTESTING)
#include <MemoryAlloc/MemoryAllocHeap.hpp>
#include <MemoryAlloc/MemoryArea.hpp>
#include <MemoryAlloc/LinearAllocator.hpp>
#endif


namespace sempervirens::memoryalloc
{
  template<class AllocationPolicy, class BoundsCheckingPolicy>
  MemoryArena<AllocationPolicy, BoundsCheckingPolicy>::MemoryArena(AllocationPolicy* allocator, std::string description) : _allocator{allocator}
  {
    SEMPERVIRENS_MSG("Memory arena ctor: " << std::move(description)
	       << "\n> .. allocator begin at: " << _allocator->begin());
  }

  template<class AllocationPolicy, class BoundsCheckingPolicy>
  void* MemoryArena<AllocationPolicy, BoundsCheckingPolicy>::allocate(std::size_t size, std::size_t alignment, const char* file, int line)
  {
    // We return the address from the allocator directly if no bounds checking is required. In this case no offset is introduced.
    if constexpr (std::is_same_v<BoundsCheckingPolicy, VoidBoundsChecker>)
    {
      return _allocator->allocate(size, alignment, 0);
    }
    else
    // If bounds checking is required, we compute the total size of the allocation to account for the guards and the offset.
    {     
      auto totalSize = size + BoundsCheckingPolicy::FRONT_GUARD_SIZE + BoundsCheckingPolicy::BACK_GUARD_SIZE;
      auto offset = BoundsCheckingPolicy::FRONT_GUARD_SIZE;

      // Simple bounds checking adds guards at front and back of allocation.
      if constexpr (std::is_same_v<BoundsCheckingPolicy, BoundsChecker>)
      {
	APtr<char> p{_allocator->allocate(totalSize, alignment, offset)};
	_boundsChecker.guardFront(p.asVoid());
	p += (offset + size);
	_boundsChecker.guardBack(p.asVoid());
	p -= size;
	return p.asVoid();
      }
      else
      // Extended bounds checking adds guards at front and back of allocation and checks guards of all allocations.
      // To do so, the bounds checker includes the size of the allocation in its back guard and the number of bytes
      // possibly lost between the previous and current allocation in its front guard.
      {
	auto ptrPrevAlloc = static_cast<char*>(_allocator->current());
	
	APtr<char> p{_allocator->allocate(totalSize, alignment, offset)};
	auto nLostBytes = static_cast<std::uint8_t>(p.asType() - ptrPrevAlloc);

	_boundsChecker.guardFront(p.asVoid(), nLostBytes);
	p += (offset + size);
	_boundsChecker.guardBack(p.asVoid(), static_cast<std::uint32_t>(size));
	_boundsChecker.checkAllGuards(_allocator->current(), _allocator->begin());

	p-= size;
	return p.asVoid();
      }
    }
  }

  template<class AllocationPolicy, class BoundsCheckingPolicy>
  void MemoryArena<AllocationPolicy, BoundsCheckingPolicy>::deallocate(void* ptr, std::size_t size)
  {
    // Simply deallocate memory if no bounds checking is required.
    if constexpr (std::is_same_v<BoundsCheckingPolicy, VoidBoundsChecker>)
    {
      _allocator->deallocate(ptr, size);
    }
    else
    // The simple bounds checker checks the front and back guards of the current allocation before
    // releasing the memory. The extended bounds checker checks the guards of all allocations before
    // releasing the memory.
    {
      APtr<char> p{ptr};
      
      if constexpr (std::is_same_v<BoundsCheckingPolicy, BoundsChecker>)
      {
	p -= BoundsCheckingPolicy::FRONT_GUARD_SIZE;
	_boundsChecker.checkFront(p.asVoid());
	p += (BoundsCheckingPolicy::FRONT_GUARD_SIZE + size);
	_boundsChecker.checkBack(p.asVoid());
      }
      else
      {
	auto ptrPastAlloc = p + size + BoundsCheckingPolicy::BACK_GUARD_SIZE;
	_boundsChecker.checkAllGuards(static_cast<void*>(ptrPastAlloc), _allocator->begin());
      }
      
      _allocator->deallocate(p.asVoid(), size);
    }
  }

  
#if SEMPERVIRENS_BUILD(UNITTESTING)
  template<class AllocationPolicy, class BoundsCheckingPolicy>
  void MemoryArena<AllocationPolicy, BoundsCheckingPolicy>::Test()
  {  
    auto areaSize = std::size_t{SEMPERVIRENS_B(64)};
    
    char* stackArea[areaSize] = {0};
    auto area = StackArea{static_cast<void*>(stackArea), areaSize};
    //auto area = HeapArea{areaSize};
    auto allocator = LinearAllocator{area.begin(), area.size()};

    //auto arena = MemoryArena<LinearAllocator, VoidBoundsChecker>{&allocator, "Linear arena on stack"};
    //auto arena = MemoryArena<LinearAllocator, BoundsChecker>{&allocator, "Linear arena on stack"};
    auto arena = MemoryArena<LinearAllocator, ExtendedBoundsChecker>{&allocator, "Linear arena on stack"};

    struct MyObject
    {
      int _value;
      MyObject() { SEMPERVIRENS_MSG("MyObject default ctor"); }
      explicit MyObject(int val) : _value{val} { SEMPERVIRENS_MSG("MyObject ctor"); }
      ~MyObject() { SEMPERVIRENS_MSG("MyObject dtor"); }
    };

    struct MyPOD
    {
      int _value;
    };

    
    Block<MyObject> myBlock = SEMPERVIRENS_NEW_ARRAY(MyObject, arena, 2);

    SEMPERVIRENS_MSG("First object allocated at " << static_cast<void*>(myBlock._ptr));
    allocator.dumpMemory();

    MyObject* objects = myBlock._ptr;
    objects[0]._value = 1;
    objects[1]._value = 2;

    allocator.dumpMemory();
    

    Block<MyPOD> myBlock2 = SEMPERVIRENS_NEW(MyPOD, arena, 3);

    allocator.dumpMemory();
    
    SEMPERVIRENS_DELETE(myBlock2, arena);
    SEMPERVIRENS_DELETE_ARRAY(myBlock, arena);

    allocator.reset();
    allocator.dumpMemory();

  }
#endif
}
