#ifndef LOGMSG_INL
#define LOGMSG_INL

namespace udmx::utils {
  
  template<typename T>
  LogMsg& LogMsg::operator<<(T value)
  {
    _buffer << value;
    return *this;
  }
}
#endif
