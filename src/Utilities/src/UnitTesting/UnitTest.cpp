#define UNITTEST_CPP
#include <UnitTesting/UnitTest.hpp>

namespace dog::utilities::unittesting {

  void test(UnitTest const& unitTest)
  {
    unitTest._self->_test();
  }
  
}
