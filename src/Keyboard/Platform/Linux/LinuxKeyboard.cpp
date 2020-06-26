#define LINUXKEYBOARD_CPP
#include <Keyboard/Platform/Linux/LinuxKeyboard.hpp>
#include <Logging/Logger.hpp>

using namespace sempervirens::eventsystem;

namespace sempervirens::keyboard
{
  LinuxKeyboard::LinuxKeyboard()
  {
    SEMPERVIRENS_MSG("LinuxKeyboard ctor, size of LinuxKeyboard: " << sizeof(LinuxKeyboard));

    SEMPERVIRENS_LISTEN(this, KeyPressedEvent);
    SEMPERVIRENS_LISTEN(this, KeyReleasedEvent);
  }

  LinuxKeyboard::~LinuxKeyboard()
  {
    SEMPERVIRENS_MSG("LinuxKeyboard dtor");
  }

  void LinuxKeyboard::onEvent(Event& event)
  {
    if (event.type() == EventType::KeyPressed)
    {
      auto& e = static_cast<KeyPressedEvent&>(event);
      _currkey = e._symbol;
      _mod = e._mod;
      _triggered = true;
      return;
    }

    if (event.type() == EventType::KeyReleased)
    {
      auto& e = static_cast<KeyReleasedEvent&>(event);
      _prevkey = e._symbol;
      _currkey = 0;
      _mod = e._mod;
      _triggered = true;
      return;
    }    
  }

  void LinuxKeyboard::onUpdate()
  {
    _prevkey = _currkey;
    _triggered = false;
  }
  
  bool LinuxKeyboard::wentDown(Keysym key)
  {
    return key == _currkey && key != _prevkey;
  }
  
  bool LinuxKeyboard::isPressed(Keysym key)
  {
    return _triggered && key == _currkey && key == _prevkey;
    //return key == _currkey && key == _prevkey;
  }
  
  bool LinuxKeyboard::wentUp(Keysym key)
  {
    return key != _currkey && key == _prevkey;
  }
}
