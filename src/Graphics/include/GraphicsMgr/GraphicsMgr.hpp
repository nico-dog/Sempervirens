#ifndef GRAPHICSMGR_HPP
#define GRAPHICSMGR_HPP

namespace dog::graphics::mgr {

#if defined(__unix__)
  using DLib = void*;
#endif
  
  class IGraphicsRenderer;

  class GraphicsMgr {

    DLib _graphicsLib;
    IGraphicsRenderer* _renderer{nullptr};
    
  public:
    GraphicsMgr() = default;
    ~GraphicsMgr();

    void load();
    void createRenderer();
    void release(); // destroy renderer + unloads dynamic lib

    IGraphicsRenderer* renderer();
  };
}
#endif
