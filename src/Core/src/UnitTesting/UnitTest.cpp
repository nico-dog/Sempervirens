#define UNITTEST_CPP
#include <UnitTesting/UnitTest.hpp>

namespace sempervirens::core::unittesting {

  void test(UnitTest const& unitTest)
  {
    unitTest._self->_test();
  }
  
}
