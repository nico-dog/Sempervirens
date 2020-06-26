#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <Window/Window.hpp>
#include <Keyboard/Keyboard.hpp>
#include <EventSystem/Event.hpp>
#include <MemoryAlloc/MemoryArea.hpp>
#include <MemoryAlloc/MemoryArena.hpp>
#include <MemoryAlloc/LinearAllocator.hpp>
#include <MemoryAlloc/BoundsCheckingPolicy.hpp>

namespace sempervirens::app
{
  class Application
  {
    Window_t* _window{nullptr};
    Keyboard_t* _keyboard{nullptr};
    
    bool _appIsRunning{true};

    
  public:
    Application();
    virtual ~Application() { SEMPERVIRENS_MSG("Application dtor"); };

    Application(Application const&) = delete;
    Application& operator=(Application const&) = delete;

    inline void setWindow(Window_t* window) { _window = window; }
    inline void setKeyboard(Keyboard_t* keyboard) { _keyboard = keyboard; }
    void run();
    void onEvent(sempervirens::eventsystem::Event& event);
  };

  // TO BE DEFINED BY CLIENT FOR USE IN ENTRY POINT.
  using namespace sempervirens::memoryalloc;
  using Arena_t = MemoryArena<LinearAllocator, VoidBoundsChecker>;
  Block<Application> createApplication(Arena_t& arena);
}
#endif
