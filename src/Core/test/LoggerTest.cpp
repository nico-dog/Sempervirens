#include <Logging/ConsoleLogger.hpp>
#include <UnitTesting/UnitTestRegister.hpp>

int main(int argc, char* argv[]) {
  
  auto reg = sempervirens::core::unittesting::UnitTestRegister{};
  reg.push(SEMPERVIRENS_TESTTYPE(sempervirens::core::logging::ConsoleLogger));
  reg.run();

  return 0;
}
