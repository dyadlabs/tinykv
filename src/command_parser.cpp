#include "tinykv/command_parser.h"
#include "tinykv/error.h"
#include <cctype>

namespace tinykv {

Command CommandParser::parse(const std::string &input) {
  auto tokens = tokenize(input);
  Command command;
  if (tokens.empty()) {
    return command;
  }

  command.name = tokens.front();

  if (tokens.size() > 1) {
    command.arguments.assign(tokens.begin() + 1, tokens.end());
  }
  return command;
}

std::vector<std::string> CommandParser::tokenize(const std::string &input) {
  std::vector<std::string> tokens;
  std::string current;
  bool in_quotes = false;
  bool token_started = false;

  for (char ch : input) {
    if (!token_started && !std::isspace(static_cast<unsigned char>(ch))) {
      token_started = true;
      if (ch == '"') {
        in_quotes = true;
        continue;
      }
      current += ch;
      continue;
    }

    if (token_started) {
      if ((std::isspace(static_cast<unsigned char>(ch)) && !in_quotes)) {
        tokens.push_back(current);
        current.clear();
        token_started = false;
        continue;
      }
      if (ch == '"') {
        tokens.push_back(current);
        current.clear();
        if (in_quotes) {
          token_started = false;
          in_quotes = false;
          continue;
        }
        in_quotes = true;
        continue;
      }
      current += ch;
    }
  }

  if (in_quotes) {
    throw ParseError("Incomplete quotes.");
  }

  if (token_started) {
    tokens.push_back(current);
  }
  return tokens;
}
} // namespace tinykv
