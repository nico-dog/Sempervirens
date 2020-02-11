#define LOGLEVEL_CPP
#include <Logging/LogLevel.hpp>

std::ostream& operator<<(std::ostream& os, sempervirens::core::logging::eLogLevel const& level) {

  using sempervirens::core::logging::eLogLevel;  

  switch(level)
  {   
    case eLogLevel::MSG: os << "> [MSG]"; break;
    case eLogLevel::DBG: os << "> [DBG]"; break;
    case eLogLevel::WRN: os << "> [WRN]"; break;
    case eLogLevel::ERR: os << "> [ERR]"; break;
    case eLogLevel::FAT: os << "> [FAT]"; break;
    default: os << "> undefined log level";
  }
  
  return os;
}
