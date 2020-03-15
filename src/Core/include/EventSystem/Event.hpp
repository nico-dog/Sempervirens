#ifndef EVENT_HPP
#define EVENT_HPP
#include <Interface/KeySymbols.hpp>

namespace sempervirens::core::event {

  // This is the delegate implementation from Stefan Reinhalter presented in
  // Game Engine Gems 3: http://www.gameenginegems.net/geg3.php
  // Just Added comparison operators.
  template <typename T>
  class Delegate {};

  template <typename R, typename... Args>
  class Delegate<R(Args...)>
  {
    using ProxyFunction = R (*)(void*, Args...);

    template <R (*Function)(Args...)>
    static inline R FunctionProxy(void*, Args... args)
    {
      return Function(std::forward<Args>(args)...);
    }

    template <class C, R (C::*Function)(Args...)>
    static inline R MethodProxy(void* instance, Args... args)
    {
      return (static_cast<C*>(instance)->*Function)(std::forward<Args>(args)...);
    }

    template <class C, R (C::*Function)(Args...) const>
    static inline R ConstMethodProxy(void* instance, Args... args)
    {
      return (static_cast<const C*>(instance)->*Function)(std::forward<Args>(args)...);
    }

  public:
    Delegate() : m_instance(nullptr), m_proxy(nullptr) {}

    template <R (*Function)(Args...)>
    void Bind(void)
    {
      m_instance = nullptr;
      m_proxy = &FunctionProxy<Function>;
    }

    template <class C, R (C::*Function)(Args...)>
    void Bind(C* instance)
    {
      m_instance = instance;
      m_proxy = &MethodProxy<C, Function>;
    }

    template <class C, R (C::*Function)(Args...) const>
    void Bind(const C* instance)
    {
      m_instance = const_cast<C*>(instance);
      m_proxy = &ConstMethodProxy<C, Function>;
    }

    R Invoke(Args... args) const
    {
      assert((m_proxy != nullptr) && "Cannot invoke unbound Delegate. Call Bind() first.");
      return m_proxy(m_instance, std::forward<Args>(args)...);
    }

    inline bool operator==(Delegate<R(Args...)> const& rhs) { return m_instance == rhs.m_instance && m_proxy == rhs.m_proxy; }
    inline bool operator!=(Delegate<R(Args...)> const& rhs) { return m_instance != rhs.m_instance && m_proxy != rhs.m_proxy; }
    
  private:
    void* m_instance;
    ProxyFunction m_proxy;
  };

  // Event types in Sempervirens.
  enum class EventType {

    WindowClosed,
    WindowExposed,
    WindowResized,
    WindowMoved,
    WindowFocusedIn,
    WindowFocusedOut,
    KeyPressed,
    KeyReleased,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved
  };
 
  // Event base class inherited by concrete event classes.
  class Event {
   
  public:
    virtual ~Event() {};

    virtual EventType type() const = 0;

  protected:
    Event() = default;
    
    bool _handled{false};
  };

  // An event listener is defined as a member method with signature <void (Event&)>.
  using EventListener = Delegate<void (Event&)>;
  constexpr int nMaxListeners{5};
  
  // Window events.
  // Window close event.
  class WindowCloseEvent : public Event {

  public:
    WindowCloseEvent() = default;
    ~WindowCloseEvent() = default;
    
    inline EventType type() const override { return EventType::WindowClosed; }

    static int _nListeners;
    static EventListener _listeners[nMaxListeners];
  };

  // Window expose event.
  class WindowExposeEvent : public Event {

  public:
    WindowExposeEvent() = default;
    ~WindowExposeEvent() = default;
    
    inline EventType type() const override { return EventType::WindowExposed; }

    static int _nListeners;
    static EventListener _listeners[nMaxListeners];
  }; 

  // Window resize event.
  class WindowResizeEvent : public Event {

  public:
    WindowResizeEvent(int width, int height);
    ~WindowResizeEvent() = default;
    
    inline EventType type() const override { return EventType::WindowResized; }

    int _width;
    int _height;
    
    static int _nListeners;
    static EventListener _listeners[nMaxListeners];
  };

  // Window move event.
  class WindowMoveEvent : public Event {

  public:
    WindowMoveEvent(int xPos, int yPos);
    ~WindowMoveEvent() = default;
    
    inline EventType type() const override { return EventType::WindowMoved; }

    int _xPos;
    int _yPos;
    
    static int _nListeners;
    static EventListener _listeners[nMaxListeners];
  };

  // Window focus in event.
  class WindowFocusInEvent : public Event {

  public:
    WindowFocusInEvent() = default;
    ~WindowFocusInEvent() = default;
    
    inline EventType type() const override { return EventType::WindowFocusedIn; }
    
    static int _nListeners;
    static EventListener _listeners[nMaxListeners];
  };

  // Window focus out event.
  class WindowFocusOutEvent : public Event {

  public:
    WindowFocusOutEvent() = default;
    ~WindowFocusOutEvent() = default;
    
    inline EventType type() const override { return EventType::WindowFocusedOut; }
    
    static int _nListeners;
    static EventListener _listeners[nMaxListeners];
  };

  // Key press event.
  class KeyPressEvent : public Event {

  public:
    KeyPressEvent(sempervirens::input::keyboard::Keysym symbol, sempervirens::input::keyboard::Keychr chr);
    ~KeyPressEvent() = default;
    
    inline EventType type() const override { return EventType::KeyPressed; }

    sempervirens::input::keyboard::Keysym _symbol;
    sempervirens::input::keyboard::Keychr _chr;
    
    static int _nListeners;
    static EventListener _listeners[nMaxListeners];    
  };


  // Key release event.
  class KeyReleaseEvent : public Event {

  public:
    KeyReleaseEvent(sempervirens::input::keyboard::Keysym symbol, sempervirens::input::keyboard::Keychr chr);
    ~KeyReleaseEvent() = default;
    
    inline EventType type() const override { return EventType::KeyReleased; }

    sempervirens::input::keyboard::Keysym _symbol;
    sempervirens::input::keyboard::Keychr _chr;
    
    static int _nListeners;
    static EventListener _listeners[nMaxListeners];    
  };  

  // Mouse move event.
  class MouseMoveEvent : public Event {

  public:
    MouseMoveEvent(int xPos, int yPos);
    ~MouseMoveEvent() = default;

    inline EventType type() const override { return EventType::MouseMoved; }

    int _xPos;
    int _yPos;

    static int _nListeners;
    static EventListener _listeners[nMaxListeners];       
  };

  // Listener helper functions 
  template<typename T>
  EventListener createListener(T* obj);

  template<typename Event>
  void addListener(EventListener listener);

  template<typename Event>
  void removeListener(EventListener listener);

  template<typename Event>
  void signal(Event& event);

  // Event system macros
#define SEMPERVIRENS_LISTEN(obj, event) (     \
        addListener<event>(createListener(obj)) \
)	
#define SEMPERVIRENS_IGNORE(obj, event) (        \
        removeListener<event>(createListener(obj)) \
)
#define SEMPERVIRENS_SIGNAL(event) signal(event);

}
#include <EventSystem/Event.inl>
#endif
