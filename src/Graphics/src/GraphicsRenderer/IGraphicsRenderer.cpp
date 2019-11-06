#define IGRAPHICSRENDERER_CPP
#include <GraphicsRenderer/IGraphicsRenderer.hpp>

#include <GraphicsRenderer/OpenGLRenderer.hpp>


namespace dog::graphics::renderer {

  extern "C" {

    IGraphicsRenderer* createRenderer() { return new OpenGLRenderer{}; }
    void destroyRenderer(IGraphicsRenderer* renderer) { delete renderer; }
  }

}
