//
// Created by mrbgn on 3/2/21.
//

#ifndef THREADING_LOGGER_HPP
#define THREADING_LOGGER_HPP

#include <nlohmann/json.hpp>
#include <iostream>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/expressions/keyword.hpp>


struct ToFile {
  std::string data;
  std::string hash;
  std::string time;
};


class Logger {
 public:
  Logger();
  Logger(std::string& fileName);
  void operator << (ToFile data);
  bool Matching(std::string hash);
  void Init();
  ~Logger();
 private:
  nlohmann::json _result;
  std::string _fileName;
};

#endif  // THREADING_LOGGER_HPP
