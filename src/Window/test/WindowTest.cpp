#include <Backend/Linux/LinuxWindow.hpp>
#include <UnitTesting/UnitTestRegister.hpp>

int main(int argc, char* argv[]) {
  
  auto reg = sempervirens::core::unittesting::UnitTestRegister{};
  reg.push(SEMPERVIRENS_TESTTYPE(sempervirens::window::LinuxWindow));
  reg.run();

  return 0;
}
