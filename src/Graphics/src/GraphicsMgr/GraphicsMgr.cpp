#define GRAPHICSMGR_CPP
#include <GraphicsMgr/GraphicsMgr.hpp>
#include <GraphicsMgr/IGraphicsRenderer.hpp>
#include <Logging/Logger.hpp>

namespace dog::graphics::mgr {

  GraphicsMgr::~GraphicsMgr() {

    if (_graphicsLib) dog::app::dlibs::release(_graphicsLib);
  }

  bool GraphicsMgr::load(std::string libname) {

    _graphicsLib = dog::app::dlibs::load(std::move(libname));
    if (!_graphicsLib) {

      DOG_LOGERR("graphics mgr could not load graphics library");
      return false;
    }
    return true;
  }

  std::shared_ptr<IGraphicsRenderer> GraphicsMgr::createRenderer() {

    auto fPtr = dog::app::dlibs::getSymbol(_graphicsLib, "createRenderer");
    if (!fPtr) {

      DOG_LOGERR("graphics mgr could not load symbol from graphics library");
      return nullptr;
    }
    using createRenderer_t = std::shared_ptr<IGraphicsRenderer> (*)();
    createRenderer_t createRenderer = reinterpret_cast<createRenderer_t>(fPtr);

    return createRenderer();
  }
  
  void GraphicsMgr::release() {

    /*
    auto fPtr = dog::app::dlibs::getSymbol(_graphicsLib, "destroyRenderer");
    if (!fPtr) {

      DOG_LOGERR("graphics mgr could not load symbol from graphics library");
      return nullptr;
    }
    using destroyRenderer_t = std::shared_ptr<IGraphicsRenderer> (*)();
    destroyRenderer_t destroyRenderer = reinterpret_cast<destroyRenderer_t>(fPtr);
    destroyRenderer(_pRenderer);
    */

    dog::app::dlibs::release(_graphicsLib);
  }

}
