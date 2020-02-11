#include <MemoryAlloc/MemoryArena.hpp>
#include <MemoryAlloc/LinearAllocator.hpp>
#include <UnitTesting/UnitTestRegister.hpp>

using namespace sempervirens::core::memoryalloc;

using LinearArena = MemoryArena<LinearAllocator, BoundsChecker>;

int main() {

  auto reg = sempervirens::core::unittesting::UnitTestRegister{};
  reg.push(SEMPERVIRENS_TESTTYPE(LinearArena));
  reg.run();
  
  return 0;
}
