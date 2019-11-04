#ifndef LOGSINK_INL
#define LOGSINK_INL

namespace dog::utilities::logging {

  template <typename T>
  void log(T const& sink, LogMsg::Meta const& meta, std::string const& msg) {

    sink(meta, msg);
  }

  template <typename T>
  LogSink::model_t<T>::model_t(T&& data) : _data{std::forward<T>(data)} {}
  
  template <typename T>
  void LogSink::model_t<T>::_log(LogMsg::Meta const& meta, std::string const& msg) const {

    log(_data, meta, msg);
  }

  template <typename T>
  LogSink::LogSink(T&& impl) : _self(std::make_shared<model_t<T>>(std::forward<T>(impl))) {}
}
#endif
