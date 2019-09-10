#define LOGGER_CPP
#include <utils/Logger.hpp>
#include <utils/LogSink.hpp>
#include <utils/Active.hpp>
#include <vector>

namespace dog::utils {

  class Logger::LoggerImpl {

  public:
    LoggerImpl() = default;
    ~LoggerImpl() = default;
    
    Active _active;
    std::vector<LogSink> _sinks;
  };

  Logger::Logger() : _pImpl{new LoggerImpl{}, [](LoggerImpl* ptr){ delete ptr; }}
  {
    addSink(makeConsoleSink());
    //addSink(makeFileSink("/home/nico/Desktop/udmx.log"));
  }

  void Logger::addSink(LogSink sink) {

    _pImpl->_sinks.push_back(std::move(sink));
  }

  void Logger::flush(LogMsg const* msg) {

    auto meta = msg->_meta;
    auto msg_ = msg->_buffer.str();
    _pImpl->_active.send([=](){	for (auto const& sink : _pImpl->_sinks) log(sink, meta, msg_); });
  }

  LogMsg Logger::operator()(eLogLevel level, std::string const& file, std::string const& func, std::size_t line) {

    return LogMsg(this, level, file, func, line);
  }


//#if UDMX_PRODUCT(UNITTEST_BUILD)
//  void Logger::test()
//  {
//    gLog << "Message log";
//    gLogDebug << "Debug log";
//    gLogWarning << "Warning log";
//    gLogError << "Error log";
//    gLogFatal << "Fatal log" << std::endl;
//  }
//#endif  
}
