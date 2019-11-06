#ifndef OPENGLRENDERER_HPP
#define OPENGLRENDERER_HPP
#include <GraphicsRenderer/IGraphicsRenderer.hpp>

namespace dog::graphics::renderer {

  class OpenGLRenderer final : public IGraphicsRenderer {

  public:
    void render() override;
  };
}
#endif
