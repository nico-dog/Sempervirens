#include <utils/Logger.hpp>

int main() {

  gLog << "test message log";
  gLogDebug << "test debug log";
  gLogWarning << "test warning log";
  gLogError << "test error log";
  gLogFatal << "test fatal log";
  gLog << "test message log";
  
  return 0;
}
