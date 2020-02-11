//***************************************************
//
// Definition of UnitTestRegister object
// The UnitTestRegister holds a container of UnitTest objects.
//
//***************************************************
#ifndef UNITTESTREGISTER_HPP
#define UNITTESTREGISTER_HPP
#include <UnitTesting/UnitTest.hpp>
#include <Macros/Build.hpp>
//#include <memory>

#define SEMPERVIRENS_TESTTYPE(type) [](){ type::test(); }
#define SEMPERVIRENS_TESTCLBL(func, ...) \
  sempervirens::core::unittesting::createUnitTest(func, ##__VA_ARGS__)

namespace sempervirens::core::unittesting {

  class UnitTestRegister {

    class UnitTestRegisterImpl;
    std::unique_ptr<UnitTestRegisterImpl, void(*)(UnitTestRegisterImpl*)> _pImpl;

  public:

    UnitTestRegister();
    
    void push(UnitTest test);
    void run();
  };
}
#endif
