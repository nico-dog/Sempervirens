#define EVENT_CPP
#include <EventSystem/Event.hpp>
#include <Logging/Logger.hpp>

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
}
