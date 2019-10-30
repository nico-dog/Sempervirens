//***************************************************
//
// Definition of LogSink object:
// A LogSink object is a generic object (wrapper) satisfying the concept of being 'loggable' (i.e. it can be logged into).
// Genericity is implemented with the runtime-concept idiom (from Sean Parent) which provides a concept-based
// runtime polymorphism.
// LogSink holds a shared_ptr to the underlying concept.
// The model implements the concept and holds the actual sink type.
// The model overrides the concept log method.

// 1) The log friend function takes a LogSink and log message data as argument
// 2) It calls the log_ method of the underlying model taking the log message data as argument
// 3) The latter calls a non-friend non-member function that takes the stored sink type as argument with the message data
// i.e. log(LogSink const&, msg) => model->log_(msg) => log(sink type, msg)
//
// Any sink type can be stored as a LogSink as long as we provide the corresponding free function.
// Sinking is be done with a call operator, so it is enough to provide a single generic free function for all sink types.
//
//***************************************************
#ifndef LOGSINK_HPP
#define LOGSINK_HPP
#include <utils/LogMsg.hpp>
#include <memory>
#include <fstream>

namespace dog::utils {

  class LogSink {

    struct concept_t {

      virtual ~concept_t() = default;
      virtual void _log(LogMsg::Meta const& meta, std::string const& msg) const = 0;
    };

    template <typename T>
    struct model_t final : public concept_t {
      
      model_t(T&& data);

      void _log(LogMsg::Meta const& meta, std::string const& msg) const override;

      T _data;
    };

    std::shared_ptr<concept_t const> _self;
    
  public:
    template<typename T>
    LogSink(T&& impl);

    friend void log(LogSink const& sink, LogMsg::Meta const&, std::string const& msg);
  };

  // Some helper functions to create common types of sinks
  LogSink makeConsoleSink();
  
  class FileSink {

  public:
    FileSink(std::string const& filename);
    ~FileSink() = default;
    FileSink(FileSink const&) = delete;
    FileSink& operator=(FileSink const&) = delete;
    FileSink(FileSink&&) noexcept = default;

    void operator()(LogMsg::Meta const& meta, std::string const& msg) const;

    std::unique_ptr<std::ofstream> _pFile;
  };
  
  LogSink makeFileSink(std::string const& filename);
}
#include <utils/LogSink.inl>
#endif
