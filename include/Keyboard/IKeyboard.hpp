#ifndef IKEYBOARD_HPP
#define IKEYBOARD_HPP
#include <Interface/KeySymbols.hpp>

namespace sempervirens::input::keyboard
{
  class IKeyboard
  {
  public:
    virtual ~IKeyboard() = default;

    virtual bool wentDown(Keysym key) = 0;
    virtual bool isPressed(Keysym key) = 0;
    virtual bool wentUp(Keysym key) = 0;


    // Definition provided by backend implementations.
    static IKeyboard* CreateKeyboard();
  };
}
#endif
