#define LOGMSG_CPP
#include <Logging/LogMsg.hpp>
#include <Logging/Logger.hpp>

namespace sempervirens::core::logging {

  LogMsg::LogMsg(Logger* logger, eLogLevel level, std::string file, std::string func, std::size_t line) :
    _logger{logger}, _meta{level, std::move(file), std::move(func), line} {}

  LogMsg::~LogMsg() {

    _logger->flush(this); // _logger always outlives LogMsg
  }

  //LogMsg& LogMsg::operator<<(std::ostream& (*fn)(std::ostream&)) {
    
  //  fn(_buffer);
  //  return *this;
  //}

  void LogMsg::operator()(std::string msg) {
    
    //_buffer << std::move(msg);
    _msg = std::move(msg);
  }
  
  
}
