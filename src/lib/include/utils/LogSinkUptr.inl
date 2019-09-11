#ifndef LOGSINKUPTR_INL
#define LOGSINKUPTR_INL

namespace dog::utils {

  // Generic non-friend non-member log function
  template <typename T>
  void log(T const& sink, LogMsg::Meta const& meta, std::string const& msg) {

    sink(meta, msg);
  }

  // model
  template <typename T>
  LogSinkUptr::model_t<T>::model_t(T data) : _data{std::move(data)} {}

  template <typename T>
  std::unique_ptr<concept_t> LogSinkUptr::model_t<T>::copy_() const {

    return std::make_unique<model_t<T>>(*this);
  }
  
  template <typename T>
  void LogSinkUptr::model_t<T>::log_(LogMsg::Meta const& meta, std::string const& msg) const {

    log(_data, meta, msg);
  }

  // wrapper
  template <typename T>
  LogSink::LogSinkUptr(T impl) : _self(std::make_unique<model_t<T>>(std::move(impl))) {}
}
#endif