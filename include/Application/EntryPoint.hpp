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

  // Create arena for application and physical devices.
  auto area = HeapArea{SEMPERVIRENS_B(48)};
  auto allocator = LinearAllocator{area.begin(), area.size()};
  auto arena = Arena_t{&allocator, "Heap allocated application arena"};
  
  
  
  auto app = createApplication(arena);

  //auto window = SEMPERVIRENS_NEW(Window, arena);
  SEMPERVIRENS_MSG("size of Window: " << sizeof(Window_t));

  allocator.dumpMemory();



  
  app._ptr->run();


  SEMPERVIRENS_DELETE(app, arena);
  
  return 0;
}
  
#endif
