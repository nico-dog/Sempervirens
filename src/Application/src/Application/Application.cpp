#define APPLICATION_CPP
#include <Application/Application.hpp>
#include <Logging/Logger.hpp>

using namespace sempervirens::window;
using namespace sempervirens::core::event;

namespace sempervirens::app {


  Application::Application()
  {
    auto windowInfo = WindowInfo{"Sempervirens Application", 0, 0, 1.f / 2, 2.f / 3};
    _window = std::unique_ptr<IWindow>(IWindow::createWindow(windowInfo));

    SEMPERVIRENS_LISTEN(this, WindowCloseEvent);
    SEMPERVIRENS_LISTEN(this, WindowExposeEvent);
    SEMPERVIRENS_LISTEN(this, WindowResizeEvent);
    SEMPERVIRENS_LISTEN(this, WindowMoveEvent);
    SEMPERVIRENS_LISTEN(this, WindowFocusInEvent);
    SEMPERVIRENS_LISTEN(this, WindowFocusOutEvent);    
  }
  
  void Application::run()
  {
    SEMPERVIRENS_MSG("Sempervirens application is running");

    while (_appIsRunning)
    {
      _window->pollEvent();
      //_window->onUpdate();
    }
  }

  void Application::onEvent(Event& event)
  {
    if (event.type() == EventType::WindowClose)
    {
      _appIsRunning = false;
      SEMPERVIRENS_MSG("Received WindowCloseEvent");
      return;
    }

    if (event.type() == EventType::WindowExpose)
    {
      SEMPERVIRENS_MSG("Received WindowExposeEvent");
      return;
    }    

    if (event.type() == EventType::WindowResize)
    {
      auto e = static_cast<WindowResizeEvent*>(&event);
      SEMPERVIRENS_MSG("Received WindowResizeEvent for width: " << e->_width << ", height: " << e->_height);
      return;
    }

    if (event.type() == EventType::WindowMove)
    {
      auto e = static_cast<WindowMoveEvent*>(&event);
      SEMPERVIRENS_MSG("Received WindowMoveEvent for xPos: " << e->_xPos << ", yPos: " << e->_yPos);
      return;
    }

    if (event.type() == EventType::WindowFocusIn)
    {
      SEMPERVIRENS_MSG("Received WindowFocusInEvent");
      return;
    }

    if (event.type() == EventType::WindowFocusOut)
    {
      SEMPERVIRENS_MSG("Received WindowFocusOutEvent");
      return;
    }    
  }


}
