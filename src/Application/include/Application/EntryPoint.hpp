#ifndef ENTRYPOINT_HPP
#define ENTRYPOINT_HPP

extern sempervirens::app::Application* sempervirens::app::createApplication();

int main(int argc, char* argv[]) {

  auto app = sempervirens::app::createApplication();
  app->run();
  delete app;
  
  return 0;
}
  
#endif
