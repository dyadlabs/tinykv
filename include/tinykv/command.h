#pragma once

#include <ostream>
#include <string>
#include <vector>

namespace tinykv {
struct Command {
  std::string name;
  std::vector<std::string> arguments;

  bool empty() const { return name.empty(); }

  friend bool operator==(const Command &lhs, const Command &rhs) {
    return lhs.name == rhs.name && lhs.arguments == rhs.arguments;
  }

  friend std::ostream &operator<<(std::ostream &os, const Command &c) {
    os << "{ ";
    os << "Name: " << c.name << ", Arguments: ";
    os << "[ ";
    for (const auto &val : c.arguments) {
      os << val << " ";
    }
    os << "]";
    os << " }";
    return os;
  }
};
} // namespace tinykv
