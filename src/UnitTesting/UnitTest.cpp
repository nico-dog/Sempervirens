#define UNITTEST_CPP
#include <UnitTesting/UnitTest.hpp>

namespace sempervirens::unittesting
{
  void test(UnitTest const& unitTest)
  {
    unitTest._self->_test();
  }
  
}
