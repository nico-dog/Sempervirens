//***************************************************
//
// Definition of IRenderer interface:
// This is the genereic renderer interface the graphics mgr knows about.
// Different implementations are provided by different dynamics libraries.
//
//***************************************************
#ifndef IRENDERER_HPP
#define IRENDERER_HPP
#include <cstddef>

namespace sempervirens::renderer {

  class IRenderer {

  public:
    virtual ~IRenderer() = default;
    virtual bool initRenderer(int width, int height) = 0;
    //virtual void terminate() = 0;
    virtual void compileShaders(char const* vertexShader, char const* fragmentShader) = 0;
    virtual void getIndexedData(float* vertices, std::size_t vtxSize, unsigned int* indices, std::size_t idxSize) = 0;
    virtual void render() = 0;
  };
}
#endif
