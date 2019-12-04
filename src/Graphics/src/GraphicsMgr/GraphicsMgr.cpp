#define GRAPHICSMGR_CPP
#include <GraphicsMgr/GraphicsMgr.hpp>
#include <GraphicsMgr/IGraphicsRenderer.hpp>
#include <Logging/Logger.hpp>

namespace dog::graphics::mgr {

  GraphicsMgr::~GraphicsMgr() {

    if (_graphicsLib) release();
  }

  bool GraphicsMgr::load(std::string libname) {

    if (auto lib = dog::app::dlibs::load(std::move(libname)); lib.has_value())
    {
      _graphicsLib = lib.value();
      //return true;
      createRenderer();
      if (_pRenderer) return true;
      else return false;
    }
    else
    {
      DOG_LOGERR("graphics mgr could not load graphics library");
      return false;
    }
  }

  void GraphicsMgr::release() {

    dog::app::dlibs::release(_graphicsLib);
  }

  void GraphicsMgr::createRenderer() {
    //std::shared_ptr<IGraphicsRenderer> GraphicsMgr::createRenderer() {

    if (auto fPtr = dog::app::dlibs::getSymbol(_graphicsLib, "createRenderer"); fPtr.has_value()) {

      using createRenderer_t = std::shared_ptr<IGraphicsRenderer> (*)();
      createRenderer_t createRenderer = reinterpret_cast<createRenderer_t>(fPtr.value());
      //return createRenderer();
      _pRenderer = createRenderer();
    }
    else
    {
      DOG_LOGERR("graphics mgr could not load symbol from graphics library");
      //return nullptr;
    }
  }

  void GraphicsMgr::render() {

    _pRenderer->render();
  }
  


}
