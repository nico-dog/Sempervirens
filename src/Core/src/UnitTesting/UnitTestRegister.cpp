#define UNITTESTREGISTER_CPP
#include <UnitTesting/UnitTestRegister.hpp>
#include <Logging/ConsoleLogger.hpp>

namespace sempervirens::core::unittesting
{
  class UnitTestRegister::UnitTestRegisterImpl
  {
  public:
    UnitTestRegisterImpl() = default;

    std::vector<UnitTest> _unitTests;
    
    sempervirens::core::logging::ConsoleLogger _logger;
  };

  UnitTestRegister::UnitTestRegister() : _pImpl{new UnitTestRegisterImpl{}, [](UnitTestRegisterImpl* ptr){ delete ptr; }} {}

  void UnitTestRegister::push(UnitTest unitTest)
  {
    _pImpl->_unitTests.emplace_back(std::move(unitTest));
  }
  
  void UnitTestRegister::run()
  {  
    for (auto const& unitTest : _pImpl->_unitTests) test(unitTest);
  }
}
