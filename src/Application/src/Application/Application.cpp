#define APPLICATION_CPP
#include <Application/Application.hpp>
#include <Interface/KeySymbols.hpp>
#include <Keyboard/Keyboard.hpp>
#include <Logging/Logger.hpp>

using namespace sempervirens::window;
using namespace sempervirens::input::keyboard;
using namespace sempervirens::core::event;

namespace sempervirens::app
{
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
    SEMPERVIRENS_LISTEN(this, KeyPressEvent);
    SEMPERVIRENS_LISTEN(this, KeyReleaseEvent);
    SEMPERVIRENS_LISTEN(this, MouseMoveEvent);
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
    if (event.type() == EventType::WindowClosed)
    {
      _appIsRunning = false;
      SEMPERVIRENS_MSG("Received WindowCloseEvent");
      return;
    }

    if (event.type() == EventType::WindowExposed)
    {
      //SEMPERVIRENS_MSG("Received WindowExposeEvent");
      return;
    }    

    if (event.type() == EventType::WindowResized)
    {
      //auto& e = static_cast<WindowResizeEvent&>(event);
      //SEMPERVIRENS_MSG("Received WindowResizeEvent for width: " << e._width << ", height: " << e._height);
      return;
    }

    if (event.type() == EventType::WindowMoved)
    {
      //auto& e = static_cast<WindowMoveEvent&>(event);
      //SEMPERVIRENS_MSG("Received WindowMoveEvent for xPos: " << e._xPos << ", yPos: " << e._yPos);
      return;
    }

    if (event.type() == EventType::WindowFocusedIn)
    {
      //SEMPERVIRENS_MSG("Received WindowFocusInEvent");
      return;
    }

    if (event.type() == EventType::WindowFocusedOut)
    {
      //SEMPERVIRENS_MSG("Received WindowFocusOutEvent");
      return;
    }


    if (event.type() == EventType::KeyPressed)
    {
      auto& e = static_cast<KeyPressEvent&>(event);
      SEMPERVIRENS_MSG("Received KeyPressEvent for " << e._chr << ", with modifier: " << e._mod);

      if (e._symbol == KEY_q && e._mod == CTRL())
	_appIsRunning = false;
      /*
      if (e._symbol == KEY_1)
	SEMPERVIRENS_MSG("Received KeyPressEvent " << e._chr);
      if (e._symbol == KEY_A)
	SEMPERVIRENS_MSG("Received KeyPressEvent " << e._chr);
      if (e._symbol == KEY_a)
	SEMPERVIRENS_MSG("Received KeyPressEvent " << e._chr);
      */
      return;
    }

    if (event.type() == EventType::KeyReleased)
    {
      auto& e = static_cast<KeyReleaseEvent&>(event);
      SEMPERVIRENS_MSG("Received KeyReleaseEvent " << e._chr<< ", with modifier: " << e._mod);
      /*
      if (e._symbol == KEY_1)
	SEMPERVIRENS_MSG("Received KeyReleaseEvent " << e._chr);
      if (e._symbol == KEY_A)
	SEMPERVIRENS_MSG("Received KeyReleaseEvent " << e._chr);
      if (e._symbol == KEY_a)
	SEMPERVIRENS_MSG("Received KeyReleaseEvent " << e._chr);
      */
      return;
    }    

    if (event.type() == EventType::MouseMoved)
    {
      //auto& e = static_cast<MouseMoveEvent&>(event);
      //SEMPERVIRENS_MSG("Received MouseMoveEvent for xPos: " << e._xPos << ", yPos: " << e._yPos);
      return;
    }
    
  }


}
