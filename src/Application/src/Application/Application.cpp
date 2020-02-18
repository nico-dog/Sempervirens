#define APPLICATION_CPP
#include <Application/Application.hpp>
#include <Logging/Logger.hpp>

using namespace sempervirens::window;

namespace sempervirens::app {


  Application::Application()
  {
    auto windowInfo = WindowInfo{"Sempervirens Application", 0, 0, 1.f / 2, 2.f / 3};
    _window = std::unique_ptr<IWindow>(IWindow::createWindow(windowInfo));
  }
  
  void Application::run()
  {
    SEMPERVIRENS_MSG("Sempervirens application is running");

    while (_appIsRunning)
    {
      _window->onUpdate();
    }
  }

  void Application::onEvent()
  {
  }
}
