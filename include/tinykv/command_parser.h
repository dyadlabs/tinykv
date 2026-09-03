#pragma once

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

namespace tinykv {
struct Command {
  std::string name;
  std::vector<std::string> arguments;

  bool empty() const { return name.empty(); }
};

class CommandParser {
public:
  Command parse(const std::string &input) const;

private:
  std::vector<std::string> tokenize(const std::string &input) const;
};
} // namespace tinykv
