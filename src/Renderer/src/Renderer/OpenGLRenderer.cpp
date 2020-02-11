#define OPENGLRENDERER_CPP
#include <Renderer/OpenGLRenderer.hpp>
#include <Logging/Logger.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace sempervirens::renderer {

  OpenGLRenderer::OpenGLRenderer() { SEMPERVIRENS_MSG("OpenGLRenderer ctor"); }
  OpenGLRenderer::~OpenGLRenderer() { SEMPERVIRENS_MSG("OpenGLRenderer dtor"); }

  bool OpenGLRenderer::initRenderer(int width, int height)
  {
    //glfwInit();
    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //{
    //  DOG_LOGERR("Failed to initialize GLAD");
    //  return false;
    //}

    //auto window = glfwGetCurrentContext();
    //if (window == nullptr) std::cout << "**** no contex ****\n";

    //PFNGLVIEWPORTPROC pfnglViewport = (PFNGLVIEWPORTPROC) glfwGetProcAddress("glViewport");
    //pfnglViewport(0, 0, width, height);

    //glViewport(0, 0, width, height);


    









    

    return true;
  }

  //void OpenGLRenderer::terminate()
  //{
  //  glDeleteVertexArrays(1, &_VAO);
  //  glDeleteBuffers(1, &_VBO);
  //  glDeleteBuffers(1, &_EBO);
  //}

  void OpenGLRenderer::compileShaders(char const* vertexShader, char const* fragmentShader)
  {
    /*
    auto vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexShader, nullptr);
    glCompileShader(vertexShaderID);
    auto success = 0;
    char infoLog[512];
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(vertexShaderID, 512, nullptr, infoLog);
      DOG_LOGERR("Vertex shader compilation failed: " << infoLog);
    }
    
    auto fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentShader, nullptr);
    glCompileShader(fragmentShaderID);
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(fragmentShaderID, 512, nullptr, infoLog);
      DOG_LOGERR("Fragment shader compilation failed: " << infoLog);
    }

    _shaderID = glCreateProgram();
    glAttachShader(_shaderID, vertexShaderID);
    glAttachShader(_shaderID, fragmentShaderID);
    glLinkProgram(_shaderID);
    glGetProgramiv(_shaderID, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(_shaderID, 512, nullptr, infoLog);
      DOG_LOGERR("Shader program linking failed: " << infoLog);
    }
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);    
    */
  }

  void OpenGLRenderer::getIndexedData(float* vertices, std::size_t vtxSize, unsigned int* indices, std::size_t idxSize)
  {
    /*
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, vtxSize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, idxSize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 
    */
  }

  void OpenGLRenderer::render()
  {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(_shaderID);
    glBindVertexArray(_VAO); 
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
  }


 
}
