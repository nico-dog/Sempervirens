#define LINUXWWINDOW_CPP
#include <Window/Platform/Linux/LinuxWindow.hpp>
#include <Keyboard/Platform/Linux/LinuxKeySymbols.hpp>
#include <Logging/Logger.hpp>
#include <EventSystem/Event.hpp>
#include <X11/XKBlib.h>

using namespace sempervirens::eventsystem;

namespace sempervirens::window
{
  //LinuxWindow::LinuxWindow(WindowInfo const& windowInfo)
  LinuxWindow::LinuxWindow()   
  {
    SEMPERVIRENS_MSG("LinuxWindow ctor, size of LinuxWindow: " << sizeof(LinuxWindow));
    //initDisplay(windowInfo);
    initDisplay(); 
  }

  LinuxWindow::~LinuxWindow()
  {
    SEMPERVIRENS_MSG("LinuxWindow dtor");
    XCloseDisplay(_display);
  }

  //bool LinuxWindow::initDisplay(WindowInfo const& windowInfo)
  bool LinuxWindow::initDisplay()    
  {
    // Connect to the display of the machine the client code runs on (local display).
    _display = XOpenDisplay(getenv("DISPLAY")); 
    if (!_display)
    {
      SEMPERVIRENS_FAT("Cannot connect to X server");
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
				  //windowInfo._xPos, windowInfo._yPos,
				  0, 0, 
				  //windowInfo._widthRatio * _screen._width, windowInfo._heightRatio * _screen._height,
				  _screen._width, _screen._height,
				  1, _screen._blackPixel, // 1 pixel wide black border
				  _screen._whitePixel);   // white background
    //XStoreName(_display, _window, windowInfo._title.c_str());
    XStoreName(_display, _window, "Sempervirens Appication");
    //auto gc = XCreateGC(_display, _window, 0,0);        
    //XSetBackground(_display, gc, _screen._whitePixel);
    //XSetForeground(_display, gc, _screen._blackPixel);
    
    // Set event masks.
    XSelectInput(_display, _window,
		 ExposureMask        |  // For exposure events.
		 StructureNotifyMask |  // For resize and move events.
		 FocusChangeMask     |  // For focus in and out events.
		 KeyPressMask        |  // For key press events.
		 KeyReleaseMask      |  // For key release events.
		 ButtonPressMask     |  // For mouse button press events.
		 ButtonReleaseMask   |  // For mouse button release events.
		 PointerMotionMask);    // For mouse motion events, irrespective of button states.


    // Enable detectable auto repeat for key pressed events.
    auto detectableAutoRepeatIsEnabled = XkbSetDetectableAutoRepeat(_display, true, nullptr); 
    if (detectableAutoRepeatIsEnabled)
      SEMPERVIRENS_MSG("Detectable auto repeat is enabled.");
    // Note: if not supported we could go around by using XQueryKeymap that returns an array of 32 bytes where each bit
    // is set if the corresponding key is held down.

    // Intercept window close event from window manager.
    Atom wmDeleteMessage = XInternAtom(_display, "WM_DELETE_WINDOW", false);
    XSetWMProtocols(_display, _window, &wmDeleteMessage, 1);
    
    // Map window to screen.
    XClearWindow(_display, _window);
    XMapWindow(_display, _window);
    XFlush(_display);
    
    return true;
  }

  void LinuxWindow::processInput()
  {
    XEvent event;
    // If the event queue is empty, XNextEvent blocks till the next event is received.
    // Avoid blocking by checking if the queue contains events before calling XNextEvent.
    if (XPending(_display)) // Equivalent to XEventsQueued(_display, QueuedAfterFlush)
      XNextEvent(_display, &event);
    else return;
    
    switch (event.type)
    {
    case ClientMessage:
    {
      Atom wmDeleteMessage = XInternAtom(_display, "WM_DELETE_WINDOW", false);
      auto client = event.xclient;
      if (client.data.l[0] == static_cast<long int>(wmDeleteMessage))
      {
	WindowCloseEvent closeEvent;
	SEMPERVIRENS_SIGNAL(closeEvent);
      }
      break;
    }

    case Expose:
    {
      //WindowExposeEvent exposeEvent{};
      //SEMPERVIRENS_SIGNAL(exposeEvent);
      break;
    }
    
    case ConfigureNotify:
    {
      auto config = event.xconfigure;
      if (config.width != _width || config.height != _height)
      {
	//WindowResizeEvent resizeEvent{config.width, config.height};
	//SEMPERVIRENS_SIGNAL(resizeEvent);
	_width = config.width;
	_height = config.height;
	break;
      }
      if (config.x != _xPos || config.y != _yPos)
      {
	//WindowMoveEvent moveEvent{config.x, config.y};
	//SEMPERVIRENS_SIGNAL(moveEvent);
	_xPos = config.x;
	_yPos = config.y;
	break;
      }
    }

    case FocusIn:
    {
      //WindowFocusInEvent focusInEvent{};
      //SEMPERVIRENS_SIGNAL(focusInEvent);
      break;
    }
    
    case FocusOut:
    {
      //WindowFocusOutEvent focusOutEvent{};
      //SEMPERVIRENS_SIGNAL(focusOutEvent);
      break;
    }
    
    case MotionNotify:
    {
      auto motion = event.xmotion;
      MouseMovedEvent mouseMovedEvent{motion.x, motion.y};
      SEMPERVIRENS_SIGNAL(mouseMovedEvent);

      break;
    }


    case KeyPress:
    {
      auto key = event.xkey;
      auto symbol = XkbKeycodeToKeysym(_display, key.keycode, 0, key.state & ShiftMask || key.state & LockMask ? 1 : 0);
      if (symbol == NoSymbol)
      {
	SEMPERVIRENS_ERR("Key pressed has no symbol");
	break;
      }

      auto chr = XKeysymToString(symbol);

      //SEMPERVIRENS_MSG("Key pressed event for " << chr);

      Keymod mod = key.state & ShiftMask ? SHIFT() : NONE();
      mod += key.state & LockMask ? LOCK() : NONE();
      mod += key.state & ControlMask ? CTRL() : NONE();     
	    
      KeyPressedEvent keyPressedEvent{symbol, chr, mod};
      SEMPERVIRENS_SIGNAL(keyPressedEvent);
      break;
    }

    case KeyRelease:
    {      
      auto key = event.xkey;
      auto symbol = XkbKeycodeToKeysym(_display, key.keycode, 0, key.state & ShiftMask || key.state & LockMask ? 1 : 0);

      if (symbol == NoSymbol)
      {
	SEMPERVIRENS_ERR("Key released has no symbol");
	break;
      }

      auto chr = XKeysymToString(symbol);

      //SEMPERVIRENS_MSG("Key released event for " << chr);

      Keymod mod = key.state & ShiftMask ? SHIFT() : NONE();
      mod += key.state & LockMask ? LOCK() : NONE();
      mod += key.state & ControlMask ? CTRL() : NONE();
      
      KeyReleasedEvent keyReleasedEvent{symbol, chr, mod};
      SEMPERVIRENS_SIGNAL(keyReleasedEvent);
      break;
    }   
      
    default:
      break;
    }
  }
    
  //void LinuxWindow::onUpdate()
  //{
  //  SEMPERVIRENS_MSG("Window update...");
  //}



#if SEMPERVIRENS_BUILD(UNITTESTING)
  void LinuxWindow::Test()
  {
    //auto windowInfo = WindowInfo{"Test Window", 0, 0, 1.0f / 2, 2.0f / 3};
    //auto window = static_cast<LinuxWindow*>(createWindow(windowInfo));
    //delete window;
  }
#endif
}
