#define LOGMSG_CPP
#include <utils/LogMsg.hpp>
#include <utils/Logger.hpp>

namespace dog::utils {

  LogMsg::LogMsg(Logger* logger, eLogLevel level, std::string const& file, std::string const& func, std::size_t line) :
    _logger{logger}, _meta{level, file, func, line} {}

  //LogMsg::LogMsg(LogMsg&& msg) : _logger{std::move(msg._logger)}, _meta{std::move(msg._meta)}, _buffer{std::move(msg._buffer)}
  //{
  //  msg._logger = nullptr;
  //}

  LogMsg::~LogMsg() {
    //if(_logger) _logger->flush(this);
    _logger->flush(this); // _logger always outlives logmsg
  }

  LogMsg& LogMsg::operator<<(std::ostream& (*fn)(std::ostream&)) {
    
    fn(_buffer);
    return *this;
  }
  
}
