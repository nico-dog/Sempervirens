#ifndef ENTRYPOINT_HPP
#define ENTRYPOINT_HPP
#include <Application/Application.hpp>

#if SEMPERVIRENS_BUILD(LOGGING)  
#include <Logging/ConsoleLogger.hpp>
#endif

using namespace sempervirens::app;
using namespace sempervirens::memoryalloc;


// DEFINED BY CLIENT.
extern Block<sempervirens::app::Application> sempervirens::app::createApplication(Arena_t& arena);

int main(int argc, char* argv[])
{
#if SEMPERVIRENS_BUILD(LOGGING)  
  auto logger = sempervirens::logging::ConsoleLogger{};
#endif

  //SEMPERVIRENS_MSG("config file: " << argv[1]);

  
  // Arena for application and physical devices.
  // TestApp = 32B
  // Window = 72B
  // Keyboard = 24B
  // Total = 128B
  auto area = HeapArea{SEMPERVIRENS_B(128)};
  auto allocator = LinearAllocator{area.begin(), area.size()};
  auto arena = Arena_t{&allocator, "Heap allocated application arena"};
  
  
  auto app = createApplication(arena);
  auto window = SEMPERVIRENS_NEW(Window_t, arena);
  app._ptr->setWindow(window._ptr);
  auto keyboard = SEMPERVIRENS_NEW(Keyboard_t, arena);
  app._ptr->setKeyboard(keyboard._ptr);


  
  allocator.dumpMemory();



  
  app._ptr->run();

  // Delete app and physical devices.
  SEMPERVIRENS_DELETE(keyboard, arena);
  SEMPERVIRENS_DELETE(window, arena);
  SEMPERVIRENS_DELETE(app, arena);
  
  return 0;
}
  
#endif
