#ifndef IGRAPHICSRENDERER_HPP
#define IGRAPHICSRENDERER_HPP

namespace dog::graphics::mgr {

  class IGraphicsRenderer {

  public:
    virtual ~IGraphicsRenderer() = default;

    virtual void render() = 0;
  };

  extern "C" {

    // these methods are defined in the dynamic lib that implements the interface
    IGraphicsRenderer* createRenderer();
    typedef IGraphicsRenderer* (*f_createRenderer)();
    
    void destroyRenderer(IGraphicsRenderer* renderer);
    typedef void (*f_destroyRenderer)(IGraphicsRenderer* renderer);
  }
}
#endif
