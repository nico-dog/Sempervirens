//***************************************************
//
// Definition of OpenGLRenderer object:
// Implementation of the render interface for OpenGL
//
//***************************************************
#ifndef OPENGLRENDERER_HPP
#define OPENGLRENDERER_HPP
#include <Renderer/IRenderer.hpp>
#include <Logging/Logger.hpp>

//class GLFWwindow;

namespace sempervirens::renderer {

  class OpenGLRenderer final : public IRenderer {

  public:
    //GLFWwindow* _window;
    unsigned int _VAO{0};
    unsigned int _VBO{0};
    unsigned int _EBO{0};
    int _shaderID{0};
    
    OpenGLRenderer();
    ~OpenGLRenderer();

    OpenGLRenderer(OpenGLRenderer const&) = delete;
    OpenGLRenderer* operator=(OpenGLRenderer const&) = delete;
    OpenGLRenderer(OpenGLRenderer&&) = delete;
    OpenGLRenderer* operator=(OpenGLRenderer&&) = delete;

    bool initRenderer(int width, int height) override;
    //void terminate() override;

    void compileShaders(char const* vertexShader, char const* fragmentShader) override;
    void getIndexedData(float* vertices, std::size_t vtxSize, unsigned int* indices, std::size_t idxSize);
    void render() override;
  };

}
#endif
