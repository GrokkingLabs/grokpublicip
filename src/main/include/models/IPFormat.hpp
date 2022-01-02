#pragma once
#ifndef IPFORMAT_HPP
#define IPFORMAT_HPP
#include <nlohmann/json.hpp>
#include <string>
namespace grok {
using namespace std;
struct IPFormat {
  string ip;
  IPFormat() = default;
  IPFormat(string const& ip) {
    this->ip = ip;
  }
};
// Now it implements the to_json and from_json functions to convert it to and
// from json
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IPFormat, ip);
}
#endif // IPFORMAT_HPP
