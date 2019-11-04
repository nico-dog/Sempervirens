#define LOGSINK_CPP
#include <Logging/LogSink.hpp>
#include <Logging/LogMsg.hpp>
#include <Logging/Logger.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace dog::utilities::logging {

  void log(LogSink const& sink, LogMsg::Meta const& meta, std::string const& msg) {

    sink._self->_log(meta, msg);
  }

  LogSink makeConsoleSink() {
    
    return [](LogMsg::Meta const& meta, std::string const& msg){
      std::cout << meta._level
		<< " ("
		<< meta._file << "): " 
		<< msg << '\n'; };
  }

  FileSink::FileSink(std::string const& filename) : _pFile{std::make_unique<std::ofstream>(filename)} {
    if (!_pFile->good())
      DOG_LOGERR("Failed to open file: " << filename);
  }

  void FileSink::operator()(LogMsg::Meta const& meta, std::string const& msg) const {

    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto localTime = std::localtime(&time_t);
    
    *_pFile << meta._level << ' ' 
	    << std::put_time(localTime, "[%H:%M:%S]") 
	    << " ("
	    << meta._file << ": " << meta._func << ", l." << meta._line
	    << "): "
	    << msg << '\n';
  }
  
  LogSink makeFileSink(std::string const& filename) {
    
    return FileSink(filename);
  }
}
