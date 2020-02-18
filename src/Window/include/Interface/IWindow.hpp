#ifndef IWINDOW_HPP
#define IWINDOW_HPP

namespace sempervirens::window {

  struct WindowInfo {

    std::string _title;
    int _xPos{0};
    int _yPos{0};
    float _widthRatio{1.0f / 2};
    float _heightRatio{2.0f / 3};

    WindowInfo(std::string title, int xPos, int yPos, float widthRatio, float heightRatio) :  
      _title{std::move(title)}, _xPos{xPos}, _yPos{yPos}, _widthRatio{widthRatio}, _heightRatio{heightRatio} {}
  };

  
  class IWindow {

  public:
    virtual ~IWindow() = default;

    virtual void onUpdate() = 0;

    static IWindow* createWindow(WindowInfo const& info);
  };
}
#endif
