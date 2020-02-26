#ifndef ENTRYPOINT_HPP
#define ENTRYPOINT_HPP
#include <Logging/ConsoleLogger.hpp>

extern sempervirens::app::Application* sempervirens::app::createApplication();

int main(int argc, char* argv[]) {

#if SEMPERVIRENS_BUILD(LOGGING)  
  auto logger = sempervirens::core::log::ConsoleLogger{};
#endif
  
  auto app = sempervirens::app::createApplication();
  app->run();
  delete app;
  
  return 0;
}
  
#endif
