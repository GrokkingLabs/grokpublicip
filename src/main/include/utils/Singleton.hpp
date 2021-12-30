#pragma once
#ifndef SINGLETON_HPP
#define SINGLETON_HPP
#include "NonCopyable.hpp"
///////////////////////////////////////////////////////////////////////////////
/// @file Singleton.hpp
/// @author GrokkingLabs
/// @version 0.1
/// @brief Helper class for creating a non copyable Singleton.
///////////////////////////////////////////////////////////////////////////////
namespace grok {
/////////////////////////////////////////////////
/// @class Singleton
/// @brief Helper class to create a singleton.
/// @details Example usage:
///          struct MakeMeSingleton : public ::grok::Singleton<MakeMeSingleton>
///          {};
/////////////////////////////////////////////////
template<class T>
class Singleton : public NonCopyable {
 public:
  static T &i() {
    static T _me;
    return _me;
  }
};
}
#endif // SINGLETON_HPP
