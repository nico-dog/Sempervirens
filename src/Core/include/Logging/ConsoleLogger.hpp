#ifndef CONSOLELOGGER_HPP
#define CONSOLELOGGER_HPP
#include <Logging/Logger.hpp>
#include <Macros/Build.hpp>

namespace sempervirens::core::logging
{
  class ConsoleLogger : public Logger
  {
  public:
    ConsoleLogger();
    ~ConsoleLogger();

    ConsoleLogger(ConsoleLogger const&) = delete;
    ConsoleLogger& operator=(ConsoleLogger const&) = delete;
    
    void log(LogSeverity severity, char const* file, char const* func, int line, std::string msg) override;

#if SEMPERVIRENS_BUILD(UNITTESTING)
    void static Test();
#endif  
  };
}
#endif
