#include "tinykv/command_parser.h"

namespace tinykv {

Command CommandParser::parse(const std::string &input) const {
  auto tokens = tokenize(input);
  Command command;
  if (tokens.empty()) {
    return command;
  }

  command.name = tokens.front();

  command.arguments.assign(tokens.begin() + 1, tokens.end());
  return command;
}

std::vector<std::string>
CommandParser::tokenize(const std::string &input) const {
  std::vector<std::string> tokens;
  std::string current;
  bool in_quotes = false;

  for (char ch : input) {
    if (ch == '"') {
      in_quotes = !in_quotes;
    }

    if (std::isspace(static_cast<unsigned char>(ch)) && !in_quotes) {
      if (!current.empty()) {
        tokens.push_back(current);
        current.clear();
      }
      continue;
    }

    current += ch;
  }

  if (!current.empty()) {
    tokens.push_back(current);
  }
  return tokens;
}
} // namespace tinykv
