#ifndef DYNAMICLIBS_HPP
#define DYNAMICLIBS_HPP
#include <Platform/Platform.hpp>
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

  dlib_t load(std::string libname);
  void release(dlib_t lib);
  symb_t getSymbol(dlib_t lib, std::string symbol);
}
#endif
