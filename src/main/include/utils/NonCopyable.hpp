#pragma once
#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP
///////////////////////////////////////////////////////////////////////////////
/// @file NonCopyable.hpp
/// @author GrokkingLabs
/// @version 0.1
/// @brief Helper class for creating a non copyable class.
///////////////////////////////////////////////////////////////////////////////
namespace grok {
/////////////////////////////////////////////////
/// @class NonCopyable
/// @brief Helper class to create a NonCopyable object
/// @details Example usage:
///          struct MakeMeNonCopyable : public ::grok::NonCopyable
///          {};
/////////////////////////////////////////////////
class NonCopyable {
 public:
  NonCopyable(const NonCopyable &) = delete;

  NonCopyable &operator=(const NonCopyable &) = delete;
};
}
#endif // NONCOPYABLE_HPP
