#ifndef UNITTEST_INL
#define UNITTEST_INL

namespace dog::utils {

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
