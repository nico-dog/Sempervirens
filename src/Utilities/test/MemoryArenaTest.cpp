#include <MemoryAlloc/MemoryArena.hpp>
#include <MemoryAlloc/LinearAllocator.hpp>
#include <UnitTesting/UnitTestRegister.hpp>

using namespace dog::utilities::memoryalloc;

using LinearArena = MemoryArena<LinearAllocator>;

int main() {

  auto reg = dog::utilities::unittesting::UnitTestRegister{};

  //reg.push(DOG_TESTTYPE(dog::utilities::memoryalloc::MemoryArena<LinearAllocator>));
  reg.push(DOG_TESTTYPE(LinearArena));

  reg.run();
  
  return 0;
}
