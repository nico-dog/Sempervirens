#define GRAPHICSMGR_CPP
#include <GraphicsMgr/GraphicsMgr.hpp>
#include <GraphicsMgr/IGraphicsRenderer.hpp>
#include <Logging/Logger.hpp>

#if defined(__unix__)
#include <dlfcn.h>
#endif

namespace dog::graphics::mgr {

  GraphicsMgr::~GraphicsMgr() {

    release();
  }

  void GraphicsMgr::load() {

#if defined(__unix__)
    _graphicsLib = dlopen("/home/nico/DawnOfGiants/Sempervirens/build/Graphics/libgraphicslib.so", RTLD_LAZY);         
    if (!_graphicsLib) {

      DOG_LOGERR("Could not load graphics library, " << dlerror());
    }
#endif
  }

  void GraphicsMgr::createRenderer() {

    f_createRenderer createRenderer;

#if defined(__unix__)
    void* fPtr = dlsym(_graphicsLib, "createRenderer");
#endif

    if (char* error = dlerror(); error != nullptr)
    {
      DOG_LOGERR("Could not load get fct ptr, " << error);
      return;
    }

    createRenderer = reinterpret_cast<f_createRenderer>(fPtr);
    _renderer = createRenderer();
    
  }
  
  void GraphicsMgr::release() {

    f_destroyRenderer destroyRenderer;

#if defined(__unix__)    
    void* fPtr = dlsym(_graphicsLib, "destroyRenderer");
    if (char* error = dlerror(); error != nullptr)
    {
      DOG_LOGERR("Could not load get fct ptr, " << error);
      return;
    }
#endif
    
    destroyRenderer = reinterpret_cast<f_destroyRenderer>(fPtr);
    destroyRenderer(_renderer);

#if defined(__unix__)
    dlclose(_graphicsLib);
#endif
  }

  IGraphicsRenderer* GraphicsMgr::renderer() { return _renderer; }

  

}
