#ifndef UNITTESTREGISTER_HPP
#define UNITTESTREGISTER_HPP
#include <utils/UnitTest.hpp>
#include <memory>

#define DOG_TESTTYPE(type) [](){ type::test(); }
#define DOG_TESTCLBL(func, ...) \
  dog::utils::createUnitTest(func, ##__VA_ARGS__)

namespace dog::utils {

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
