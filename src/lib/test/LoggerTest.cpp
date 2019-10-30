#include <utils/Logger.hpp>
#include <utils/UnitTestRegister.hpp>

int main() {

  auto reg = dog::utils::UnitTestRegister{};

  reg.push(DOG_TESTTYPE(dog::utils::Logger));

  reg.run();

  return 0;
}
