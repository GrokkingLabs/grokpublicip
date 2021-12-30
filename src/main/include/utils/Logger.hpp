#pragma once
#ifndef LOGGER_HPP
#define LOGGER_HPP
///////////////////////////////////////////////////////////////////////////////
/// @file Logger.hpp
/// @author GrokkingLabs
/// @version 0.1
/// @brief Helper class for creating a logger.
///////////////////////////////////////////////////////////////////////////////
#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/async.h>
#include <boost/preprocessor/control/expr_iif.hpp>
namespace grok {
/////////////////////////////////////////////////
/// @fn l
/// @brief Returns the log
///        This will be logging to the logs. It uses spdlog to log to file
/// @return Returns the log.
/////////////////////////////////////////////////
inline spdlog::logger &l() {
  static const std::size_t q_size = 1048576; //queue size must be power of 2
  static auto ret = spdlog::daily_logger_mt("url_shortner",
                                            "query_log.log");
  static bool initialized = false;
  if (!initialized) {
    spdlog::set_pattern("***[%l] [%H:%M:%S %z] [thread %t] %v ***");
    initialized = true;
  }

  return *ret;
}

inline spdlog::logger &cl() {
  // create color multi threaded log
  static auto console = spdlog::stdout_color_mt<spdlog::async_factory>("console");
  static auto err_logger = spdlog::stderr_color_mt<spdlog::async_factory>("stderr");
  return *spdlog::get("console");
}
#define gklog grok::cl()
#define GROK_DBG 1
#define DEBUG_LOG(...) BOOST_PP_EXPR_IIF(GROK_DBG, grok::cl().info(__VA_ARGS__))
#define INFO_LOG(...) BOOST_PP_EXPR_IIF(GROK_DBG, grok::cl().info(__VA_ARGS__))
}

#endif // LOGGER_HPP
