//***************************************************
//
// Logger supports different log levels.
// Different log levels will appear in logs with different formating.
//
//***************************************************
#ifndef LOGLEVEL_HPP
#define LOGLEVEL_HPP

#include <ostream>

namespace dog::utils {

  enum class eLogLevel {
    MSG, // Simple message
    DBG, // Debug message
    WRN, // Warning message
    ERR, // Error message
    FAT  // Fatal error message
  };
}

std::ostream& operator<<(std::ostream& os, udmx::utils::eLogLevel const& level);

#endif
