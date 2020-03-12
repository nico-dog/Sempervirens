#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <Interface/IWindow.hpp>
#include <EventSystem/Event.hpp>

namespace sempervirens::app {

  class Application {

    std::unique_ptr<sempervirens::window::IWindow> _window{nullptr};
    bool _appIsRunning{true};
    
  public:
    Application();
    virtual ~Application() {};

    Application(Application const&) = delete;
    Application& operator=(Application const&) = delete;

    void run();
    void onEvent(sempervirens::core::event::Event& event);

  };

  // TO BE DEFINED BY CLIENT.
  Application* createApplication();
}
#endif
