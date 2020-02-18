//***************************************************
//
// Definition of Logger object:
// The Logger object is a global and unique resource (Singleton).
// Based on implementation from GrandMaster's Playground, Game Engine tutorial 2:
// http://www.grandmaster.nu/blog/?page_id=158
//
// Currently holds an array of 2 log sinks, one to the std output, the other to the given file.
//
//***************************************************
#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <Macros/Build.hpp>
#include <Logging/Singleton.hpp>
#include <Logging/LogMsg.hpp> 
//#include <memory>
//#include <cstring>

namespace sempervirens::core::logging {

class Logger : public Singleton<Logger> {
  
  friend class Singleton<Logger>;

  class LoggerImpl;
  std::unique_ptr<LoggerImpl, void(*)(LoggerImpl*)> _pImpl;
    
  Logger(); // Made private for singleton

public:
  ~Logger() = default;
  Logger(Logger const&) = delete;
  Logger& operator=(Logger const&) = delete;
    
  //void addSink(LogSink sink);
  void flush(LogMsg const* msg);
    
  LogMsg operator()(eLogLevel level, std::string file, std::string func, std::size_t line);

#if SEMPERVIRENS_BUILD(UNITTESTING)
  void static test();
#endif
};

// Macros to create empty-buffer messages with proper log levels
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#if SEMPERVIRENS_BUILD(LOGGING)
#define SEMPERVIRENS_LOG(level, msg) (			 \
    sempervirens::core::logging::Logger::instance()( \
    sempervirens::core::logging::eLogLevel::level,   \
    __FILENAME__,				 \
    __PRETTY_FUNCTION__,			 \
    __LINE__					 \
  )                                              \
  (						 \
    static_cast<std::ostringstream&>(		 \
      std::ostringstream().flush() << msg        \
    ).str()	                                 \
  )                                              \
)
#else
#define SEMPERVIRENS_LOG(level, msg) do {} while(0)
#endif

#define SEMPERVIRENS_MSG(msg) SEMPERVIRENS_LOG(MSG, msg)
#define SEMPERVIRENS_DBG(msg) SEMPERVIRENS_LOG(DBG, msg)
#define SEMPERVIRENS_WRN(msg) SEMPERVIRENS_LOG(WRN, msg)
#define SEMPERVIRENS_ERR(msg) SEMPERVIRENS_LOG(ERR, msg)
#define SEMPERVIRENS_FAT(msg) SEMPERVIRENS_LOG(FAT, msg)
}
#endif
