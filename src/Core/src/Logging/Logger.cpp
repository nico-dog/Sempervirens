#define LOGGER_CPP
#include <Logging/Logger.hpp>

namespace sempervirens::core::log {

  Logger* Logger::_head = nullptr;
  Logger* Logger::_tail = nullptr;
  std::mutex Logger::_mutex{};

  void Logger::addToList(Logger* logger)
  {
    std::lock_guard<std::mutex> lock(Logger::_mutex);
    
    if (!Logger::_head)
    {
      Logger::_head = logger;
      Logger::_tail = logger;
      logger->_prev = nullptr;
      logger->_next = nullptr;
    }
    else
    {
      Logger::_tail->_next = logger;
      logger->_prev = Logger::_tail;
      logger->_next = nullptr;
      Logger::_tail = logger;
    }         
  }

  void Logger::removeFromList(Logger* logger)
  {
    std::lock_guard<std::mutex> lock(Logger::_mutex);
    
    if (logger == Logger::_head)
    {
      if (logger == Logger::_tail)
      {
	Logger::_head = nullptr;
	Logger::_tail = nullptr;
      }
      else
      {
	Logger::_head = logger->_next;
	Logger::_head->_prev = nullptr;
      }  
      return;
    }

    if (logger == Logger::_tail)
    {
      Logger::_tail = logger->_prev;
      Logger::_tail->_next = nullptr;
      return;
    }

    auto curr = Logger::_head->_next;
    do
    {
      if (curr == logger)
      {
	auto prev = curr->_prev;
	auto next = curr->_next;	
	prev->_next = next;
	next->_prev = prev;
	break;
      }
      curr = curr->_next;
    }
    while (curr != Logger::_tail);
  }
}

std::ostream& operator<<(std::ostream& os, sempervirens::core::log::LogSeverity const& severity)
{
  using namespace sempervirens::core::log;
  switch(severity)
  {   
    case LogSeverity::MSG: os << "> [MSG]"; break;
    case LogSeverity::WRN: os << "> [WRN]"; break;
    case LogSeverity::ERR: os << "> [ERR]"; break;
    case LogSeverity::FAT: os << "> [FAT]"; break;
    default: os << "> undefined log severity";
  } 
  return os;
}  
