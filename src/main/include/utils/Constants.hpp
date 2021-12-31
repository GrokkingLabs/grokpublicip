#pragma once
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
///////////////////////////////////////////////////////////////////////////////
/// @file Constants.hpp
/// @author GrokkingLabs
/// @brief Class to store constants that can be used through out code.
///////////////////////////////////////////////////////////////////////////////
#include <string>

namespace grok {
struct Constants {
  static const std::string LOCATION;
  // HTTP CODES
  static const std::string HTTP_MOVED_PERMANENTLY;
  static const std::string HTTP_FOUND_MOVED_TEMPORARILY;
  static const std::string HTTP_OK;
  static const std::string HTTP_CREATED;
  static const std::string HTTP_NOT_FOUND;
  static const std::string HTTP_NOT_MODIFIED;
  static const std::string HTTP_NO_CONTENT;
  static const std::string HTTP_BAD_REQUEST;
  static const std::string HTTP_INTERNAL_SERVER_ERROR;
  static const std::string HTTP_NOT_IMPLEMENTED;
  // Configurations
  static const std::string TRUE;
  static const std::string FALSE;
  static const std::string FOUND;
  static const std::string NOT_FOUND;
  static const std::string EVENTING_ENABLED;
  static const std::string SHORTNING_ENABLED;
  static const std::string IN_MAINTENANCE;
  static const std::string METRICS_COLLECTION_ENABLED;
};
} // namespace grok
#endif // CONSTANTS_HPP
