#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <Macros/Build.hpp>

namespace sempervirens::core::log {

  enum class LogSeverity {
    MSG, // Simple message
    WRN, // Warning message
    ERR, // Error message
    FAT  // Fatal error message
  };
  
  class Logger {

    static Logger* _head;
    static Logger* _tail;
    
  public:
    Logger() = default;
    virtual ~Logger() {}

    virtual void log(LogSeverity severity, char const* file, char const* func, int line, std::string msg) {};

    static void Log(LogSeverity severity, char const* file, char const* func, int line, std::string msg)
    {
      std::lock_guard<std::mutex> lock(Logger::_mutex);
      Logger::_head->log(severity, file, func, line, msg);
    };

    Logger* _next{nullptr};
    Logger* _prev{nullptr};

  protected:
    static std::mutex _mutex; 
    static void addToList(Logger* logger);
    static void removeFromList(Logger* logger);
  };


#if SEMPERVIRENS_BUILD(LOGGING)  
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define SEMPERVIRENS_LOG(severity, msg) (	     \
    sempervirens::core::log::Logger::Log(            \
    sempervirens::core::log::LogSeverity::severity,  \
    __FILENAME__,				     \
    __PRETTY_FUNCTION__,			     \
    __LINE__,					     \
    static_cast<std::ostringstream&>(		     \
      std::ostringstream().flush() << msg            \
    ).str()	                                     \
  )                                                  \
)
#else
#define SEMPERVIRENS_LOG(severity, msg) do {} while(0)
#endif  
#define SEMPERVIRENS_MSG(msg) SEMPERVIRENS_LOG(MSG, msg)
#define SEMPERVIRENS_WRN(msg) SEMPERVIRENS_LOG(WRN, msg)
#define SEMPERVIRENS_ERR(msg) SEMPERVIRENS_LOG(ERR, msg)
#define SEMPERVIRENS_FAT(msg) SEMPERVIRENS_LOG(FAT, msg)  

}

std::ostream& operator<<(std::ostream& os, sempervirens::core::log::LogSeverity const& severity);

#endif
