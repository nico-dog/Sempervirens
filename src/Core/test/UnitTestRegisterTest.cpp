#include <UnitTesting/UnitTestRegister.hpp>
#include <Logging/ConsoleLogger.hpp>
#include <fstream>

class TestableType {
  
  int _val{0};
  
public:
  void print() const { SEMPERVIRENS_MSG("TestableType::print: " << _val); }
  void add(int n) { SEMPERVIRENS_MSG("TestableType::add: " << n); _val += n; }

#if SEMPERVIRENS_BUILD(UNITTESTING)
  void static test() {

    TestableType t{};
    t.print();
    t.add(2);
    t.print();
  }
#endif
};

class MyType {
  
  int _val{0};
  
public:
  void print() const { SEMPERVIRENS_MSG("MyType::print: " << _val); }
  void add(int n) { SEMPERVIRENS_MSG("MyType::add: " << n); _val += n; }
};

auto closure = [](int val){ SEMPERVIRENS_MSG("closure, arg: " << val); };
void freeFunction0() { SEMPERVIRENS_MSG("free function, no arg"); }
void freeFunction1(int val) { SEMPERVIRENS_MSG("free function1, arg: " << val); }

class MyTest {

public:

  MyTest(std::string filename) : _pFile{std::make_unique<std::ofstream>(std::move(filename))} {}
  
  void operator()() const {

    SEMPERVIRENS_MSG("MyTest");
    *_pFile << "...\n";
  }

  std::unique_ptr<std::ofstream> _pFile;
};

int main() {

  auto logger = sempervirens::core::log::ConsoleLogger{};
  
  auto reg = sempervirens::core::unittesting::UnitTestRegister();

  // push test for type providing a static test() method
  reg.push(SEMPERVIRENS_TESTTYPE(TestableType));

  // push test for closure
  reg.push(SEMPERVIRENS_TESTCLBL(closure, 2));

  // push tests for free functions
  reg.push(SEMPERVIRENS_TESTCLBL(freeFunction0));
  reg.push(SEMPERVIRENS_TESTCLBL(freeFunction1, 10));

  // push tests for member functions
  MyType t;
  reg.push(SEMPERVIRENS_TESTCLBL(&MyType::add, std::ref(t), 10));
  reg.push(SEMPERVIRENS_TESTCLBL(&MyType::print, std::ref(t)));

  // push test for custom unit test
  reg.push(MyTest{"/home/nico/Desktop/MyTest.txt"});
  
  reg.run();
 
  return 0;
}

