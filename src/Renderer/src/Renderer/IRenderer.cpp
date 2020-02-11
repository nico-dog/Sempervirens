#define IRENDERER_CPP
#include <Renderer/IRenderer.hpp>
#include <Renderer/OpenGLRenderer.hpp>
#include <Logging/Logger.hpp>
#include <memory>

namespace sempervirens::renderer {

  extern "C" {

    void destroyRenderer(IRenderer* renderer) {
      
      SEMPERVIRENS_MSG("destroy OpenGLRenderer");
      delete renderer;
    }
    
    std::shared_ptr<IRenderer> createRenderer() {

      SEMPERVIRENS_MSG("create OpenGLRenderer");
      return std::shared_ptr<IRenderer>{new OpenGLRenderer{}, destroyRenderer};
    }
  }
}
