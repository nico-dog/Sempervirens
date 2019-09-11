#ifndef LOGSINK_INL
#define LOGSINK_INL

namespace dog::utils {

  // Generic non-friend non-member log function
  template <typename T>
  void log(T const& sink, LogMsg::Meta const& meta, std::string const& msg) {

    sink(meta, msg);
  }

  // model
  template <typename T>
  LogSink::model_t<T>::model_t(T data) : _data{std::move(data)} {}
  
  template <typename T>
  void LogSink::model_t<T>::log_(LogMsg::Meta const& meta, std::string const& msg) const {

    log(_data, meta, msg);
  }

  // wrapper
  template <typename T>
  LogSink::LogSink(T impl) : _self(std::make_shared<model_t<T>>(std::move(impl))) {}
}
#endif
