//***************************************************
//
// Definition of RendererMgr object:
// The graphics mgr static library is responsible for providing an instance of the graphics renderer.
// The renderer instance implements a generic interface which is the only thing the mgr knows about.
// The mgr is responsible for loading the dynamic library that provides the chosen implementation.
//
//***************************************************
#ifndef RENDERERMGR_HPP
#define RENDERERMGR_HPP
#include <DynamicLibs/DynamicLibs.hpp>
#include <memory>

namespace sempervirens::renderer::mgr {

  class IRenderer;

  class RendererMgr {

    sempervirens::core::dlibs::dlib_t _rendererLib;
    std::shared_ptr<IRenderer> _renderer;

    void createRenderer();
    
  public:
    RendererMgr() = default;
    ~RendererMgr();

    RendererMgr(RendererMgr const&) = delete;
    RendererMgr& operator=(RendererMgr const&) = delete;
    RendererMgr(RendererMgr&&) = delete;
    RendererMgr& operator=(RendererMgr&&) = delete;

    bool load(std::string libname);
    void release();

    bool initRenderer(int width, int height);
    //void terminate();
    void compileShaders(char const* vertexShader, char const* fragmentShader);
    void getIndexedData(float* vertices, std::size_t vtxSize, unsigned int* indices, std::size_t idxSize);
    void render();
  };
}
#endif
