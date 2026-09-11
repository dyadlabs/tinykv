#pragma once

#include <stdexcept>
#include <string>

namespace tinykv {

class TinyKVError : public std::runtime_error {
public:
  explicit TinyKVError(const std::string &message)
      : std::runtime_error(message) {}
};

class ParseError : public TinyKVError {
public:
  using TinyKVError::TinyKVError;
};

class UnknownCommand : public TinyKVError {
public:
  using TinyKVError::TinyKVError;
};

class InvalidArguments : public TinyKVError {
public:
  using TinyKVError::TinyKVError;
};

class InvalidKey : public TinyKVError {
public:
  using TinyKVError::TinyKVError;
};
} // namespace tinykv
