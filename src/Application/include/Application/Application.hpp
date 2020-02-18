#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <Interface/IWindow.hpp>

namespace sempervirens::app {

  class Application {

    std::unique_ptr<sempervirens::window::IWindow> _window{nullptr};
    bool _appIsRunning{true};
    
  public:
    Application();
    virtual ~Application() {};

    void run();
    void onEvent();
  };

  // To be defined by client.
  Application* createApplication();
}
#endif
