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
#include <macros/Build.hpp>
#include <utils/Singleton.hpp>
#include <utils/LogMsg.hpp> 
#include <utils/LogLevel.hpp> 
#include <memory>
#include <cstring>

//#if DOG_BUILD(UNITTEST)
//#include <utils/UnitTestable.hpp>
//#endif

namespace dog::utils {

  class LogSink;
  
  //#if UDMX_PRODUCT(UNITTEST_BUILD)   
  //class Logger : public Singleton<Logger>, public UnitTestable<Logger> {

  //  friend struct Test<Logger>;
  //  static void test();
  //#else
  class Logger : public Singleton<Logger> {
  //#endif

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
  };
}
//#if UDMX_PRODUCT(UNITTEST_BUILD)   
//    REGISTER_TYPE_NAME(udmx::utils::Logger, class Logger);
//#endif
    

// Macros to create empty-buffer messages with proper log levels
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
/*
#define DOG_LOG(level) (						\
dog::utils::Logger::instance()(						\
dog::utils::eLogLevel::level,						\
__FILENAME__,								\
__PRETTY_FUNCTION__,							\
__LINE__								\
))
#define DOG_LOGMSG (DOG_LOG(MSG))
#define DOG_LOGDBG (DOG_LOG(DBG))
#define DOG_LOGWRN (DOG_LOG(WRN))
#define DOG_LOGERR (DOG_LOG(ERR))
#define DOG_LOGFAT (DOG_LOG(FAT))
*/
#if DOG_BUILD(LOGGING)
#define DOG_LOG(level, msg) (			\
  dog::utils::Logger::instance()(		\
    dog::utils::eLogLevel::level,		\
    __FILENAME__,				\
    __PRETTY_FUNCTION__,			\
    __LINE__					\
  )			                        \
  (						\
    static_cast<std::ostringstream&>(		\
      std::ostringstream().flush() << msg       \
    ).str()	                                \
  )                                             \
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
