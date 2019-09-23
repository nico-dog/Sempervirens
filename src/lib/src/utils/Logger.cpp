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

    std::vector<LogSink> _sinks;
    Active _active;
    //std::vector<LogSink> _sinks;
  };

  Logger::Logger() : _pImpl{new LoggerImpl{}, [](LoggerImpl* ptr){ delete ptr; }} {
    
    addSink(makeConsoleSink());
    addSink(makeFileSink("/home/nico/Desktop/dog.log"));
  }

  void Logger::addSink(LogSink sink) {

    _pImpl->_sinks.push_back(std::move(sink));
  }

  void Logger::flush(LogMsg const* logMsg) {

    auto meta = std::move(logMsg->_meta);
    auto msg = std::move(logMsg->_buffer.str());
    _pImpl->_active.send([this, _meta{std::move(meta)}, _msg{std::move(msg)}]()
			 { for (auto const& sink : _pImpl->_sinks) log(sink, _meta, _msg); });
  }

  LogMsg Logger::operator()(eLogLevel level, std::string file, std::string func, std::size_t line) {

    return LogMsg(this, level, std::move(file), std::move(func), line);
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
