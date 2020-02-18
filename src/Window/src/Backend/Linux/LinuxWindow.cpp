#define LINUXWWINDOW_CPP
#include <Backend/Linux/LinuxWindow.hpp>
#include <Logging/Logger.hpp>

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
				  //800, 600,
				  1, _screen._blackPixel, // 1 pixel wide black border
				  _screen._whitePixel);   // white background



    //auto gc = XCreateGC(_display, _window, 0,0);        

    //XSetBackground(_display, gc, _screen._whitePixel);
    //XSetForeground(_display, gc, _screen._blackPixel);
    
    // Set event masks.
    //XSelectInput(_display, _window, ExposureMask | KeyPressMask);


    //Atom wmDeleteMessage = XInternAtom(_display, "WM_DELETE_WINDOW", false);
    //XSetWMProtocols(_display, _window, &wmDeleteMessage, 1);
    

    // Map window to screen.
    XClearWindow(_display, _window);
    XMapWindow(_display, _window);
    XFlush(_display);
    
    return true;
  }

  void LinuxWindow::onUpdate()
  {
    //SEMPERVIRENS_MSG("Window update...");
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
    auto window = createWindow(windowInfo);

    window->onUpdate();
    
    delete window;
  }
#endif
}
