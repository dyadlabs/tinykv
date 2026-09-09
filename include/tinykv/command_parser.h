#pragma once

#include "command.h"

#include <cctype>
#include <sstream>

namespace tinykv {
class CommandParser {
public:
  static Command parse(const std::string &input);

private:
  static std::vector<std::string> tokenize(const std::string &input);
};
} // namespace tinykv
