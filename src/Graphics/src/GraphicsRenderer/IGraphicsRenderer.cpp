#define IGRAPHICSRENDERER_CPP
#include <GraphicsRenderer/IGraphicsRenderer.hpp>
#include <GraphicsRenderer/OpenGLRenderer.hpp>
#include <Logging/Logger.hpp>
#include <memory>

namespace dog::graphics::renderer {

  extern "C" {

    void destroyRenderer(IGraphicsRenderer* renderer) {
      
      DOG_LOGMSG("destroy OpenGLRenderer");
      delete renderer;
    }
    
    std::shared_ptr<IGraphicsRenderer> createRenderer() {

      DOG_LOGMSG("create OpenGLRenderer");
      return std::shared_ptr<IGraphicsRenderer>{new OpenGLRenderer{}, destroyRenderer};
    }
    

  }

}
