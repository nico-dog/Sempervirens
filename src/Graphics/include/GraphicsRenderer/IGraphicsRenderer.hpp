//***************************************************
//
// Definition of IGraphicsRenderer interface:
// This is the genereic renderer interface the graphics mgr knows about.
// Different implementations are provided by different dynamics libraries.
//
//***************************************************
#ifndef IGRAPHICSRENDERER_HPP
#define IGRAPHICSRENDERER_HPP

namespace dog::graphics::renderer {

  class IGraphicsRenderer {

  public:
    virtual ~IGraphicsRenderer() = default;
    virtual void render() = 0;
  };
}
#endif
