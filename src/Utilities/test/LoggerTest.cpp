#include <Logging/Logger.hpp>
#include <UnitTesting/UnitTestRegister.hpp>

int main() {

  auto reg = dog::utilities::unittesting::UnitTestRegister{};

  reg.push(DOG_TESTTYPE(dog::utilities::logging::Logger));

  reg.run();

  return 0;
}
