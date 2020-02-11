#ifndef APPLICATION_HPP
#define APPLICATION_HPP

namespace sempervirens::app {

  class Application {

  public:
    virtual ~Application() {};

    virtual void run() = 0;
    
  };

  // To be defined by client.
  Application* createApplication();
}
#endif
