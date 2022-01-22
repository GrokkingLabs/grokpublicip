#pragma once
#ifndef SINGLETON_HPP
#define SINGLETON_HPP
#include <boost/noncopyable.hpp>
///////////////////////////////////////////////////////////////////////////////
/// @file Singleton.hpp
/// @author GrokkingLabs
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
template <class T> class Singleton : public boost::noncopyable {
public:
  static T &i() {
    static T _me;
    return _me;
  }
};
} // namespace grok
#endif // SINGLETON_HPP
