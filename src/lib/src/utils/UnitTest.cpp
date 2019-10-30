#define UNITTEST_CPP
#include <utils/UnitTest.hpp>

namespace dog::utils {

  void test(UnitTest const& unitTest)
  {
    unitTest._self->_test();
  }
  
}
