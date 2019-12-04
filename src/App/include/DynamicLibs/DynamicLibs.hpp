//***************************************************
//
// Definition of dlibs namespace:
// The namespace provides a platform-indepedent interface for loading dynamic libraries
// (i.e., HAL, "Hardware Abstraction Layer")
// Different implementations are provided for different platforms.
//
//***************************************************
#ifndef DYNAMICLIBS_HPP
#define DYNAMICLIBS_HPP
#include <Platform/Platform.hpp>
#include <optional>
#include <string>

namespace dog::app::dlibs {

#if DOG_PLATFORM(UNIX)
  using dlib_t = void*;
  using symb_t = void*;
#elif DOG_PLATFORM(WIN32)
  using dlib_t = void*;
#elif DOG_PLATFORM(APPLE)
  using dlib_t = void*;
#endif

  std::optional<dlib_t> load(std::string libname);
  void release(dlib_t lib);
  std::optional<symb_t> getSymbol(dlib_t lib, std::string symbol);
}
#endif
