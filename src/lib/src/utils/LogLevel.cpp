#define LOGLEVEL_CPP
#include <utils/LogLevel.hpp>

std::ostream& operator<<(std::ostream& os, dog::utils::eLogLevel const& level) {

  using dog::utils::eLogLevel;  

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
