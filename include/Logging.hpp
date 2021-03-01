//
// Created by mrbgn on 2/24/21.
//
#ifndef THREADING_LOGGING_HPP
#define THREADING_LOGGING_HPP

#include "boost/log/trivial.hpp"
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/console.hpp>

namespace logging = boost::log;

/*
void inition()
{
  const std::string format = "%TimeStamp% <%Severity%> (%ThreadID%): %Message%";

  auto sink_to_file_trace = logging::add_file_log(
      logging::keywords::file_name = "..logs/trace/log_trace_%N.log",
      logging::keywords::rotation_size = 10 * 1024 * 1024,
      logging::keywords::format = format);
  sink_to_file_trace->set_filter(
      logging::trivial::severity == boost::log::trivial::trace);
  auto sink_to_file_info = logging::add_file_log(
      logging::keywords::file_name = "..logs/info/log_info_%N.log",
      logging::keywords::rotation_size = 10 * 1024 * 1024,
      logging::keywords::format = format);
  sink_to_file_info->set_filter(
      logging::trivial::severity == logging::trivial::info);

  auto sink_to_console = logging::add_console_log(
      std::cout,
      logging::keywords::format = format);
  sink_to_console->set_filter(
      logging::trivial::severity == logging::trivial::info);

  logging::add_common_attributes();
}
*/
#endif  // THREADING_LOGGING_HPP
