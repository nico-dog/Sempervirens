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
#include <Build/Build.hpp>
#include <Logging/Singleton.hpp>
#include <Logging/LogMsg.hpp> 
#include <Logging/LogLevel.hpp> 
#include <memory>
#include <cstring>

namespace dog::utilities::logging {

  class LogSink;
  
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

#if DOG_BUILD(UNITTESTS)
    void static test();
#endif
  };
}

// Macros to create empty-buffer messages with proper log levels
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#if DOG_BUILD(LOGGING)
#define DOG_LOG(level, msg) (			 \
    dog::utilities::Logging::Logger::instance()( \
    dog::utilities::Logging::eLogLevel::level,   \
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
#define DOG_LOG(level, msg) do {} while(0)
#endif

#define DOG_LOGMSG(msg) DOG_LOG(MSG, msg)
#define DOG_LOGDBG(msg) DOG_LOG(DBG, msg)
#define DOG_LOGWRN(msg) DOG_LOG(WRN, msg)
#define DOG_LOGERR(msg) DOG_LOG(ERR, msg)
#define DOG_LOGFAT(msg) DOG_LOG(FAT, msg)

#endif
