#ifndef ENTRYPOINT_HPP
#define ENTRYPOINT_HPP
#if SEMPERVIRENS_BUILD(LOGGING)  
#include <Logging/ConsoleLogger.hpp>
#endif

extern sempervirens::app::Application* sempervirens::app::createApplication();

int main(int argc, char* argv[])
{
#if SEMPERVIRENS_BUILD(LOGGING)  
  auto logger = sempervirens::core::logging::ConsoleLogger{};
#endif
  
  auto app = sempervirens::app::createApplication();
  app->run();
  delete app;
  
  return 0;
}
  
#endif
