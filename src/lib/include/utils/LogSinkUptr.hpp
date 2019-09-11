//***************************************************
//
// Definition of LogSink object:
// A LogSink object is a generic object (wrapper) satisfying the concept of being 'loggable' (i.e. it can be logged into).
// Genericity is implemented with the runtime-concept idiom (from Sean Parent) which provides a concept-based
// runtime polymorphism.
// LogSink holds a shared_ptr to the underlying concept.
// The model implements the concept and holds the actual sink type.
// The model derives overrides the concept log method.

// 1) The log friend function takes a LogSink and log message data as argument
// 2) It calls the log_ method of the underlying model taking the log message data as argument
// 3) The latter calls a non-friend non-member function that takes the stored sink type as argument with the message data
// i.e. log(LogSink const&, msg) => model->log_(msg) => log(sink type, msg)
//
// Any sink type can be stored as a LogSink as long as we provide the corresponding free function.
// Sinking should be done with a call operator, so it is enough to provide a single generic free function for all sink types.
//
// N.B.: this is the original implementation using a unique_ptr instead of shared_ptr
//
//***************************************************
#ifndef LOGSINKUPTR_HPP
#define LOGSINKUPTR_HPP
#include <utils/LogMsg.hpp>
#include <memory>
#include <fstream>

namespace dog::utils {

  class LogSinkUptr {

    struct concept_t {

      virtual ~concept_t() = default;
      virtual std::unique_ptr<concept_t> copy_() const = 0;
      virtual void log_(LogMsg::Meta const& meta, std::string const& msg) const = 0;
    };

    template <typename T>
    struct model_t final : public concept_t {
      
      model_t(T data);

      std::unique_ptr<concept_t> copy_() const override
      {
        return std::make_unique<model_t<T>>(*this);
      }
      
      void log_(LogMsg::Meta const& meta, std::string const& msg) const override;

      T _data;
    };

    std::unique_ptr<concept_t> _self;
    
  public:
    template<typename T>
    LogSinkUptr(T impl);
    
    LogSinkUptr(LogSink const&);
    LogSinkUptr(LogSinkUptr&&) noexcept = default;
    LogSinkUptr& operator=(LogSinkUptr const& logSinkUptr)
    {
      return *this = LogSinkUptr(logSinkUptr);
    }
    LogSinkUptr& operator=(LogSinkUptr&&) noexcept = default;

    friend void log(LogSinkUptr const& sink, LogMsg::Meta const&, std::string const& msg);
  };

  // Some helper functions to create common type of sinks
  LogSinkUptr makeConsoleSink();
  
  class FileSink {

  public:
    FileSink(std::string const& filename);

    void operator()(LogMsg::Meta const& meta, std::string const& msg) const;

    std::unique_ptr<std::ofstream> _pFile;
  };
  
  LogSinkUptr makeFileSink(std::string const& filename);
}
#include <utils/LogSinkUptr.inl>
#endif
