#ifndef OPENGLRENDERER_HPP
#define OPENGLRENDERER_HPP
#include <GraphicsRenderer/IGraphicsRenderer.hpp>

namespace dog::graphics::renderer {

  class OpenGLRenderer final : public IGraphicsRenderer {

  public:
    OpenGLRenderer();
    ~OpenGLRenderer();
    void render() override;
  };
}
#endif
