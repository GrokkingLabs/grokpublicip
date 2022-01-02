#pragma once
#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP
///////////////////////////////////////////////////////////////////////////////
/// @file StringUtils.hpp
/// @author GrokkingLabs
/// @brief Various string utilities.
///////////////////////////////////////////////////////////////////////////////
#include <nlohmann/json.hpp>
#include <fmt/format.h>
#include <string>
#include <string_view>
#include <vector>

namespace grok {
using namespace std;
using namespace fmt;
using namespace nlohmann;
using json = nlohmann::json;
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
  /// @brief Converts any value to string
  /// @return Returns the string representation of the value
  /// @details This code is borrowed from the following
  /// @link https://www.cppstories.com/2018/07/string-view-perf-followup/
  /////////////////////////////////////////////////
  inline static vector<std::string_view>
  splitStringView(std::string_view strv, char delims = ' ') {
    vector<std::string_view> output;
    size_t first = 0;

    while (first < strv.size()) {
      const auto second = strv.find_first_of(delims, first);

      if (first != second)
        output.emplace_back(strv.substr(first, second - first));

      if (second == std::string_view::npos)
        break;

      first = second + 1;
    }

    return output;
  }

  /////////////////////////////////////////////////
  /// @fn objToJsonString
  /// @brief Converts the object to json string
  /// @return Returns the json string representation of the object
  /// @details For this to work the NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE or
  /// its variants should be defined
  /////////////////////////////////////////////////
  template<typename T>
  inline static string objToJsonString(T const& obj) {
    json j;
    nlohmann::to_json(j, obj);
    return j.dump();
  }
};
} // namespace grok
#endif // STRINGUTILS_HPP
