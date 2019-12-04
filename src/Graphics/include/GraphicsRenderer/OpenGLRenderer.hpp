//***************************************************
//
// Definition of OpenGLRenderer object:
// Implementation of the render interface for OpenGL
//
//***************************************************
#ifndef OPENGLRENDERER_HPP
#define OPENGLRENDERER_HPP
#include <GraphicsRenderer/IGraphicsRenderer.hpp>

namespace dog::graphics::renderer {

  class OpenGLRenderer final : public IGraphicsRenderer {

  public:
    OpenGLRenderer();
    ~OpenGLRenderer();

    OpenGLRenderer(OpenGLRenderer const&) = delete;
    OpenGLRenderer* operator=(OpenGLRenderer const&) = delete;
    OpenGLRenderer(OpenGLRenderer&&) = delete;
    OpenGLRenderer* operator=(OpenGLRenderer&&) = delete;
    
    void render() override;
  };
}
#endif
