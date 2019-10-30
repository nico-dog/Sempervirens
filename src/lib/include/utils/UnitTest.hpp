#ifndef UNITTEST_HPP
#define UNITTEST_HPP

#include <memory>

namespace dog::utils {

  class UnitTest {

    struct concept_t {

      virtual ~concept_t() = default;
      virtual void _test() const = 0;
    };

    template <typename T>
    struct model_t final : public concept_t {
      
      model_t(T&& data);

      void _test() const override;

      T _data;
    };
    
    std::shared_ptr<concept_t const> _self;

  public:
    template<typename T>
    UnitTest(T&& impl);

    UnitTest(UnitTest const&) = default;
    UnitTest& operator=(UnitTest const&) = default;
    UnitTest(UnitTest&&) noexcept = default;
    UnitTest& operator=(UnitTest&&) noexcept = default;
    
    friend void test(UnitTest const& unitTest);
  };

  template<typename F, typename... Args>
  UnitTest createUnitTest(F&& func, Args&&... args);
}
#include <utils/UnitTest.inl>
#endif
