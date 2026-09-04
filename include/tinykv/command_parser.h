#pragma once

#include "command.h"

#include <cctype>
#include <sstream>

namespace tinykv {
class CommandParser {
public:
  Command parse(const std::string &input) const;

private:
  std::vector<std::string> tokenize(const std::string &input) const;
};
} // namespace tinykv
