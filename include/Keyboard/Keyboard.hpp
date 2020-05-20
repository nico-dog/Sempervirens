#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include <Keyboard/KeySymbols.hpp>

namespace sempervirens::keyboard
{
  //struct Key
  //{
  //  Keysym _symbol;
  //  Keychr _chr;
  //};

  using KeyModifier = unsigned int;
  //namespace keyModifier
  //{
#define NONE() 0
#define SHIFT() 1
#define LOCK() 2
#define CTRL() 3
  //}
  
  class Keyboard
  {
  public:
    Keyboard() = default;
    ~Keyboard() = default;

    bool wentDown(Keysym key);
    bool isPressed(Keysym key);
    bool wentUp(Keysym key);
  };
}
#endif
