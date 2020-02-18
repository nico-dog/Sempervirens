#define CONSOLELOGGER_CPP
#include <Logging/ConsoleLogger.hpp>

namespace sempervirens::core::log {

  ConsoleLogger::ConsoleLogger() { addToList(this); }
  ConsoleLogger::~ConsoleLogger() { removeFromList(this); }

  void ConsoleLogger::log(LogSeverity severity, char const* file, char const* func, int line, std::string msg)
  {
    std::cout << severity << ' '
	      << file << ", " << func << ", l." << line << ": "
	      << msg << '\n';
    
    if (_next) _next->log(severity, file, func, line, std::move(msg));    
  }

#if SEMPERVIRENS_BUILD(UNITTESTING)
  void ConsoleLogger::test() {

    // No need to create console logger, it is created by the unit test register.
    SEMPERVIRENS_MSG("Test message");
  }
#endif  
  
}
