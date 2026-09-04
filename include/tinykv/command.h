#pragma once

#include <string>
#include <vector>

namespace tinykv {
struct Command {
  std::string name;
  std::vector<std::string> arguments;

  bool empty() const { return name.empty(); }
};
} // namespace tinykv
