#pragma once
#ifndef LOGGER_HPP
#define LOGGER_HPP
///////////////////////////////////////////////////////////////////////////////
/// @file Logger.hpp
/// @author GrokkingLabs
/// @brief Helper class for creating a logger.
///////////////////////////////////////////////////////////////////////////////
#include <boost/preprocessor/control/expr_iif.hpp>
#include <spdlog/async.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
namespace grok {
/////////////////////////////////////////////////
/// @fn l
/// @brief Returns the log
///        This will be logging to the logs. It uses spdlog to log to file
/// @return Returns the log.
/////////////////////////////////////////////////
inline static spdlog::logger &l() {
  static const std::size_t q_size = 1048576; // queue size must be power of 2
  static auto ret = spdlog::daily_logger_mt("url_shortner", "query_log.log");
  static bool initialized = false;
  if (!initialized) {
    spdlog::set_pattern("***[%l] [%H:%M:%S %z] [thread %t] %v ***");
    initialized = true;
  }

  return *ret;
}

/////////////////////////////////////////////////
/// @fn col
/// @brief Returns the color log
///        This will be logging to the logs. It uses spdlog to log to file
/// @return Returns the log.
/////////////////////////////////////////////////
inline static spdlog::logger &col() {
  // create color multi threaded log
  static auto console =
      spdlog::stdout_color_mt<spdlog::async_factory>("console");
  static auto err_logger =
      spdlog::stderr_color_mt<spdlog::async_factory>("stderr");
  return *spdlog::get("console");
}
#define glog grok::col()
#define GROK_DBG 1
//#define DEBUG_LOG(...) BOOST_PP_EXPR_IIF(GROK_DBG, grok::col().info(__VA_ARGS__))
//#define INFO_LOG(...) BOOST_PP_EXPR_IIF(GROK_DBG, grok::col().info(__VA_ARGS__))
} // namespace grok

#endif // LOGGER_HPP
