#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include <Interface/KeySymbols.hpp>

namespace sempervirens::input::keyboard {

  struct Key {

    Keysym _symbol;
    Keychr _chr;
  };
  
  class Keyboard {

  public:
    Keyboard() = default;
    ~Keyboard() = default;

    bool wentDown(Key key);
    bool isPressed(Key key);
    bool wentUp(Key key);
  };
}
#endif
