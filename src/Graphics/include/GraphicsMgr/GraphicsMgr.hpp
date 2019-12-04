//***************************************************
//
// Definition of GraphicsMgr object:
// The graphics mgr static library is responsible for providing an instance of the graphics renderer.
// The renderer instance implements a generic interface which is the only thing the mgr knows about.
// The mgr is responsible for loading the dynamic library that provides the chosen implementation.
//
//***************************************************
#ifndef GRAPHICSMGR_HPP
#define GRAPHICSMGR_HPP
#include <DynamicLibs/DynamicLibs.hpp>
#include <memory>

namespace dog::graphics::mgr {

  class IGraphicsRenderer;

  class GraphicsMgr {

    dog::app::dlibs::dlib_t _graphicsLib;
    std::shared_ptr<IGraphicsRenderer> _pRenderer;

    void createRenderer();
    
  public:
    GraphicsMgr() = default;
    ~GraphicsMgr();

    GraphicsMgr(GraphicsMgr const&) = delete;
    GraphicsMgr& operator=(GraphicsMgr const&) = delete;
    GraphicsMgr(GraphicsMgr&&) = delete;
    GraphicsMgr& operator=(GraphicsMgr&&) = delete;

    bool load(std::string libname);
    void release();

    void render();
  };
}
#endif
