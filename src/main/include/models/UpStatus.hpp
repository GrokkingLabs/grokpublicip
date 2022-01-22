#pragma once
#ifndef UPSTATUS_HPP
#define UPSTATUS_HPP
///////////////////////////////////////////////////////////////////////////////
/// @file UpStatus.hpp
/// @author GrokkingLabs
/// @brief Status of the application. This object can be converted to json and
/// sent
///////////////////////////////////////////////////////////////////////////////
#include <nlohmann/json.hpp>
#include <string>
#include "utils/Constants.hpp"
namespace grok {
using namespace std;
using namespace nlohmann;
/////////////////////////////////////////////////
/// @class UpStatus
/// @brief This class models a status update of the server .
/////////////////////////////////////////////////
struct UpStatus {
  string status = Constants::UP;
  UpStatus() = default;
  bool up() const {
    return status == Constants::UP;
  }
};
// Now it implements the to_json and from_json functions to convert it to and
// from json
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(UpStatus, status);
}
#endif // UPSTATUS_HPP
