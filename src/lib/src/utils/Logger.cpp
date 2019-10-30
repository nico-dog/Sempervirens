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

    //std::vector<LogSink> _sinks;
    std::array<LogSink, 2> _sinks = {makeConsoleSink(),
				     makeFileSink("/home/nico/Desktop/dog.log")};   
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


#if DOG_BUILD(UNITTESTS)
  void Logger::test() {

    auto i = 2;
    DOG_LOGMSG("i has value " << i);
    DOG_LOGDBG("i has value " << i);
    DOG_LOGWRN("i has value " << i);
    DOG_LOGERR("i has value " << i);
    DOG_LOGFAT("i has value " << i);  
  }
#endif  
}
