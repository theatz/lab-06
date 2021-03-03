//
// Created by mrbgn on 3/2/21.
//
#include "Logger.hpp"

#include <fstream>
namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

void Logger::operator << (ToFile data) {
    if (Matching(data.hash)) {
      std::cout << data.hash << std::endl;
      auto js = nlohmann::json::object();
      js["data"] = data.data;
      js["hash"] = data.hash;
      js["time"] = data.time;
      _result.push_back(js);
    }
}
Logger::Logger() {
  _result.clear();
}

Logger::Logger(std::string& fileName) : _fileName(fileName) {
  _result.clear();
}

Logger::~Logger() {
  if (!_fileName.empty())
  {
    std::ofstream file(_fileName + ".json");
    if (file.is_open()) {
      file << _result.dump(4);
      _result.clear();
      file.close();
    }
  }
}
bool Logger::Matching(std::string hash) {
  const std::string expected = "0000";
  return hash.substr(hash.size() - expected.size()) == expected;
}
void Logger::Init() {
  const std::string format = "%TimeStamp% <%Severity%> (%ThreadID%): %Message%";
  logging::add_console_log(std::cout,
                           keywords::format = "[%TimeStamp%] [%Severity%] %Message%",
                           keywords::auto_flush = true,
                           keywords::filter = logging::trivial::severity
                                              == logging::trivial::info);

  typedef sinks::synchronous_sink<sinks::text_file_backend> file_sink;
  boost::shared_ptr<file_sink> sink(new file_sink(
      keywords::file_name = "./logs/file_%5N.log",
      keywords::rotation_size = 5 * 1024 * 1024,
      keywords::auto_flush = true));

  sink->set_formatter(expr::stream
                          << "["
                          << expr::attr<boost::posix_time::ptime>("TimeStamp")
                          << "] [" << logging::trivial::severity << "] "
                          << expr::smessage);

  logging::core::get()->add_sink(sink);
  logging::add_common_attributes();
}
