#pragma once

#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

namespace tinykv {

class KVStore {
public:
  bool put(const std::string &key, const std::string &value);
  std::optional<std::string> get(std::string_view key) const;
  bool remove(std::string_view key);
  bool exists(std::string_view key) const;

private:
  std::unordered_map<std::string, std::string> data_;
};

} // namespace tinykv
