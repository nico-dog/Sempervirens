//***************************************************
//
// Definition of Singleton object:
// The Singleton object is a generic wrapper for the singleton pattern.
// Classes that need to provide the singleton functionality do it with the CRTP pattern.
// Note: these classes need to declare the Singleton<> template as a friend class (for access to private ctor).
//
//***************************************************
#ifndef SINGLETON_HPP
#define SINGLETON_HPP

namespace dog::utilities::logging {

  template<typename T>
  class Singleton {

  protected:
    Singleton() = default;

  public:
    Singleton(Singleton const&) = delete;
    Singleton& operator=(Singleton const&) = delete;

    static T& instance();
  };
}

#include <Logging/Singleton.inl>
#endif
