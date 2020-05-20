#include <Logging/Logger.hpp>

namespace sempervirens::event
{
  template<typename T>
  EventListener createListener(T* obj)
  {
    EventListener d;
    d.Bind<T, &T::onEvent>(obj);
    return d;
  }

  template<typename Event>
  void addListener(EventListener listener)
  {
    assert(Event::_nListeners < nMaxListeners);

    for (auto i = 0; i < Event::_nListeners; ++i)
    {
      if (listener == Event::_listeners[i])
      {
	SEMPERVIRENS_WRN("Trying to add existing listener.");
	return;
      }
    }
    Event::_listeners[Event::_nListeners++] = listener;    
  }

  template<typename Event>
  void removeListener(EventListener listener)
  {
    for (auto i = 0; i < Event::_nListeners; ++i)
    {
      if (listener == Event::_listeners[i])
      {
	std::swap(listener, Event::_listeners[Event::_nListeners - 1]);
      }
    }
    --Event::_nListeners;
  }

  template<typename Event>
  void signal(Event& event)
  {
    for (auto i = 0; i < Event::_nListeners; ++i)
      Event::_listeners[i].Invoke(event);    
  }

}
