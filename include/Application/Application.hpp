#ifndef APPLICATION_HPP
#define APPLICATION_HPP
//#include <Interface/IWindow.hpp>
#include <EventSystem/Event.hpp>
#include <Macros/Build.hpp>

//#if SEMPERVIRENS_PLATFORM(UNIX)
//#include <Backend/Linux/LinuxWindow.hpp>
//#endif
#include <Window/Window.hpp>

#include <MemoryAlloc/MemoryArea.hpp>
#include <MemoryAlloc/MemoryArena.hpp>
#include <MemoryAlloc/LinearAllocator.hpp>
#include <MemoryAlloc/BoundsCheckingPolicy.hpp>

namespace sempervirens::app
{
  class Application
  {
    std::unique_ptr<Window_t> _window{nullptr};
    bool _appIsRunning{true};

    void _processInputs();
    
  public:
    Application();
    virtual ~Application() { SEMPERVIRENS_MSG("Application dtor"); };

    Application(Application const&) = delete;
    Application& operator=(Application const&) = delete;

    void run();
    void onEvent(sempervirens::event::Event& event);
  };

  // TO BE DEFINED BY CLIENT.
  using namespace sempervirens::memoryalloc;
  using Arena_t = MemoryArena<LinearAllocator, VoidBoundsChecker>;
  Block<Application> createApplication(Arena_t& arena);
}
#endif
