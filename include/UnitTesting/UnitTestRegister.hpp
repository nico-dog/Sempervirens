#ifndef UNITTESTREGISTER_HPP
#define UNITTESTREGISTER_HPP
#include <UnitTesting/UnitTest.hpp>
#include <Macros/Build.hpp>

#define SEMPERVIRENS_TESTTYPE(type) [](){ type::Test(); }
#define SEMPERVIRENS_TESTCLBL(func, ...) \
  sempervirens::unittesting::createUnitTest(func, ##__VA_ARGS__)

namespace sempervirens::unittesting
{
  class UnitTestRegister
  {
    class UnitTestRegisterImpl;
    std::unique_ptr<UnitTestRegisterImpl, void(*)(UnitTestRegisterImpl*)> _pImpl;

  public:
    UnitTestRegister();
   
    void push(UnitTest test);
    void run();
  };
}
#endif
