#pragma once

#include <optional>
#include <string>
#include <unordered_map>

namespace tinykv {

class KVStore {
public:
  bool put(const std::string &key, const std::string &value);
  std::optional<std::string> get(const std::string &key) const;
  bool remove(const std::string &key);
  bool exists(const std::string &key) const;

private:
  std::unordered_map<std::string, std::string> data_;

  friend bool operator==(const KVStore &lhs, const KVStore &rhs) {
    return lhs.data_ == rhs.data_;
  }
};

} // namespace tinykv
