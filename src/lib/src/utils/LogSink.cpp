#define LOGSINK_CPP
#include <utils/LogSink.hpp>
#include <utils/LogMsg.hpp>
#include <utils/Logger.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace dog::utils {

  void log(LogSink const& sink, LogMsg::Meta const& meta, std::string const& msg) {

    sink._self->log_(meta, msg);
  }

  LogSink makeConsoleSink() {
    
    return [](LogMsg::Meta const& meta, std::string const& msg){
      std::cout << meta._level
		<< "("
		<< meta._func << " / " << meta._file << ": l." << meta._line
		<< "): " 
		<< msg << '\n'; };
  }

  FileSink::FileSink(std::string const& filename) : _pFile{std::make_unique<std::ofstream>(filename)} {
    if (!_pFile->good())
      gLogError << "Failed to open file: " << filename;
  }

  void FileSink::operator()(LogMsg::Meta const& meta, std::string const& msg) const {

    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto localTime = std::localtime(&time_t);
    
    *_pFile << std::put_time(localTime, "[%H:%M:%S]")
	    << meta._level
	    << msg
	    << " ("
	    << meta._func << " / " << meta._file << ": l." << meta._line
	    << ")\n";
  }
  
  LogSink makeFileSink(std::string const& filename) {
    
    return FileSink(filename);
  }
}
