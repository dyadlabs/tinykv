#pragma once

#include <optional>
#include <string>
#include <variant>
namespace tinykv {
struct PutResult {
  std::string key;
  std::string value;
  std::optional<std::string> original_value;
};
struct GetResult {
  std::string key;
  std::optional<std::string> value;
};
struct RemoveResult {
  bool success;
  std::string key;
};
struct ExistsResult {
  bool exists;
  std::string key;
};

using ExecutionResult =
    std::variant<PutResult, GetResult, RemoveResult, ExistsResult>;
} // namespace tinykv
