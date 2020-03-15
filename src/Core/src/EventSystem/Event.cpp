#define EVENT_CPP
#include <EventSystem/Event.hpp>

namespace sempervirens::core::event {

  EventListener WindowCloseEvent::_listeners[nMaxListeners];
  int WindowCloseEvent::_nListeners{0};

  EventListener WindowExposeEvent::_listeners[nMaxListeners];
  int WindowExposeEvent::_nListeners{0};

  EventListener WindowResizeEvent::_listeners[nMaxListeners];
  int WindowResizeEvent::_nListeners{0};
  WindowResizeEvent::WindowResizeEvent(int width, int height) : _width{width}, _height{height} {}

  EventListener WindowMoveEvent::_listeners[nMaxListeners];
  int WindowMoveEvent::_nListeners{0};
  WindowMoveEvent::WindowMoveEvent(int xPos, int yPos) : _xPos{xPos}, _yPos{yPos} {}

  EventListener WindowFocusInEvent::_listeners[nMaxListeners];
  int WindowFocusInEvent::_nListeners{0};
  EventListener WindowFocusOutEvent::_listeners[nMaxListeners];
  int WindowFocusOutEvent::_nListeners{0};

  EventListener KeyPressEvent::_listeners[nMaxListeners];
  int KeyPressEvent::_nListeners{0};
  KeyPressEvent::KeyPressEvent(sempervirens::input::keyboard::Keysym symbol, sempervirens::input::keyboard::Keychr chr) : _symbol{symbol}, _chr{chr} {}
  
  EventListener KeyReleaseEvent::_listeners[nMaxListeners];
  int KeyReleaseEvent::_nListeners{0};
  KeyReleaseEvent::KeyReleaseEvent(sempervirens::input::keyboard::Keysym symbol, sempervirens::input::keyboard::Keychr chr) : _symbol{symbol}, _chr{chr} {}
  
  EventListener MouseMoveEvent::_listeners[nMaxListeners];
  int MouseMoveEvent::_nListeners{0};
  MouseMoveEvent::MouseMoveEvent(int xPos, int yPos) : _xPos{xPos}, _yPos{yPos} {}  
}
