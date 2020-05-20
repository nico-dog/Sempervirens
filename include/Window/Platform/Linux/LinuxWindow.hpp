#ifndef LINUXWINDOW_HPP
#define LINUXWINDOW_HPP
#include <Macros/Build.hpp>
#include <X11/Xlib.h>

namespace sempervirens::window
{
 struct WindowInfo
  {
    std::string _title;
    int _xPos{0};
    int _yPos{0};
    float _widthRatio{1.0f / 2};
    float _heightRatio{2.0f / 3};

    WindowInfo(std::string title, int xPos, int yPos, float widthRatio, float heightRatio) :  
      _title{std::move(title)}, _xPos{xPos}, _yPos{yPos}, _widthRatio{widthRatio}, _heightRatio{heightRatio} {}
  };

  struct ScreenInfo
  {
    int _id;
    int _width;
    int _height;
    Window _rootWindow;
    unsigned long _whitePixel;
    unsigned long _blackPixel;    
  };
  
  class LinuxWindow
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

    //void pollEvent() override;
    //void onUpdate() override;
    void pollEvent();
    void onUpdate();    

#if SEMPERVIRENS_BUILD(UNITTESTING)
    void static Test();
#endif   
  };
  
}
#endif
