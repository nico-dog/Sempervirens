//***************************************************
//
// Definition of IGraphicsRenderer interface:
// This is the genereic renderer interface the graphics mgr knows about.
// Different implementations are provided by different dynamics libraries.
//
//***************************************************
#ifndef IGRAPHICSRENDERER_HPP
#define IGRAPHICSRENDERER_HPP
#include <memory>

namespace dog::graphics::mgr {

  class IGraphicsRenderer {

  public:
    virtual ~IGraphicsRenderer() = default;
    virtual void render() = 0;
  };

  //extern "C" {

    // these methods are defined in the dynamic lib that implements the interface
    //std::shared_ptr<IGraphicsRenderer> createRenderer();
    
    //IGraphicsRenderer* createRenderer();
    //void destroyRenderer(IGraphicsRenderer* renderer);
  //}
}
#endif
