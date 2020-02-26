#define LINUXWWINDOW_CPP
#include <Backend/Linux/LinuxWindow.hpp>
#include <Logging/Logger.hpp>
#include <EventSystem/Event.hpp>

namespace sempervirens::window {

  LinuxWindow::LinuxWindow(WindowInfo const& windowInfo)
  {
    initDisplay(windowInfo);
  }

  LinuxWindow::~LinuxWindow()
  {
    XCloseDisplay(_display);
  }

  bool LinuxWindow::initDisplay(WindowInfo const& windowInfo)
  {
    // Connect to the display of the machine the client code runs on (local display).
    _display = XOpenDisplay(getenv("DISPLAY")); 
    if (!_display)
    {
      SEMPERVIRENS_ERR("Cannot connect to X server");
      return false;
    }

    
    // Get screen information.
    _screen._id = DefaultScreen(_display);
    _screen._width = DisplayWidth(_display, _screen._id);
    _screen._height = DisplayHeight(_display, _screen._id);
    _screen._rootWindow = RootWindow(_display, _screen._id);
    _screen._whitePixel = WhitePixel(_display, _screen._id);
    _screen._blackPixel = BlackPixel(_display, _screen._id);
    SEMPERVIRENS_MSG("Screen info:\n .. id: " << _screen._id << 
		     "\n .. width: " << _screen._width <<
		     "\n .. height: " << _screen._height <<
		     "\n .. root window id: " << _screen._rootWindow);

    
    // Create the window.
    _window = XCreateSimpleWindow(_display,
				  _screen._rootWindow,
				  windowInfo._xPos, windowInfo._yPos,
				  windowInfo._widthRatio * _screen._width, windowInfo._heightRatio * _screen._height,
				  1, _screen._blackPixel, // 1 pixel wide black border
				  _screen._whitePixel);   // white background

    XStoreName(_display, _window, windowInfo._title.c_str());

    //auto gc = XCreateGC(_display, _window, 0,0);        
    //XSetBackground(_display, gc, _screen._whitePixel);
    //XSetForeground(_display, gc, _screen._blackPixel);
    
    // Set event masks.
    XSelectInput(_display, _window,
		 ExposureMask        |  // For exposure events.
		 StructureNotifyMask |  // For resize and move events.
		 FocusChangeMask     |  // For focus in and out events.
		 KeyPressMask);         // For key press/release events.

    // Catch window close event from window manager.
    Atom wmDeleteMessage = XInternAtom(_display, "WM_DELETE_WINDOW", false);
    XSetWMProtocols(_display, _window, &wmDeleteMessage, 1);
    
    // Map window to screen.
    XClearWindow(_display, _window);
    XMapWindow(_display, _window);
    XFlush(_display);
    
    return true;
  }

  void LinuxWindow::pollEvent()
  {
    XEvent event;
    // If the event queue is empty, XNextEvent blocks till the next event is received.
    // Avoid blocking by checking is the queue contains events before calling XNextEvent.
    if (XEventsQueued(_display, QueuedAfterFlush))
      XNextEvent(_display, &event);
    else return;
    
    switch (event.type)
    {
    case ClientMessage:
    {
      Atom wmDeleteMessage = XInternAtom(_display, "WM_DELETE_WINDOW", false);
      if (event.xclient.data.l[0] == static_cast<long int>(wmDeleteMessage))
      {
	sempervirens::core::event::WindowCloseEvent closeEvent;
	SEMPERVIRENS_SIGNAL(closeEvent);
      }
      break;
    }

    case Expose:
    {
      sempervirens::core::event::WindowExposeEvent exposeEvent{};
      SEMPERVIRENS_SIGNAL(exposeEvent);
      break;
    }
    
    case ConfigureNotify:
    {
      XConfigureEvent config = event.xconfigure;
      if (config.width != _width || config.height != _height)
      {
	sempervirens::core::event::WindowResizeEvent resizeEvent{config.width, config.height};
	SEMPERVIRENS_SIGNAL(resizeEvent);
	_width = config.width;
	_height = config.height;
	break;
      }
      if (config.x != _xPos || config.y != _yPos)
      {
	sempervirens::core::event::WindowMoveEvent moveEvent{config.x, config.y};
	SEMPERVIRENS_SIGNAL(moveEvent);
	_xPos = config.x;
	_yPos = config.y;
	break;
      }
    }

    case FocusIn:
    {
      sempervirens::core::event::WindowFocusInEvent focusInEvent{};
      SEMPERVIRENS_SIGNAL(focusInEvent);
      break;
    }
    case FocusOut:
    {
      sempervirens::core::event::WindowFocusOutEvent focusOutEvent{};
      SEMPERVIRENS_SIGNAL(focusOutEvent);
      break;
    }    
      
    default:
      break;
    }
  }
    
  void LinuxWindow::onUpdate()
  {
    SEMPERVIRENS_MSG("Window update...");
  }

  IWindow* IWindow::createWindow(WindowInfo const& windowInfo)
  {
    SEMPERVIRENS_MSG("Create Linux window \"" << windowInfo._title << "\":" <<
		     "\n .. x pos: " << windowInfo._xPos <<
		     "\n .. y pos: " << windowInfo._yPos <<
		     "\n .. width ratio: " << windowInfo._widthRatio <<
		     "\n .. height ratio: " << windowInfo._heightRatio);
    
    return new LinuxWindow{windowInfo};
  }

#if SEMPERVIRENS_BUILD(UNITTESTING)
  void LinuxWindow::test()
  {
    auto windowInfo = WindowInfo{"Test Window", 0, 0, 1.0f / 2, 2.0f / 3};
    auto window = static_cast<LinuxWindow*>(createWindow(windowInfo));
    delete window;
  }
#endif
}
