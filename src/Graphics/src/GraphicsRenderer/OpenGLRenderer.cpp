#define OPENGLRENDERER_CPP
#include <GraphicsRenderer/OpenGLRenderer.hpp>
#include <Logging/Logger.hpp>

namespace dog::graphics::renderer {

  void OpenGLRenderer::render() {

    DOG_LOGMSG("rendering...");
  }

  OpenGLRenderer::OpenGLRenderer() { DOG_LOGMSG("OpenGLRenderer ctor"); }
  OpenGLRenderer::~OpenGLRenderer() { DOG_LOGMSG("OpenGLRenderer dtor"); }
}
