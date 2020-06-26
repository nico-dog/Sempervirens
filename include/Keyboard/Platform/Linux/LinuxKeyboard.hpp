#ifndef LINUXKEYBOARD_HPP
#define LINUXKEYBOARD_HPP
#include <Keyboard/Platform/Linux/LinuxKeySymbols.hpp>
#include <EventSystem/Event.hpp>

namespace sempervirens::keyboard
{
  class LinuxKeyboard
  {
    Keysym _prevkey{0};
    Keysym _currkey{0};
    Keymod _mod{0};
    //Keychr _chr{nullptr};
    bool _triggered{false};
    
  public:
    LinuxKeyboard();
    ~LinuxKeyboard();

    void onEvent(sempervirens::eventsystem::Event& event);

    inline void processInput() {}
    void onUpdate();

    bool wentDown(Keysym key);
    bool isPressed(Keysym key);
    bool wentUp(Keysym key);
  };  
}
#endif
