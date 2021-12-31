#pragma once
#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP
///////////////////////////////////////////////////////////////////////////////
/// @file StringUtils.hpp
/// @author GrokkingLabs
/// @brief Various string utilities.
///////////////////////////////////////////////////////////////////////////////
#include <fmt/format.h>
#include <string>
#include <thread>
#include <sstream>

namespace grok {
using namespace std;
using namespace fmt;
/////////////////////////////////////////////////
/// @class StringUtils
/// @brief Class to contain all the string utility functions. Functions will be
/// static functions
/// @details Example usage:
///          StringUtils::threadIdToString
/////////////////////////////////////////////////
class StringUtils {
public:
  /////////////////////////////////////////////////
  /// @fn toString
  /// @brief Converts any value to string
  /// @return Returns the string representation of the value
  /////////////////////////////////////////////////
  template <typename T> inline static string toString(const T val) {
    return move(format("{}", val));
  }

  /////////////////////////////////////////////////
  /// @fn toString
  /// @brief Converts the thread ID to a string and returns it
  /// @return Returns the thread id as a string.
  /////////////////////////////////////////////////
  template <> inline static string toString(thread::id const&id) {
    stringstream ss;
    ss << id;
    return ss.str();
  }
};
} // namespace grok
#endif // STRINGUTILS_HPP
