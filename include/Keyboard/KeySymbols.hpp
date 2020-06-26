#ifndef KEYSYMBOLS_HPP
#define KEYSYMBOLS_HPP
#include <Macros/Platform.hpp>

#if SEMPERVIRENS_PLATFORM(UNIX)
#include <Keyboard/Platform/Linux/LinuxKeySymbols.hpp>

namespace sempervirens::keyboard
{ 
  using Keysym = KeySym;
  using Keychr = char*;
  using Keymod = unsigned int;
#define NONE() 0
#define SHIFT() 1
#define LOCK() 2
#define CTRL() 3
}
#endif

#endif
