#define LOGGER_CPP
#include <Logging/Logger.hpp>
#include <Logging/LogSink.hpp>
#include <Logging/Active.hpp>

namespace sempervirens::core::logging {

  class Logger::LoggerImpl {

  public:
    LoggerImpl() = default;
    ~LoggerImpl() = default;

    //std::vector<LogSink> _sinks;
    std::array<LogSink, 2> _sinks = {makeConsoleSink(),
				     makeFileSink("/home/nico/Desktop/sempervirens.log")};   
    Active _active;  // Needs to be declared last for proper order of destruction
  };

  Logger::Logger() : _pImpl{new LoggerImpl{}, [](LoggerImpl* ptr){ delete ptr; }} {
    
    //addSink(makeConsoleSink());
    //addSink(makeFileSink("/home/nico/Desktop/dog.log"));
  }

  //void Logger::addSink(LogSink sink) {

    //_pImpl->_sinks.push_back(std::move(sink));
  //}
  
  void Logger::flush(LogMsg const* logMsg) {

    _pImpl->_active.send([this,
			  _meta{std::move(logMsg->_meta)},
			  _msg{std::move(logMsg->_msg)}]()
			 { for (auto const& sink : _pImpl->_sinks) log(sink, _meta, _msg); });
  }

  LogMsg Logger::operator()(eLogLevel level, std::string file, std::string func, std::size_t line) {

    return {this, level, std::move(file), std::move(func), line};
  }


#if SEMPERVIRENS_BUILD(UNITTESTING)
  void Logger::test() {

    auto i = 2;
    SEMPERVIRENS_MSG("i has value " << i);
    SEMPERVIRENS_DBG("i has value " << i);
    SEMPERVIRENS_WRN("i has value " << i);
    SEMPERVIRENS_ERR("i has value " << i);
    SEMPERVIRENS_FAT("i has value " << i);  
  }
#endif  
}
