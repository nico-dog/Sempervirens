//***************************************************
//
// Definition of Logger object:
// The Logger object is a global resource (Singleton).
// Based on implementation from GrandMaster's Playground, Game Engine tutorial 2.
//
//***************************************************
#ifndef LOGGER_HPP
#define LOGGER_HPP
//#include <flags/Product.hpp>
#include <utils/Singleton.hpp>
#include <utils/LogMsg.hpp> // Needed for gLogLevel macro
#include <utils/LogLevel.hpp> // Needed for gLogLevel macro
#include <memory>
#include <cstring>

//#if UDMX_PRODUCT(UNITTEST_BUILD)
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
    
    Logger();

  public:
    ~Logger() = default;
    
    void addSink(LogSink sink);
    void flush(LogMsg const* msg);

    LogMsg operator()(eLogLevel level, std::string const& file, std::string const& func, std::size_t line);
  };
}
//#if UDMX_PRODUCT(UNITTEST_BUILD)   
//    REGISTER_TYPE_NAME(udmx::utils::Logger, class Logger);
//#endif
    

// Macros to create empty-buffer messages with proper log levels
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)  
#define gLogLevel(level) (			\
	udmx::utils::Logger::instance()(	\
	      udmx::utils::eLogLevel::level, \
	      __FILENAME__,	\
              __PRETTY_FUNCTION__, \
	      __LINE__	\
	))  
		     	
#define gLog        (gLogLevel(MSG))
#define gLogDebug   (gLogLevel(DBG))
#define gLogWarning (gLogLevel(WRN))
#define gLogError   (gLogLevel(ERR))
#define gLogFatal   (gLogLevel(FAT))

#endif
