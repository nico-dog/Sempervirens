#define RENDERERMGR_CPP
#include <RendererMgr/RendererMgr.hpp>
#include <RendererMgr/IRenderer.hpp>
#include <Logging/Logger.hpp>

namespace sempervirens::renderer::mgr {

  RendererMgr::~RendererMgr()
  {
    if (_rendererLib) release();
  }

  bool RendererMgr::load(std::string libname)
  {
    if (auto lib = sempervirens::core::dlibs::load(std::move(libname)); lib.has_value())
    {
      _rendererLib = lib.value();

      SEMPERVIRENS_MSG("loaded renderer library at " << _rendererLib);
      
      createRenderer();
      if (_renderer) return true;
      else return false;
    }
    else
    {
      SEMPERVIRENS_ERR("renderer mgr could not load renderer library");
      return false;
    }
  }

  void RendererMgr::release()
  {
    //dog::app::dlibs::release(_rendererLib);
  }

  void RendererMgr::createRenderer()
  {
    if (auto fPtr = sempervirens::core::dlibs::getSymbol(_rendererLib, "createRenderer"); fPtr.has_value()) {

      using createRenderer_t = std::shared_ptr<IRenderer> (*)();
      createRenderer_t createRenderer = reinterpret_cast<createRenderer_t>(fPtr.value());

      SEMPERVIRENS_MSG("retrieved createRenderer symbol");
      
      
      _renderer = createRenderer();
    }
    else
    {
      SEMPERVIRENS_ERR("graphics mgr could not load symbol from graphics library");
    }
  }

  bool RendererMgr::initRenderer(int width, int height)
  {
    return _renderer->initRenderer(width, height);
  }
  
  //void RendererMgr::terminate()
  //{
  //  _renderer->terminate();
  //}

  void RendererMgr::compileShaders(char const* vertexShader, char const* fragmentShader)
  {
    _renderer->compileShaders(vertexShader, fragmentShader);
  }

  void RendererMgr::getIndexedData(float* vertices, std::size_t vtxSize, unsigned int* indices, std::size_t idxSize)
  {
    _renderer->getIndexedData(vertices, vtxSize, indices, idxSize);
  }

  void RendererMgr::render()
  {
    _renderer->render();
  }
}
