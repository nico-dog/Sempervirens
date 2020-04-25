#ifndef LINUXWINDOW_HPP
#define LINUXWINDOW_HPP
#include <Interface/IWindow.hpp>
#include <Macros/Build.hpp>
#include <X11/Xlib.h>

namespace sempervirens::window
{
  struct ScreenInfo
  {
    int _id;
    int _width;
    int _height;
    Window _rootWindow;
    unsigned long _whitePixel;
    unsigned long _blackPixel;    
  };
  
  class LinuxWindow : public IWindow
  {
    Display* _display{nullptr};
    ScreenInfo _screen;
    Window _window;

    int _width{0};
    int _height{0};
    int _xPos{0};
    int _yPos{0};
    
    bool initDisplay(WindowInfo const& windowInfo);
    
  public:
    LinuxWindow(WindowInfo const& windowInfo);
    ~LinuxWindow();

    void pollEvent() override;
    void onUpdate() override;

#if SEMPERVIRENS_BUILD(UNITTESTING)
    void static Test();
#endif   
  };
  
}
#endif
