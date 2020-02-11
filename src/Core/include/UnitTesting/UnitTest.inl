//***************************************************
//
// Definition of UnitTest object
// UnitTest is a polymorphics wrapper for the concept of being testable.
// A type is testable of it provides a free test() function and a call operator.
//
//***************************************************
#ifndef UNITTEST_INL
#define UNITTEST_INL

namespace sempervirens::core::unittesting {

  template<typename T>
  void test(T const& unitTest) {

    unitTest();
  }

  template<typename T>
  UnitTest::model_t<T>::model_t(T&& data) : _data{std::forward<T>(data)} {}
  
  template <typename T>
  void UnitTest::model_t<T>::_test() const {

    test(_data);
  }

  template<typename T>
  UnitTest::UnitTest(T&& impl) : _self(std::make_shared<model_t<T>>(std::forward<T>(impl))) {}

  template<typename F, typename... Args>
  UnitTest createUnitTest(F&& func, Args&&... args) {

    return [_func = std::forward<F>(func),
	    _args = std::make_tuple(std::forward<Args>(args)...)]() 
           {
	     std::apply(_func, _args);
	   };
  }
  
}
#endif
