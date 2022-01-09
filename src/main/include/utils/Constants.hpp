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
using namespace std;
struct Constants {
  static const string LOCATION;
  // HTTP CODES
  static const string HTTP_MOVED_PERMANENTLY;
  static const string HTTP_FOUND_MOVED_TEMPORARILY;
  static const string HTTP_OK;
  static const string HTTP_CREATED;
  static const string HTTP_NOT_FOUND;
  static const string HTTP_NOT_MODIFIED;
  static const string HTTP_NO_CONTENT;
  static const string HTTP_BAD_REQUEST;
  static const string HTTP_INTERNAL_SERVER_ERROR;
  static const string HTTP_NOT_IMPLEMENTED;
  // HTTP Content Types
  static inline const string CONTENT_TYPE = "Content-Type";
  static inline const string CONTENT_TYPE_JSON = "application/json";
  static inline const string CONTENT_TYPE_TEXT = "text/plain";
  // HTTP Header Values
  static inline const string X_FORWARDED_FOR = "x-forwarded-for";
  static inline const string ORIGIN = "origin";
  static inline const char X_FORWARDED_FOR_IP_SEPARATOR = ',';
  // Query Parameters
  static inline const string FORMAT = "format";
  static inline const string JSON_FORMAT = "json";
  // Configurations
  static const string TRUE;
  static const string FALSE;
  static const string FOUND;
  static const string NOT_FOUND;
  static const string EVENTING_ENABLED;
  static const string SHORTNING_ENABLED;
  static const string IN_MAINTENANCE;
  static const string METRICS_COLLECTION_ENABLED;
  // Application status
  static inline const string UP = "UP";
  static inline const string DOWN = "DOWN";
  // Others
  static inline const string NA = "NA";
  static inline int const DEFAULT_NUMBER_OF_THREADS = 2;
};
} // namespace grok
#endif // CONSTANTS_HPP
