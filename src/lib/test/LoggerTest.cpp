#include <utils/Logger.hpp>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

int main() {

  gLog << "test message log";
  gLogDebug << "test debug log";
  gLogWarning << "test warning log";
  gLogError << "test error log";
  gLogFatal << "test fatal log";
  gLog << "test message log";

  // Need to make sure the background thread of the active object is executed
  // before the Logger::dtor is called. Should not be a problem in production code
  std::this_thread::sleep_for(1s);
  
  return 0;
}
