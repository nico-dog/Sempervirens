#include <UnitTesting/UnitTestRegister.hpp>
#include <Logging/Logger.hpp>
#include <fstream>

class TestableType {
  
  int _val{0};
  
public:
  void print() const { DOG_LOGMSG("TestableType::print: " << _val); }
  void add(int n) { DOG_LOGMSG("TestableType::add: " << n); _val += n; }

#if DOG_BUILD(UNITTESTS)
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
  void print() const { DOG_LOGMSG("MyType::print: " << _val); }
  void add(int n) { DOG_LOGMSG("MyType::add: " << n); _val += n; }
};

auto closure = [](int val){ DOG_LOGMSG("closure, arg: " << val); };
void freeFunction0() { DOG_LOGMSG("free function, no arg"); }
void freeFunction1(int val) { DOG_LOGMSG("free function1, arg: " << val); }

class MyTest {

public:

  MyTest(std::string filename) : _pFile{std::make_unique<std::ofstream>(std::move(filename))} {}
  
  void operator()() const {

    DOG_LOGMSG("MyTest");
    *_pFile << "...\n";
  }

  std::unique_ptr<std::ofstream> _pFile;
};

int main() {
  
  auto reg = dog::utilities::unittesting::UnitTestRegister();

  // push test for type providing a static test() method
  reg.push(DOG_TESTTYPE(TestableType));

  // push test for closure
  reg.push(DOG_TESTCLBL(closure, 2));

  // push tests for free functions
  reg.push(DOG_TESTCLBL(freeFunction0));
  reg.push(DOG_TESTCLBL(freeFunction1, 10));

  // push tests for member functions
  MyType t;
  reg.push(DOG_TESTCLBL(&MyType::add, std::ref(t), 10));
  reg.push(DOG_TESTCLBL(&MyType::print, std::ref(t)));

  // push test for custom unit test
  reg.push(MyTest{"/home/nico/Desktop/MyTest.txt"});
  
  reg.run();
 
  return 0;
}

