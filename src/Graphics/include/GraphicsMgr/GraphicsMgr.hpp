#ifndef GRAPHICSMGR_HPP
#define GRAPHICSMGR_HPP
#include <DynamicLibs/DynamicLibs.hpp>
#include <memory>

namespace dog::graphics::mgr {

  class IGraphicsRenderer;

  class GraphicsMgr {

    dog::app::dlibs::dlib_t _graphicsLib;
    
  public:
    GraphicsMgr() = default;
    ~GraphicsMgr();

    bool load(std::string libname);
    std::shared_ptr<IGraphicsRenderer> createRenderer();
    void release(); 
  };
}
#endif
