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
