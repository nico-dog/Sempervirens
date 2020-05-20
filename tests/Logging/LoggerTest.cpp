#include <Logging/ConsoleLogger.hpp>
#include <UnitTesting/UnitTestRegister.hpp>

int main(int argc, char* argv[]) {
  
  auto reg = sempervirens::unittesting::UnitTestRegister{};
  reg.push(SEMPERVIRENS_TESTTYPE(sempervirens::logging::ConsoleLogger));
  reg.run();

  return 0;
}
