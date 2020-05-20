#include <MemoryAlloc/MemoryArena.hpp>
#include <MemoryAlloc/LinearAllocator.hpp>
#include <UnitTesting/UnitTestRegister.hpp>

using namespace sempervirens::memoryalloc;

using LinearArena = MemoryArena<LinearAllocator, BoundsChecker>;

int main() {

  auto reg = sempervirens::unittesting::UnitTestRegister{};
  reg.push(SEMPERVIRENS_TESTTYPE(LinearArena));
  reg.run();
  
  return 0;
}
