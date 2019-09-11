//***************************************************
//
// Definition of LogMsg object:
// The LogMsg objects can only be created by the logger call operator.
// Messages are created with meta data (log level, filename, function name and line number) and an empty buffer.
// Buffer is filled using overloaded << operator.
// Message gets flushed by logger when out of scope.
//
//***************************************************
#ifndef LOGMSG_HPP
#define LOGMSG_HPP
#include <utils/LogLevel.hpp>
#include <string>
#include <sstream>

namespace dog::utils {

  class Logger;
  
  class LogMsg {

  public:
    struct Meta {

      eLogLevel _level;
      std::string _file;
      std::string _func;
      std::size_t _line;
    };

  private:
    friend class Logger;
    
    LogMsg(Logger* logger, eLogLevel level, std::string const& file, std::string const& func, std::size_t line);
    LogMsg(LogMsg const&) = delete;
    LogMsg(LogMsg&&) = delete;

    Logger* _logger;
    Meta _meta;
    std::ostringstream _buffer;

  public:
    ~LogMsg();
    LogMsg& operator=(LogMsg const&) = delete;
    LogMsg& operator=(LogMsg&&) = delete;

    template<typename T>
    LogMsg& operator<<(T value);

    LogMsg& operator<<(std::ostream& (*fn)(std::ostream&));
  };
}
#include <utils/LogMsg.inl>
#endif